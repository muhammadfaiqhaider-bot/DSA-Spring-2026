#include <iostream>
#include <string>
#include "evaluator.h"
#include "inputvalidator.h"
#include "postfix.h"
#include "runtime.h"

using namespace std;



int evaluator(string postfix)
{
	int res = 0;
	int i = 0;

	Int_Stack st(postfix.length());

	while (i < postfix.length())
	{
		string op = "";

		while (i < postfix.length() && postfix[i] != ' ')
		{
			op += postfix[i];
			i++;
		}

		if (op.length() != 0)
		{
			if (op == "+")
			{
				int op2 = st.pop();
				int op1 = st.pop();
				st.push(op1 + op2);
			}
			else if (op == "-")
			{
				int op2 = st.pop();
				int op1 = st.pop();
				st.push(op1 - op2);
			}
			else if (op == "*")
			{
				int op2 = st.pop();
				int op1 = st.pop();
				st.push(op1 * op2);
			}
			else if (op == "/")
			{
				int op2 = st.pop();
				int op1 = st.pop();
				st.push(op1 / op2);
			}
			else
			{
				int x = stoi(op);
				st.push(x);
			}
		}

		i++;
	}

	res = st.pop();

	return res;
}
