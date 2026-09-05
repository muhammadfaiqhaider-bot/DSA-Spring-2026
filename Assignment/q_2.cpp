#include <iostream>
using namespace std;

void fillPrices(float *begin, float *end, int n)
{
    for (int i = 0; begin < end; i++)
    {
        *begin = float((n + 613 * i) % 4000) / 2.0f + 250.0f;
        begin++;
    }
}

float sumRange(const float *begin, const float *end)
{
    float sum = 0;
    for (int i = 0; begin + i < end; i++)
    {
        sum += *(begin + i);
    }
    return sum;
}
float *maxElementPtr(float *begin, float *end)
{
    if (begin == end)
        return nullptr;

    float *maxElem = begin;

    for (int i = 0; begin + i < end; i++)
    {
        if (*(begin + i) > *maxElem)
            maxElem = begin + i;
    }

    return maxElem;
}
int main()
{
    float sum[5] = {1, 2, 3, 4, 5};
    cout << sumRange(&sum[0], &sum[4]);
    return 0;
}