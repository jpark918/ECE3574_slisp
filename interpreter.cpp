#include "interpreter.hpp"

// system includes
#include <stack>
#include <stdexcept>
#include <iostream>

// module includes
#include "tokenize.hpp"
#include "expression.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"

/*
* The parse method will call the tokenize method to create the deque object.
* Then after checking for validity, the tree method will get called to create the
* Expression tree object.
*/
bool Interpreter::parse(std::istream& expression) noexcept {
	// TODO: implement this function
	// return true if input is valid. otherwise, return false.
	//return true;


	//call the tokenize inside the parse method.
	std::deque <std::string> dequetoken;
	dequetoken = tokenize(expression);
	//Environment eco;     this.env!!!!!!
	//Expression exp;      this.ast!!!!!!

	//loop through and find ( and )
	int opencount = 0;
	int closecount = 0;
	int RegressionTest = 0;
	bool RegressionFail = false;
	for (size_t z = 0; z < dequetoken.size(); z++) {
		if (dequetoken[z] == "(") {
			opencount++;
			RegressionTest++;
		}
		else if (dequetoken[z] == ")") {
			closecount++;
			RegressionTest--;
		}
		if ((dequetoken[z] != "\r\n" || dequetoken[z] != "\n") && RegressionTest == 0) {
			if (RegressionTest == 0 && (z != dequetoken.size() - 1 && (z != dequetoken.size() - 2) && dequetoken[dequetoken.size() - 1] != "\n\n") && dequetoken.back() != "\n" && dequetoken.front() != "\n" && dequetoken.back() != "\r\n" && dequetoken.front() != "\r\n") {
				RegressionFail = true;
				break;
			}
		}
	}
	if (opencount == closecount && (opencount != 0 && closecount != 0) && !RegressionFail) {
		bool begin1 = false;
		Expression* e = nullptr;
		bool start = false;
		int ucount = 0;
		this->ast = Expression();
		tree(dequetoken, e, begin1, start, ucount);
		if (begin1) {
			return true;
		}
	}
		return false;
	//then create the ast tree.
};

/*
* The eval() method will use the ast created from parse (if parse returns true)
* this method will call getExpression() method and returns the evaluated result
*/
Expression Interpreter::eval() {
	// TODO: implement this function

	//piazza 197 (handle define begin and if inside eval) ??

	bool checkProcedure = env.getProcedure(this->ast.head.value.sym_value);
	if (this->ast.tail.empty() && checkProcedure) { //if it is just a Procedure Type with no other in tree
		throw InterpreterSemanticError("Cannot evaluate only a procedure");
	}
	if (this->ast.tail.empty() && (this->ast.head.type == BooleanType || this->ast.head.type == NumberType)) {
		return this->ast.head;
	}
	/*
	if (!checkProcedure) {
		throw InterpreterSemanticError("not a valid Procedure");
	} */
	 //we can go further down the tree to check
		Expression final = ast;
		bool done = false;
		//bool defclimb = false;
		Expression* e = &final;
		Expression* top = &final;
		Expression* cookiecrumb = nullptr;
		Expression procresult;
		bool operated = false;
		bool checkhead = false;
		bool iflast = false;
		std::vector<Expression>* drew = &graphics;
		env.getExpression(procresult, e, top, done, cookiecrumb, val, operated, checkhead, iflast, drew);
		return procresult;
}


//ADDED CONSTRUCTOR
Interpreter::Interpreter() {
	//env = Environment();
	ast = Expression();
}

