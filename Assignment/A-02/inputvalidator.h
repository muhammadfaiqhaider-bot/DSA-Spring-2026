#include <iostream>
#include <string>
using namespace std;

string get_func_definition_name(string inp);
bool func_name_validator(string inp);
string* func_name_collector(string inp);
bool duplicate_defined_function(string* funcs, int nums);
string* nested_func_collector(string inp);
bool undefined_validator(string* definitions, int definitionCount, string* nested_funcs);
string* top_levelcalls(string inp);
bool undefined_top_level_call(string* defeinitions, int m, string* top_calls, int n);
int number_of_func_def(string inp);
int number_of_topcall(string inp);
int stack_size(string inp);
void input_validator(string inp);