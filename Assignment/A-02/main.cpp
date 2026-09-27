#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"
#include "runtime.h"

using namespace std;



int main()
{
	string inp = "3 1 28\nfunA(3){funB} 5\nfunB(2){funC} 7\nfunC(){} 9\nfunA";

	int n = number_of_func_def(inp);
	int s = stack_size(inp);

	int first_line_end = inp.find('\n');

	string definitions = inp.substr(first_line_end + 1);

	Function* funcs = new Function[n];

	store_info_of_function_defi(funcs, n, definitions);

	for (int i = 0; i < n; i++)
	{
		cout << "Function: " << funcs[i].name << endl;
		cout << "Recursion: " << funcs[i].recursion << endl;
		cout << "Memory: " << funcs[i].memory << endl;

		for (int j = 0; j < funcs[i].nested_count; j++)
		{
			cout << "Nested: " << funcs[i].nested[j] << endl;
		}

		cout << endl;
	}

	FrameStack st(s / 4, s);

	delete[] funcs;

	return 0;
}