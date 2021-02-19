// Stefan Marinkov
// 25.05.2020.

#ifndef __IR__
#define __IR__

#include "Types.h"
#include <memory>

/**
 * This class represents one variable from program code.
 */

class Variable
{
public:
	enum VariableType
	{
		MEM_VAR,
		REG_VAR,
		NO_TYPE
	};

	Variable() : m_type(NO_TYPE), m_name(""), m_position(-1), m_assignment(no_assign) {}
	Variable(std::string name, int pos) : m_type(NO_TYPE), m_name(name), m_position(pos), m_assignment(no_assign) {}
	void setType(const VariableType& v) 
	{
		m_type = v;
	}
	void setName(const std::string& n)
	{
		m_name = n;
	}
	void setPosition(const int& p)
	{
		m_position = p;
	}
	void setAssignment(const Regs& r)
	{
		m_assignment = r;
	}
	VariableType getType() const 
	{
		return m_type;
	}
	std::string getName() const 
	{
		return m_name;
	}
	int getPosition() const
	{
		return m_position;
	}
	Regs getAssignment() const
	{
		return m_assignment;
	}

private:
	VariableType m_type;
	std::string m_name;
	int m_position;
	Regs m_assignment;
};


/**
 * This type represents list of variables from program code.
 */
typedef std::list<std::shared_ptr<Variable>> Variables;


/**
 * This class represents one instruction in program code.
 */
class Instruction
{
public:
	Instruction () : m_position(0), m_type(I_NO_TYPE), m_constant(0) {}
	Instruction (int pos, InstructionType type, Variables& dst, Variables& src) :
		m_position(pos),
		m_type(type),
		m_dst(dst),
		m_src(src),
		m_constant(-1){}

	void setPosition(const int& p)
	{
		m_position = p;
	}
	void setType(const InstructionType& t)
	{
		m_type = t;
	}
	void setDst(const Variables& v)
	{
		m_dst = v;
	}
	void setSrc(const Variables& v)
	{
		m_src = v;
	}
	void setUse(const Variables& v)
	{
		m_use = v;
	}
	void setDef(const Variables& v)
	{
		m_def = v;
	}
	void setIn(const Variables& v)
	{
		m_in = v;
	}
	void setOut(const Variables& v)
	{
		m_out = v;
	}
	void setSucc(const std::vector<std::shared_ptr<Instruction>>& i)
	{
		m_succ = i;
	}
	void setPred(const std::vector<std::shared_ptr<Instruction>>& i)
	{
		m_pred = i;
	}
	void setInstructionNum(const int& i)
	{
		m_instructionNum = i;
	}
	void setConstant(const int& c)
	{
		m_constant = c;
	}
	void serForm(const std::string s)
	{
		m_form = s;
	}

	Variables& getDst()
	{
		return m_dst;
	}
	Variables& getSrc()
	{
		return m_src;
	}
	Variables& getUse()
	{
		return m_use;
	}
	Variables& getDef()
	{
		return m_def;
	}
	Variables& getIn()
	{
		return m_in;
	}
	Variables& getOut()
	{
		return m_out;
	}
	InstructionType getType() const
	{
		return m_type;
	}
	std::vector<std::shared_ptr<Instruction>>& getSucc()
	{
		return m_succ;
	}
	std::vector<std::shared_ptr<Instruction>>& getPred()
	{
		return m_pred;
	}
	int getConstant()
	{
		return m_constant;
	}
	int getInstructionNum()
	{
		return m_instructionNum;
	}
	int getPosition() const
	{
		return m_position;
	}
	std::string getForm()
	{
		return m_form;
	}

private:
	int m_position;
	InstructionType m_type;
	
	Variables m_dst;
	Variables m_src;
	int m_instructionNum;
	int m_constant;
	std::string m_form;

	Variables m_use;
	Variables m_def;
	Variables m_in;
	Variables m_out;
	std::vector<std::shared_ptr<Instruction>> m_succ;
	std::vector<std::shared_ptr<Instruction>> m_pred;
};


/**
 * This type represents list of instructions from program code.
 */
typedef std::vector<std::shared_ptr<Instruction>> Instructions;

#endif
