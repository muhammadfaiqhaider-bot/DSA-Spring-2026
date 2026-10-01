#pragma once
#include <iostream>
#include <string>
using namespace std;



struct Frame
{
	string name;
	int memory;
};

struct FrameStack
{
	int top;
	int size;
	int memory_limit;
	int stack_memory;
	Frame* arr;

	FrameStack(int s, int limit)
	{
		size = s;
		memory_limit = limit;
		stack_memory = 0;
		top = -1;
		arr = new Frame[size];
	}

	void push(Frame f)
	{
		arr[++top] = f;
		stack_memory += f.memory;
	}

	Frame pop()
	{
		Frame f = arr[top];
		top--;
		stack_memory -= f.memory;
		return f;
	}

	Frame peek()
	{
		return arr[top];
	}

	bool is_empty()
	{
		return (top == -1);
	}

	bool is_full()
	{
		return (top == size - 1);
	}

	bool memory_exceeded(int memory)
	{
		return (stack_memory + memory > memory_limit);
	}

	~FrameStack()
	{
		delete[] arr;
	}
};


struct Function
{
	string name;
	int recursion;
	int memory;
	string* nested;
	int nested_count;
	string definition;

	Function()
	{
		recursion = 1;
		memory = 0;
		nested = nullptr;
		nested_count = 0;
		definition = "";
	}

	~Function()
	{
		delete[] nested;
	}
};


struct Statistics
{
	int total_calls;
	int successful_calls;
	int overflow_calls;
	int max_depth;
	int max_memory;
	int* function_calls;

	Statistics(int n)
	{
		total_calls = 0;
		successful_calls = 0;
		overflow_calls = 0;
		max_depth = 0;
		max_memory = 0;

		function_calls = new int[n];

		for (int i = 0; i < n; i++)
		{
			function_calls[i] = 0;
		}
	}

	~Statistics()
	{
		delete[] function_calls;
	}
};



int stack_size(string inp);
int requested_memory(string inp);
int memory_allignment(int req);
int recursion_count(string inp);
void store_info_of_function_defi(Function* funcs, int n, string inp);
Function* function_finder(Function* funcs, int n, string name);
void execute_function(string name, Function* funcs, int n, FrameStack& st, int recursion_left, Statistics& stat);
string ternary_function(string inp);
string ternary_selector(string inp);
string* runtime_nested_collector(string inp);
string most_frequent_function(Function* funcs, int n, Statistics& stat);
string* test_case_collector(string inp);
void run_valid_input(string inp);
void process_file_input();