// Stefan Marinkov
// 22.5.2020.
#include "Directives.h"

MemoryDirective::MemoryDirective(std::string name) : m_name(name), m_value(0) {}

std::string MemoryDirective::getName() const
{
	return m_name;
}

int MemoryDirective::getValue() const
{
	return m_value;
}

void MemoryDirective::setValue(int v)
{
	m_value = v;
}

RegisterDirective::RegisterDirective(std::string name) : m_name(name) {}

std::string RegisterDirective::getName() const
{
	return m_name;
}

FunctionDirective::FunctionDirective(std::string name, int n) : m_name(name), m_value(0), m_namespace(n) {}

std::string FunctionDirective::getName() const
{
	return m_name;
}

int FunctionDirective::getValue() const
{
	return m_value;
}

int FunctionDirective::getNamespace() const
{
	return m_namespace;
}

void FunctionDirective::setValue(int v)
{
	m_value = v;
}

LabelDirective::LabelDirective(std::string name, int n) : m_name(name), m_value(0), m_namespace(n) {}

std::string LabelDirective::getName() const
{
	return m_name;
}

int LabelDirective::getNamespace() const
{
	return m_namespace;
}

int LabelDirective::getValue() const
{
	return m_value;
}

void LabelDirective::setValue(int v)
{
	m_value = v;
}

std::ostream& operator<<(std::ostream& os, const MemoryDirective& m)
{
	os << "Name: " << m.m_name << "\tValue: " << m.m_value;
	return os;
}

void printMemoryDirectives(MemoryDirectives& g_memoryDirective)
{
	std::cout << std::endl << "MemoryDirectives:" << std::endl;
	for (std::shared_ptr<MemoryDirective> m : g_memoryDirective)
		std::cout << *m << std::endl;
}

bool findMemoryDirective(Token token, MemoryDirectives& m_memoryDirectives)
{
	for (std::shared_ptr<MemoryDirective> m : m_memoryDirectives)
	{
		if (m->getName() == token.getValue())
			return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const RegisterDirective& r)
{
	os << "Name: " << r.m_name;
	return os;
}

void printRegisterDirective(RegisterDirectives& m_registerDirectives)
{
	std::cout << std::endl << "RegisterDirectives:" << std::endl;
	for (std::shared_ptr<RegisterDirective> g : m_registerDirectives)
		std::cout << *g << std::endl;
}

bool findRegisterDirective(Token token, RegisterDirectives& m_registerDirectives)
{
	for (std::shared_ptr<RegisterDirective> r : m_registerDirectives)
	{
		if (r->getName() == token.getValue())
			return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const FunctionDirective& f)
{
	os << "Name: " << f.m_name << "\t" << "Value: " << f.m_value;
	return os;
}

void printFunctionDirectives(FunctionDirectives& g_functionDirective)
{
	std::cout << std::endl << "FunctionDirectives:" << std::endl;
	for (std::shared_ptr<FunctionDirective> f : g_functionDirective)
		std::cout << *f << std::endl;
}

bool findFunctionDirective(Token token, FunctionDirectives& m_functionDirectives)
{
	for (std::shared_ptr<FunctionDirective> d : m_functionDirectives)
	{
		if (d->getName() == token.getValue())
			return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const LabelDirective& l)
{
	os << "Name: " << l.m_name << "\t" << "Value: " << l.m_value;
	return os;
}

void printLabelDirectives(LabelDirectives& m_labelDirectives)
{
	std::cout << std::endl << "LabelDirectives:" << std::endl;
	for (std::shared_ptr<LabelDirective> l : m_labelDirectives)
		std::cout << *l << std::endl;
}

bool findLabelDirective(Token token, LabelDirectives& m_labelDirectives)
{
	for (std::shared_ptr<LabelDirective> l : m_labelDirectives)
	{
		if (l->getName() == token.getValue())
			return true;
	}
	return false;
}

