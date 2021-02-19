//Autor: Stefan Marinkov
//Datum: 30.05.2020.
#pragma once
#include "SyntaxAnalysis.h"
#include "IR.h"
#include "Functions.h"


class InstructionsMaking : public SyntaxAnalysis
{
public:
	InstructionsMaking(LexicalAnalysis& lex, RegisterDirectives& r, LabelDirectives& l, FunctionDirectives& f, MemoryDirectives& m, Variables& v);
	void Do();
	Instructions& getInstructions();

private:
	std::shared_ptr<Variable> takeFirstVar(const Variable::VariableType v);
	std::shared_ptr<Variable> takeSecondVar(const Variable::VariableType v);
	std::shared_ptr<Variable> takeThirdVar(const Variable::VariableType v);
	std::shared_ptr<Variable> findVariable(std::string name);
	int findLabOrFuncNamespace(const std::string name);
	int fundLabOrFuncConstant(const std::string name);
	bool findNoInstFuncOrLabel(const int n);
	void printWrongNamespaceError();
	void printJalError();
	void printNoInstrError();
	void checkForErrors(bool isJal = false);
	Instructions m_instructions;
	int m_namespace;
};
