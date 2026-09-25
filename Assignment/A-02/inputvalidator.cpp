#include <iostream>
#include <string>
using namespace std;


// this func extract the func name from whole expression 
string get_name(string inp)
{
    int i = 0;
    string fun = "";
    while (inp[i] != '(')
    {
        fun += inp[i];
        i++;
    }
    return fun;
}


// Validate function name
// first character alphabet or remaining characters alphabet or digit

bool func_name(string inp)
{

    if (!((inp[0] >= 'A' && inp[0] <= 'Z') ||
        (inp[0] >= 'a' && inp[0] <= 'z')))
    {
        return false;
    }


    for (int i = 1; i < inp.length(); i++)
    {
        if (!((inp[i] >= 'A' && inp[i] <= 'Z') ||
            (inp[i] >= 'a' && inp[i] <= 'z') ||
            (inp[i] >= '0' && inp[i] <= '9')))
        {
            return false;
        }
    }

    return true;
}


// Circular dependency will be implemented later
bool circular_error(string name)
{
    return false;
}




void input_validator(string inp)
{

    string name = get_name(inp);


    if (!func_name(name))
    {
        cout << "Invalid Function Name: " << name << endl;
        return;
    }


    if (circular_error(name))
    {
        cout << "Circular Function Error" << endl;
        return;
    }

    cout << "Valid Function Name: " << name << endl;
}

