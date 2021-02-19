// Autor: Stefan Marinkov
// Datum: 03.06.2020.

#include "ResourceAllocation.h"

ResourceAllocation::ResourceAllocation(GraphMatrix& graph, Variables& variables)
	: m_originalGraph(graph),
	m_maxNumerOfInterference(__REG_NUMBER__ - 1),
	m_finished(false)
{
	for (auto it = variables.begin(); it != variables.end(); ++it)
	{
		m_map[(*it)->getPosition()] = (*it);
	}
	m_graph = graph;
	//setGraph(graph);
}

void ResourceAllocation::makeStack()
{
	int sum = 0;
	m_maxNumerOfInterference = __REG_NUMBER__ - 1;
	for (int k = 0; k < __REG_NUMBER__; ++k)				// Po svim rangovima 
	{
		for (int i = 0; i < m_graph.size(); ++i)			// Po vrstama
		{
			for (int j = 0; j < m_graph.size(); ++j)		// Po kolonama
			{
				sum += m_graph[i][j];						// broji koliko ima smetnji (ivica)
			}
			if (sum == m_maxNumerOfInterference)			// Ukoliko je pronađen čvor sa maksimalnim rangom
			{
				for (int j = 0; j < m_graph.size(); ++j)
				{
					m_graph[i][j] = 0;						// Briše čvor iz matrice
					m_graph[j][i] = 0;
				}
				m_simplificationStack.push(m_map[i]);		// ubačeno u stek
				m_pushedIndexes.push_back(i);				// vektor vrednosti čvorova koji su već na steku
				makeStack();
				if (m_finished)
					return;
			}
			sum = 0;
		}
		m_maxNumerOfInterference--;							// smanjuje maksimalan broj smetnji
		if (m_maxNumerOfInterference == 0)
		{ 
				checkForSpill();							// Ako dođe do prolivanja error
				pushRangZero();								// Ukoliko su ostali samo čvorovi ranga 0
				m_finished = true;
				return;
		}
	}
}

void ResourceAllocation::printMemorySpill()
{
	std::cout << "Error! Too few registers caused memory spill." << std::endl;
	throw std::runtime_error("");
}

Regs ResourceAllocation::takeNext(Regs r)
{
	switch (r) {
	case t0:
		return t1;
	case t1: 
		return t2;
	case t2: 
		return t3;
	default: 
		return t0;
	}
}

void ResourceAllocation::Do()
{
	makeStack();

	if (m_simplificationStack.size() > 0) 
	{
		std::shared_ptr<Variable> preVal = m_simplificationStack.top();
		std::shared_ptr<Variable> nowVal;
		Variables alreadyColored;
		preVal->setAssignment(t0);

		alreadyColored.push_back(preVal);
		m_simplificationStack.pop();

		while (m_simplificationStack.size() != 0)
		{
			nowVal = m_simplificationStack.top();
			if (!checkForInterference(alreadyColored, nowVal))
			{
				nowVal->setAssignment(preVal->getAssignment());
			}
			else
			{
				Regs assignment = takeNext(preVal->getAssignment());
				if (assignment == t0)
					printMemorySpill();
				else
					nowVal->setAssignment(assignment);
			}
			preVal = nowVal;
			alreadyColored.push_back(nowVal);
			m_simplificationStack.pop();
		}
	}
	
}

VariablesStack& ResourceAllocation::getStack()
{
	return m_simplificationStack;
}

bool ResourceAllocation::checkForInterference(Variables& alreadyColored, std::shared_ptr<Variable> nowVal)
{
	for (std::shared_ptr<Variable> var : alreadyColored)
	{
		if (m_originalGraph[var->getPosition()][nowVal->getPosition()] != 0)
			return true;
	}

	return false;
}

void ResourceAllocation::setGraph(GraphMatrix g)
{
	m_graph = g;
}

void ResourceAllocation::pushRangZero()
{
	sort(m_pushedIndexes.begin(), m_pushedIndexes.end());	// sortiran vektor od manjeg ka većem, pr. 1, 2, 5, 6
	if (m_simplificationStack.size() > 0)
	{
		int p = 0;
		for (int i = 0; i < m_map.size(); ++i)
		{
			if (m_pushedIndexes[p] != i)
				m_simplificationStack.push(m_map[i]);
			else if (p != m_pushedIndexes.size() - 1)
				++p;
		}
	}
	
}

void ResourceAllocation::checkForSpill()
{
	for (int i = 0; i < m_graph.size(); ++i)
		for (int j = 0; j < m_graph.size(); ++j)
		{
			if (m_graph[i][j] != 0)
				printMemorySpill();
		}
}
