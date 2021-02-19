// Stefan Marinkov
// 21.5.2020.
#pragma once

#include<list>

template<typename T>
class Lista 
{
public:
	std::list<T*> lista;
	void push_back(T* t);
	~Lista();
};

