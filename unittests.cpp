#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

// TODO: add your unit tests here

#include "interpreter_semantic_error.hpp"
#include <string>
#include "expression.hpp"
#include "interpreter.hpp"
#include "environment.hpp"
#include "tokenize.hpp"
#include <iostream>

static Expression run(const std::string& program) {

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);
	if (!ok) {
		std::cerr << "[GRADER] Failed to parse: " << program << std::endl;
	}
	REQUIRE(ok == true);

	Expression result;
	REQUIRE_NOTHROW(result = interp.eval());

	return result;
}

//Testing the token_to_atom method from expression.cpp
TEST_CASE("Test Double", "[types]") {

	Atom a;
	std::string token = "True";

	token = "19";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == 19);

	token = "-120";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == -120);
	
	token = "1e-4";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == 1e-4);

	token = "+1e+2";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == 1e+2);

	token = "-3e+5";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == -3e+5);
}
//testing the deque from tokenize.cpp
TEST_CASE("tokenize", "[types]") {
	std::string program = "(begin (if (< a b) a b))";
	std::istringstream iss(program);

	TokenSequenceType tokens = tokenize(iss);

	REQUIRE(tokens.size() == 13);
	REQUIRE(tokens[0] == "(");
	REQUIRE(tokens[1] == "begin");
	REQUIRE(tokens[2] == "(");
	REQUIRE(tokens[3] == "if");
	REQUIRE(tokens[4] == "(");
	REQUIRE(tokens[5] == "<");
	REQUIRE(tokens[6] == "a");
	REQUIRE(tokens[7] == "b");
	REQUIRE(tokens[8] == ")");
	REQUIRE(tokens[9] == "a");
	REQUIRE(tokens[10] == "b");
	REQUIRE(tokens[11] == ")");
	REQUIRE(tokens[12] == ")");
}
//Testing token_to_atom with varying strings
TEST_CASE("Test Type Inference student ver.", "[types]") {

	Atom a;

	std::string token = "True3da";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == SymbolType);
	REQUIRE(a.value.sym_value == "True3da");

	token = "3False";
	REQUIRE(!token_to_atom(token, a));

	token = "1235654734523";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == 1235654734523);

	token = "-1123123e+5";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == NumberType);
	REQUIRE(a.value.num_value == -1123123e+5);

	token = "var777";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == SymbolType);
	REQUIRE(a.value.sym_value == "var777");

	token = "1abc";
	REQUIRE(!token_to_atom(token, a));

	token = "TrueFalse";
	REQUIRE(token_to_atom(token, a));
	REQUIRE(a.type == SymbolType);
	REQUIRE(a.value.sym_value == token);

}
//testing parse from interpreter.cpp
TEST_CASE("Tree building simulator", "[types]") {

	std::string program = "(begin (if (< a b) a b))"; //a and b are defined but similar to another failing test case

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok == true);
}
//testing another parse from interpreter.cpp
TEST_CASE("Tree building simulator2", "[interpreter]") {

	std::string program = "(begin (if (< 1 2) (- 5 6) True))"; //a and b are defined but similar to another failing test case

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok == true);
}
//testing another parse from interpreter.cpp
TEST_CASE("Tree building simulator3", "[interpreter]") {

	std::string program = "(begin) (define r 10) (* pi) (* r r)))";

	std::istringstream iss(program);

	Interpreter interp;

	bool ok = interp.parse(iss);

	REQUIRE(ok == false);
}
//testing both parse and evaluate from interpreter.cpp
TEST_CASE("Solve tree", "[interpreter]")
{
	std::string program = "(begin (define answer (- 50 11)) (answer))";
	Expression result = run(program);
	REQUIRE(result == Expression(39.));
}
//testing both parse and evaluate from interpreter.cpp
TEST_CASE("Solve tree 2", "[interpreter]") {

	std::string program = "(< 500 1000)";
	Expression result = run(program);
	REQUIRE(result == Expression(true));
}
//testing both parse and evaluate from interpreter.cpp
TEST_CASE("Solve tree 3", "[interpreter]") {

	std::string program = "(- 3 6 12)";
	Interpreter interp;
	std::istringstream iss(program);
	bool ok = interp.parse(iss);
	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
}
//testing both parse and evaluate from interpreter.cpp
TEST_CASE("Solve tree 4", "[interpreter]") {

	std::string program = "( + 1 (- 3) 12)";
	Expression result = run(program);
	//std::cout << result;
	REQUIRE(result == Expression(10.));
}
//testing both parse and evaluate from interpreter.cpp
TEST_CASE("Solve tree 5", "[interpreter]") {
	
	std::string program = "(- a b)";
	Interpreter interp;
	std::istringstream iss(program);
	bool ok = interp.parse(iss);
	//std::cout << interp.eval();
	REQUIRE_THROWS_AS(interp.eval(), InterpreterSemanticError);
}
//testing what returns out to the command prompt (for booleans)
TEST_CASE("test Defines", "[interpreter]") {

	std::string program = "(define a True)";
	Expression result = run(program);
	//std::cout << result << std::endl;
	REQUIRE(result == Expression(true));
}