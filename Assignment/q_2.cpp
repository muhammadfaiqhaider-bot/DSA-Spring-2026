#include <iostream>
#include "q_2.h"
#include "q_1.h"
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

    payloadAppointment = sizeof(int) + sizeof(char *) + 9 * sizeof(char) + sizeof(float);
    sizeOfAppointment = sizeof(Appointment);
    paddingAppointment = sizeOfAppointment - payloadAppointment;

    // for DaySchedule
    int paddingDaySchedule = 0;
    int payloadDaySchedule = 0;
    int sizeOfDaySchedule = 0;

    payloadDaySchedule = sizeof(Appointment *) + sizeof(int) + sizeof(int);
    sizeOfDaySchedule = sizeof(DaySchedule);
    paddingDaySchedule = sizeOfDaySchedule - payloadDaySchedule;

    // for Week
    int paddingWeek = 0;
    int payloadWeek = 0;
    int sizeOfWeek = 0;

    payloadWeek = sizeof(DaySchedule *) + sizeof(int);
    sizeOfWeek = sizeof(Week);
    paddingWeek = sizeOfWeek - payloadWeek;

    cout << "------------------------------------------------------" << endl;
    cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  Appointment  |        " << sizeOfAppointment << "         |    " << payloadAppointment << "   |    " << paddingAppointment << endl;
    cout << "  DaySchedule  |        " << sizeOfDaySchedule << "         |    " << payloadDaySchedule << "   |    " << paddingDaySchedule << endl;
    cout << "  Week         |        " << sizeOfWeek << "         |    " << payloadWeek << "   |    " << paddingWeek << endl;
}

void initWeek(Week &w)
{
    w.dayCount = DAYS_IN_WEEK;
    w.days = new DaySchedule[DAYS_IN_WEEK];
    for (int i = 0; i < w.dayCount; i++)
    {
        w.days[i].slots = nullptr;
        w.days[i].count = 0;
        w.days[i].capacity = 0;
    }
}

bool growDay(DaySchedule &d)
{
    int newCapacity = 0;
    if (d.capacity == 0)
    {
        newCapacity = P2;
    }
    else
    {
        newCapacity = P3 + d.capacity;
    }

    if (newCapacity > MAX_SLOTS)
    {
        cout << "ERR DAY_FULL" << endl;
        return false;
    }

    Appointment *temp = new Appointment[newCapacity];

    for (int i = 0; i < d.count; i++)
    {
        temp[i].clientId = d.slots[i].clientId;
        myStrCopy(temp[i].service, d.slots[i].service);
        temp[i].price = d.slots[i].price;
        temp[i].clientName = d.slots[i].clientName;
    }

    delete[] d.slots;

    d.slots = temp;
    d.capacity = newCapacity;

    return true;
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