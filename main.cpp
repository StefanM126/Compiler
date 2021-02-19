// Stefan Marinkov
// 14.06.2020.

#include <iostream>
#include <exception>

#include "LexicalAnalysis.h"
#include "SyntaxAnalysis.h"
#include "InstructionsMaking.h"
#include "LivenessAnalysis.h"
#include "ResourceAllocation.h"
#include "PrintToFile.h"

using namespace std;

void callLexicalAnalysis()
{

}

int main()
{
	try
	{
		std::string fileName = ".\\..\\examples\\simple.mavn"; 
		//std::string fileName = ".\\..\\examples\\multiply.mavn"; 
		bool retVal = false;

// ------------------------------ LexicalAnalysis ------------------------------------------
		LexicalAnalysis lex;

		if (!lex.readInputFile(fileName))
			throw runtime_error("\nException! Failed to open input file!\n");

		lex.initialize();

		retVal = lex.Do();

		if (retVal)
		{
			lex.printTokens();
			cout << endl;
			cout << "Lexical analysis finished successfully!" << endl;
			cout << endl;
		}
		else
		{
			lex.printLexError();
			throw runtime_error("\nException! Lexical analysis failed!\n");
		}

//------------------------------ SyntaxAnalysis ---------------------------------------------
		SyntaxAnalysis syntax(lex);
		syntax.Do();
		cout << endl;
		cout << "Syntax analysis finished successfully!" << endl;
		cout << endl;
		cout << "First pass finished successfully!" << endl;
		printMemoryDirectives(syntax.getMemoryDirectives());
		printRegisterDirective(syntax.getRegisterDirectives());
		printFunctionDirectives(syntax.getFunctionDirectives());
		printLabelDirectives(syntax.getLabelDirectives());
		cout << endl;
		
//------------------------------ InstructionsMaking ---------------------------------------------	
		InstructionsMaking instr(lex, syntax.getRegisterDirectives(), syntax.getLabelDirectives(), syntax.getFunctionDirectives(), syntax.getMemoryDirectives(), syntax.getRegisterVariables());
		instr.Do();
			cout << "Instructions making finished successfully!" << endl;
			cout << endl;
			printInstructions(instr.getInstructions());

//------------------------------ LivenessAnalysis ---------------------------------------------
		LivenessAnalysis liveness(instr.getInstructions(), syntax.getRegisterVariables());
		liveness.Do();
		liveness.makeInterferenceGraph();
		cout << "Instructions making finished successfully!" << endl;
		cout << endl;
		printInstructions(liveness.getInstructions());
		liveness.printGraph();

//------------------------------ ResourceAllocation ---------------------------------------------
		ResourceAllocation alloc(liveness.getInterferenceGraph().getGraph(), liveness.getInterferenceGraph().getVariables());
		alloc.Do();
		printVariables(liveness.getInterferenceGraph().getVariables());

//------------------------------ PrintingToFile -------------------------------------------------
		PrintToFile print(liveness.getInterferenceGraph().getVariables(), instr.getMemoryDirectives(), instr.getLabelDirectives(), instr.getFunctionDirectives(), instr.getInstructions());
		cout << endl;
		cout << "Printing to file..." << endl;
		print.Do();
		cout << "Printing finished!" << endl;
	}	
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
