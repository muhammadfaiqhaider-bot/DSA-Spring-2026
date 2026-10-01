#include <iostream>
#include <string>
#include"inputvalidator.h"
#include"evaluator.h"
#include"postfix.h"
#include"runtime.h"


using namespace std;





string value_extraction(string inp)
{
	int i = 1;
	string value;

	while (inp[i] != '\0')
	{
		if (inp[i - 1] == '(')
		{
			int j = i;
			while (inp[j] != ')')
			{
				value += inp[j];
				j++;
			}
			return value;
		}
		i++;
	}
	return "";
}


int is_operand(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
		return 0;
	else
		return 1;
}
int precedence(char ch)
{
	if (ch == '*' || ch == '/')
		return 2;
	if (ch == '+' || ch == '-')
		return 1;

	return 0;
}


string infix_to_postix(string infix)
{
	string postfix;
	Stack st(infix.length());
	int i = 0;

	while (i < infix.length())
	{
		if (infix[i] == '(')
		{
			st.push(infix[i]);
		}
		else if (infix[i] == ')')
		{
			while (st.peek() != '(')
			{
				postfix += st.pop();
				postfix += " ";
			}

			st.pop();
		}
		else if (infix[i] >= '0' && infix[i] <= '9')
		{
			while (i < infix.length() && infix[i] >= '0' && infix[i] <= '9')
			{
				postfix += infix[i];
				i++;
			}

			postfix += " ";
			continue;
		}
		else
		{
			if (st.is_empty())
			{
				st.push(infix[i]);
			}
			else if (precedence(infix[i]) > precedence(st.peek()))
			{
				st.push(infix[i]);
			}
			else
			{
				postfix += st.pop();
				postfix += " ";
				st.push(infix[i]);
			}
		}

		i++;
	}

	while (!st.is_empty())
	{
		postfix += st.pop();
		postfix += " ";
	}

	return postfix;
}

