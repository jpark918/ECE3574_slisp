#include "expression.hpp"


// system includes
#include <sstream>
#include <cmath>
#include <limits>
#include <cctype>
#include <tuple>

//Jihoon added
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
	this->head.value.point_value = Point();
	this->head.value.line_value = Line();
	this->head.value.arc_value = Arc();
}

//Construct an Expression with a single Number atom with value
Expression::Expression(double num) {
	// TODO: implement this function
	  //num must be a double floating point value  (do I need to even check for this?)
	this->head.type = NumberType;
	this->head.value.num_value = num;
	this->head.value.bool_value = Boolean();
	this->head.value.sym_value = Symbol();
	this->head.value.point_value = Point();
	this->head.value.line_value = Line();
	this->head.value.arc_value = Arc();
}

//Construct an Expression with a single Symbol atom with value
Expression::Expression(const std::string& sym) {
	// TODO: implement this function
	//symbol can be any string with no white space, can't parse as a number, not beginning with a numerical digit
	bool whitespace = false;
	this->head.value.bool_value = Boolean();
	this->head.value.num_value = Number();
	this->head.value.point_value = Point();
	this->head.value.line_value = Line();
	this->head.value.arc_value = Arc();
	if (sym == "pi") {
		this->head.type = NumberType;
		this->head.value.num_value = atan2(0, -1);
	}
	else if (sym[0] < 48 || sym[0] > 57) {
		std::cout << sym << " not beginning with a numerical digit" << std::endl;
		for (unsigned int i = 0; i < sym.size(); i++) {
			if (sym[i] == 32) {
				//if it is whitespace (it isn't allowed)
				whitespace = true;
				this->head.type = NoneType;
				break;
			}
		}
		if (!whitespace) {
			this->head.type = SymbolType;
			this->head.value.sym_value = sym;
		}
		else {
			this->head.type = NoneType;
		}
	}
	else {
		//began with a numerical digit.
		this->head.type = NoneType;
	}
}
//Construct an Expression with a single Point atom with value
Expression::Expression(std::tuple<double, double> value) {
	// TODO: implement this function
	this->head.type = PointType;
	this->head.value.point_value.x = std::get<0>(value);
	this->head.value.point_value.y = std::get<1>(value);

}
//Construct an Expression with a single Line atom with starting
//point start and ending point end
Expression::Expression(std::tuple<double, double> start,
	std::tuple<double, double> end) {
	// TODO: implement this function
	this->head.type = LineType;
	this->head.value.line_value.first.x = std::get<0>(start);
	this->head.value.line_value.first.y = std::get<1>(start);

	this->head.value.line_value.second.x = std::get<0>(end);
	this->head.value.line_value.second.y = std::get<1>(end);
}

// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians
Expression::Expression(std::tuple<double, double> center,
	std::tuple<double, double> start,
	double angle) {
	// TODO: implement this function
	this->head.type = ArcType;
	this->head.value.arc_value.center.x = std::get<0>(center);
	this->head.value.arc_value.center.y = std::get<1>(center);

	this->head.value.arc_value.start.x = std::get<0>(start);
	this->head.value.arc_value.start.y = std::get<1>(start);
	this->head.value.arc_value.span = angle;
}

//Equality operator for two Expressions, two expressions are equal if they have the same 
//type, atom value, and number of arguments
bool Expression::operator==(const Expression& exp) const noexcept {
	// TODO: implement this function
	if (this->head.type == exp.head.type) {
		bool check = false;
		if ((fabs(this->head.value.point_value.x - exp.head.value.point_value.x) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.point_value.y - exp.head.value.point_value.y) < std::numeric_limits<double>::epsilon()) &&
			 exp.head.type == PointType ) {
			check = true;
		}
		else if ((fabs(this->head.value.line_value.first.x - exp.head.value.line_value.first.x) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.line_value.first.y - exp.head.value.line_value.first.y) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.line_value.second.x - exp.head.value.line_value.second.x) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.line_value.second.y - exp.head.value.line_value.second.y) < std::numeric_limits<double>::epsilon()) &&
			exp.head.type == LineType) {
			check = true;
		}
		else if ((fabs(this->head.value.arc_value.center.x - exp.head.value.arc_value.center.x) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.arc_value.center.y - exp.head.value.arc_value.center.y) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.arc_value.start.x - exp.head.value.arc_value.start.x) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.arc_value.start.y - exp.head.value.arc_value.start.y) < std::numeric_limits<double>::epsilon())
			&& (fabs(this->head.value.arc_value.span - exp.head.value.arc_value.span) < std::numeric_limits<double>::epsilon()) &&
			exp.head.type == ArcType) {
			check = true;
		} 
		else if (this->head.value.bool_value == exp.head.value.bool_value && this->head.value.num_value == exp.head.value.num_value
			&& this->head.value.sym_value == exp.head.value.sym_value) {
			check = true;
		}
		else if ((fabs(this->head.value.num_value - exp.head.value.num_value) < std::numeric_limits<double>::epsilon()) &&
			(fabs(this->head.value.num_value - exp.head.value.num_value) < std::numeric_limits<double>::epsilon()) && exp.head.type == NumberType) {
			check = true;
		}
		if (check) {
			return true;
		}
	}
		return false;
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
	if (token == "True") {
		atom.value.bool_value = true;
		atom.type = BooleanType;
	}
	else if (token == "False") {
		atom.value.bool_value = false;
		atom.type = BooleanType;
	}
	else if (token[0] == 45 || (token[0] > 47 && token[0] < 58) || (token[1] > 47 && token[1] < 58) || (token[0] == 43 && token[1] > 47 && token[1] < 58)) { //check if negative symbol or a number (ascii)
		char* end = nullptr;
		double numcheck = strtod(token.c_str(), &end);

		if (token[0] == 45 && token.size() == 1) { //negative only
			atom.type = SymbolType;
			atom.value.sym_value = "-";
		}
		else if (end != token.c_str() && *end == '\0' && numcheck != HUGE_VAL) {
			atom.type = NumberType;
			atom.value.num_value = numcheck;
		}
		else {
			return end != token.c_str() && *end == '\0' && numcheck != HUGE_VAL; //how to verify a string is valid double 
		}
	}
	else if (token == "pi") {  //technically a symbol but will be a number type
		atom.type = NumberType;
		atom.value.num_value = atan2(0, -1);
	}
	else if (token[0] < 48 || token[0] > 57) { //checking for symbol
		return symcheck(token, whitespace, atom);
	}
	else {
		return false;
	}
	return true;
}
 
bool symcheck(const std::string& token, bool& whitespace, Atom& atom) {
	if (token == "true" || token == "false") {
		return false;
	}
	for (unsigned int i = 0; i < token.size(); i++) {
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
	}
	else {
		return false;
	}
	return true;
}