#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

// system includes
#include <string>
#include <istream>


// module includes
#include "expression.hpp"
#include "environment.hpp"
#include "tokenize.hpp"

// Interpreter has
// Environment, which starts at a default
// parse method, builds an internal AST
// eval method, updates Environment, returns last result
class Interpreter{
public:
/*
* The parse method will call the tokenize method to create the deque object.
* Then after checking for validity, the tree method will get called to create the
* Expression tree object.
*/
  bool parse(std::istream & expression) noexcept;
  Expression eval();

   Interpreter();

   //Atom tree(std::deque<std::string> &dequetoken,  Atom& a, bool &state, Expression *p);

   /*
   * A recursive method that transfers the deque made from tokenize to the Expression ast private object.
   * The parameters include the deque, an expression pointer for traversal through the tree, and booleans
   * to meet end conditions.
   * This method gets called in parse.
   */
   Expression tree(std::deque<std::string>& dequetoken, Expression* e, bool& state, bool& start, int& ucount);
   //Expression getExpression(Expression &final, Expression* e, bool &done); 

private:
  Environment env; //how do I use the getExpression method? How do I pass vector<Atom> args? how to call the function pointer 
  Expression ast;
  std::vector <std::string> val;
};


#endif
