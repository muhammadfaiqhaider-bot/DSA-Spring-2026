#pragma once
#include <iostream>
using namespace std;

int evaluator(string postfix);


struct Int_Stack
{
	int top;
	int size;
	int* arr;

	Int_Stack(int s)
	{
		size = s;
		top = -1;
		arr = new int[size];
	}

	void push(int ch)
	{
		arr[++top] = ch;
	}

	int pop()
	{
		int ch = arr[top];
		top--;
		return ch;
	}

	int peek()
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

	~Int_Stack()
	{
		delete[] arr;
	}
};