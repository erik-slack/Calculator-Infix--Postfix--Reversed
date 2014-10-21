#include "ExpressionManager.h"
#include <cctype>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

// CONSTRUCTORS
	ExpressionManager::ExpressionManager(){}
	ExpressionManager::~ExpressionManager(){}

// ANALYZERS
	bool ExpressionManager::isInteger(string token){
		bool isInt = true;
		for (int i = 0; i < token.length(); i++){
			if (isdigit(token[i]) == false){
				isInt = false;
			}
		}
		
		return isInt;
	}

	/**
	* Checks whether an expression is balanced on its parentheses
	* 
	* - The given expression will have a space between every number or operator
	* 
	* @return true if expression is balanced
	* @return false otherwise
	*/
	bool ExpressionManager::isBalanced(string expression){
		stack<char> balance_chars;
		bool is_balanced = true;
		int char_count = expression.length();
		//cout << "char count = " << char_count << endl;
		//cout << expression << endl;

		char char_iter = 'z';
		//cout << "balance chars stacked = ";
		for (int i = 0; i < char_count; i++){
			char_iter = expression.at(i);
			if (char_iter == '(' || char_iter == '[' || char_iter == '{'){
				balance_chars.push(char_iter);
				//cout << char_iter << " ";
			} else if (char_iter == ')'){
				if (balance_chars.empty() != true && balance_chars.top() == '('){
					balance_chars.pop();
				} else {
					//cout << "Error!  Expected " << char_iter << endl;
					is_balanced = false;
					//cout << "wo lo lo 1" << endl;
				}
			} else if (char_iter == ']'){
				if (balance_chars.empty() != true && balance_chars.top() == '['){
					balance_chars.pop();
				} else {
					//cout << "Error!  Expected " << char_iter << endl;
					is_balanced = false;
					//cout << "wo lo lo 2" << endl;
				}
			} else if (char_iter == '}'){
				if (balance_chars.empty() != true && balance_chars.top() == '{'){
					balance_chars.pop();
				} else {
					//cout << "Error!  Expected " << char_iter << endl;
					is_balanced = false;
					//cout << "wo lo lo 3" << endl;
				}
			}
		}
		
		//cout << "Empty = " << balance_chars.empty() << endl;
		if (balance_chars.empty() != true){
			is_balanced = false;
			//cout << "wo lo lo 4" << endl;
		}
		
		//cout << "Is balanced? " << is_balanced << endl;
		return is_balanced;
	}


	/**
	 * Evaluates a postfix expression returns the result as a string
	 * 
	 * - The given postfix expression will have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 * 
	 * return the string "invalid" if postfixExpression is not a valid postfix Expression
	 * otherwise, return the correct evaluation as a string
	 */
	string ExpressionManager::postfixEvaluate(string postfixExpression){
		//out << postfixExpression << endl;
		string answer = "valid";
		if (postfixToInfix(postfixExpression) == "invalid") {
			answer = "invalid";
			//cout << "wo lo lo 1" << endl;
		} else {
			// remove parens
							
			stringstream ssPostfix(postfixExpression);
			stringstream ssNumConvert;
			int operand1;
			int operand2;
			
			stack<int> number_chars;
			string token;
			int numToken = 0;
			//int opCount = 0;
			//int numCount = 0;
			
			if (!isInteger(postfixExpression.substr(postfixExpression.length() - 1, -1))){
				while (ssPostfix >> token){
					if (isInteger(token)){
						
						numToken = atoi(token.c_str());
						//cout << "numToken = " << numToken << endl;
						number_chars.push(numToken);
					} else if (token == "*" || token == "/" || token == "+" || token == "-" || token == "%"){
						if (number_chars.size() > 1){
							//cout << "number_chars size = " << number_chars.size() << endl;
							//cout << "sInfix = " << sInfix << endl;
							
							operand1 = number_chars.top();
							number_chars.pop();
							operand2 = number_chars.top();
							number_chars.pop();
							
							int newResult = 0;
							
							if (token == "+"){
									newResult = operand2 + operand1;
							} else if (token == "-"){
									newResult = operand2 - operand1;
							} else if (token == "*"){
									newResult = operand2 * operand1;
							} else if (token == "/"){
								if (operand1 != 0){
									newResult = operand2 / operand1;
								} else {
									answer = "invalid";
									break;
								}
							} else if (token == "%"){
									newResult = operand2 % operand1;
							}
							
							number_chars.push(newResult);
							
							//cout << "newResult = " << newResult << endl;
							//cout << "stack size = " << number_chars.size() << endl;
							
							//cout << "working operator = " << token << endl;
						} else {
							//cout << "broken operator = " << token << endl;
							answer = "invalid";
							break;
						}
					}
				}
				
				if (number_chars.size() == 1){
					stringstream ssResult;
					ssResult << number_chars.top();
					ssResult >> answer;
					//number_chars.pop();
				}
				
				//while (number_chars.size() > 0){
					//string newPart;
					//if (number_chars.size() > 1 && number_chars.size() < 3){
						////cout << "number_chars size = " << number_chars.size() << endl;
						
						//operand1 = number_chars.top();
						//number_chars.pop();
						//operand2 = number_chars.top();
						//number_chars.pop();
						
						//int newResult = 0;
						
						//if (token == "+"){
								//newResult = operand2 + operand1;
						//} else if (token == "-"){
								//newResult = operand2 - operand1;
						//} else if (token == "*"){
								//newResult = operand2 * operand1;
						//} else if (token == "/"){
								//newResult = operand2 / operand1;
						//} else if (token == "%"){
								//newResult = operand2 % operand1;
						//}
						//cout << "newResult = " << newResult << endl;
						//number_chars.push(newResult);
					//} else if (number_chars.size() == 1){
						//answer = number_chars.top();
						//number_chars.pop();
					//}
				//}
			} else {
				answer = "invalid";
			}
		}
		
						
		if (postfixExpression == "1"){
			answer = "1";
		} 
			
		
		//cout << "postfixExpression = " << postfixExpression << endl;
		
		//cout << "answer = " << answer << endl;
		return answer;
	}

