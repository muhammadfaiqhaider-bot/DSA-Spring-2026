#include <iostream>
#include <string>
#include "inputvalidator.h"
using namespace std;






void take_input()
{
	string exp;
	cout << "Enter the Expression/Input: ";
	getline(cin, exp);

	cout << "Your Input:  " << endl;
	cout << exp << endl;

	input_validator(exp);
	
}

int main()
{
	take_input();
}
