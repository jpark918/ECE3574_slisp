#include "environment.hpp"

#include <cassert>
#include <cmath>

#include "interpreter_semantic_error.hpp"

#include <iostream>

Expression ifenv(const std::vector<Atom>& args) {

	Expression a;
	if (args[0].value.bool_value) {
		a.head.type = NumberType;
		a.head.value.num_value = args[1].value.num_value;
		//return args[1].value;
	}
	else {
		a.head.type = NumberType;
		a.head.value.num_value = args[2].value.num_value;
	}
	return a;
	//}
	//return Expression();
}
Expression defenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[1].type == NumberType) {

		double hold = args[1].value.num_value;
		a.head.type = NumberType;
		a.head.value.num_value = hold;
		//a.head.value.sym_value = args[0].value.sym_value;// set to default constructor 
	}
	else if (args[1].type == BooleanType) {
		if (args[1].value.bool_value) {
			a.head.type = BooleanType;
			a.head.value.bool_value = true;
		}
		else {
			a.head.type = BooleanType;
			a.head.value.bool_value = false;
		}
	}
	return a;
}

Expression andenv(const std::vector<Atom>& args) {

	bool result = args[0].value.bool_value;
	for (int i = 1; i < args.size(); i++) {
		result = result && args[i].value.bool_value;
	}
	Expression a;
	a.head.type = BooleanType;
	a.head.value.bool_value = result;
	return a;
}

Expression notenv(const std::vector<Atom>& args) {
	if (args.size() > 1) {
		throw InterpreterSemanticError("too many args for Not procedure");
	}
	Expression a;
	a.head.type = BooleanType;
	a.head.value.bool_value = !args[0].value.bool_value;
	return a;
}

Expression orenv(const std::vector<Atom>& args) {

	bool result = args[0].value.bool_value;
	for (int i = 1; i < args.size(); i++) {
		result = result || args[i].value.bool_value;
	}
	Expression a;
	a.head.type = BooleanType;
	a.head.value.bool_value = result;
	return a;
}

Expression lessenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[0].value.num_value < args[1].value.num_value) {
		a.head.type = BooleanType;
		a.head.value.bool_value = true;
	}
	else {
		a.head.type = BooleanType;
		a.head.value.bool_value = false;
	}
	return a;
}

Expression lesseqenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[0].value.num_value <= args[1].value.num_value) {
		a.head.type = BooleanType;
		a.head.value.bool_value = true;
	}
	else {
		a.head.type = BooleanType;
		a.head.value.bool_value = false;
	}
	return a;
}

Expression grenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[0].value.num_value > args[1].value.num_value) {
		a.head.type = BooleanType;
		a.head.value.bool_value = true;
	}
	else {
		a.head.type = BooleanType;
		a.head.value.bool_value = false;
	}
	return a;
}

Expression greqenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[0].value.num_value >= args[1].value.num_value) {
		a.head.type = BooleanType;
		a.head.value.bool_value = true;
	}
	else {
		a.head.type = BooleanType;
		a.head.value.bool_value = false;
	}
	return a;
}

Expression eqenv(const std::vector<Atom>& args) {
	Expression a;
	if (args[0].value.num_value == args[1].value.num_value) {
		a.head.type = BooleanType;
		a.head.value.bool_value = true;
	}
	else {
		a.head.type = BooleanType;
		a.head.value.bool_value = false;
	}
	return a;
}

Expression addenv(const std::vector<Atom>& args) {
	double store = 0;
	for (int i = 0; i < args.size(); i++) {
		store += args[i].value.num_value;
	}
	Expression d;
	d.head.type = NumberType;
	d.head.value.num_value = store;
	return d;
	//return Expression();
}

Expression subenv(const std::vector<Atom>& args) {
	Expression a;
	if (args.size() == 1) { //negative number
		a.head.type = NumberType;
		a.head.value.num_value = -args[0].value.num_value;
	}
	else { //subtraction
		if (args.size() > 2) {
			throw InterpreterSemanticError("too many args for subtraction procedure");
		}

		a.head.type = NumberType;
		a.head.value.num_value = args[0].value.num_value - args[1].value.num_value;
	}
	return a;
}

