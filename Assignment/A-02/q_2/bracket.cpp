
#include <iostream>
#include <string>
#include "bracket.h"
using namespace std;


char expected_bracket(char ch)
{
	if (ch == '(')
		return ')';
	else if (ch == '{')
		return '}';
	else if (ch == '[')
		return ']';

	return '\0';
}



bool valid_paranthesis(string inp)
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
		cout << "Error bcz " << temp.bracket
			<< " was opened at line " << temp.line
			<< " and column " << temp.column
			<< " but never closed" << endl;

		return false;
	}

	cout << "Valid" << endl;
	cout << "Maximum Nesting Depth: " << max_depth << endl;
	cout << "Total Matched Pairs: " << match_pairs << endl;
	return true;
}



void analyze_source_code(string inp)
{

	const int original = 0;
	const int str = 1;
	const int charcters = 2;
	const int singlecomment = 3;
	const int multicomment = 4;
	int i = 0;
	
	int sta = original;

	while (inp[i] != '\0')
	{
		if (inp[i] == (char)(34)) // ascii code for " = 34
		{
			sta = str;
			int j = i;
			while (inp[j] != (char)(34))
			{
				j++;
			}
			i = j;
		}
		else if (inp[i] == (char)(39)) // ascci code for ' = 39
		{
			sta = charcters;
			int j = i;
			while (inp[j] != (char)(39))
			{
				j++;
			}
			i = j;
		}
		
		else if (inp[i] == (char)(47) && inp[i + 1] == (char)(47)) // ascci code for / = 47
		{
			sta = singlecomment;
			int j = i;
			while (inp[j] != (char)(47))
			{
				j++;
			}
			i = j;
		}
		else if (inp[i] == (char)(47) && inp[i + 1] == (char)(42)) // ascci code for * = 42
		{
			sta = multicomment;
			int j = i;
			while (inp[j] != (char)(47))
			{
				j++;
			}
			i = j;
		}
		
		else
		{
			sta == original;
		}
		i++;
	}
}



int main()
{
	if (valid_paranthesis("{[()]}"))
	{
		cout << "valid " << endl;
	}
	else
	{
		cout << "Nopsies" << endl;
	}

	return 0;
}

