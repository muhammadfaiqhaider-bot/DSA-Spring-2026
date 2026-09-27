#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"
#include "runtime.h"

using namespace std;


int main()
{
	string inp = "3 2 28\nfunA(3){} 5\nfunB(){} 7\nfunC(){} 9\nfunA\nfunB";

	int n = number_of_func_def(inp);
	int s = stack_size(inp);
	int m = number_of_topcall(inp);

	int first_line_end = inp.find('\n');

	string definitions = inp.substr(first_line_end + 1);

	Function* funcs = new Function[n];

	store_info_of_function_defi(funcs, n, definitions);

	string* top_calls = top_levelcalls(definitions);

	FrameStack st(10, s);

	for (int i = 0; i < m; i++)
	{
		Function* temp = function_finder(funcs, n, top_calls[i]);

		execute_function(top_calls[i], funcs, n, st, temp->recursion);
	}

	delete[] top_calls;
	delete[] funcs;

	return 0;
}