Expression multenv(const std::vector<Atom>& args) {
	Expression a;
	double store = 1;
	for (int i = 0; i < args.size(); i++) {
		store = store * args[i].value.num_value;
	}
	a.head.type = NumberType;
	a.head.value.num_value = store;
	return a;
}

Expression divenv(const std::vector<Atom>& args) {
	double store = 0;
	Expression a;
	store = args[0].value.num_value / args[1].value.num_value;
	a.head.type = NumberType;
	a.head.value.num_value = store;
	return a;
}

Expression logenv(const std::vector<Atom>& args) {
	double store;
	if (args.size() == 1 && args[0].value.num_value != Number()) {
		store = log10(args[0].value.num_value);
	}
	else {
		throw InterpreterSemanticError("more than 1 argument for log");
	}
	Expression a;
	a.head.type = NumberType;
	a.head.value.num_value = store;
	return a;
}

Expression powenv(const std::vector<Atom>& args) {
	double store;
	if (args.size() == 2 && args[0].value.num_value != Number() && args[1].value.num_value != Number()) {
		store = pow(args[0].value.num_value, args[1].value.num_value);
	}
	else {
		throw InterpreterSemanticError("more than 2 argument for pow");
	}
	Expression a;
	a.head.type = NumberType;
	a.head.value.num_value = store;
	return a;
}

