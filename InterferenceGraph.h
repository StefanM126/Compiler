// Autor: Stefan Marinkov
// Datum: 02.06.2020.
#pragma once

#include "IR.h"
typedef std::vector<std::vector<uint16_t>> GraphMatrix;

class InterferenceGraph 
{
public:
	InterferenceGraph(Variables& variables);
	void setInterference(int v1, int v2);
	Variables& getVariables();
	GraphMatrix& getGraph();
	friend std::ostream& operator<<(std::ostream& os, const InterferenceGraph& g);

private:
	Variables m_variables;
	GraphMatrix m_graph;
};