// Autor: Stefan Marinkov
// Datum: 03.06.2020.

#pragma once

#include "InterferenceGraph.h"

#include <map>
#include <algorithm>

typedef	std::stack<std::shared_ptr<Variable>> VariablesStack;
typedef std::map<int, std::shared_ptr<Variable>> VariablesMap;

class ResourceAllocation
{
public:
	ResourceAllocation(GraphMatrix& graph, Variables& variables);
	void Do();
	VariablesStack& getStack();

private:
	bool checkForInterference(Variables& alreadyColored, std::shared_ptr<Variable> nowVal);
	void setGraph(GraphMatrix g);
	void pushRangZero();
	void checkForSpill();
	void makeStack();
	void printMemorySpill();
	Regs takeNext(Regs r);

	GraphMatrix m_graph;
	GraphMatrix m_originalGraph;
	VariablesStack m_simplificationStack;
	VariablesMap m_map;
	bool m_finished;
	std::vector<int> m_pushedIndexes;
	int m_maxNumerOfInterference;
};