Environment::Environment() {
	// TODO: implement your code ...

	envmap.clear();


	envmap["begin"];
	envmap["begin"].type = ProcedureType;

	envmap["if"];
	envmap["if"].type = ProcedureType;
	envmap["if"].proc = ifenv;

	envmap["define"];
	envmap["define"].type = ProcedureType;
	envmap["define"].proc = defenv;

	envmap["and"];
	envmap["and"].type = ProcedureType;
	envmap["and"].proc = andenv;

	envmap["not"];
	envmap["not"].type = ProcedureType;
	envmap["not"].proc = notenv;

	envmap["or"];
	envmap["or"].type = ProcedureType;
	envmap["or"].proc = orenv;

	envmap["<"];
	envmap["<"].type = ProcedureType;
	envmap["<"].proc = lessenv;

	envmap["<="];
	envmap["<="].type = ProcedureType;
	envmap["<="].proc = lesseqenv;

	envmap[">"];
	envmap[">"].type = ProcedureType;
	envmap[">"].proc = grenv;

	envmap[">="];
	envmap[">="].type = ProcedureType;
	envmap[">="].proc = greqenv;

	envmap["="];
	envmap["="].type = ProcedureType;
	envmap["="].proc = eqenv;

	envmap["+"];
	envmap["+"].type = ProcedureType;
	envmap["+"].proc = addenv;

	envmap["-"];
	envmap["-"].type = ProcedureType; //there are 2 of these
	envmap["-"].proc = subenv;

	envmap["*"];
	envmap["*"].type = ProcedureType;
	envmap["*"].proc = multenv;

	envmap["/"];
	envmap["/"].type = ProcedureType;
	envmap["/"].proc = divenv;

	envmap["log10"];
	envmap["log10"].type = ProcedureType;
	envmap["log10"].proc = logenv;

	envmap["pow"];
	envmap["pow"].type = ProcedureType;
	envmap["pow"].proc = powenv;

}
/*
* This method will take the ast made from parse and will determine the Expression 
* from a given string with procedures. This method gets called in Interpreter::eval()
* The method will recursively find the final expression.
* The parameters include: the Expression result which travels throughout the recursions, Expression pointer for recursive traversal,
* Expression pointer that always points to the root/head, a boolean for end condition, a Expression pointer that will remember where the parent 'node' is,
* a vector of strings that will add procedures and expressions to the envmap, and 3 booleans that are required for some implementations.
*/
Expression Environment::getExpression(Expression& procresult, Expression*& e, Expression* top, bool& done, Expression* cookiecrumb, std::vector<std::string>& val, bool& operated, bool& checkhead, bool& iflast) {
	//after the tree gets created we will want to go down the created tree.
	bool useless = false;
	bool endoftop = false;
	if (!top->tail.empty() && envmap[top->head.value.sym_value].type != ProcedureType) {
		throw InterpreterSemanticError("Root value is not a proper procedure or Expression");
	}/*
	if (useless) {
		//return procresult;
	}*/
	else {
		//if (envmap[e->head.value.sym_value].type == ProcedureType) {
		if (!e->tail.empty()) { //we can go further down the tree to check
			std::vector<Atom> store;
			for (int i = 0; i < e->tail.size(); i++) {
				if (envmap[e->tail[i].head.value.sym_value].type == ProcedureType) { //does this only check if it is in map or does it also call the function
					if (e->head.value.sym_value == "define") {
						if (e->tail[0].head.value.sym_value == "begin" || e->tail[i].head.value.sym_value == "if" || e->tail[i].head.value.sym_value == "define") { //Semantic error check
							throw InterpreterSemanticError("Special form procedure symbol is not allowed as variable");
						}
					}
					cookiecrumb = e;
					e = &e->tail[i];
					//definecheck = e->head.value.sym_value;
					procresult = getExpression(procresult, e, top, done, cookiecrumb, val, operated, checkhead, iflast);
					//store.clear();
					if (done) {
						e = top;
						if (e->tail[i].head.value.sym_value == "if" && e->tail[top->tail.size() - 1].head.value.sym_value == "if" && top->head.value.sym_value == "begin") {
							useless = true;
						}
					}
					e = cookiecrumb;
					if (operated) { //add the procedure math operation into the vector
						store.push_back(e->tail[i].head);
						endoftop = true;
						operated = false;
					}
				}
				else {
					if (e->head.value.sym_value == "define") {
						if (e->tail[0].head.value.num_value == atan2(0, -1)) {
							throw InterpreterSemanticError("built in symbol is not allowed as variable");
						}
					}
					bool newthing = true;
					for (int v = 0; v < val.size(); v++) {
						if (e->tail[i].head.value.sym_value == val[v]) { //if it is already in the envmap
							Expression z;
							z = envmap[e->tail[i].head.value.sym_value].exp;
							store.push_back(z.head);
							newthing = false;
						}
					}
					if (newthing) {

						if (e->tail[i].head.type == SymbolType && val.empty() && e->head.value.sym_value != "define") { //checking if I am not using an undefined symbol
							throw InterpreterSemanticError("Symbol has not been defined");
						}
						store.push_back(e->tail[i].head);
						if (e->head.value.sym_value == "begin" && envmap[e->tail[i].head.value.sym_value].type != ProcedureType) {
							store.clear();
						}
					}
					//store.push_back(e->tail[i].head);
					if (e->head.value.sym_value == "define" && i == 0) { //pushing a variable name to the map 
						envmap[e->tail[i].head.value.sym_value];
						val.push_back(e->tail[i].head.value.sym_value);
					}
				}
			}
			/*
			if (e->head.value.sym_value == "define" && store.size() >= 2 && !envmap.count(top->tail[top->tail.size() - 1].head.value.sym_value)) { //removed ! from envmap
				if (store[1].value.num_value != Number()) {
					procresult = store[1].value.num_value; //define but no output var on last spot of tree
					return procresult;
				}
			}*/
			for (int j = 0; j < val.size(); j++) {
				if (e->head.value.sym_value == "begin" && store.size() == 1 && val[j] == e->tail[e->tail.size() - 1].head.value.sym_value) { //define with output var on last spot
					return procresult;
				}
				else if (endoftop && e->head.value.sym_value == "begin" && envmap[top->tail[top->tail.size() - 1].head.value.sym_value].type != ProcedureType && store.size() == 1)
				{	//begin with procedure on last spot 
					return procresult;
				}
				else if (top->head.value.sym_value == "define" && store.size() >= 2 && val[j] != top->tail[top->tail.size() - 1].head.value.sym_value && j == val.size() - 1
					&& envmap[top->tail[top->tail.size() - 1].head.value.sym_value].type != ProcedureType) {
					if (store[1].type == NumberType) {
						procresult = store[1].value.num_value; //define but no output var on last spot of tree
						envmap[store[0].value.sym_value].exp = procresult;
					}
					else if (store[1].type == BooleanType) {
						procresult = store[1].value.bool_value;
						envmap[store[0].value.sym_value].exp = procresult;
					}
					return procresult;
				}
				else if (top->head.value.sym_value == "begin" && !store.empty() && top->tail[top->tail.size() - 1].head.value.num_value != Number()) {
					//begin as head but number on the last tail
					return procresult;
				}
				else if (top->head.value.sym_value == "begin" && e->tail[e->tail.size() - 1].head.value.sym_value == "if" && useless) {
					return procresult;
				}
			}
			/*
			if (store.size() == 1 && envmap.find(store[0].value.sym_value) != envmap.end() && e->head.value.sym_value == top->head.value.sym_value) {
				procresult = envmap.at(store[0].value.sym_value).exp; //define with output var on last spot of tree
				return procresult;
			}*/
			if (!store.empty()) {
				Procedure proc = envmap[e->head.value.sym_value].proc;
				//Expression procresult;
				procresult = (*proc)(store);
			}
			if (top->head.value.sym_value != "begin" && top->head.value.sym_value != "define" && top->head.value.sym_value != "if") { //nested procedure math operations
				if (e == top && top->head.value.sym_value == "+") { //if the root is + and we are at the root
					return procresult;
				}
				/*
				else if (e->head.value.sym_value == "+") { //if the head is + we want to change it to a number
					e->head = procresult.head;
				}*/
			}
			if (e->head.value.sym_value == "+" || e->head.value.sym_value == "<" || e->head.value.sym_value == "-" || e->head.value.sym_value == "and" || e->head.value.sym_value == "log10" || e->head.value.sym_value == "pow") { //if the head is + we want to change it to a number
				e->head = procresult.head;
				operated = true;
				iflast = true;
			}
			if (e->head.value.sym_value == "define") {
				//may need to check for val size before loop
				for (int i = 0; i < val.size(); i++) {
					if (val[i] == "pi") {
						throw InterpreterSemanticError("built in symbol is not allowed as variable");
					}
				}
				envmap[e->tail[0].head.value.sym_value].exp = procresult; //stored the defined variable's expression in the map
				done = true;
			}
			if (cookiecrumb != nullptr) {
				e = cookiecrumb;
			}
			store.clear();
		}
		return procresult;
	}
}

