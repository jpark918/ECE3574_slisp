#include "expression.hpp"

#include <cmath>
#include <limits>
#include <cctype>

// system includes
#include <sstream>

#include <iostream>
#include <string>
#include <cstdlib>
//Construct an Expression with a single Boolean atom with value
Expression::Expression(bool tf) {
	// TODO: implement this function
	this->head.type = BooleanType;
	this->head.value.bool_value = tf; //assign the head's bool_value to the param?
	this->head.value.num_value = Number();
	this->head.value.sym_value = Symbol();
}
//Construct an Expression with a single Number atom with value
Expression::Expression(double num) {
	// TODO: implement this function
	  //num must be a double floating point value  (do I need to even check for this?)
	this->head.type = NumberType;
	this->head.value.num_value = num;
	this->head.value.bool_value = Boolean();
	this->head.value.sym_value = Symbol();
}
//Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string& sym) {
	// TODO: implement this function
	//symbol can be any string with no white space, can't parse as a number, not beginning with a numerical digit
	bool whitespace = false;
	if (sym[0] < 48 || sym[0] > 57) {
		std::cout << sym << " not beginning with a numerical digit" << std::endl;
		for (int i = 0; i < sym.size(); i++) {
			if (sym[i] == 32) {
				//if it is whitespace (it isn't allowed)
				whitespace = true;
				break;
			}
		}
		if (!whitespace) {
			this->head.type = SymbolType;
			this->head.value.sym_value = sym;
			//----

		}
	}
	else if (sym == "pi") {
		this->head.type = NumberType;
		this->head.value.num_value = atan2(0, -1);
	}
	else {
		//began with a numerical digit.
		this->head.type = NoneType;
	}
}
//Equality operator for two Expressions, two expressions are equal if they have the same 
//type, atom value, and number of arguments
bool Expression::operator==(const Expression& exp) const noexcept {
	// TODO: implement this function
	if (this->head.type == exp.head.type) {

		if (this->head.value.bool_value == exp.head.value.bool_value && this->head.value.num_value == exp.head.value.num_value
			&& this->head.value.sym_value == exp.head.value.sym_value) {
			return true;
		}
		return false;

	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& out, const Expression& exp) {
	// TODO: implement this function

	if (exp.head.type != NoneType) {
		Atom a;
		a.value = exp.head.value;
		//if (exp.head.value.sym_value != Symbol()) {
		if (exp.head.type == SymbolType) {
			out << exp.head.value.sym_value;
		}
		// else if (exp.head.value.num_value != Number()) {
		else if (exp.head.type == NumberType) {
			out << exp.head.value.num_value;
		}
		else { //Boolean() is default false
			if (exp.head.value.bool_value) {
				out << "True";
			}
			else {
				out << "False";
			}
			//out << exp.head.value.bool_value;
		}
	}
	/*
	out << exp.head;
	out << " ";*/
	return out;
}
// map a token to an Atom
bool token_to_atom(const std::string& token, Atom& atom) {
	// TODO: implement this function
	// return true if it a token is valid. otherwise, return false.
	Expression e = Expression();
	atom = e.head;
	//double numcheck = std::stod(token);
	bool whitespace = false;
	if (token == "True") { //cannot be "true"
		atom.value.bool_value = true;
		//reset the atom in case the same atom being passed in
		//atom.value.num_value = double();
		//atom.value.sym_value = std::string();
		atom.type = BooleanType;
		return true;
	}
	else if (token == "False") { //cannot be "false" 
		atom.value.bool_value = false;
		//reset the atom in case the same atom being passed in
		//atom.value.num_value = double();
		//atom.value.sym_value = std::string();
		atom.type = BooleanType;
		return true;
	}
	else if (token[0] == 45 || (token[0] > 47 && token[0] < 58) || token[1] > 47 && token[1] < 58 || (token[0] == 43 && token[1] > 47 && token[1] < 58)) { //check if negative symbol or a number (ascii)
		char* end = nullptr;
		double numcheck = strtod(token.c_str(), &end);

		if (token[0] == 45 && token.size() == 1) { //negative only
			atom.type = SymbolType;
			atom.value.sym_value = "-";
			return true;
		}
		if (end != token.c_str() && *end == '\0' && numcheck != HUGE_VAL) {
			atom.type = NumberType;
			atom.value.num_value = numcheck;
			//reset the atom in case the same atom being passed in
			//atom.value.bool_value = bool();
			//atom.value.sym_value = std::string();
			return true;
		}
		else {
			return end != token.c_str() && *end == '\0' && numcheck != HUGE_VAL; //how to verify a string is valid double 
		}
	}
	else if (token == "pi") {  //technically a symbol but will be a number type
		atom.type = NumberType;
		atom.value.num_value = atan2(0, -1);
		//reset the atom in case the same atom being passed in
		//atom.value.bool_value = bool();
		//atom.value.sym_value = std::string();
		return true;
	}
	else if (token[0] < 48 || token[0] > 57) { //checking for symbol
		//std::cout << token << " not beginning with a numerical digit" << std::endl;
		for (int i = 0; i < token.size(); i++) {
			if (token[i] == 32) {
				//if it is whitespace (it isn't allowed)
				whitespace = true;
				return false;
			}
		}
		if (!whitespace) {
			atom.type = SymbolType;
			atom.value.sym_value = token;
			//reset the atom in case the same atom being passed in
			//atom.value.num_value = double();
			//atom.value.bool_value = bool ();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}

}
//ADDED METHODS HERE
/*
typedef Expression ::(*Not)(const std::vector<Atom>& args) {

}
*/

/*
bool Expression::add(const std::vector<Atom>& args) {

}

bool Expression::not(const std::vector<Atom>& args) {

}*/