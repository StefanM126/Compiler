//Autor: Stefan Marinkov
//Datum: 30.05.2020.
#include "InstructionsMaking.h"

InstructionsMaking::InstructionsMaking(LexicalAnalysis& lex, RegisterDirectives& r, LabelDirectives& l, FunctionDirectives& f, MemoryDirectives& m, Variables& v)
	: SyntaxAnalysis(lex, r, l, f, m, v),
	m_namespace(-1) {}
	

void InstructionsMaking::Do()
{
	while (m_currentToken.getType() != T_END_OF_FILE)
	{
		m_currentToken = getNextToken();
		switch (m_currentToken.getType())
		{
		case T_FUNC:
		{
			m_currentToken = getNextToken();
			++m_namespace;
			break;
		}
//--------------------------------- ADD ------------------------------
		case T_ADD:
		{
			Variables srcList;
			Variables dstList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();
			
			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();
			
			srcList.push_back(takeThirdVar(Variable::REG_VAR));
			checkForErrors();
			
			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_ADD);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("add \t\t`d, `s, `s");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- ADDI ------------------------------
		case T_ADDI:
		{
			Variables srcList;
			Variables dstList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			m_currentToken = getNextToken();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_ADDI);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("addi\t\t`d, `s, `c");
			instructionPtr->setConstant(atoi((m_currentToken.getValue()).c_str()));
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- SUB ------------------------------
		case T_SUB:
		{
			Variables dstList;
			Variables srcList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeThirdVar(Variable::REG_VAR));
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_SUB);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("sub \t\t`d, `s, `s");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- AND ------------------------------
		case T_AND:
		{
			Variables dstList;
			Variables srcList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeThirdVar(Variable::REG_VAR));
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_AND);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("and \t\t`d, `s, `s");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- OR ------------------------------
		case T_OR:
		{
			Variables dstList;
			Variables srcList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeThirdVar(Variable::REG_VAR));
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_OR);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("or  \t\t`d, `s, `s");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- LA ------------------------------
		case T_LA:
		{
			Variables dstList;
			Variables srcList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::MEM_VAR));
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_LA);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("la  \t\t`d, `s");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- LW ------------------------------
		case T_LW:	
		{
			Variables dstList;
			Variables srcList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			m_currentToken = getNextToken();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setConstant(atoi((m_currentToken.getValue()).c_str()));

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			instructionPtr->setType(I_LW);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("lw  \t\t`d, `c(`s)");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- LI ------------------------------
		case T_LI:
		{
			Variables dstList;

			dstList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();
			
			m_currentToken = getNextToken();
			m_currentToken = getNextToken();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_LI);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setDst(dstList);
			instructionPtr->serForm("li  \t\t`d, `c");
			instructionPtr->setConstant(atoi((m_currentToken.getValue()).c_str()));
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- SW ------------------------------
		case T_SW:
		{
			Variables srcList;

			srcList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			m_currentToken = getNextToken();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setConstant(atoi((m_currentToken.getValue()).c_str()));

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			instructionPtr->setType(I_SW);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("sw  \t\t`s, `c(`s)");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//-------------------------------- JAL -----------------------------
		case T_JAL:
		{
			m_currentToken = getNextToken();
			checkForErrors(true);

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setConstant(fundLabOrFuncConstant(m_currentToken.getValue()));
			instructionPtr->setType(I_JAL);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->serForm("jal   \t\t`l");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();

			break;
		}
//--------------------------------- B ------------------------------		
		case T_B:
		{
			
			m_currentToken = getNextToken();
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setConstant(fundLabOrFuncConstant(m_currentToken.getValue()));
			instructionPtr->setType(I_B);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->serForm("b   \t\t`l");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- BLTZ ------------------------------
		case T_BLTZ:
		{
			Variables srcList;

			srcList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			m_currentToken = getNextToken();
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setConstant(fundLabOrFuncConstant(m_currentToken.getValue()));
			instructionPtr->setType(I_BLTZ);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("bltz\t\t`s, l`");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- BEQ ------------------------------
		case T_BEQ:
		{
			Variables srcList;

			srcList.push_back(takeFirstVar(Variable::REG_VAR));
			checkForErrors();

			srcList.push_back(takeSecondVar(Variable::REG_VAR));
			checkForErrors();

			m_currentToken = getNextToken();
			m_currentToken = getNextToken();
			checkForErrors();

			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_BEQ);
			instructionPtr->setConstant(fundLabOrFuncConstant(m_currentToken.getValue()));
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->setSrc(srcList);
			instructionPtr->serForm("beq \t\t`s, `s, `l");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
//--------------------------------- NOP ------------------------------
		case T_NOP:
		{
			std::shared_ptr<Instruction> instructionPtr(new Instruction());
			instructionPtr->setType(I_NOP);
			instructionPtr->setInstructionNum(m_instructionNum++);
			instructionPtr->serForm("nop");
			m_instructions.push_back(instructionPtr);
			m_currentToken = getNextToken();
			break;
		}
		default:
			break;
		}
	}
	if (findNoInstFuncOrLabel(m_instructionNum))
		printNoInstrError();
}

void InstructionsMaking::checkForErrors(bool isJal)
{
	bool error = false;
	bool wrongNamespaceError = false;
	bool jalError = false;
	switch (m_currentToken.getType())
	{
	case T_R_ID:
		error = !findRegisterDirective(m_currentToken, m_registerDirectives);
		break;
	case T_M_ID:
		error = !findMemoryDirective(m_currentToken, m_memoryDirectives);
		break;
	case T_ID:
		if (isJal)
			jalError = !findFunctionDirective(m_currentToken, m_functionDirectives);
		else
		{
			error = !findFunctionDirective(m_currentToken, m_functionDirectives) && !findLabelDirective(m_currentToken, m_labelDirectives);
			wrongNamespaceError = !(m_namespace == findLabOrFuncNamespace(m_currentToken.getValue()));
		}
		break;
	default:
		break;
	}
	if (error)
		printNoVarError(m_currentToken);
	if (wrongNamespaceError)
		printWrongNamespaceError();
	if (jalError)
		printJalError();
}

std::shared_ptr<Variable> InstructionsMaking::takeFirstVar(const Variable::VariableType v)
{
	m_currentToken = getNextToken();
	std::shared_ptr<Variable> varPtr(new Variable);
	if (v == Variable::MEM_VAR)
	{
		varPtr->setType(v);
		varPtr->setName(m_currentToken.getValue());
	}
	else if (v == Variable::REG_VAR)
	{
		varPtr = findVariable(m_currentToken.getValue());
	}
	else
		varPtr = nullptr;
	
	return varPtr;
}

std::shared_ptr<Variable> InstructionsMaking::takeSecondVar(const Variable::VariableType v)
{
	m_currentToken = getNextToken();
	m_currentToken = getNextToken();
	std::shared_ptr<Variable> varPtr(new Variable);
	if (v == Variable::MEM_VAR)
	{
		varPtr->setType(v);
		varPtr->setName(m_currentToken.getValue());
	}
	else if (v == Variable::REG_VAR)
	{
		varPtr = findVariable(m_currentToken.getValue());
	}
	else
		varPtr = nullptr;

	return varPtr;
}

std::shared_ptr<Variable> InstructionsMaking::takeThirdVar(const Variable::VariableType v)
{
	m_currentToken = getNextToken();
	m_currentToken = getNextToken();
	std::shared_ptr<Variable> varPtr(new Variable);
	if (v == Variable::MEM_VAR)
	{
		varPtr->setType(v);
		varPtr->setName(m_currentToken.getValue());
	}
	else if (v == Variable::REG_VAR)
	{
		varPtr = findVariable(m_currentToken.getValue());
	}
	else
		varPtr = nullptr;

	return varPtr;
}

std::shared_ptr<Variable> InstructionsMaking::findVariable(std::string name)
{
	for (std::shared_ptr<Variable> var : m_registerVariables)
	{
		if (var->getName() == name)
		{
			return var;
		}
	}
	return nullptr;
}

Instructions& InstructionsMaking::getInstructions()
{
	return m_instructions;
}

int InstructionsMaking::findLabOrFuncNamespace(const std::string name)
{
	for (std::shared_ptr<LabelDirective> l : m_labelDirectives)
	{
		if (l->getName() == name)
		{
			return l->getNamespace();
		}
	}

	for (std::shared_ptr<FunctionDirective> f : m_functionDirectives)
	{
		if (f->getName() == name)
		{
			return f->getNamespace();
		}
	}
	return 0;
}

int InstructionsMaking::fundLabOrFuncConstant(const std::string name)
{
	for (std::shared_ptr<LabelDirective> l : m_labelDirectives)
	{
		if (l->getName() == name)
		{
			return l->getValue();
		}
	}

	for (std::shared_ptr<FunctionDirective> f : m_functionDirectives)
	{
		if (f->getName() == name)
		{
			return f->getValue();
		}
	}
	return 0;
}

bool InstructionsMaking::findNoInstFuncOrLabel(const int n)
{
	for (const auto& f : m_functionDirectives)
	{
		if (f->getValue() >= n)
			return true;
	}

	for (const auto& l : m_labelDirectives)
	{
		if (l->getValue() >= n)
			return true;
	}

	return false;
}

void InstructionsMaking::printWrongNamespaceError()
{
	std::cout << "Error! Can't jump on " << m_currentToken.getValue() << " because it is't in current namespace." << std::endl;
	throw std::runtime_error("");
}

void InstructionsMaking::printJalError()
{
	std::cout << "Error! jal tried to jump on label " << m_currentToken.getValue() << ".";
	throw std::runtime_error("");
}

void InstructionsMaking::printNoInstrError()
{
	std::cout << "Error! There is no instruction at the adress of current label or function." << std::endl;
	throw std::runtime_error("");
}

