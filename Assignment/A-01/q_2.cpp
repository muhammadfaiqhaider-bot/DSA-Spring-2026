#include <iostream>
#include <iomanip>
#include "q_2.h"

using namespace std;



int myStrLen(const char* s)
{
	int count = 0;
	int index = 0;
	while (*(s + index) != '\0')
	{
		count++;
		index++;
	}
	return count;
}

void myStrCopy(char* dest, const char* src)
{
	int index = 0;
	while (*(src + index) != '\0')
	{
		*(dest + index) = *(src + index);
		index++;
	}
	*(dest + index) = '\0';
}

int myStrCompare(const char* a, const char* b)
{
	int diff = 0;
	int index = 0;

	while (*(a + index) != '\0' || *(b + index) != '\0')
	{
		if (*(a + index) == *(b + index))
		{
			index++;
		}
		else
		{
			diff = (int)(unsigned char)*(a + index) - (int)(unsigned char)*(b + index);
			return diff;
		}
	}
	return 0;
}

char* cloneCString(const char* src)
{
	char* clone = new char[myStrLen(src) + 1];
	int index = 0;
	while (*(src + index) != '\0')
	{
		*(clone + index) = *(src + index);
		index++;
	}
	*(clone + index) = '\0';
	return clone;
}

void fillPrices(float* begin, float* end, int n)
{
    for (int i = 0; begin < end; i++)
    {
        *begin = float((n + 613 * i) % 4000) / 2.0f + 250.0f;
        begin++;
    }
}

float sumRange(const float* begin, const float* end)
{
    float sum = 0;
    for (int i = 0; begin + i < end; i++)
    {
        sum += *(begin + i);
    }
    return sum;
}
float* maxElementPtr(float* begin, float* end)
{
    if (begin == end)
        return nullptr;

    float* maxElem = begin;

    for (int i = 0; begin + i < end; i++)
    {
        if (*(begin + i) > *maxElem)
            maxElem = begin + i;
    }

    return maxElem;
}

int countAbove(const float* begin, const float* end, float threshold)
{
    int count = 0;

    for (int i = 0; begin + i < end; i++)
    {
        if (*(begin + i) > threshold)
            count++;
    }
    return count;
}

void reverseInPlace(float* begin, float* end)
{
    int left = 0;
    int right = -1;
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

    cout << "------------------------------------------------------" << endl;
    cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
    cout << "------------------------------------------------------" << endl;
    cout << "  Appointment  |        " << sizeOfAppointment << "         |    " << payloadAppointment << "   |    " << paddingAppointment << endl;
    cout << "  DaySchedule  |        " << sizeOfDaySchedule << "         |    " << payloadDaySchedule << "   |    " << paddingDaySchedule << endl;
    cout << "  Week         |        " << sizeOfWeek << "         |    " << payloadWeek << "   |    " << paddingWeek << endl;
}

void initWeek(Week& w)
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

bool growDay(DaySchedule& d)
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

    Appointment* temp = new Appointment[newCapacity];

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
    //check for week if it exssist or not
    if (w.days == nullptr)
    {
        outDay = -1;
        outSlot = -1;
        return nullptr;
    }


    // itrate through each day and each day has its specific number of appoitiess if apointment found than return appointment
    for (int i = 0; i < w.dayCount; i++)
    {
        for (int j = 0; j < w.days[i].count; j++)
        {
            if (w.days[i].slots[j].clientId == clientId)
            {
                outDay = i;
                outSlot = j;
                return &w.days[i].slots[j];
            }
        }
    }

    // if no fount make return null....
    outDay = -1;
    outSlot = -1;
    return nullptr;
}

float dayRevenue(const DaySchedule& d)
{
    // js for calculating total revenue for the day
    float total = 0;
    for (int i = 0; i < d.count; i++)
    {
        total += d.slots[i].price;
    }
    return total;
}

void printDay(const DaySchedule& d, int dayIndex)
{
    const char* dayNames[7] = { "Mon", "Tue", "Wed", "Thurs", "Fri", "Sat", "Sun" };

    cout << endl;
    cout << "*************************************************************" << endl;
    cout << "============================================================" << endl;

    cout << left << setw(8) << "DAY"  << setw(8) << dayIndex + 1  << setw(8) << dayNames[dayIndex]<< setw(15) << "BOOKED"<< setw(15) << "REVENUE" << endl;
    cout << left << setw(8) << "" << setw(8) << ""<< setw(8) << ""<< setw(15) << ((d.count) + "/" + (d.capacity))<< setw(15) << dayRevenue(d) << endl;

    cout << "------------------------------------------------------------" << endl;

    if (d.count == 0)
    {
        cout << " No booking today... " << endl;
    }
    else
    {
        cout << left << setw(8) << "Slot" << setw(8) << "ID"<< setw(20) << "Client Name" << setw(20) << "Service"<< setw(10) << "Price" << endl;

        cout << "------------------------------------------------------------" << endl;

        for (int i = 0; i < d.count; i++)
        {
            cout << left << setw(8) << i+1 << setw(8) << d.slots[i].clientId  << setw(20) << d.slots[i].clientName << setw(20) << d.slots[i].service << setw(10) << d.slots[i].price<< endl;
        }
    }

    cout << "============================================================" << endl;
    cout << "*************************************************************" << endl;
    cout << endl;
}


