// Autor: Stefan Marinkov
// Datum: 02.06.2020.

#include "InterferenceGraph.h"

InterferenceGraph::InterferenceGraph(Variables& variables)
{
	m_variables = variables;
	std::vector<uint16_t> v(variables.size(), 0);
	for (int i = 0; i < variables.size(); ++i)
		{
			m_graph.push_back(v);
		}
}

void InterferenceGraph::setInterference(int v1, int v2)
{
	m_graph[v1][v2] = 1;
	m_graph[v2][v1] = 1;
}

Variables & InterferenceGraph::getVariables()
{
	return m_variables;
}

GraphMatrix& InterferenceGraph::getGraph()
{
	return m_graph;
}

std::ostream & operator<<(std::ostream& os, const InterferenceGraph& g)
{
	os << "--- Interference graph: " << std::endl;
	os << std::endl;
	os << "   ";
	
	for (std::shared_ptr<Variable> v : g.m_variables)
	{
		os << v->getName() << " ";
	}
	os << std::endl;

	auto it = (g.m_variables).begin();

	for (int i = 0; i < (g.m_variables).size(); ++i)
	{
		os << (*it)->getName() << " ";
		++it;
		for (int j = 0; j < (g.m_variables).size(); ++j)
		{
			os << " " << g.m_graph[i][j] << " ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}
