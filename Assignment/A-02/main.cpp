#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"
#include "runtime.h"

using namespace std;


int main()
{
	string inp = "4 1 20\nfunA(2){(true?funB:funC)} 5\nfunB(){} 7\nfunC(){} 9\nfunD(){} 4\nfunA";

	int n = number_of_func_def(inp);
	int s = stack_size(inp);
	int m = number_of_topcall(inp);

	int first_line_end = inp.find('\n');

	string definitions = inp.substr(first_line_end + 1);

	Function* funcs = new Function[n];

	store_info_of_function_defi(funcs, n, definitions);

	string* top_calls = top_levelcalls(definitions);

	FrameStack st(10, s);
	Statistics stat(n);

	for (int i = 0; i < m; i++)
	{
		Function* temp = function_finder(funcs, n, top_calls[i]);

		execute_function(top_calls[i], funcs, n, st, temp->recursion, stat);
	}

	cout << endl;

	cout << "Total Calls: " << stat.total_calls << endl;
	cout << "Successful Calls: " << stat.successful_calls << endl;
	cout << "Overflow Calls: " << stat.overflow_calls << endl;
	cout << "Maximum Stack Depth: " << stat.max_depth << endl;
	cout << "Maximum Stack Memory: " << stat.max_memory << endl;

	cout << "Function Calls:" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << funcs[i].name << " = " << stat.function_calls[i] << endl;
	}

	cout << "Most Frequent Function: "
		<< most_frequent_function(funcs, n, stat) << endl;

	delete[] top_calls;
	delete[] funcs;

	return 0;
}