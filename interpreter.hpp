#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// system includes
#include <string>
#include <istream>
#include <vector>


// module includes
#include "expression.hpp"
#include "environment.hpp"

//Jihoon Added
#include "tokenize.hpp"

// Interpreter has
// Environment, which starts at a default
// parse method, builds an internal AST
// eval method, updates Environment, returns last result
class Interpreter {
public:
	/*
	* The parse method will call the tokenize method to create the deque object.
	* Then after checking for validity, the tree method will get called to create the
	* Expression tree object.
	*/
	bool parse(std::istream& expression) noexcept;
	Expression eval();
	
	//Jihoon Added
	Interpreter();
	/*
	 * A recursive method that transfers the deque made from tokenize to the Expression ast private object.
	 * The parameters include the deque, an expression pointer for traversal through the tree, and booleans
	 * to meet end conditions.
	 * This method gets called in parse.
	 */
	Expression tree(std::deque<std::string>& dequetoken, Expression* e, bool& state, bool& start, int& ucount);
	std::vector<Expression> getDraw();
	bool checkDeque(int& ucount, bool& start, std::string& current, std::deque<std::string>& dequetoken, bool& confirm, Expression* e, bool& state);
	bool CheckDequeEnd(std::string& current, int& ucount, bool& start, bool& confirm, Expression* e, std::deque<std::string>& dequetoken, bool& state);
	bool TreeTypeCheck(Expression* e, int& ucount, bool& start, bool& confirm, bool& state, Atom& a, std::deque<std::string>& dequetoken, int& count);
protected:
	Environment env;
	Expression ast;
	std::vector<Expression> graphics;

	//Jihoon added
	std::vector <std::string> val;
	Atom* checkDequeatom;
	Atom* CheckDequeEndatom;
	Atom* TreeTypeCheckatom;
};


#endif
