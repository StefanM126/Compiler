// Stefan Marinkov
// 21.5.2020.

#include <memory>
#include "SyntaxAnalysis.h"

#include <iostream>
#include <iomanip>
#include "IR.h"
#include "Types.h"
#include "Directives.h"

using namespace std;

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex)
	: m_lexicalAnalysis(lex),
	  m_tokenIterator(m_lexicalAnalysis.getTokenList().begin()),
	  m_function(false),
	  m_instructionNum(0),
	  m_varPosition(0),
	  m_namespace(-1) {}


void SyntaxAnalysis::Do() 
{
	m_currentToken = getNextToken();
	Q();
	if (m_namespace == -1)
		printNoFuncError();

}

FunctionDirectives& SyntaxAnalysis::getFunctionDirectives()
{
	return m_functionDirectives;
}

MemoryDirectives& SyntaxAnalysis::getMemoryDirectives()
{
	return m_memoryDirectives;
}

LabelDirectives& SyntaxAnalysis::getLabelDirectives()
{
	return m_labelDirectives;
}

RegisterDirectives& SyntaxAnalysis::getRegisterDirectives()
{
	return m_registerDirectives;
}

Variables & SyntaxAnalysis::getRegisterVariables()
{
	return m_registerVariables;
}

SyntaxAnalysis::SyntaxAnalysis(LexicalAnalysis& lex, RegisterDirectives& r, LabelDirectives& l, FunctionDirectives& f, MemoryDirectives& m, Variables& v)
	: m_registerDirectives(r),
	m_labelDirectives(l),
	m_functionDirectives(f),
	m_memoryDirectives(m),
	m_registerVariables(v),
	m_lexicalAnalysis(lex),
	m_tokenIterator(m_lexicalAnalysis.getTokenList().begin()),
	m_function(false),
	m_instructionNum(0),
	m_varPosition(0),
	m_namespace(-1) {}

void SyntaxAnalysis::printSyntaxError(Token token)
{
	cout << "Error! Token: " << token.getValue() << " unexpected." << endl;
	throw runtime_error("");
}

void SyntaxAnalysis::printNoVarError(Token token)
{
	cout << "Error! There is no " << token.getValue() << " defined." << endl;
	throw runtime_error("");
}

void SyntaxAnalysis::printRedefinedError(Token token)
{
	cout << "Error! " << token.getValue() << " is redefined." << endl;
	throw runtime_error("");
}

void SyntaxAnalysis::printNoFuncError()
{
	std::cout << "Error! There is no function in this file." << std::endl;
	throw std::runtime_error("");
}


void SyntaxAnalysis::printTokenInfo(Token token)
{
	cout << setw(20) << left << token.tokenTypeToString(token.getType());
	cout << setw(25) << right << token.getValue() << endl;
}


void SyntaxAnalysis::eat(TokenType t)
{

		if (errorDuplicate(m_currentToken))
		{
			printRedefinedError(m_currentToken);
		}
		else if (m_currentToken.getType() == t) 
		{
			printTokenInfo(m_currentToken);
			if (m_currentToken.getType() != T_END_OF_FILE) // jer je oef poslednji token i ako se uzme sledeći biće bačen izuzetak
				m_currentToken = getNextToken();
		}
		else {
			printSyntaxError(m_currentToken);
	}
}


Token SyntaxAnalysis::getNextToken()
{
	if (m_tokenIterator == m_lexicalAnalysis.getTokenList().end())
		throw runtime_error("End of input file reached");
	return *m_tokenIterator++;
}

void SyntaxAnalysis::Q()
{
	S();
	eat(T_SEMI_COL);
	L();
}

void SyntaxAnalysis::S() 
{
	m_function = true;
	if (m_currentToken.getType() == T_MEM) 
	{
		eat(T_MEM);
		std::shared_ptr<MemoryDirective> m(new MemoryDirective(m_currentToken.getValue()));
		eat(T_M_ID);
		m->setValue(atoi((m_currentToken.getValue()).c_str()));
		eat(T_NUM);		
		m_memoryDirectives.push_back(m);
	}
	else if (m_currentToken.getType() == T_REG)
	{
		eat(T_REG);
		std::shared_ptr<RegisterDirective> r(new RegisterDirective(m_currentToken.getValue()));
		std::shared_ptr<Variable> v(new Variable(m_currentToken.getValue(), m_varPosition++));
		v->setType(Variable::REG_VAR);
		eat(T_R_ID);
		m_registerDirectives.push_back(r);
		m_registerVariables.push_back(v);
	}
	else if (m_currentToken.getType() == T_FUNC)
	{
		eat(T_FUNC);
		std::shared_ptr<FunctionDirective> f(new FunctionDirective(m_currentToken.getValue(), ++m_namespace));
		f->setValue(m_instructionNum);
		eat(T_ID);
		m_functionDirectives.push_back(f);
	}
	else if (m_currentToken.getType() == T_ID) 
	{
		std::shared_ptr<LabelDirective> l(new LabelDirective(m_currentToken.getValue(), m_namespace));
		eat(T_ID);
		eat(T_COL);
		l->setValue(m_instructionNum);
		m_labelDirectives.push_back(l);
		E();
	}
	else
	{
		E();
	}
}

void SyntaxAnalysis::L() 
{
	if (m_currentToken.getType() == T_END_OF_FILE)
	{
		eat(T_END_OF_FILE);
	}
	else
	{
		Q();
	}
}

void SyntaxAnalysis::E()
{
	m_function = false;
	m_instructionNum++;
	switch (m_currentToken.getType())
	{
	case T_ADD:

		eat(T_ADD);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;

	case T_ADDI:
		eat(T_ADDI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		break;
	
	case T_SUB:
		eat(T_SUB);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;

	case T_LA:
		eat(T_LA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_M_ID);
		break;

	case T_LW:
		eat(T_LW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
		break;

	case T_LI:
		eat(T_LI);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		break;

	case T_SW:
		eat(T_SW);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_NUM);
		eat(T_L_PARENT);
		eat(T_R_ID);
		eat(T_R_PARENT);
		break;

	case T_B:
		eat(T_B);
		eat(T_ID);
		break;

	case T_BLTZ:
		eat(T_BLTZ);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_ID);
		break;

	case T_NOP:
		eat(T_NOP);
		break;

	case T_AND:
		eat(T_AND);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;

	case T_OR:
		eat(T_OR);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		break;

	case T_BEQ:
		eat(T_BEQ);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_R_ID);
		eat(T_COMMA);
		eat(T_ID);
		break;

	case T_JAL:
		eat(T_JAL);
		eat(T_ID);
		break;
		
	default:
		eat(T_ERROR);
		break;
	}
}

bool SyntaxAnalysis::errorDuplicate(Token token)
{
	if (m_function)
		return 
			findFunctionDirective(token, m_functionDirectives) ||
			findLabelDirective(token, m_labelDirectives) ||
			findMemoryDirective(token, m_memoryDirectives) ||
			findRegisterDirective(token, m_registerDirectives);

	return false;
}

