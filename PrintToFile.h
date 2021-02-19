// Stefan Marinkov
// 12.06.2020.
#pragma once

#include "Directives.h"
#include "IR.h"

class PrintToFile
{
public:
	PrintToFile(Variables& v, MemoryDirectives& m, LabelDirectives& l, FunctionDirectives& f, Instructions& i);
	void Do();

private:
	void printError();
	void printGlobl(std::ofstream& file);
	void printData(std::ofstream& file);
	void printText(std::ofstream& file);
	void printLabel(std::ofstream& file, int i);
	void printFunction(std::ofstream& file, int i, bool& first);
	void printInstruction(std::ofstream& file, int i);
	Variables m_registers;
	MemoryDirectives m_memory;
	LabelDirectives m_labels;
	FunctionDirectives m_functions;
	Instructions m_instructions;
};
