#include <iostream>
#include <string>

using namespace std;



// this get_func_definition_name fuction give me the name of the defined function.....
string get_func_definition_name(string inp)
{
	int i = 0;
	string fun = "";

	while (i < inp.length() && inp[i] != '(')
	{
		fun += inp[i];
		i++;
	}

	return fun;
}


// this function validate the conventions of function defination....
bool func_name_validator(string inp)
{
	if (inp.length() == 0)
		return false;

	if (!((inp[0] >= 'A' && inp[0] <= 'Z') || (inp[0] >= 'a' && inp[0] <= 'z')))
		return false;


	for (int i = 1; i < inp.length(); i++)
	{
		if (!((inp[i] >= 'A' && inp[i] <= 'Z') || (inp[i] >= 'a' && inp[i] <= 'z') || (inp[i] >= '0' && inp[i] <= '9')))
			return false;
	}


	return true;
}


// this function collect all the name of function definitions
string* func_name_collector(string inp)
{
	int i = 0;
	int j = 0;
	int z = 0;
	int nameCount = 0;
	int bracket_count = 0;


	string* names = new string[50];

	while (inp[z] != '\0')
	{
		if (inp[z] == '(')
			bracket_count++;

		z++;
	}

	while (i < inp.length())
	{
		if (inp[i] == '\n')
		{
			i++;
			j = i;
			continue;
		}

		int line_end = i;

		while (line_end < inp.length() && inp[line_end] != '\n')
			line_end++;

		string line = inp.substr(i, line_end - i);

		if (line.length() != 0)
		{
			for (int k = 0; k < line.length(); k++)
			{
				if (line[k] == '(')
				{
					string na = get_func_definition_name(line);
					names[nameCount] = na;
					nameCount++;
					break;
				}
			}
		}

		i = line_end + 1;
		j = i;
	}

	return names;
}


// check the repetition int the function definition names 
bool duplicate_defined_function(string* funcs, int nums)
{
	for (int i = 0; i < nums; i++)
	{
		for (int j = i + 1; j < nums; j++)
		{
			if (funcs[i] == funcs[j])
				return false;
		}
	}
	return true;
}



// this function extract all the nested functions inside function definition....
string* nested_func_collector(string inp)
{
	int i = 0;
	int array_index = 0;
	string na = "";
	string* nested_func = new string[50];

	while (i < inp.length())
	{
		if (inp[i] == '{')
		{

			int j = i + 1;
			while (j < inp.length() && inp[j] != '}')
			{
				if (inp[j] == ',' || inp[j] == ':' || inp[j] == '?' || inp[j] == '(' || inp[j] == ')' || inp[j] == ' ')
				{
					if (na != "true" && na != "false" && na.length() != 0)
					{
						nested_func[array_index] = na;
						array_index++;
						na = "";
					}
					else
					{
						na = "";
					}
				}
				else
				{
					na += inp[j];
				}
				j++;
			}

			if (na != "true" && na != "false" && na.length() != 0)
			{
				nested_func[array_index] = na;
				array_index++;
				na = "";
			}

			i = j + 1;
		}
		else
		{
			i++;
		}
	}

	return nested_func;
}



// is there any function that hasn't been defined 
bool undefined_validator(string* definitions, int definitionCount, string* nested_funcs)
{
	bool present = false;

	for (int i = 0; nested_funcs[i].length() != 0; i++)
	{
		present = false;

		for (int j = 0; j < definitionCount; j++)
		{
			if (definitions[j] == nested_funcs[i])
			{
				present = true;
				break;
			}
		}

		if (!present)
		{
			return true;
		}
	}

	return false;
}


// givre all top calls in string array
string* top_levelcalls(string inp)
{
	int i = 0;
	int j = 0;
	int z = 0;
	int nameCount = 0;
	int bracket_count = 0;

	string* names = new string[50];

	while (inp[z] != '\0')
	{
		if (inp[z] == '(')
			bracket_count++;

		z++;
	}

	while (i < inp.length())
	{
		if (inp[i] == '\n')
		{
			i++;
			j = i;
			continue;
		}

		int line_end = i;

		while (line_end < inp.length() && inp[line_end] != '\n')
			line_end++;

		string line = inp.substr(i, line_end - i);

		bool definition = false;

		for (int k = 0; k < line.length(); k++)
		{
			if (line[k] == '(')
			{
				definition = true;
				break;
			}
		}

		if (!definition)
		{
			string na = line;

			if (func_name_validator(na))
			{
				names[nameCount] = na;
				nameCount++;
			}
		}

		i = line_end + 1;
		j = i;
	}

	return names;
}


// are those top call has been defined
bool undefined_top_level_call(string* defeinitions, int m, string* top_calls, int n)
{
	bool flag = false;

	for (int i = 0; i < n; i++)
	{
		flag = false;

		for (int j = 0; j < m; j++)
		{
			if (defeinitions[j] == top_calls[i])
			{
				flag = true;
				break;
			}
			else
			{
				flag = false;
			}
		}

		if (!flag)
			return true;
	}

	return false;
}



// give me number of function definiitiions
int number_of_func_def(string inp)
{
	int i = 0;
	int n = 0;

	while (inp[i] != ' ')
	{
		n = n * 10 + (inp[i] - '0');
		i++;
	}

	return n;
}



int number_of_topcall(string inp)
{
	int i = 0;
	int m = 0;

	while (inp[i] != ' ')
	{
		i++;
	}

	i++;

	while (inp[i] != ' ')
	{
		m = m * 10 + (inp[i] - '0');
		i++;
	}

	return m;
}

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

void input_validator(string inp)
{
	int n = number_of_func_def(inp);
	int m = number_of_topcall(inp);
	int s = stack_size(inp);

	int first_line_end = inp.find('\n');
	string data = inp.substr(first_line_end + 1);

	string* definitions = func_name_collector(data);
	string* nested_funcs = nested_func_collector(data);
	string* top_calls = top_levelcalls(data);

	bool valid_name = true;

	for (int i = 0; i < n; i++)
	{
		if (!func_name_validator(definitions[i]))
		{
			valid_name = false;
			break;
		}
	}

	bool dub_defi = !duplicate_defined_function(definitions, n);
	bool undifined_nested = undefined_validator(definitions, n, nested_funcs);
	bool undifened_top = undefined_top_level_call(definitions, n, top_calls, m);
	bool circular_dep = false;//i ll implement late....


	if (!valid_name)
	{
		cout << "Invalid Function Name error." << endl;

	}
	if (dub_defi)
	{
		cout << "Function Definition repeteation error." << endl;
	}
	if (undifined_nested)
	{
		cout << "undifined nested Function error... " << endl;
	}
	if (undifened_top)
	{
		cout << "Undifined top level function error..." << endl;
	}

	if (circular_dep)
	{
		cout << "There is circular dependency in your input which cause infinite loop.error." << endl;
	}


	if (valid_name == false || dub_defi == true || undifined_nested == true || undifened_top == true)
	{
		delete[] definitions;
		delete[] nested_funcs;
		delete[] top_calls;
		return;
	}
	 
	cout << "Everything is fine you may proceed to more work ..." << endl;
	delete[] definitions;
	delete[] nested_funcs;
	delete[] top_calls;
}
