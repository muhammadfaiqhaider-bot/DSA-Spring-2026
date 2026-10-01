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

	while (i < inp.length() && inp[i] != '\n')
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

		funcs[z].definition = line;
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



Function* function_finder(Function* funcs, int n, string name)
{
	for (int i = 0; i < n; i++)
	{
		if (funcs[i].name == name)
		{
			return &funcs[i];
		}
	}

	return nullptr;
}





void execute_function(string name, Function* funcs, int n, FrameStack& st, int recursion_left, Statistics& stat)
{
	stat.total_calls++;

	Function* temp = function_finder(funcs, n, name);

	if (temp == nullptr)
	{
		stat.overflow_calls++;
		return;
	}

	Frame* fra = new Frame;

	fra->memory = temp->memory;
	fra->name = temp->name;

	if (!st.memory_exceeded(fra->memory))
	{
		st.push(*fra);

		stat.successful_calls++;

		int function_index = temp - funcs;
		stat.function_calls[function_index]++;

		if (st.top + 1 > stat.max_depth)
			stat.max_depth = st.top + 1;

		if (st.stack_memory > stat.max_memory)
			stat.max_memory = st.stack_memory;

		cout << fra->name << " called " << endl;
		cout << st.stack_memory << endl;

		if (recursion_left > 1)
		{
			execute_function(name, funcs, n, st, recursion_left - 1, stat);
		}

		string* runtime_nested = runtime_nested_collector(temp->definition);

		int i = 0;

		while (runtime_nested[i].length() != 0)
		{
			Function* nested = function_finder(funcs, n, runtime_nested[i]);

			execute_function(runtime_nested[i], funcs, n, st, nested->recursion, stat);

			i++;
		}

		delete[] runtime_nested;

		Frame temp_fra = st.pop();

		cout << temp_fra.name << " finished" << endl;
		cout << st.stack_memory << endl;
	}
	else
	{
		stat.overflow_calls++;

		cout << "Sorry Memory Full Can't add your Function anymore (runtime error)" << endl;
	}

	delete fra;
}


string ternary_selector(string inp)
{
	string selected = "";

	int question = inp.find('?');
	int colon = inp.find(':');

	if (inp.find("true") != string::npos)
	{
		selected = inp.substr(question + 1, colon - question - 1);
	}
	else if (inp.find("false") != string::npos)
	{
		selected = inp.substr(colon + 1);
	}

	return selected;
}


string* runtime_nested_collector(string inp)
{
	int i = 0;
	int array_index = 0;
	string na = "";

	string* nested_func = new string[50];

	while (i < inp.length() && inp[i] != '{')
	{
		i++;
	}

	i++;

	while (i < inp.length() && inp[i] != '}')
	{
		if (inp[i] == ',')
		{
			if (na.length() != 0)
			{
				if (na.find('?') != string::npos)
				{
					nested_func[array_index] = ternary_selector(na);
				}
				else
				{
					nested_func[array_index] = na;
				}

				array_index++;
				na = "";
			}
		}
		else if (inp[i] == '(')
		{
			int bracket = 1;
			i++;

			while (i < inp.length() && bracket != 0)
			{
				if (inp[i] == '(')
					bracket++;

				if (inp[i] == ')')
					bracket--;

				if (bracket != 0)
					na += inp[i];

				i++;
			}

			if (na.find('?') != string::npos)
			{
				nested_func[array_index] = ternary_selector(na);
				array_index++;
				na = "";
			}

			continue;
		}
		else
		{
			na += inp[i];
		}

		i++;
	}

	if (na.length() != 0)
	{
		if (na.find('?') != string::npos)
		{
			nested_func[array_index] = ternary_selector(na);
		}
		else
		{
			nested_func[array_index] = na;
		}

		array_index++;
	}

	return nested_func;
}






string most_frequent_function(Function* funcs, int n, Statistics& stat)
{
	int max = stat.function_calls[0];
	int index = 0;

	for (int i = 1; i < n; i++)
	{
		if (stat.function_calls[i] > max)
		{
			max = stat.function_calls[i];
			index = i;
		}
	}

	return funcs[index].name;
}




string* test_case_collector(string inp)
{
	int i = 0;
	int array_index = 0;

	string* test_cases = new string[50];

	while (i < inp.length())
	{
		int separator = inp.find("###", i);

		if (separator == string::npos)
		{
			string temp = inp.substr(i);

			if (temp.length() != 0)
			{
				test_cases[array_index] = temp;
				array_index++;
			}

			break;
		}

		string temp = inp.substr(i, separator - i);

		if (temp.length() != 0)
		{
			test_cases[array_index] = temp;
			array_index++;
		}

		i = separator + 3;
	}

	return test_cases;
}








void run_valid_input(string inp)
{
	int n = number_of_func_def(inp);
	int s = stack_size(inp);
	int m = number_of_topcall(inp);

	int first_line_end = inp.find('\n');

	string definitions = inp.substr(first_line_end + 1);

	Function* funcs = new Function[n];

	store_info_of_function_defi(funcs, n, definitions);

	string* top_calls = top_levelcalls(definitions);

	FrameStack st(s / 4, s);
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
		cout << funcs[i].name << " = "
			<< stat.function_calls[i] << endl;
	}

	cout << "Most Frequent Function: "
		<< most_frequent_function(funcs, n, stat) << endl;

	delete[] top_calls;
	delete[] funcs;
}




