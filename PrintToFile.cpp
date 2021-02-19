// Stefan Marinkov
// 12.06.2020.
#include "PrintToFile.h"

#include "Functions.h"
#include <fstream>

PrintToFile::PrintToFile(Variables& v, MemoryDirectives& m, LabelDirectives& l, FunctionDirectives& f, Instructions& i) 
	: m_registers(v),
	m_memory(m),
	m_labels(l),
	m_functions(f),
	m_instructions(i) {}

void PrintToFile::Do()
{
	std::ofstream file;
	file.open("out.s", std::ios::out);

	if (file.is_open())
	{
		printGlobl(file);
		printData(file);
		printText(file);
	}
	else
		printError();

	file.close();
}

void PrintToFile::printError()
{
	std::cout << "Error! Unable to open file." << std::endl;
	throw std::runtime_error("");
}

void PrintToFile::printGlobl(std::ofstream& file)
{
	for (std::shared_ptr<FunctionDirective> f : m_functions)
	{
		file << ".globl " << f->getName() << std::endl;
	}
	file << std::endl;
}

void PrintToFile::printData(std::ofstream& file)
{
	file << ".data" << std::endl;
	for (std::shared_ptr<MemoryDirective> m : m_memory)
	{
		file << m->getName() << ":\t\t\t.word " << m->getValue() << std::endl;
	}
}

void PrintToFile::printText(std::ofstream& file)
{
	file << std::endl;
	file << ".text" << std::endl;
	bool first = true;
	for (int i = 0; i < m_instructions.size(); ++i)
	{
		printFunction(file, i, first);
		printLabel(file, i);
		printInstruction(file, i);
	}
	file << "\t\tjr  \t\t$ra";
}

void PrintToFile::printLabel(std::ofstream& file, int i)
{
	for (std::shared_ptr<LabelDirective> l : m_labels)
	{
			if (l->getValue() == i)
			file << l->getName() << ":" << std::endl;
	}
}

void PrintToFile::printFunction(std::ofstream& file, int i, bool& first)
{
	for(std::shared_ptr<FunctionDirective> f : m_functions)
	{
		if (f->getValue() == i)
		{
			if (!first)
				file << "\t\tjr   \t\t$ra" << std::endl;
			file << f->getName() << ":" << std::endl;
		}
		first = false;
	}
}

void PrintToFile::printInstruction(std::ofstream& file, int i)
{
	
	std::string form = m_instructions[i]->getForm();
	int pos;

	if (m_instructions[i]->getType() == I_JAL)
	{
		file << std::endl;
		file << "\t\taddi\t\t$sp,$sp,-4" << std::endl;
		file << "\t\tsw  \t\t$ra,($sp)" << std::endl;
		file << std::endl;
	}

	for (std::shared_ptr<Variable> d : m_instructions[i]->getDst())
	{
		pos = form.find("`d");
		if (pos != std::string::npos)
		{
			form.erase(pos, 2);
			if (d->getType() == Variable::MEM_VAR)
				form.insert(pos, d->getName());
			else
				form.insert(pos, RegsToString(d->getAssignment()));
		}

	}

	for (std::shared_ptr<Variable> s : m_instructions[i]->getSrc())
	{
		pos = form.find("`s");
		if (pos != std::string::npos)
		{
			form.erase(pos, 2);
			if (s->getType() == Variable::MEM_VAR)
				form.insert(pos, s->getName());
			else
				form.insert(pos, RegsToString(s->getAssignment()));
		}

	}

	pos = form.find("`c");
	if (pos != std::string::npos)
	{
		form.erase(pos, 2);
		form.insert(pos, std::to_string(m_instructions[i]->getConstant()));
	}
		

	for (std::shared_ptr<LabelDirective> l : m_labels)
	{
		pos = form.find("`l");
		if (pos != std::string::npos)
		{
			if (l->getValue() == m_instructions[i]->getConstant())
			{
				form.erase(pos, 2);
				form.insert(pos, l->getName());
			}
		}
	}

	for (std::shared_ptr<FunctionDirective> f : m_functions)
	{
		pos = form.find("`l");
		if (pos != std::string::npos)
		{
			if (f->getValue() == m_instructions[i]->getConstant())
			{
				form.erase(pos, 2);
				form.insert(pos, f->getName());
			}
		}
	}

	file << "\t\t" + form << std::endl;

	if (m_instructions[i]->getType() == I_JAL)
	{
		file << std::endl;
		file << "\t\tlw  \t\t$ra,($sp)" << std::endl;
		file << "\t\taddi \t\t$sp,$sp,4" << std::endl;
		file << std::endl;
	}


}
