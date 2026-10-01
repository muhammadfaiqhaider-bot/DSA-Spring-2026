#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"
#include "runtime.h"
#include <fstream>

using namespace std;





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



string manual_input()
{
	string inp = "";
	string line;
	int n;
	int m;

	cout << "Enter N M S: ";
	getline(cin, line);

	inp += line;
	inp += "\n";

	n = number_of_func_def(line);
	m = number_of_topcall(line);

	cout << "Enter " << n << " function definitions:" << endl;

	for (int i = 0; i < n; i++)
	{
		getline(cin, line);

		inp += line;
		inp += "\n";
	}

	cout << "Enter " << m << " top level calls:" << endl;

	for (int i = 0; i < m; i++)
	{
		getline(cin, line);

		inp += line;

		if (i != m - 1)
			inp += "\n";
	}

	return inp;
}
void process_file_input()
{
	string inp = file_input();

	if (inp.length() == 0)
	{
		return;
	}

	string* test_cases = test_case_collector(inp);

	for (int i = 0; test_cases[i].length() != 0; i++)
	{
		cout << endl;
		cout << "============================" << endl;
		cout << "Test Case " << i + 1 << endl;
		cout << "============================" << endl;

		bool valid = input_validator(test_cases[i]);

		if (valid)
		{
			cout << "Input is valid." << endl;
			cout << endl;

			run_valid_input(test_cases[i]);
		}
		else
		{
			cout << "Input is invalid." << endl;
		}
	}

	delete[] test_cases;
}


void process_manual_input()
{
	string inp = manual_input();

	cout << endl;
	cout << "Checking input..." << endl;

	bool valid = input_validator(inp);

	if (valid)
	{
		cout << "Input is valid." << endl;
		cout << endl;

		run_valid_input(inp);
	}
	else
	{
		cout << "Input is invalid." << endl;
	}
}

void menu()
{
	int choice;

	cout << "============================" << endl;
	cout << "     RUNTIME STACK SIMULATOR" << endl;
	cout << "============================" << endl;
	cout << "1. Manual Input" << endl;
	cout << "2. File Input" << endl;
	cout << "Enter your choice: ";

	cin >> choice;
	cin.ignore();

	if (choice == 1)
	{
		process_manual_input();
	}
	else if (choice == 2)
	{
		process_file_input();
	}
	else
	{
		cout << "Invalid choice." << endl;
	}
}

int main()
{
	menu();

	return 0;
}