void printWeek(const Week& w)
{
    if (w.days == nullptr)// no booking for this week......no data entered.....
    {
        cout << endl;
        cout << "Nooo booking for this week (thankyouu)" << endl;
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
    cout << "------------------------------------------------------------" << endl;
    cout << "............................................................" << endl;
    cout << "                  WEEKLY REPORT " << endl;
    cout << "............................................................" << endl;

    cout << left<< setw(20)  << "BOOKINGS : "<< totalBookings<<  setw(20) << "REVENUE : "<< totalRevenue << endl;

    cout << "------------------------------------------------------------" << endl;
    cout << endl << endl;

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
    // differenct check for calidation day count , moving appointment from same day to same day 
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

    //check if the number of appointmebts for that day is fulled so enhance the capacity
    if (w.days[toDay].count == w.days[toDay].capacity)
    {
        if (!growDay(w.days[toDay]))//if the capacity reach it limit so we can't add more appointment for the day and we return form the function 
            return false;
    }

    Appointment mov = w.days[fromDay].slots[fromSlot]; // crate appointment mov that copies the appointment
    w.days[toDay].slots[w.days[toDay].count] = mov; // and where i need to move ill mov ther sort of pasting
    w.days[toDay].count++;

    // As slot removed soo i have to move my afterwords slots one one step back and less my conunt asw..
    for (int i = fromSlot; i < w.days[fromDay].count - 1; i++)
    {
        w.days[fromDay].slots[i] = w.days[fromDay].slots[i + 1];
    }
    w.days[fromDay].count--;

    return true;
}


// function of this function is to bring all the appointments togetther in a consective memory 
Appointment** buildIndex(const Week& w, int& outCount)
{
    if (w.days == nullptr)
    {
        outCount = 0;
        return nullptr;
    }

    int total = 0;
    for (int i = 0; i < w.dayCount; i++)
        total += w.days[i].count; // track the appointments per days 

    if (total == 0)
    {
        outCount = 0;
        return nullptr;
    }

    Appointment** index = new Appointment * [total];
    int storing_index = 0;
    for (int i = 0; i < w.dayCount; i++)
    {
        for (int j = 0; j < w.days[i].count; j++)
        {
            index[storing_index] = &w.days[i].slots[j]; // index[SI] stores the pointing address to specific appointies
            storing_index++;
        }
    }

    outCount = total;
    return index;
}

void sortIndexByPrice(Appointment** index, int n)
{
    if (index == nullptr)
        return;
    //sorting ez peasy scene 
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
    cout << "===================== PRICE INDEX =====================" << endl;
    cout << "Size: " << n << endl;
    cout << "---------------------------------------------------------" << endl;

    if (index == nullptr || n == 0)
    {
        cout << "                     (no appointments)" << endl;
    }
    else
    {
        cout << left <<setw(5) << "No."<< setw(8) << "Client" << setw(16) << "Name"<< setw(10) << "Service"<< right << setw(12) << "Price" << endl;
        cout << "---------------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            cout << "[" << i << "] "
                << index[i]->clientId << "  "
                << index[i]->clientName << "  "
                << index[i]->service << "  PKR "
                << index[i]->price << endl;
        }
    }

    cout << "=========================================================" << endl << endl;
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

    int i = day.count;
    day.slots[i].clientId = clientId;
    day.slots[i].clientName = cloneCString(name);
    myStrCopy(day.slots[i].service, service);
    day.slots[i].price = price;

    day.count++;

    return true;
}

