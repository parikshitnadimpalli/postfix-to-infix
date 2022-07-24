#include "methods.h"
using namespace std;

bool isBalanced(string expr)
{
	stack<char> s;
	char ch;

	for (int i = 0; i < expr.length(); i++)		// Traversing through the string
	{
		if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{')	// If the character is an opening bracket
		{
			s.push(expr[i]);
			continue;
		}

		switch (expr[i])		// If a closing bracket is encountered, the top of the stack is checked to see if it is a valid pair or not
		{
		case ')':
			ch = s.top();
			s.pop();
			if (ch == '{' || ch == '[')
				return false;
			break;
		case '}':
			ch = s.top();
			s.pop();
			if (ch == '(' || ch == '[')
				return false;
			break;
		case ']':
			ch = s.top();
			s.pop();
			if (ch == '(' || ch == '{')
				return false;
			break;
		default:
			break;
		}
	}

	return s.empty();	// After performing all checks, if the stack is empty, then return true. If not, that means there is an extra bracket and return false
}

bool isValid(string expr)
{
	if (!(isBalanced(expr)))	// Returning false if the brackets in the expression are not valid
		return false;

	string s = expr;
	while (s[0] == ' ' || s[0] == '\t')
	{
		s.erase(s.begin());

		if (s.length() == 0 || s.length() == 1 || s.length() == 2) // The expression is valid only if the length is a minimum of 3
			return false;
		if (s[0] == '+' || s[0] == '-' || s[0] == '/' || s[0] == '%' || s[0] == '*' || s[0] == '^') // If the expression starts with an operator
			return false;
	}

	for (int i = 1; i < s.length(); i++)
	{
		if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '%' || s[i] == '*' || s[i] == '^')
		{
			int j = i - 1;								// Checking if character before an operator is also an operator
			while (s[j] == ' ' || s[j] == '\t')
			{
				j--;
			}
			if (s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '%' || s[j] == '*' || s[j] == '^')
				return false;
			else
			{
				j = i + 1;								// Checking if the next character after an operator is a closing bracket or operator
				while (s[j] == ' ' || s[j] == '\t')
				{
					j++;
				}
				if (s[j] == ')' || s[j] == ']' || s[j] == '}' || s[j] == '+' || s[j] == '-' || s[j] == '/' || s[j] == '%' || s[j] == '*' || s[j] == '^')
					return false;
			}

		}
	}

	while (s.length() != 0)
	{
		string::iterator i = s.end();
		char end = *(i - 1);

		if (end == ')' || end == ']' || end == '}' || end == ' ' || end == '\t')	// If the last character is a bracket or space, move back one space
		{
			s.pop_back();
			continue;
		}

		if (end == '+' || end == '-' || end == '/' || end == '%' || end == '*' || end == '^')		// If the last character is an operator, the expression is invalid
			return false;
		else
			return true;
	}
}

string postfixToInfix(string postfix)
{
	if (postfix.length() == 0 || postfix.length() == 1 || postfix.length() == 2)
		return " ";

	string infix;
	stack<string> s;

	for (int i = 0; i < postfix.length(); i++)
	{
		if (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/' && postfix[i] != '%' && postfix[i] != '^' && postfix[i] != ' ' && postfix[i] != '\t')
		{
			string x(1, postfix[i]);
			s.push(x);
		}
		else if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/' || postfix[i] == '%' || postfix[i] == '^')
		{
			if (s.empty())
				return " ";

			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();

			string exp = "(" + op2 + postfix[i] + op1 + ")";
			s.push(exp);
		}
	}

	while (!s.empty())
	{
		infix += s.top();
		s.pop();
	}

	if (!isValid(infix))
		return " ";

	return infix;
}