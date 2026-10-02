#pragma once
#include <iostream>
using namespace std;


struct bracket
{
	char bracket;
	int line;
	int column;
};


struct bracketStack
{
	bracket* arr;
	int top;
	int size;

	bracketStack(int s)
	{
		size = s;
		top = -1;
		arr = new bracket[size];
	}

	void push(char ch, int l, int c)
	{
		if (top == size - 1)
		{
			cout << "Stack Overflow" << endl;
			return;
		}

		top++;

		arr[top].bracket = ch;
		arr[top].line = l;
		arr[top].column = c;
	}

	void pop()
	{
		if (top == -1)
		{
			cout << "Stack Underflow" << endl;
			return;
		}

		top--;
	}

	bool is_empty()
	{
		return (top == -1);
	}

	bool is_full()
	{
		return (top == size - 1);
	}

	char peek()
	{
		if (!is_empty())
		{
			return arr[top].bracket;
		}

		return '\0';
	}

	bracket peek_frame()
	{
		return arr[top];
	}

	~bracketStack()
	{
		delete[] arr;
	}
};


char expected_bracket(char ch);
bool valid_paranthesis(string inp);
void analyze_source_code(string inp);
string* test_case_collector(string inp);
string file_input();
void process_file();
string manual_input();
void process_manual_input();
void menu();