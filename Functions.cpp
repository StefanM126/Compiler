// Autor: Stefan Marinkov
// Datum: 25.05.2020.
#include "Functions.h"

void printInstructions(Instructions& instructions)
{
	for (std::shared_ptr<Instruction> i : instructions)
	{
		printInstruction(*i);
	}
}

void printVariablesName(const Variables& variables)
{
	for (std::shared_ptr<Variable> var : variables)
	{
		std::cout << var->getName() << "  ";
	}

}

void printVariables(const Variables& variables)
{
	std::cout << "--- Register variables:" << std::endl;
	std::cout << std::endl;
	for (std::shared_ptr<Variable> var : variables)
	{
		std::cout << "( Name: " << var->getName() << ", ";
		std::cout << "Assignment: " << var->getAssignment() << ", ";
		std::cout << "Positon: " << var->getPosition() << ")";
		std::cout << std::endl;
	}


}


std::string InstructionTypeToString(InstructionType i)
{
	std::string ret;
	switch (i)
	{
	case I_ADD:
		ret = "ADD";
		break;
	case I_ADDI:
		ret = "ADDI";
		break;
	case I_SUB:
		ret = "SUB";
		break;
	case I_LA:
		ret = "LA";
		break;
	case I_LI:
		ret = "LI";
		break;
	case I_LW:
		ret = "LW";
		break;
	case I_SW:
		ret = "SW";
		break;
	case I_BLTZ:
		ret = "BLTZ";
		break;
	case I_B:
		ret = "B";
		break;
	case I_NOP:
		ret = "NOP";
		break;
	case I_AND:
		ret = "AND";
		break;
	case I_OR:
		ret = "OR";
		break;
	case I_BEQ:
		ret = "BEQ";
		break;
	case I_JAL:
		ret = "JAL";
		break;
	default:
		ret = "NO TYPE";
		break;
	}
	return ret;
}

void printInstruction(Instruction& instruction)
{
	std::cout << "--- Instruction: " << InstructionTypeToString(instruction.getType()) << std::endl;
	std::cout << "SRC: ";
	printVariablesName(instruction.getSrc());
	std::cout << std::endl;
	std::cout << "DST: ";
	printVariablesName(instruction.getDst());
	std::cout << std::endl;
	std::cout << "USE: ";
	printVariablesName(instruction.getUse());
	std::cout << std::endl;
	std::cout << "DEF: ";
	printVariablesName(instruction.getDef());
	std::cout << std::endl;
	std::cout << "IN : ";
	printVariablesName(instruction.getIn());
	std::cout << std::endl;
	std::cout << "OUT: ";
	printVariablesName(instruction.getOut());
	std::cout << std::endl;
	std::cout << "Constant: " << instruction.getConstant();
	std::cout << std::endl;
	std::cout << std::endl;
}

bool pred(std::shared_ptr<Variable> const var1, std::shared_ptr<Variable> const var2)
{
	return var1->getName() == var2->getName();
}

bool sortPred(std::shared_ptr<Variable> const var1, std::shared_ptr<Variable> const var2)
{
	return compareNocase(var1->getName(), var2->getName());
}

std::string RegsToString(Regs r)
{
	switch (r) {
	case t0:
		return "$t0";
	case t1:
		return "$t1";
	case t2:
		return "$t2";
	case t3:
		return "$t3";
	default:
		return "No_assing";
	}
}

bool compareNocase(const std::string& first, const std::string& second)
{
	unsigned int i = 0;
	while ((i<first.length()) && (i<second.length()))
	{
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return (first.length() < second.length());
}