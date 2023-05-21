#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

// system includes
#include <map>

// module includes
#include "expression.hpp"
//#include "interpreter.hpp" causes an error for private member 

class Environment {
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
    Expression getExpression(Expression& procresult, Expression*& e, Expression* top, bool& done, Expression* cookiecrumb, std::vector<std::string>& val, bool& operated, bool& checkhead, bool& iflast, std::vector<Expression>*drew);
    //This is used in interpreter::eval() in order to confirm a procedure symbol
    bool getProcedure(Symbol sym);

    void CheckingForRecursion(std::vector<Atom>& store, bool& endoftop, bool& useless,unsigned int& i, Expression& procresult, Expression*& e, Expression* top, bool& done, Expression* cookiecrumb, std::vector<std::string>& val, bool& operated, bool& checkhead, bool& iflast, std::vector<Expression>* drew);
    void CheckAndAddToVector(Expression*& e, unsigned int& i, std::vector<std::string>& val, std::vector<Atom>& store);
    bool CheckToEnd(std::vector<Atom>& store, bool& endoftop, bool& useless,  unsigned int& j, Expression& procresult, Expression*& e, Expression* top, std::vector<std::string>& val);
    bool ProcedureAndSet(std::vector<Atom>& store, Expression& procresult, Expression*& e, Expression* top, bool& done, Expression* cookiecrumb, std::vector<std::string>& val, bool& operated, bool& iflast, std::vector<Expression>* drew);
        // void setExpression(Expression e, Symbol sym);
     //void pushtoEnvmap(std::vector<Expression>& saveval, std::vector<std::string>& savevar, std::vector<std::string>& val);
    // bool getEnvType(Symbol sym);

private:
    // Environment is a mapping from symbols to expressions or procedures
    enum EnvResultType { ExpressionType, ProcedureType };
    struct EnvResult {
        EnvResultType type;
        Expression exp;
        Procedure proc;
    };

    std::map<Symbol, EnvResult> envmap;
};

#endif
