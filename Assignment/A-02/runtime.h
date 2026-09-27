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

	Function()
	{
		recursion = 1;
		memory = 0;
		nested = nullptr;
		nested_count = 0;
	}

	~Function()
	{
		delete[] nested;
	}
};

int stack_size(string inp);
int requested_memory(string inp);
int memory_allignment(int req);
int recursion_count(string inp);
void store_info_of_function_defi(Function* funcs, int n, string inp);