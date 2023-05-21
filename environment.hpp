#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// system includes
#include <map>

// module includes
#include "expression.hpp"
//#include "interpreter.hpp" causes an error for private member 

class Environment{
public:
  Environment();
  //Expression trueenv(Expression a, Expression b);

  /*
* This method will take the ast made from parse and will determine the Expression
* from a given string with procedures. This method gets called in Interpreter::eval()
* The method will recursively find the final expression.
* The parameters include: the Expression result which travels throughout the recursions, Expression pointer for recursive traversal,
* Expression pointer that always points to the root/head, a boolean for end condition, a Expression pointer that will remember where the parent 'node' is,
* a vector of strings that will add procedures and expressions to the envmap, and 3 booleans that are required for some implementations.
*/
  Expression getExpression(Expression & procresult, Expression* &e, Expression* top, bool& done, Expression* cookiecrumb, std::vector<std::string>& val, bool& operated, bool& checkhead, bool& iflast);
  //This is used in interpreter::eval() in order to confirm a procedure symbol
  bool getProcedure(Symbol sym);

 // void setExpression(Expression e, Symbol sym);
  //void pushtoEnvmap(std::vector<Expression>& saveval, std::vector<std::string>& savevar, std::vector<std::string>& val);
 // bool getEnvType(Symbol sym);
    /*
  void andmap(const Symbol sym); //1
  void ormap(const Symbol sym);
  bool lessmap(const Symbol sym);
  bool lessequalmap(const Symbol sym);
  bool notmap(const Symbol sym);
  bool greatermap(const Symbol sym);
  bool greaterequalmap(const Symbol sym);
  bool equalmap(const Symbol sym);
  void addmap(const Symbol sym);
  void submap(const Symbol sym);
  void negmap(const Symbol sym);
  void prodmap(const Symbol sym);
  void divmap(const Symbol sym);
  void logmap(const Symbol sym);
  void powmap(const Symbol sym); //15
  */

private:
  // Environment is a mapping from symbols to expressions or procedures
  enum EnvResultType {ExpressionType, ProcedureType};
  struct EnvResult{
    EnvResultType type;
    Expression exp;
    Procedure proc;
  };
 
  std::map<Symbol,EnvResult> envmap;
};

#endif
