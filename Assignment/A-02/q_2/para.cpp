
#include <iostream>
#include "bracket.h"
using namespace std;


static char expected_bracket(char ch)
{
	if (ch == '(')
		return ')';
	else if (ch == '{')
		return '}';
	else if (ch == '[')
		return ']';

	return '\0';
}

static bool valid_paranthesis(string inp)
{
	bracketStack st(10);
	int i = 0;
	int j = 1;
	int line = 1;
	int max_depth = 0;
	int match_pairs = 0;

	while (i < inp.length())
	{
		if (inp[i] == '\n')
		{
			j = 1;
			line++;
			i++;
			continue;
		}

		if (inp[i] == '(' || inp[i] == '{' || inp[i] == '[')
		{
			st.push(inp[i], line, j);
			if (st.top + 1 > max_depth)
				max_depth = st.top + 1;
		}


		else if (inp[i] == ')' || inp[i] == '}' || inp[i] == ']')
		{
			if (st.is_empty())
			{
				cout << "Invalid " << endl;
				cout << "error bcz at line " << line << " and column " << j
					<< " i found " << inp[i] << " but there was no opening bracket" << endl;
				return false;
			}

			if ((st.peek() == '(' && inp[i] == ')') ||
				(st.peek() == '{' && inp[i] == '}') ||
				(st.peek() == '[' && inp[i] == ']'))
			{
				st.pop();
				match_pairs++;
			}
			else
			{
				cout << "Invalid " << endl;
				cout << "error bcz at line " << line << " and column " << j
					<< " i found " << inp[i]
					<< " but i expect " << expected_bracket(st.peek()) << endl;
				return false;
			}
		}

        i++;
		j++;
	}

	if (!st.is_empty())
	{
		bracket temp = st.peek_frame();

		cout << "Invalid " << endl;
		cout << "Error: '" << temp.bracket
			<< "' opened at Line " << temp.line
			<< ", Column " << temp.column
			<< " was never closed" << endl;

		return false;
	}

	cout << "Valid " << endl;
	cout << "Maximum Nesting Depth: " << max_depth << endl;
	cout << "Total Matched Pairs: " << match_pairs << endl;

	return true;
}
