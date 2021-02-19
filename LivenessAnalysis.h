// Autor: Stefan Marinkov
// Datum: 01.06.2020.

#pragma once
#include "InstructionsMaking.h"
#include "InterferenceGraph.h"
#include <string>

class LivenessAnalysis
{
public:
	LivenessAnalysis(Instructions& instr, Variables& variables);
	Instructions& getInstructions();
	void Do();
	void makeInterferenceGraph();
	void printGraph();
	InterferenceGraph& getInterferenceGraph();

private:
	void fillInAndOut();
	void refreshIn(Instructions::reverse_iterator& rIt);
	void refreshOut(Instructions::reverse_iterator& rIt);
	void fillUse(int i);
	void fillDef(int i);
	void fillSucc(int i);
	void fillPred(int i);
	Instructions m_instructions;
	InterferenceGraph m_interferenceGraph;
};
