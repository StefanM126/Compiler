// Stefan Marinkov
// 22.5.2020.
#pragma once

#include "Token.h"
#include <memory>

class MemoryDirective
{
public:
	MemoryDirective(std::string name);
	std::string getName() const;
	int getValue() const;
	void setValue(int v);
	friend std::ostream& operator<<(std::ostream& os, const MemoryDirective& m);
	
private:
	int m_value;
	std::string m_name;
};

typedef std::list<std::shared_ptr<MemoryDirective>> MemoryDirectives;

void printMemoryDirectives(MemoryDirectives& m);

bool findMemoryDirective(Token token, MemoryDirectives& m_memoryDirectives); // returns true when directive found

class RegisterDirective
{
public:
	RegisterDirective(std::string name);
	std::string getName() const;
	friend std::ostream& operator<<(std::ostream& os, const RegisterDirective& r);

private:
	std::string m_name;
};

typedef std::list<std::shared_ptr<RegisterDirective>> RegisterDirectives;

void printRegisterDirective(RegisterDirectives& m_registerDirectives);

bool findRegisterDirective(Token token, RegisterDirectives& m_registerDirectives); // returns true when directive found

class FunctionDirective
{
public:
	FunctionDirective(std::string name, int n);
	std::string getName() const;
	int getValue() const;
	int getNamespace() const;
	void setValue(int v);
	friend std::ostream& operator<<(std::ostream& os, const FunctionDirective& f);

protected:
	std::string m_name;
	int m_value; // broj instrukcije koja se nalazi ispod funkcije
	int m_namespace;
};

typedef std::list<std::shared_ptr<FunctionDirective>> FunctionDirectives;

void printFunctionDirectives(FunctionDirectives& g_functionDirective);

bool findFunctionDirective(Token token, FunctionDirectives& m_functionDirectives); // returns true when directive found

class LabelDirective
{
public:
	LabelDirective(std::string name, int n);
	std::string getName() const;
	int getNamespace() const;
	int getValue() const;
	void setValue(int v);
	friend std::ostream& operator<<(std::ostream& os, const LabelDirective& l);

protected:
	std::string m_name;
	int m_value;
	int m_namespace;
};

typedef std::list<std::shared_ptr<LabelDirective>> LabelDirectives;

void printLabelDirectives(LabelDirectives& m_labelDirectives);

bool findLabelDirective(Token token, LabelDirectives& m_labelDirectives); // returns true when directive found

