#include <cstdlib>

//Jihoon Added
#include "environment.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include "tokenize.hpp" 
#include "interpreter_semantic_error.hpp"

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	vector<string> arguments;
	for (int i = 0; i < argc; ++i) {    //shove all the argvs in a vector
		arguments.emplace_back(argv[i]);
	}
	std::string check;
	if (arguments.size() == 2) { //check for .slp file
		if (arguments[1] != "-e") {
			check = arguments[1].substr(arguments[1].size() - 4, 4);
			//std::cout << "file type is: " << check << std::endl;
		}
	}
	if (argc == 1) { //REPL
		Interpreter interp;  //move it outside for the envmap to remember.
		while (!cin.eof()) {
			std::cout << "slisp> ";
			string in;
			getline(cin, in);
			//cout << "string is " << in << endl;
			//cin.get(); //user presses "Enter" button
			//std::cout << std::endl;
			if (!in.empty()) {	//checks if user did not just "enter" only
				std::istringstream iss(in);
				bool gate = false;
				gate = interp.parse(iss);
				if (gate) {
					//std::cout << "gate == true" << std::endl;
					try {
						Expression result = interp.eval();
						//savevalue.push_back(result); //saving Number/Bool value
						std::cout << "(" << result << ")" << std::endl;
					}
					catch (const InterpreterSemanticError& e) {
						std::cout << "Error: Failure to execute from command line" << std::endl;
						interp = Interpreter();
					}
				}
				else {
					std::cout << "Error: Failure to execute from command line" << std::endl;
					interp = Interpreter();
				}
			}
		}
		//return EXIT_SUCCESS;
	}
	else if (argc == 3 && arguments[1] == "-e") { //TestExecuteCommandline from autograder
		//std::cout << "-e condition" << std::endl;
		std::string program = arguments[2];
		std::istringstream iss(program);
		Interpreter interp;
		bool gate = false;
		gate = interp.parse(iss);
		if (gate) {
			//std::cout << "gate == true" << std::endl;
			try {
				Expression result = interp.eval();
				std::cout << "(" << result << ")" << std::endl;
				return EXIT_SUCCESS;
			}
			catch (const InterpreterSemanticError& e) {
				std::cout << "Error: Failure to execute from command line" << std::endl;
				return EXIT_FAILURE;
			}
		}
		else {
			std::cout << "Error: Failure to execute from command line" << std::endl;
			return EXIT_FAILURE;
		}
	}
	else if (check == ".slp") {
		//std::string check = arguments[1];
		//std::cout << "entered .slp" << std::endl;
		std::ifstream ifs(arguments[1]);
		if (!ifs.is_open()) {
			std::cout << "Error: Failure to open file" << std::endl;
			return EXIT_FAILURE;
		}
		Interpreter interp;
		bool check = false;
		check = interp.parse(ifs);
		if (check) {
			try {
				Expression result = interp.eval();
				std::cout << "(" << result << ")" << std::endl;
				return EXIT_SUCCESS;
			}
			catch (const InterpreterSemanticError& e) {
				std::cout << "Error: Failure to eval .slp file" << std::endl;
				return EXIT_FAILURE;
			}
		}
		else {
			std::cout << "Error: Failure to parse .slp file" << std::endl;
			return EXIT_FAILURE;
		}

	}
	else {
		std::cout << "Error: none of the above conditions are passable." << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}