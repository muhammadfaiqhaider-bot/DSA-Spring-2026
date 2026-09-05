#include <iostream>
using namespace std;


void fillPrices(float* begin, float* end, int n)
{
    for (int i = 0 ; begin<end; i++)
    {
        *begin = float((n + 613 * i) % 4000) / 2.0f + 250.0f;
        begin++;
    }
}

int  main ()
{


    return 0;
}