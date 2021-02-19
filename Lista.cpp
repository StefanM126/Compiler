// Stefan Marinkov
// 21.5.2020.
#include "Lista.h"

template<typename T>
inline void Lista<T>::push_back(T* t)
{
	lista.push_back(t);
}

template<typename T>
Lista<T>::~Lista()
{
	for (T* t : lista)
	{
		delete t;
	}
	lista.clear();
}
