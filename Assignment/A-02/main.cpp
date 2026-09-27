#include <iostream>
#include <string>
#include "inputvalidator.h"
#include "evaluator.h"
#include "postfix.h"

using namespace std;



int main()
{
	//string inp = "2 1 20\nfunA(){funB} 5\nfunB(){} 7\nfunA";
	//input_validator(inp);
	cout << "Enter expression: ";
	string n;
	getline(cin, n);
	cout << "Postfix: " << infix_to_postix(n) << endl;;
	cout << "Result: " << evaluator(infix_to_postix(n));

	return 0;
}