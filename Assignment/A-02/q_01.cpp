#include <iostream>
#include <string>
using namespace std;

void take_input();

void take_input()
{
	string exp;
	cout << "Enter the Expression/Input: ";
	getline(cin, exp);

	cout << "Your Input:  " << endl;
	cout << exp << endl;;
}

int main()
{
	take_input();
}
