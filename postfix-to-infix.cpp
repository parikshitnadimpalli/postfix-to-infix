#include "methods.h"
using namespace std;

int main()
{
	cout << "\t\t\t|--------Infix to Prefix conversion using a stack--------|" << endl << endl;
	cout << "\t\tNOTE: You can use any type of brackets. Just be sure to properly balance them in your expression :)" << endl;

	string msg, postfix, infix;

	cout << endl << "Enter the postfix expression to be converted: ";
	getline(cin, postfix);
	infix = postfixToInfix(postfix);

	msg = infix == " " || infix == postfix ? "Invalid infix expression entered!" : infix; // Checking to see if user input is valid or not
	cout << endl << "The converted expression is:\n" << msg;

	return 0;
}