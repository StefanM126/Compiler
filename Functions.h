// Autor: Stefan Marinkov
// Datum: 25.05.2020.

#pragma once
#include "IR.h"

// ---------------------------- InstructionsMaking ---------------------------------
void printVariablesName(const Variables& variables);
void printVariables(const Variables& variables);
void printInstruction(Instruction& instruction);
void printInstructions(Instructions& instructions);
std::string InstructionTypeToString(InstructionType i);

//----------------------------- LivnessAnalysis ------------------------------------
bool pred(std::shared_ptr<Variable> const var1, std::shared_ptr<Variable> const var2);
bool compareNocase(const std::string& first, const std::string& second);
bool sortPred(std::shared_ptr<Variable> const var1, std::shared_ptr<Variable> const var2);

//------------------------------ PrintToFile ----------------------------------------
std::string RegsToString(Regs r);