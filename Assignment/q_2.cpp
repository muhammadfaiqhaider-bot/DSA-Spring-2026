#include <iostream>
#include <iomanip>
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

bool bookAppointment(Week& w, int day, int clientId, const char* name, const char* service, float price)
{
    if (w.days == nullptr)
    {
        cout << "ERR WEEK_DESTROYED" << endl;
        return false;
    }

    if (day < 0 || day >= DAYS_IN_WEEK)
    {
        cout << "ERR BAD_DAY" << endl;
        return false;
    }

    if (clientId < CLIENT_MIN || clientId > CLIENT_MAX)
    {
        cout << "ERR BAD_CLIENT" << endl;
        return false;
    }

    if (myStrLen(name) < 1 || myStrLen(name) > NAME_LIMIT)
    {
        cout << "ERR BAD_NAME" << endl;
        return false;
    }

    if (myStrLen(service) < 1 || myStrLen(service) > SERVICE_LIMIT)
    {
        cout << "ERR BAD_SERVICE" << endl;
        return false;
    }

    if (price < 100.0f || price > 20000.0f)
    {
        cout << "ERR BAD_PRICE" << endl;
        return false;
    }

    for (int i = 0; i < w.days[day].count; i++)
    {
        if (w.days[day].slots[i].clientId == clientId)
        {
            cout << "ERR DUP_BOOKING" << endl;
            return false;
        }
    }

    if (w.days[day].count == w.days[day].capacity)
    {
        if (!growDay(w.days[day]))
            return false;
    }

    int idx = w.days[day].count;
    w.days[day].slots[idx].clientId = clientId;
    w.days[day].slots[idx].clientName = cloneCString(name);
    myStrCopy(w.days[day].slots[idx].service, service);
    w.days[day].slots[idx].price = price;

    w.days[day].count++;

    return true;
}

bool cancelAppointment(Week& w, int day, int slot)
{
    if (w.days == nullptr)
    {
        cout << "ERR WEEK_DESTROYED" << endl;
        return false;
    }

    if (day < 0 || day >= DAYS_IN_WEEK)
    {
        cout << "ERR BAD_DAY" << endl;
        return false;
    }

    if (slot < 0 || slot >= w.days[day].count)
    {
        cout << "ERR BAD_SLOT" << endl;
        return false;
    }

    delete[] w.days[day].slots[slot].clientName;

    for (int i = slot; i < w.days[day].count - 1; i++)
    {
        w.days[day].slots[i] = w.days[day].slots[i + 1];
    }

    w.days[day].count--;

    return true;
}

Appointment* findAppointment(const Week& w, int clientId, int& outDay, int& outSlot)
{
    if (w.days == nullptr)
    {
        outDay = -1;
        outSlot = -1;
        return nullptr;
    }

    for (int d = 0; d < w.dayCount; d++)
    {
        for (int s = 0; s < w.days[d].count; s++)
        {
            if (w.days[d].slots[s].clientId == clientId)
            {
                outDay = d;
                outSlot = s;
                return &w.days[d].slots[s];
            }
        }
    }

    outDay = -1;
    outSlot = -1;
    return nullptr;
}

float dayRevenue(const DaySchedule& d)
{
    float total = 0;
    for (int i = 0; i < d.count; i++)
    {
        total += d.slots[i].price;
    }
    return total;
}

void printDay(const DaySchedule& d, int dayIndex)
{
	const char* dayNames[7] = { "MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN" };

	cout << endl;
	cout << "*************************************************************" << endl;
	cout << "============================================================" << endl;

	cout << left
		<< setw(8) << "DAY"
		<< setw(8) << dayIndex
		<< setw(8) << dayNames[dayIndex]
		<< setw(15) << "BOOKED"
		<< setw(15) << "REVENUE" << endl;

	cout << left
		<< setw(8) << ""
		<< setw(8) << ""
		<< setw(8) << ""
		<< setw(15) << (to_string(d.count) + "/" + to_string(d.capacity))
		<< setw(15) << dayRevenue(d) << endl;

	cout << "------------------------------------------------------------" << endl;

	if (d.count == 0)
	{
		cout << "  (free)" << endl;
	}
	else
	{
		cout << left
			<< setw(8) << "Slot"
			<< setw(8) << "ID"
			<< setw(20) << "Client Name"
			<< setw(20) << "Service"
			<< setw(10) << "Price" << endl;

		cout << "------------------------------------------------------------" << endl;

		for (int i = 0; i < d.count; i++)
		{
			cout << left
				<< setw(8) << i
				<< setw(8) << d.slots[i].clientId
				<< setw(20) << d.slots[i].clientName
				<< setw(20) << d.slots[i].service
				<< setw(10) << d.slots[i].price
				<< endl;
		}
	}

	cout << "------------------------------------------------------------" << endl;
	cout << "*************************************************************" << endl;
	cout << endl;
}


void printWeek(const Week& w)
{
	if (w.days == nullptr)
	{
		cout << endl;
		cout << "WEEK bookings=0 revenue=0.00" << endl;
		cout << " (destroyed)" << endl;
		cout << "END WEEK" << endl;
		return;
	}

	int totalBookings = 0;
	float totalRevenue = 0;

	for (int i = 0; i < w.dayCount; i++)
	{
		totalBookings += w.days[i].count;
		totalRevenue += dayRevenue(w.days[i]);
	}

	cout << endl;
	cout << "*************************************************************" << endl;
	cout << "============================================================" << endl;

	cout << left
		<< setw(20) << "WEEK"
		<< setw(20) << "BOOKINGS"
		<< setw(20) << "REVENUE" << endl;

	cout << left
		<< setw(20) << ""
		<< setw(20) << totalBookings
		<< setw(20) << totalRevenue << endl;

	cout << "------------------------------------------------------------" << endl;

	for (int i = 0; i < w.dayCount; i++)
	{
		printDay(w.days[i], i);
	}

	cout << "END WEEK" << endl;
	cout << "*************************************************************" << endl;
	cout << endl;
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