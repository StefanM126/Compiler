// Autor: Stefan Marinkov
// Datum: 01.06.2020.

#include "LivenessAnalysis.h"
#include "Functions.h"


LivenessAnalysis::LivenessAnalysis(Instructions & instr, Variables& variables) : m_interferenceGraph(variables)
{
	m_instructions = instr;
}

Instructions& LivenessAnalysis::getInstructions()
{
	return m_instructions;
}

void LivenessAnalysis::fillInAndOut()
{
	bool flag = false;
	Variables inPrime;
	Variables outPrime;
	Instructions::reverse_iterator rIt;
	while (!flag)
	{
		flag = true;
		for (rIt = m_instructions.rbegin(); rIt != m_instructions.rend(); ++rIt)
		{
			inPrime = (*rIt)->getIn();
			outPrime = (*rIt)->getOut();
			refreshOut(rIt);
			refreshIn(rIt);
			

			if ((*rIt)->getIn() != inPrime || (*rIt)->getOut() != outPrime)
			{
				flag = false;						// ukoliko se bar jedan skup razlikuje potrebno je izvršiti bar još jednu iteraciju
			}

		}
	}
}

void LivenessAnalysis::refreshIn(Instructions::reverse_iterator& rIt)
{
	Variables in;

	for (std::shared_ptr<Variable> varUse : (*rIt)->getUse())
	{
		in.push_back(varUse);
	}

	for (std::shared_ptr<Variable> varOut : (*rIt)->getOut())
	{
		in.push_back(varOut);
		for (std::shared_ptr<Variable> varDef : (*rIt)->getDef()) // svaki put prolazi kroz def skup i ako se promenljive iz out i def poklope
		{														  // promenjiva se izacuje iz liste
			if (varOut->getName() == varDef->getName())
			{
				in.pop_back();
			}
		}
	}

	in.sort(sortPred);
	in.unique(pred);
	(*rIt)->setIn(in);

}

void LivenessAnalysis::refreshOut(Instructions::reverse_iterator& rIt)
{
	Variables out;
	
	for (std::shared_ptr<Instruction> instruction : (*rIt)->getSucc()) // out je unija in skupova skih sledbenika
	{	
		for (std::shared_ptr<Variable> varIn : instruction->getIn())
		{
			out.push_back(varIn);
		}
	}

	out.sort(sortPred);
	out.unique(pred);
	(*rIt)->setOut(out);
}

void LivenessAnalysis::fillUse(int i)
{
	Variables& src = m_instructions[i]->getSrc();
	Variables v;

	for (std::shared_ptr<Variable> var : src)
	{
		if (var->getType() == Variable::REG_VAR)
		{
			v.push_back(var);
		}
	}
	m_instructions[i]->setUse(v);
}

void LivenessAnalysis::fillDef(int i)
{
	Variables& dst = m_instructions[i]->getDst();
	Variables v;

	for (std::shared_ptr<Variable> var : dst)
	{
		if (var->getType() == Variable::REG_VAR)
		{
			v.push_back(var);
		}
	}
	m_instructions[i]->setDef(v);
}

void LivenessAnalysis::fillSucc(int i)
{
	Instructions instructions;

	if (m_instructions[i]->getType() == I_B || m_instructions[i]->getType() == I_JAL)
	{
		instructions.push_back(m_instructions[m_instructions[i]->getConstant()]); // Sledenik joj je instrukcija na koju će skočiti
		m_instructions[i]->setSucc(instructions);
		instructions.clear();
	}
	else if (m_instructions[i]->getType() == I_BEQ || m_instructions[i]->getType() == I_BLTZ)
	{
		instructions.push_back(m_instructions[i + 1]);
		instructions.push_back(m_instructions[m_instructions[i]->getConstant()]);
		m_instructions[i]->setSucc(instructions);
		instructions.clear();
	}
	else
	{
		instructions.push_back(m_instructions[i + 1]);
		m_instructions[i]->setSucc(instructions);
		instructions.clear();
	}
}

void LivenessAnalysis::fillPred(int i)
{
	Instructions instructions;
	Instructions succ;

	succ = m_instructions[i]->getSucc();

	for (std::shared_ptr<Instruction> instr : succ)
	{
		instructions = instr->getPred(); // uzimam sve prethodnike iz liste sledbenika
		instructions.push_back(m_instructions[i]); // dodajem trenutnu instrukciju
		instr->setPred(instructions); // vraćam izmenjenu listu prethodnika
		instructions.clear();
	}
}

void LivenessAnalysis::makeInterferenceGraph()
{
	for (std::shared_ptr<Instruction> instr : m_instructions)
	{
		for (std::shared_ptr<Variable> varDef : instr->getDef())
		{
			for (std::shared_ptr<Variable> varOut : instr->getOut())
			{
				if (varDef->getPosition() != varOut->getPosition())
				{
					m_interferenceGraph.setInterference(varDef->getPosition(), varOut->getPosition());
				}
			}
		}
	}
}


void LivenessAnalysis::Do()
{
	for (int i = 0; i < m_instructions.size() - 1; ++i)
	{
		fillUse(i);
		fillDef(i);
		fillSucc(i);
	}

	fillUse(m_instructions.size() - 1);
	fillDef(m_instructions.size() - 1);

	for (int i = 0; i < m_instructions.size(); ++i)
	{
		fillPred(i);
	}

	fillInAndOut();

}

void LivenessAnalysis::printGraph()
{
	std::cout << m_interferenceGraph;
}

InterferenceGraph& LivenessAnalysis::getInterferenceGraph()
{
	return m_interferenceGraph;
}

