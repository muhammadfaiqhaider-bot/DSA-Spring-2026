#pragma once

#include <iostream>
using namespace std;

string infix_to_postix(string infix);
int precedence(char ch);
int is_operand(char ch);
string value_extraction(string inp);

struct Stack
{
	int top;
	int size;
	char* arr;

	Stack(int s)
	{
		size = s;
		top = -1;
		arr = new char[size];
	}

	void push(char ch)
	{
		arr[++top] = ch;
	}

	char pop()
	{
		char ch = arr[top];
		top--;
		return ch;
	}

	char peek()
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

	~Stack()
	{
		delete[] arr;
	}
};