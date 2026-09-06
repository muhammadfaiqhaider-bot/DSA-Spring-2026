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

bool moveAppointment(Week& w, int fromDay, int fromSlot, int toDay)
{
    if (w.days == nullptr)
    {
        cout << "ERR WEEK_DESTROYED" << endl;
        return false;
    }

    if (fromDay < 0 || fromDay >= DAYS_IN_WEEK || toDay < 0 || toDay >= DAYS_IN_WEEK)
    {
        cout << "ERR BAD_DAY" << endl;
        return false;
    }

    if (fromDay == toDay)
    {
        cout << "ERR SAME_DAY" << endl;
        return false;
    }

    if (fromSlot < 0 || fromSlot >= w.days[fromDay].count)
    {
        cout << "ERR BAD_SLOT" << endl;
        return false;
    }

    int movingClientId = w.days[fromDay].slots[fromSlot].clientId;

    for (int i = 0; i < w.days[toDay].count; i++)
    {
        if (w.days[toDay].slots[i].clientId == movingClientId)
        {
            cout << "ERR DUP_BOOKING" << endl;
            return false;
        }
    }

    if (w.days[toDay].count == w.days[toDay].capacity)
    {
        if (!growDay(w.days[toDay]))
            return false;
    }

    Appointment moving = w.days[fromDay].slots[fromSlot];
    w.days[toDay].slots[w.days[toDay].count] = moving;
    w.days[toDay].count++;

    for (int i = fromSlot; i < w.days[fromDay].count - 1; i++)
    {
        w.days[fromDay].slots[i] = w.days[fromDay].slots[i + 1];
    }
    w.days[fromDay].count--;

    return true;
}

Appointment** buildIndex(const Week& w, int& outCount)
{
    if (w.days == nullptr)
    {
        outCount = 0;
        return nullptr;
    }

    int total = 0;
    for (int d = 0; d < w.dayCount; d++)
        total += w.days[d].count;

    if (total == 0)
    {
        outCount = 0;
        return nullptr;
    }

    Appointment** index = new Appointment*[total];
    int idx = 0;
    for (int d = 0; d < w.dayCount; d++)
    {
        for (int s = 0; s < w.days[d].count; s++)
        {
            index[idx] = &w.days[d].slots[s];
            idx++;
        }
    }

    outCount = total;
    return index;
}

void sortIndexByPrice(Appointment** index, int n)
{
    if (index == nullptr)
        return;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (index[j]->price < index[j + 1]->price)
            {
                Appointment* temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }
}

void printIndex(Appointment** index, int n)
{
    cout << "INDEX size=" << n << endl;

    if (index == nullptr || n == 0)
    {
        cout << " (none)" << endl;
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            cout << " [" << (i < 10 ? "0" : "") << i << "] "
                 << (index[i]->clientId < 10 ? "000" : index[i]->clientId < 100 ? "00" : index[i]->clientId < 1000 ? "0" : "")
                 << index[i]->clientId << " "
                 << index[i]->clientName << " "
                 << index[i]->service << " PKR "
                 << index[i]->price << endl;
        }
    }

    cout << "END INDEX" << endl;
}

void destroyIndex(Appointment**& index, int& n)
{
    delete[] index;
    index = nullptr;
    n = 0;
}

void destroyWeek(Week& w)
{
    if (w.days != nullptr)
    {
        for (int d = 0; d < w.dayCount; d++)
        {
            for (int s = 0; s < w.days[d].count; s++)
            {
                delete[] w.days[d].slots[s].clientName;
            }
            delete[] w.days[d].slots;
        }
        delete[] w.days;
    }

    w.days = nullptr;
    w.dayCount = 0;
}

bool bookByValue(DaySchedule day, int clientId, const char* name, const char* service, float price)
{
    for (int i = 0; i < day.count; i++)
    {
        if (day.slots[i].clientId == clientId)
        {
            cout << "ERR DUP_BOOKING" << endl;
            return false;
        }
    }

    if (day.count == day.capacity)
    {
        if (!growDay(day))
            return false;
    }

    int idx = day.count;
    day.slots[idx].clientId = clientId;
    day.slots[idx].clientName = cloneCString(name);
    myStrCopy(day.slots[idx].service, service);
    day.slots[idx].price = price;

    day.count++;

    return true;
}

