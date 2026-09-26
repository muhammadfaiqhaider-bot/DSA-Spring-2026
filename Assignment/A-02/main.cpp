#include <iostream>
#include "inputvalidator.h"
#include <string>

using namespace std;



int main()
{
	string inp = "2 1 20\nfunA(){funB} 5\nfunB(){} 7\nfunA";

	input_validator(inp);

	return 0;
}