void loadSeedWeek(Week& w)
{
    destroyWeek(w);
    initWeek(w);

    const char* names[8] = { "Ayesha", "Hina", "Sana", "Mahnoor", "Zara", "Iqra", "Nimra", "Rabia" };
    const char* services[6] = { "HAIRCUT", "FACIAL", "MANI", "PEDI", "COLOR", "MAKEUP" };
    float prices[6] = { 1500.0f, 2500.0f, 800.0f, 4200.0f, 1200.0f, 3000.0f };

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
    cout << "      SALMA & SHUGUFTA BEAUTY PALOR SYSTEM  " << endl;
    cout << "-------------------------------------------" << endl << endl;

    cout << "MADE BY : MUHAMMAD FAIQ HAIDER" << endl;
    cout << "ROLL NUMBER : " << ROLL_N << " P2=" << P2 << " P3=" << P3 << endl;
    system("pause");

    Week w;
    initWeek(w);
    Appointment** index = nullptr;
    int indexCount = 0;

    int choice;
    do
    {
        system("cls");

        cout << "-------------------------------------------" << endl;
        cout << "      SALMA & SHUGUFTA BEAUTY PALOR SYSTEM  " << endl;
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

        cin >> choice;

        if (choice == 0)
            break;

        switch (choice)
        {
        case 1: // BOOK
        {
            int day, clientId;
            char name[40];
            char service[40];
            float price;

            cout << "Enter Day (1-7) : ";
            cin >> day;
            cout << "Enter Client ID : ";
            cin >> clientId;
            cout << "Enter Client name : ";
            cin >> name;
            cout << "Enter service : ";
            cin >> service;
            cout << "Enter Price : ";
            cin >> price;

            if (index != nullptr)
                destroyIndex(index, indexCount);

            if (bookAppointment(w, day - 1, clientId, name, service, price))
                cout << "Appointment Booked for day " << day << " of client "  << clientId << endl;

            break;
        }
        case 2: // CANCEL
        {
            int day, slot;
            cout << "Enter Day (1-7) : ";
            cin >> day;
            cout << "Enter Slot : ";
            cin >> slot;

            if (index != nullptr)
                destroyIndex(index, indexCount);

            if (cancelAppointment(w, day-1, slot - 1))
                cout << "Appointment cancelled of day " << day << " sloy : " << slot << endl;

            break;
        }
        case 3: // PRINT_DAY
        {
            int day;
            cout << "Enter Day (1-7): ";
            cin >> day;

            if (w.days == nullptr)
            {
                cout << "ERR WEEK_DESTROYED" << endl;
            }
            else if (day < 1 || day > DAYS_IN_WEEK)
            {
                cout << "ERR BAD_DAY" << endl;
            }
            else
            {
                printDay(w.days[day - 1], day - 1);
            }
            break;
        }
        case 4: 
        {
            printWeek(w);
            break;
        }
        case 5: // MOVE
        {
            int fromDay, fromSlot, toDay;
            cout << "Enter From Day (1-7): ";
            cin >> fromDay;
            cout << "Enter From Slot: ";
            cin >> fromSlot;
            cout << "Enter To Day (1-7): ";
            cin >> toDay;

            if (index != nullptr)
                destroyIndex(index, indexCount);

            if (moveAppointment(w, fromDay-1, fromSlot-1, toDay))
                cout << "Appointment Successfully shifted from day " << fromDay << " slot " << fromSlot << " to day " << toDay << endl;

            break;
        }
        case 6: // BUILD_INDEX
        {
            if (index != nullptr)
                destroyIndex(index, indexCount);

            index = buildIndex(w, indexCount);
            cout << "Index built successfully - " << indexCount << " appointment(s) indexed." << endl;
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
            cout << "Index sorted by price (highest to lowest)." << endl;
            break;
        }
        case 9: // DROP_INDEX
        {
            destroyIndex(index, indexCount);
            cout << "Index dropped - memory released." << endl;
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
                cout << "Apointment founded " << endl;
                cout << "Client ID : " << clientId << " day : " << foundDay<< " slot : " << foundSlot<< " " << result->service << " PKR " << result->price<< endl;
            }
            break;
        }
        case 11: 
        {
            if (index != nullptr)
                destroyIndex(index, indexCount);

            loadSeedWeek(w);
            cout << "Random Appointment Seeded Successfully  " << endl;
            break;
        }
        case 12: 
        {
            int day, clientId;
            char name[30], service[30];
            float price;

            cout << "Enter Day (1-7): ";
            cin >> day;
            cout << "Enter Client ID: ";
            cin >> clientId;
            cout << "Enter Client Name: ";
            cin >> name;
            cout << "Enter Service: ";
            cin >> service;
            cout << "Enter Price: ";
            cin >> price;

            if (day < 1 || day > DAYS_IN_WEEK)
            {
                cout << "ERR BAD_DAY" << endl;
            }
            else if (w.days == nullptr)
            {
                cout << "ERR WEEK_DESTROYED" << endl;
            }
            else
            {
                cout << "BY value count before  : " << w.days[day -1].count << " capacity : " << w.days[day -1].capacity << endl;
                bool result = bookByValue(w.days[day -1], clientId, name, service, price);
                cout << "By value returned : " << result << endl;
                cout << "By value count After : " << w.days[day].count << " capacity : " << w.days[day].capacity << endl;
            }
            break;
        }
        case 13: // DESTROY_WEEK
        {
            if (index != nullptr)
                destroyIndex(index, indexCount);

            destroyWeek(w);
            cout << "Week Destroyed Successfully " << endl;
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

            cout << "A2 SUM : " << sumRange(list, list + 10) << endl;

            float* maxPtr = maxElementPtr(list, list + 10);
            cout << "A2 MAX : " << *maxPtr << " OFF : " << (maxPtr - list) << endl;

            cout << "A2 ABOVE : " << countAbove(list, list + 10, 1000.0f) << endl;

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
    cout << "Thanlyou for Visiting...." << endl;

    return 0;
}


