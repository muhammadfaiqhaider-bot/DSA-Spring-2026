
#include <iostream>
#include <string>
#include "bracket.h"
#include <fstream>
using namespace std;



string manual_input();



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

void analyze_source_code(string inp)
{
	const int original = 0;
	const int str = 1;
	const int charcters = 2;
	const int singlecomment = 3;
	const int multicomment = 4;

	int i = 0;
	int line = 1;
	int column = 1;

	int sta = original;


	bool first_non_space = true;
	bool preprocessor = false;

	bracketStack st(inp.length() + 1);

	int max_depth = 0;
	int match_pairs = 0;

	while (i < inp.length())
	{
		if (sta == original)
		{
			if (preprocessor == true)
			{
				if (inp[i] == '\n')
				{
					preprocessor = false;
					first_non_space = true;
				}
			}
			else
			{
				if (first_non_space == true)
				{
					if (inp[i] == ' ' || inp[i] == '\t')
					{

					}
					else
					{
						first_non_space = false;

						if (inp[i] == '#')
						{
							preprocessor = true;
						}
					}
				}

				if (preprocessor == false)
				{
					if (inp[i] == '"')
					{
						sta = str;
					}
					else if (inp[i] == '\'')
					{
						sta = charcters;
					}
					else if (inp[i] == '/' && i + 1 < inp.length() && inp[i + 1] == '/')
					{
						sta = singlecomment;
						i++;
						column++;
					}
					else if (inp[i] == '/' && i + 1 < inp.length() && inp[i + 1] == '*')
					{
						sta = multicomment;
						i++;
						column++;
					}
					else if (inp[i] == '(' || inp[i] == '{' || inp[i] == '[')
					{
						st.push(inp[i], line, column);

						if (st.top + 1 > max_depth)
							max_depth = st.top + 1;
					}
					else if (inp[i] == ')' || inp[i] == '}' || inp[i] == ']')
					{
						if (st.is_empty())
						{
							cout << "Invalid" << endl;
							cout << "Error at Line " << line
								<< ", Column " << column
								<< ": Unexpected '" << inp[i] << "'" << endl;

							return;
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
							cout << "Invalid" << endl;
							cout << "Error at Line " << line
								<< ", Column " << column
								<< ": Expected '" << expected_bracket(st.peek())
								<< "' but found '" << inp[i] << "'" << endl;

							return;
						}
					}
				}
			}
		}

		else if (sta == str)
		{
			if (inp[i] == '\\')
			{
				if (i + 1 < inp.length())
				{
					i++;
					column++;
				}
			}
			else if (inp[i] == '"')
			{
				sta = original;
			}
		}

		else if (sta == charcters)
		{
			if (inp[i] == '\\')
			{
				if (i + 1 < inp.length())
				{
					i++;
					column++;
				}
			}
			else if (inp[i] == '\'')
			{
				sta = original;
			}
		}

		else if (sta == singlecomment)
		{
			if (inp[i] == '\n')
			{
				sta = original;
				first_non_space = true;
			}
		}

		else if (sta == multicomment)
		{
			if (inp[i] == '*' && i + 1 < inp.length() && inp[i + 1] == '/')
			{
				sta = original;
				i++;
				column++;
			}
		}

		// remaining essential stuff for moving through input..
		if (inp[i] == '\n')
		{
			line++;
			column = 1;
			first_non_space = true;
			preprocessor = false;
		}
		else
		{
			column++;
		}

		i++;
	}

	if (!st.is_empty())
	{
		bracket temp = st.peek_frame();

		cout << "Invalid" << endl;
		cout << "Error: '" << temp.bracket
			<< "' opened at Line " << temp.line
			<< ", Column " << temp.column
			<< " was never closed" << endl;

		return;
	}

	cout << "Valid" << endl;
	cout << "Maximum Nesting Depth: " << max_depth << endl;
	cout << "Total Matched Pairs: " << match_pairs << endl;
}







string* test_case_collector(string inp)
{
	int i = 0;
	int array_index = 0;

	string* test_cases = new string[50];

	for (int k = 0; k < 50; k++)
	{
		test_cases[k] = "";
	}

	while (i < inp.length())
	{
		int line_end = i;

		while (line_end < inp.length() && inp[line_end] != '\n')
		{
			line_end++;
		}

		string line = inp.substr(i, line_end - i);

		if (line == "###" || line == "###\r")
		{
			array_index++;
		}
		else
		{
			if (test_cases[array_index].length() != 0)
				test_cases[array_index] += "\n";

			test_cases[array_index] += line;
		}

		i = line_end + 1;
	}

	return test_cases;
}





string file_input()
{
	string filename;
	string inp = "";
	string line;

	cout << "Enter file name: ";
	getline(cin, filename);

	ifstream file(filename);

	if (!file)
	{
		cout << "Unable to open file." << endl;
		return "";
	}

	while (getline(file, line))
	{
		inp += line;
		inp += "\n";
	}

	file.close();

	return inp;
}








void process_file()
{
	string inp = file_input();

	if (inp.length() == 0)
	{
		return;
	}

	string* test_cases = test_case_collector(inp);
	cout << endl << endl;;
	for (int i = 0; test_cases[i].length() != 0; i++)
	{
		cout << "        Test Case " << i + 1  << endl;

		analyze_source_code(test_cases[i]);

		cout << endl;
	}

	delete[] test_cases;
}



void process_manual_input()
{
	string inp = manual_input();

	cout << endl;
	cout << "Checking input..." << endl;

	analyze_source_code(inp);
}





string manual_input()
{
	string inp = "";
	string line;

	cout << "Enter your source code." << endl;
	cout << "Enter ### when you are finished." << endl;

	while (true)
	{
		getline(cin, line);

		if (line == "###")
		{
			break;
		}

		inp += line;
		inp += "\n";
	}

	return inp;
}



void menu()
{
	int choice;

	cout << "Press 1 for Manual Input" << endl;
	cout << "Press 2 for File Input" << endl;
	cout << "Enter your choice: ";

	cin >> choice;
	cin.ignore(1000, '\n');

	if (choice == 1)
	{
		process_manual_input();
	}
	else if (choice == 2)
	{
		process_file();
	}
	else
	{
		cout << "Invalid choice." << endl;
	}
}








