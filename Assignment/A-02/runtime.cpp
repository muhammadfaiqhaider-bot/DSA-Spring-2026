#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"
#include "runtime.h"
using namespace std;



int stack_size(string inp)
{
	int i = 0;
	int s = 0;

	while (inp[i] != ' ')
	{
		i++;
	}

	i++;

	while (inp[i] != ' ')
	{
		i++;
	}

	i++;

	while (inp[i] != '\0')
	{
		s = s * 10 + (inp[i] - '0');
		i++;
	}
	return s;
}


int requested_memory(string inp)
{
	int x = 0;
	int i = 0;
	string memo = "";

	while (i < inp.length() && inp[i] != '\n')
	{
		if (inp[i] == '}')
		{

			int j = i + 1;
			while (j < inp.length() && inp[j] != '\n')
			{
				memo += inp[j];
				j++;
			}
			i = j;
		}
		i++;
	}

	x = stoi(memo);
	return x;
}


int memory_allignment(int req)
{
	int x = 0;

	if (req % 4 == 0)
		req--;

	x = req / 4;

	return (x * 4) + 4;
}


int recursion_count(string inp)
{
	int i = 0;
	string rec = "";

	while (i < inp.length() && inp[i] != '(')
	{
		i++;
	}

	i++;

	while (i < inp.length() && inp[i] != ')')
	{
		rec += inp[i];
		i++;
	}

	if (rec.length() == 0)
		return 1;

	return evaluator(infix_to_postix(rec));
}


void store_info_of_function_defi(Function* funcs, int n, string inp)
{
	int i = 0;

	for (int z = 0; z < n; z++)
	{
		int line_end = i;

		while (line_end < inp.length() && inp[line_end] != '\n')
			line_end++;

		string line = inp.substr(i, line_end - i);

		funcs[z].name = get_func_definition_name(line);
		funcs[z].recursion = recursion_count(line);
		funcs[z].memory = memory_allignment(requested_memory(line));
		funcs[z].nested = nested_func_collector(line);

		funcs[z].nested_count = 0;

		while (funcs[z].nested[funcs[z].nested_count].length() != 0)
		{
			funcs[z].nested_count++;
		}

		i = line_end + 1;
	}
}