//This is used in interpreter::eval() in order to confirm a procedure symbol
bool Environment::getProcedure(Symbol sym) {
	//return envmap[sym].proc;
	if (envmap.count(sym) == 1) {
		return true;
	}
	return false;
}

//this is used in tree in order to add expresion to envmap
//if Expression is define
/*
void Environment::setExpression(Expression e, Symbol sym) {
	envmap[sym];
	envmap[sym].type = ExpressionType;
}*/
//this will be used in eval to determine if I can go further down the tree.
/*
bool Environment::getEnvType(Symbol sym) {
	if (envmap[sym].type == ExpressionType) {
		return true;
	}
	else {
		return false; //Procedure Type
	}
}*/

/*
bool Environment::map(const Symbol sym) {
	if (sym == "define" || sym == "begin" || sym == "if") {
		envmap[sym].type = ProcedureType; //HELP does this mean I do not need to create a struct object
		//envmap.insert(std::pair<Symbol, EnvResult>( sym, result ));
		return true;
	}
	else if (sym == "not") {
		envmap[sym].type = ProcedureType; //Procedure Symbols (+, -, etc)
		//envmap[sym].proc = add;
		return true;
	}
	else if (sym == "and") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "or") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "<") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "<=") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == ">") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == ">=") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "=") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "+") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "-") { //THIS CAN BE MINUS OPERATION OR NEGATIVE
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "*") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "/") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "log10") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else if (sym == "pow") {
		envmap[sym].type = ProcedureType;
		return true;
	}
	else {
		if (envmap.find(sym) == envmap.end()) {
			std::cout << "Duplicate Symbol not allowed" << std::endl;
			return false;
		}
		else {
			envmap[sym].type = ExpressionType; //Expression Symbols (a, pi, anything else)
			return true;
		}
		return false;
	}
}
*/
