#include "ExpressionManagerInterface.h"
#include <stack>
#include <sstream>

using namespace std;
//g++ *.cpp -o calculator

class ExpressionManager : public ExpressionManagerInterface 
{

public:
	// CONSTRUCTORS
	ExpressionManager();
	~ExpressionManager();

	// ANALYZERS
	bool isInteger(string token);
	bool isBalanced(string expression);
	string postfixEvaluate(string postfixExpression);

	// MUTATORS
	string postfixToInfix(string postfixExpression);
	string infixToPostfix(string infixExpression);

};