/*
* A recursive method that transfers the deque made from tokenize to the Expression ast private object.
* The parameters include the deque, an expression pointer for traversal through the tree, and booleans
* to meet end conditions.
* This method gets called in parse.
* the symbols in the deque the atom that will be basically the expression added in the tail
* the boolean which will determine the result of parse the pointer to remember the Expression within the tail due to it being an atom being stored in it.
*/
Expression Interpreter::tree(std::deque<std::string>& dequetoken, Expression* e, bool& state, bool& start, int& ucount) {
	bool confirm;
	int count = 0;
	if (dequetoken.empty() && this->ast.head.type != NoneType) { //can't be nonetype. There must be something in the ast that is not just ( )
		state = true;
		return e != nullptr;
	}
	std::string current = dequetoken.front();
	dequetoken.pop_front();
	if (this->ast.head.type == NoneType && current == "(") { //do I store ( and ) inside the tree? Probably not
		if (checkDeque(ucount, start, current, dequetoken, confirm, e, state)) {
			return checkDequeatom != nullptr;
		}
	}
	else if (current == "(") {
		Atom a;
		current = dequetoken.front();	//after the ast's head has been added
		dequetoken.pop_front();
		if (current.size() >= 4) { //for test_car.slp dequetoken index 87~
			std::string ch = current.substr(current.size() - 1, 2);
			std::string ch2 = current.substr(current.size() - 2, 4);
			if (ch2 == "\n\n" || ch2 == "\r\n") {
				current = current.substr(0, current.size() - 1);
			}
			if (ch == "\n") { //removing strings that have \n appended
				current = current.substr(0, current.size() - 1);
			}
		}
		confirm = token_to_atom(current, a);
		std::string check = dequetoken.front();
		ucount++;
		count = ucount;
		if (a.type == SymbolType || a.type == BooleanType) {
			if (TreeTypeCheck(e, ucount, start, confirm, state, a, dequetoken, count)) {
				return TreeTypeCheckatom != nullptr;
			}
		}
		else if (a.type == NumberType && check == ")") { // (#) condition
			if (confirm) {
				e->tail.emplace_back(a);
				e = &e->tail[e->tail.size() - 1];
				tree(dequetoken, e, state, start, ucount);
			}
			else {
				state = false;
				return a;
			}
		}
	}
	else {
		if (CheckDequeEnd(current, ucount, start, confirm, e, dequetoken, state)) {
			return CheckDequeEndatom != nullptr;
		}
	}
	if (!start) {
		tree(dequetoken, e, state, start, ucount);
	}
	return e != nullptr;
}
//b

std::vector<Expression>Interpreter::getDraw() {
	return this->graphics;
}


bool Interpreter::checkDeque(int& ucount, bool& start, std::string& current, std::deque<std::string>& dequetoken, bool& confirm, Expression* e, bool& state) {
	ucount++;
	start = true;
	current = dequetoken.front();
	dequetoken.pop_front();
	if (current.size() >= 4) {
		std::string ch = current.substr(current.size() - 1, 2);
		std::string ch2 = current.substr(current.size() - 2, 4);
		if (ch2 == "\n\n" || ch2 == "\r\n") {
			current = current.substr(0, current.size() - 1);
		}
		if (ch == "\n") { //removing strings that have \n appended
			current = current.substr(0, current.size() - 1);
		}
	}
	Atom a;
	confirm = token_to_atom(current, a); //token_to_atom
	if (confirm && current != ")") {
		this->ast.head.type = a.type;
		this->ast.head.value = a.value;
		while (!dequetoken.empty()) {
			e = &ast;
			tree(dequetoken, e, state, start, ucount); //call it recursively again.
		}
		tree(dequetoken, e, state, start, ucount);
	}
	else {
		state = false;
		checkDequeatom = &a;
		return true;
		//return a;
	}
	return false;
}

bool Interpreter::CheckDequeEnd(std::string& current, int& ucount, bool& start, bool& confirm, Expression* e, std::deque<std::string>& dequetoken, bool& state) {
	if (current == ")") {
		// I think it should end the current branch and return to the main one. 
		//count--;
		ucount--;
	}
	else {
		if (current != "\n" && start && current != "\n\n" && current != "\r\n") {
			Atom a;
			confirm = token_to_atom(current, a);
			if (confirm) {
				//e.tail.emplace_back(a);
				//env.setExpression(e, current);  //WE only shove Symbol objects into the envmap 
				e->tail.emplace_back(a);
				//p->tail.emplace_back(a);
				//p = &p->tail[p->tail.size()]; //the most recent emplaced atom (pointer is pointing to expression)
				//we don't want to update the expression head with the line above.
				tree(dequetoken, e, state, start, ucount);
			}
			else {
				state = false;
				CheckDequeEndatom = &a;
				return true;
				//return a;
			}
		}
	}
	return false;
	//return true; //return true if empty?
}

bool Interpreter::TreeTypeCheck(Expression* e, int& ucount, bool& start, bool& confirm, bool& state, Atom& a, std::deque<std::string>& dequetoken, int& count) {
	if (confirm) {

		//this->ast.tail.emplace_back(a);
		e->tail.emplace_back(a);
		e = &e->tail[e->tail.size() - 1];
		tree(dequetoken, e, state, start, ucount); //call it recursively again

		//I need a check here in order to allow more tree calls here !!!!!!!!!!
		while (ucount == count) {
			tree(dequetoken, e, state, start, ucount);
		}
	}
	else {
		state = false;
		TreeTypeCheckatom = &a;
		return true;
		//return a;
	}
	return false;
}
