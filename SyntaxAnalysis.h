// Stefan Marinkov
// 20.5.2020.

#pragma once

#include "LexicalAnalysis.h"
#include "Directives.h"
#include "Token.h"
#include "IR.h"


class SyntaxAnalysis
{
public:
	bool errorDuplicate(Token token);
	/**
	* Constructor
	*/
	SyntaxAnalysis(LexicalAnalysis& lex);

	/**
	* Method which performs lexical analysis
	*/
	void Do();

	FunctionDirectives& getFunctionDirectives();

	MemoryDirectives& getMemoryDirectives();

	LabelDirectives& getLabelDirectives();

	RegisterDirectives& getRegisterDirectives();

	Variables& getRegisterVariables();

protected:
	SyntaxAnalysis(LexicalAnalysis& lex, RegisterDirectives& r, LabelDirectives& l, FunctionDirectives& f, MemoryDirectives& m, Variables& v);
	/**
	* Prints the error message, and token that caused the syntax error
	*/
	void printSyntaxError(Token token);
	/**
	* Prints the error message, and token if t _mem or _reg variable isn't defined
	*/
	void printNoVarError(Token token);
	/**
	* Prints the error message, and token when same variable is redefined
	*/
	void printRedefinedError(Token token);
	/**
	* Prints the error message, and token when there is no function in source code
	*/
	void printNoFuncError();
	/**
	* Prints the token info
	*/
	void printTokenInfo(Token token);

	/**
	* Eats the current token if its type is "t"
	* otherwise reports syntax error
	*
	* param[in] - t - the expected token type
	*/
	void eat(TokenType t);

	/**
	* Returns the next token from the token list
	*/
	Token getNextToken();

	/**
	* Nonterminal Q
	*/
	void Q();

	/**
	* Nonterminal S
	*/
	void S();

	/**
	* Nonterminal L
	*/
	void L();

	/**
	* Nonterminal E
	*/
	void E();

	/**
	* Reference to lexical analysis module
	*/
	LexicalAnalysis& m_lexicalAnalysis;

	/**
	* Iterator to the token list which represents the output of the lexical analysis
	*/
	TokenList::iterator m_tokenIterator;

	/**
	* Current token that is being analyzed
	*/
	Token m_currentToken;
	/**
	* If _func is before ID
	*/
	bool m_function;
	// true - labela ili id nakon _func
	// false - id u instrukciji
	int m_instructionNum;

	int m_varPosition;

	FunctionDirectives m_functionDirectives;

	RegisterDirectives m_registerDirectives;

	MemoryDirectives m_memoryDirectives;

	LabelDirectives m_labelDirectives;

	Variables m_registerVariables;

	int m_namespace;
};