void loadSeedWeek(Week& w)
{
    destroyWeek(w);
    initWeek(w);

    const char* names[8] = {"Ayesha", "Hina", "Sana", "Mahnoor", "Zara", "Iqra", "Nimra", "Rabia"};
    const char* services[6] = {"HAIRCUT", "FACIAL", "MANI", "PEDI", "COLOR", "MAKEUP"};
    float prices[6] = {1500.0f, 2500.0f, 800.0f, 4200.0f, 1200.0f, 3000.0f};

    int total = (SEED % 3) + 9;

    for (int k = 0; k < total; k++)
    {
        int day = 5 + (k % 2);
        int clientId = 500 + SEED + 7 * k;
        const char* name = names[(SEED + k) % 8];
        int which = (SEED + k) % 6;
        const char* service = services[which];
        float price = prices[which];

        bookAppointment(w, day, clientId, name, service, price);
    }

    int day = SEED % 5;
    int clientId = 500 + SEED + 7 * total;
    const char* name = names[(SEED + total) % 8];
    int which = (SEED + total) % 6;
    const char* service = services[which];
    float price = prices[which];

    bookAppointment(w, day, clientId, name, service, price);
}





int main()
{
	cout << "-------------------------------------------" << endl;
	cout << "      GLOW & GRACE SALON SYSTEM  " << endl;
	cout << "-------------------------------------------" << endl << endl;

	cout << "NAME : MUHAMMAD FAIQ HAIDER" << endl;
	cout << "ROLL NUMBER : " << ROLL_N << " P2=" << P2 << " P3=" << P3 << endl;

	Week w;
	initWeek(w);
	Appointment** index = nullptr;
	int indexCount = 0;

	int cmd;
	do
	{
		system("cls");

		cout << "-------------------------------------------" << endl;
		cout << " GLOW & GRACE - COMMAND GUIDE" << endl;
		cout << "-------------------------------------------" << endl;
		cout << " 0  EXIT" << endl;
		cout << " 1  BOOK a new appointment" << endl;
		cout << " 2  CANCEL an appointment" << endl;
		cout << " 3  PRINT a single day" << endl;
		cout << " 4  PRINT the whole week" << endl;
		cout << " 5  MOVE an appointment between days" << endl;
		cout << " 6  BUILD price index" << endl;
		cout << " 7  PRINT price index" << endl;
		cout << " 8  SORT price index" << endl;
		cout << " 9  DROP price index" << endl;
		cout << "10  FIND appointment by client ID" << endl;
		cout << "11  SEED the week with sample data" << endl;
		cout << "12  BOOK an appointment BY VALUE" << endl;
		cout << "13  DESTROY the week" << endl;
		cout << "14  UTILS (sizes + price utilities)" << endl;
		cout << "-------------------------------------------" << endl;

		cin >> cmd;

		if (cmd == 0)
			break;

		switch (cmd)
		{
		case 1: // BOOK
		{
			int day, clientId;
			char name[30], service[30];
			float price;

			cout << "Enter Day (0-6): ";
			cin >> day;
			cout << "Enter Client ID: ";
			cin >> clientId;
			cout << "Enter Client Name: ";
			cin >> name;
			cout << "Enter Service: ";
			cin >> service;
			cout << "Enter Price: ";
			cin >> price;

			if (index != nullptr)
				destroyIndex(index, indexCount);

			if (bookAppointment(w, day, clientId, name, service, price))
				cout << "OK BOOKED d" << day << " "
				     << (clientId < 10 ? "000" : clientId < 100 ? "00" : clientId < 1000 ? "0" : "")
				     << clientId << endl;

			break;
		}
		case 2: // CANCEL
		{
			int day, slot;
			cout << "Enter Day (0-6): ";
			cin >> day;
			cout << "Enter Slot: ";
			cin >> slot;

			if (index != nullptr)
				destroyIndex(index, indexCount);

			if (cancelAppointment(w, day, slot))
				cout << "OK CANCELLED d" << day << " s" << slot << endl;

			break;
		}
		case 3: // PRINT_DAY
		{
			int day;
			cout << "Enter Day (0-6): ";
			cin >> day;

			if (w.days == nullptr)
			{
				cout << "ERR WEEK_DESTROYED" << endl;
			}
			else if (day < 0 || day >= DAYS_IN_WEEK)
			{
				cout << "ERR BAD_DAY" << endl;
			}
			else
			{
				printDay(w.days[day], day);
			}
			break;
		}
		case 4: // PRINT_WEEK
		{
			printWeek(w);
			break;
		}
		case 5: // MOVE
		{
			int fromDay, fromSlot, toDay;
			cout << "Enter From Day (0-6): ";
			cin >> fromDay;
			cout << "Enter From Slot: ";
			cin >> fromSlot;
			cout << "Enter To Day (0-6): ";
			cin >> toDay;

			if (index != nullptr)
				destroyIndex(index, indexCount);

			if (moveAppointment(w, fromDay, fromSlot, toDay))
				cout << "OK MOVED d" << fromDay << " s" << fromSlot << " -> d" << toDay << endl;

			break;
		}
		case 6: // BUILD_INDEX
		{
			if (index != nullptr)
				destroyIndex(index, indexCount);

			index = buildIndex(w, indexCount);
			cout << "OK INDEX_BUILT size=" << indexCount << endl;
			break;
		}
		case 7: // PRINT_INDEX
		{
			printIndex(index, indexCount);
			break;
		}
		case 8: // SORT_INDEX
		{
			sortIndexByPrice(index, indexCount);
			cout << "OK INDEX_SORTED" << endl;
			break;
		}
		case 9: // DROP_INDEX
		{
			destroyIndex(index, indexCount);
			cout << "OK INDEX_DROPPED" << endl;
			break;
		}
		case 10: // FIND
		{
			int clientId;
			cout << "Enter Client ID: ";
			cin >> clientId;

			int foundDay, foundSlot;
			Appointment* result = findAppointment(w, clientId, foundDay, foundSlot);

			if (result == nullptr)
			{
				cout << "ERR NOT_FOUND" << endl;
			}
			else
			{
				cout << "OK FOUND "
				     << (clientId < 10 ? "000" : clientId < 100 ? "00" : clientId < 1000 ? "0" : "")
				     << clientId << " day=" << foundDay << " slot=" << foundSlot << " "
				     << result->service << " PKR " << result->price << endl;
			}
			break;
		}
		case 11: // SEED
		{
			if (index != nullptr)
				destroyIndex(index, indexCount);

			loadSeedWeek(w);
			cout << "OK SEED_LOADED" << endl;
			break;
		}
		case 12: // BOOK_BYVAL
		{
			int day, clientId;
			char name[30], service[30];
			float price;

			cout << "Enter Day (0-6): ";
			cin >> day;
			cout << "Enter Client ID: ";
			cin >> clientId;
			cout << "Enter Client Name: ";
			cin >> name;
			cout << "Enter Service: ";
			cin >> service;
			cout << "Enter Price: ";
			cin >> price;

			if (day < 0 || day >= DAYS_IN_WEEK)
			{
				cout << "ERR BAD_DAY" << endl;
			}
			else if (w.days == nullptr)
			{
				cout << "ERR WEEK_DESTROYED" << endl;
			}
			else
			{
				cout << "BYVAL pre count=" << w.days[day].count << " capacity=" << w.days[day].capacity << endl;
				bool result = bookByValue(w.days[day], clientId, name, service, price);
				cout << "BYVAL returned=" << (result ? 1 : 0) << endl;
				cout << "BYVAL post count=" << w.days[day].count << " capacity=" << w.days[day].capacity << endl;
			}
			break;
		}
		case 13: // DESTROY_WEEK
		{
			if (index != nullptr)
				destroyIndex(index, indexCount);

			destroyWeek(w);
			cout << "OK WEEK_DESTROYED" << endl;
			break;
		}
		case 14: // UTILS
		{
			reportSizes();

			float list[10];
			fillPrices(list, list + 10, 10);

			cout << "A2 LIST:";
			for (int i = 0; i < 10; i++)
				cout << " " << list[i];
			cout << endl;

			cout << "A2 SUM=" << sumRange(list, list + 10) << endl;

			float* maxPtr = maxElementPtr(list, list + 10);
			cout << "A2 MAX=" << *maxPtr << " OFF=" << (maxPtr - list) << endl;

			cout << "A2 ABOVE=" << countAbove(list, list + 10, 1000.0f) << endl;

			reverseInPlace(list, list + 10);
			cout << "A2 REV:";
			for (int i = 0; i < 10; i++)
				cout << " " << list[i];
			cout << endl;

			break;
		}
		default:
			cout << "ERR BAD_CMD" << endl;
		}

		system("pause");

	} while (true);

	if (index != nullptr)
		destroyIndex(index, indexCount);
	destroyWeek(w);
	cout << "BYE" << endl;

	return 0;
}


