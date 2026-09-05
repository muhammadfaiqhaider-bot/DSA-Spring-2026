#include <iostream>
#include "q_2.h"
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

int countAbove(const float *begin, const float *end, float threshold)
{
    int count = 0;

    for (int i = 0; begin + i < end; i++)
    {
        if (*(begin + i) > threshold)
            count++;
    }
    return count;
}

void reverseInPlace(float *begin, float *end)
{
    int left = 0;
    int right = 0;
    while (begin + left < end + right)
    {
        float temp = *(begin + left);
        *(begin + left) = *(end + right);
        *(end + right) = temp;
        left++;
        right--;
    }
}


void reportSizes()
{
	// for Appointment
	int paddingAppointment = 0;
	int payloadAppointment = 0;
	int sizeOfAppointment = 0;

	payloadAppointment = sizeof(int) + sizeof(char*) + 9 * sizeof(char) + sizeof(float);
	sizeOfAppointment = sizeof(Appointment);
	paddingAppointment = sizeOfAppointment - payloadAppointment;

	// for DaySchedule
	int paddingDaySchedule = 0;
	int payloadDaySchedule = 0;
	int sizeOfDaySchedule = 0;

	payloadDaySchedule = sizeof(Appointment*) + sizeof(int) + sizeof(int);
	sizeOfDaySchedule = sizeof(DaySchedule);
	paddingDaySchedule = sizeOfDaySchedule - payloadDaySchedule;

	// for Week
	int paddingWeek = 0;
	int payloadWeek = 0;
	int sizeOfWeek = 0;

	payloadWeek = sizeof(DaySchedule*) + sizeof(int);
	sizeOfWeek = sizeof(Week);
	paddingWeek = sizeOfWeek - payloadWeek;

	cout << "SIZEOF Appointment=" << sizeOfAppointment
	     << " payload=" << payloadAppointment
	     << " padding=" << paddingAppointment << "\n";

	cout << "SIZEOF DaySchedule=" << sizeOfDaySchedule
	     << " payload=" << payloadDaySchedule
	     << " padding=" << paddingDaySchedule << "\n";

	cout << "SIZEOF Week=" << sizeOfWeek
	     << " payload=" << payloadWeek
	     << " padding=" << paddingWeek << "\n";
}

int main()
{
    float sum[5] = {1, 2, 3, 4, 5};
    reverseInPlace(&sum[0], &sum[4]);
    for (int i = 0; i < 5; i++)
    {
        cout << sum[i] << " ";
    }
    return 0;
}