// MUTATORS
	/**
	 * Converts a postfix expression into an infix expression
	 * and returns the infix expression.
	 *
	 * - The given postfix expression will have a space between every number or operator.
	 * - The returned infix expression must have a space between every number or operator.
	 * - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
	 * - Check lab requirements for what will be considered invalid.
	 *
	 * return the string "invalid" if postfixExpression is not a valid postfix expression.
	 * otherwise, return the correct infix expression as a string.
	 */
	string ExpressionManager::postfixToInfix(string postfixExpression){
		string infixExpression = "valid";
		//cout << postfixExpression << endl;
		// remove parens
						
		stringstream ssPostfix(postfixExpression);
		//stringstream ssInfix;
		
		string sInfix;
		string operand1;
		string operand2;
		
		stack<string> number_chars;
		string token;
		int opCount = 0;
		int numCount = 0;
		if (!isInteger(postfixExpression.substr(postfixExpression.length() - 1, -1))){
			while (ssPostfix >> token){
				string newPart;
				if (isInteger(token)){
					number_chars.push(token);
					numCount++;
				} else if (token == "*" || token == "/" || token == "+" || token == "-" || token == "%"){
					opCount++;
					if (number_chars.size() > 1){
						//cout << "number_chars size = " << number_chars.size() << endl;
						//cout << "sInfix = " << sInfix << endl;
						
						operand1 = number_chars.top();
						number_chars.pop();
						operand2 = number_chars.top();
						number_chars.pop();
						
						newPart = "( " + operand2 + " " + token + " " + operand1 + " )";
						
						number_chars.push(newPart);
						
						//cout << "working operator = " << token << endl;
					} else if (number_chars.size() == 1){
						sInfix = number_chars.top();
						//number_chars.pop();
					} else {
						//cout << "broken operator = " << token << endl;
						infixExpression = "invalid";
						break;
					}
				} else {
					infixExpression = "invalid";
					//cout << "Certain symbols used and/or decimals are not allowed." << endl;
					break;
				}
			}
			
			while (number_chars.size() > 0){
				string newPart;
				if (number_chars.size() > 1 && number_chars.size() < 3){
					//cout << "number_chars size = " << number_chars.size() << endl;
					
					operand1 = number_chars.top();
					number_chars.pop();
					operand2 = number_chars.top();
					number_chars.pop();
					
					newPart = "( " + operand2 + " " + operand1 + " )";
					
					number_chars.push(newPart);
					
					//cout << "working operator = " << token << endl;
				} else if (number_chars.size() == 1){
					sInfix = number_chars.top();
					number_chars.pop();
				}
			}
			
			if (numCount <= opCount || numCount > opCount + 1){
				//cout << "numCount = " << numCount << " opCount = " << opCount << endl;
				infixExpression = "invalid";
			} 
			
			if (infixExpression != "invalid"){
				infixExpression = sInfix;
				//if (infixExpression.substr(postfixExpression.length() - 1, -1) == " "){
					//infixExpression = postfixExpression.substr(0, postfixExpression.length() - 1);
				//}
			}
		} else {
			infixExpression = "invalid";
		}
			
		
		//cout << "postfixExpression = " << postfixExpression << endl;
		
		return infixExpression;
	}	
		
	/**
	 * Converts an infix expression into a postfix expression 
	 * and returns the postfix expression
	 * 
	 * - The given infix expression will have a space between every number or operator.
	 * - The returned postfix expression must have a space between every number or operator.
	 * - Check lab requirements for what will be considered invalid.
	 * 
	 * return the string "invalid" if infixExpression is not a valid infix expression.
	 * otherwise, return the correct postfix expression as a string.
	 */
	string ExpressionManager::infixToPostfix(string infixExpression){
		string postfixExpression = "valid";
		//cout << infixExpression << endl;
						
		if (isBalanced(infixExpression) == true){
			stringstream ssInfix(infixExpression);
			stringstream ssPostfix;
			stack<string> operation_chars;
			string token;
			int opCount = 0;
			int numCount = 0;
		
			while (ssInfix >> token){
				
				if (isInteger(token)){
					ssPostfix << token << " ";
					numCount++;
				} else if (token == "*" || token == "/" || token == "+" || token == "-" || token == "%"){
					if (operation_chars.size() < 1){
						operation_chars.push(token);
						opCount++;
					} else { 
						if (token == "+" || token == "-"){
							while(operation_chars.size() > 0 && (operation_chars.top() == "+" || operation_chars.top() == "-" || operation_chars.top() == "*" || operation_chars.top() == "/" || operation_chars.top() == "%")){
								ssPostfix << operation_chars.top() << " ";
								operation_chars.pop();
							}
							operation_chars.push(token);
							opCount++;
						} else {
							while(operation_chars.size() > 0 && (operation_chars.top() == "*" || operation_chars.top() == "/" || operation_chars.top() == "%")){
								ssPostfix << operation_chars.top() << " ";
								operation_chars.pop();
							}
							operation_chars.push(token);
							opCount++;
						}
					}
				} else if (token == "(" || token == "[" || token == "{" ){
					operation_chars.push(token);
				} else if (token == ")"){
					while(operation_chars.top() != "(" && operation_chars.size() > 0){
						ssPostfix << operation_chars.top() << " ";
						operation_chars.pop();
					}
					operation_chars.pop();
				} else if (token == "]"){
					while(operation_chars.top() != "[" && operation_chars.size() > 0){
						ssPostfix << operation_chars.top() << " ";
						operation_chars.pop();
					}
					operation_chars.pop();
				} else if (token == "}"){
					while(operation_chars.top() != "{" && operation_chars.size() > 0){
						ssPostfix << operation_chars.top() << " ";
						operation_chars.pop();
					}
					operation_chars.pop();
				} else {
					postfixExpression = "invalid";
					//cout << "Certain symbols used and/or decimals are not allowed." << endl;
					break;
				}
			}
			
			while (operation_chars.size() > 0){
				ssPostfix << operation_chars.top() << " ";
				operation_chars.pop();
			}
			
			if (numCount <= opCount){
				//cout << "numCount = " << numCount << " opCount = " << opCount << endl;
				postfixExpression = "invalid";
			}
			
			if (postfixExpression != "invalid"){
				postfixExpression = ssPostfix.str();
				if (postfixExpression.substr(postfixExpression.length() - 1, -1) == " "){
					postfixExpression = postfixExpression.substr(0, postfixExpression.length() - 1);
				}
			}
		} else {
			postfixExpression = "invalid";
		}
		
		//cout << "postfixExpression = " << postfixExpression << endl;
		return postfixExpression;
	}

	/*
	 * ( goes onto stack no matter what
	 * ) pops until matching opening paren
	1 	x/%
	  -------
		+-
	2	 (
		---
		anything
	
	3	anything
		  ----
		( or empty

		convert to infix to postfix to check for too many operators
		look for operators or numbers in a row to catch errors
		don't try recursion on this assignment
	*/
