#include <iostream>
#include <iomanip>
#include "Q_1.h"
using namespace std;

// QUESTION - 01 (PART-A)

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

void reportSizes()
{
	// for Reading
	int paddingReading = 0;
	int payloadReading = 0;
	int sizeOfReading = 0;

	payloadReading = 9 * sizeof(char) + sizeof(char) + sizeof(float);
	sizeOfReading = sizeof(Reading);
	paddingReading = sizeOfReading - payloadReading;

	// for Probe
	int paddingProbe = 0;
	int payloadProbe = 0;
	int sizeOfProbe = 0;

	payloadProbe = sizeof(int) + sizeof(int) + sizeof(int) + (int)sizeof(Reading*) + (int)sizeof(char*);
	sizeOfProbe = sizeof(Probe);
	paddingProbe = sizeOfProbe - payloadProbe;

	// for Fleet

	int paddingFleet = 0;
	int payloadFleet = 0;
	int sizeOfFleet = 0;

	payloadFleet = sizeof(int) + sizeof(int) + sizeof(Probe**);
	sizeOfFleet = sizeof(Fleet);
	paddingFleet = sizeOfFleet - payloadFleet;

	cout << "Size of: " << endl;
	cout << "char: " << (int)sizeof(char) << " int: " << (int)sizeof(int) << " float: " << (int)sizeof(float) << " ptr: " << (int)sizeof(char*) << "\n";

	cout << "------------------------------------------------------" << endl;
	cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "   Reading     |        " << sizeOfReading << "         |    " << payloadReading << "   |    " << paddingReading << endl;
	cout << "   Probe       |        " << sizeOfProbe << "         |    " << payloadProbe << "   |    " << paddingProbe << endl;
	cout << "   Fleet       |        " << sizeOfFleet << "         |    " << payloadFleet << "   |    " << paddingFleet << endl;
}

// PART B

void initFleet(Fleet& f, int initialCapacity)
{

	if (initialCapacity < 1)
		initialCapacity = 1;
	f.capacity = initialCapacity;
	f.count = 0;

	f.probes = new Probe * [initialCapacity];
	for (int i = 0; i < initialCapacity; i++)
	{
		f.probes[i] = nullptr;
	}
}

bool growFleet(Fleet& f)
{

	int newCapacity = 0;
	if (f.capacity <= 0)
		newCapacity = P1;
	else
		newCapacity = f.capacity * 2;

	if (newCapacity > MAX_PROBES)
	{
		cout << "ERR FLEET_FULL" << endl;
		return false;
	}

	Probe** newProbes = new Probe * [newCapacity];
	for (int i = 0; i < newCapacity; i++)
	{
		newProbes[i] = nullptr;
	}

	for (int i = 0; i < f.count; i++)
	{
		newProbes[i] = f.probes[i];
	}

	delete[] f.probes;

	f.capacity = newCapacity;
	f.probes = newProbes;

	return true;
}

bool addProbe(Fleet& f, int probeId, const char* callSign)
{

	int count = 0;

	if (probeId < ID_MIN || probeId > ID_MAX)
	{
		cout << "ERR BAD_ID" << endl;
		return false;
	}

	count = myStrLen(callSign);

	if (count < 1 || count > SIGN_LIMIT)
	{
		cout << "ERR BAD_SIGN" << endl;
		return false;
	}

	for (int i = 0; i < f.count; i++)
	{
		if (f.probes[i]->probeId == probeId)
		{
			cout << "ERR DUP_ID" << endl;
			return false;
		}
	}

	if (f.count == f.capacity)
	{
		growFleet(f);
	}

	Probe* pro = new Probe;
	pro->probeId = probeId;
	pro->callSign = cloneCString(callSign);
	pro->readingCapacity = 0;
	pro->readingCount = 0;
	pro->readings = nullptr;

	f.probes[f.count] = pro;
	f.count++;

	return true;
}

bool growReadings(Probe* p)
{

	int newCapacity = 0;
	if (p->readingCapacity <= 0)
		newCapacity = P2;
	else
		newCapacity = p->readingCapacity + P3;

	if (newCapacity > MAX_READINGS)
	{
		cout << "ERR LOG_FULL" << endl;
		return false;
	}

	Reading* newReading = new Reading[newCapacity];

	for (int i = 0; i < p->readingCount; i++)
	{
		newReading[i] = p->readings[i];
	}

	delete[] p->readings;
	p->readingCapacity = newCapacity;
	p->readings = newReading;

	return true;
}

bool addReading(Probe* p, const char* sensor, float value, char status)
{

	if (p == nullptr)
	{
		cout << "ERR NO_PROBE" << endl;
		return false;
	}

	if (myStrLen(sensor) < 1 || myStrLen(sensor) > SENSOR_LIMIT)
	{
		cout << "ERR BAD_SENSOR" << endl;
		return false;
	}

	if (status != 'N' && status != 'W' && status != 'C')
	{
		cout << "ERR BAD_STATUS" << endl;
		return false;
	}

	for (int i = 0; i < p->readingCount; i++)
	{
		if (!(myStrCompare(sensor, p->readings[i].sensor)))
		{
			cout << "ERR DUP_SENSOR." << endl;
			return false;
		}
	}

	if (p->readingCount == p->readingCapacity)
	{
		if (!growReadings(p))
			return false;
	}

	myStrCopy(p->readings[p->readingCount].sensor, sensor);
	p->readings[p->readingCount].value = value;
	p->readings[p->readingCount].status = status;

	p->readingCount++;

	return true;
}

Probe** findSlot(const Fleet& f, int probeId)
{
	if (f.count <= 0)
		return nullptr;
	if (f.probes == nullptr)
		return nullptr;

	for (int i = 0; i < f.count; i++)
	{
		if (f.probes[i]->probeId == probeId)
		{
			return &f.probes[i];
		}
	}

	return nullptr;
}

Probe* findProbe(const Fleet& f, int probeId)
{
	Fleet temp;
	temp.probes = findSlot(f, probeId);
	if (temp.probes == nullptr)
	{
		return nullptr;
	}
	else
	{
		return *temp.probes;
	}
}

float probeHealth(const Probe* p)
{
	float mean = 0;
	if (p == nullptr)
		return 0;
	if (p->readingCount <= 0)
		return 0;

	for (int i = 0; i < p->readingCount; i++)
	{
		if (p->readings[i].status == 'N')
			mean += 1;
		else if (p->readings[i].status == 'W')
			mean += 0.5;
		else if (p->readings[i].status == 'C')
			mean += 0;
	}
	mean = mean / p->readingCount;
	return mean;
}

void printProbe(const Probe* p)
{
	cout << endl;
	cout << "*************************************************************" << endl;
	cout << "============================================================" << endl;

	cout << left
		<< setw(18) << "ProbeID"
		<< setw(20) << "Call Sign"
		<< setw(12) << "LOGS"
		<< setw(10) << "Health" << endl;

	cout << left
		<< setw(18) << p->probeId
		<< setw(20) << p->callSign
		<< setw(12) << p->readingCount
		<< setw(10) << probeHealth(p) << endl;

	cout << "------------------------------------------------------------" << endl;

	for (int i = 0; i < p->readingCount; i++)
	{
		cout << left
			<< setw(8) << "Log"
			<< setw(4) << i + 1
			<< setw(20) << p->readings[i].sensor
			<< setw(8) << p->readings[i].status
			<< setw(10) << p->readings[i].value
			<< endl;
	}
	cout << "------------------------------------------------------------" << endl;
	cout << "*************************************************************" << endl;
	cout << endl;

}

void printFleet(const Fleet& f)
{
	for (int i = 0; i < f.count; i++)
	{
		printProbe(f.probes[i]);
	}
}

void destroyProbe(Probe*& p)
{
	if (p != nullptr)
	{
		delete[] p->callSign;

		if (p->readingCount > 0)
		{
			delete[] p->readings;
			p->readings = nullptr;
		}

		delete p;
		p = nullptr;
	}
}

void compactFleet(Fleet& f, int removedIndex)
{
	if (removedIndex >= 0 && removedIndex < f.count)
	{
		for (int i = removedIndex; i < f.count - 1; i++)
		{
			f.probes[i] = f.probes[i + 1];
		}
		f.probes[f.count - 1] = nullptr;
		f.count--;
	}
}

bool removeProbe(Fleet& f, int probeId)
{
	int index = 0;
	Probe** temp = findSlot(f, probeId);
	if (temp == nullptr)
	{
		cout << "ERR NOT_FOUND" << endl;
		return false;
	}

	for (int i = 0; i < f.count; i++)
	{
		if (f.probes[i]->probeId == probeId)
			index = i;
	}

	destroyProbe(f.probes[index]);
	compactFleet(f, index);

	return true;
}

void deepCopyProbe(const Probe* src, Probe*& dest)
{

	if (src == nullptr)
	{
		dest = nullptr;
	}
	else
	{
		Probe* temp = new Probe;
		temp->probeId = src->probeId;
		temp->callSign = cloneCString(src->callSign);
		if (src->readingCapacity > 0)
		{
			temp->readings = new Reading[src->readingCapacity];
			temp->readingCount = src->readingCount;
			temp->readingCapacity = src->readingCapacity;
			for (int i = 0; i < src->readingCount; i++)
			{
				myStrCopy(temp->readings[i].sensor, src->readings[i].sensor);
				temp->readings[i].status = src->readings[i].status;
				temp->readings[i].value = src->readings[i].value;
			}
		}
		else
		{
			temp->readings = nullptr;
			temp->readingCount = 0;
			temp->readingCapacity = 0;
		}
		dest = temp;
	}
}

void aliasCopyProbe(Probe* src, Probe* dest)
{
	if (src != nullptr && dest != nullptr)
	{
		dest->probeId = src->probeId;
		dest->callSign = src->callSign;
		dest->readings = src->readings;
		dest->readingCapacity = src->readingCapacity;
		dest->readingCount = src->readingCount;
	}
}

void destroyFleet(Fleet& f)
{
	for (int i = 0; i < f.count; i++)
	{
		destroyProbe(f.probes[i]);
	}

	delete[] f.probes;

	f.probes = nullptr;
	f.count = 0;
	f.capacity = 0;
}

bool addProbeByValue(Fleet f, int probeId, const char* callSign)
{
	if (probeId < ID_MIN || probeId > ID_MAX)
	{
		cout << "ERR BAD_ID" << endl;
		return false;
	}

	int len = myStrLen(callSign);

	if (len < 1 || len > SIGN_LIMIT)
	{
		cout << "ERR BAD_SIGN" << endl;
		return false;
	}

	for (int i = 0; i < f.count; i++)
	{
		if (f.probes[i]->probeId == probeId)
		{
			cout << "ERR DUP_ID" << endl;
			return false;
		}
	}

	if (f.count == f.capacity)
	{
		growFleet(f);
	}

	Probe* pro = new Probe;
	pro->probeId = probeId;
	pro->callSign = cloneCString(callSign);
	pro->readingCapacity = 0;
	pro->readingCount = 0;
	pro->readings = nullptr;

	f.probes[f.count] = pro;
	f.count++;

	return true;
}

bool mergeFleets(Fleet& target, const Fleet& source)
{
	for (int i = 0; i < source.count; i++)
	{
		if (!findProbe(target, source.probes[i]->probeId))
		{
			if (!addProbe(target, source.probes[i]->probeId, source.probes[i]->callSign))
				return false;

			Probe* newProbe = findProbe(target, source.probes[i]->probeId);

			for (int j = 0; j < source.probes[i]->readingCount; j++)
			{
				if (!addReading(newProbe, source.probes[i]->readings[j].sensor, source.probes[i]->readings[j].value, source.probes[i]->readings[j].status))
					return false;
			}
		}
	}
	return true;
}

void loadFleetA(Fleet& f)
{
	destroyFleet(f);
	initFleet(f, P1);

	const char* signs[8] = { "Voyager", "Pathfinder", "Odyssey", "Horizon", "Sentinel", "Aurora", "Vanguard", "Meridian" };
	const char* senser[6] = { "TEMP-A", "PWR-BUS", "RAD-CNT", "GYRO-X", "COMMS-1", "FUEL-P" };
	char status[3] = { 'N', 'W', 'C' };

	int total = (SEED % 3) + 3;

	for (int i = 0; i < total; i++)
	{
		int id = 1000 + SEED + 11 * i;
		addProbe(f, id, signs[(SEED + i) % 8]);

		Probe* p = findProbe(f, id);

		int logs = (SEED + i) % 4;
		for (int j = 0; j < logs; j++)
		{
			float value = (float)(SEED + 10 * i + 3 * j) + 0.5f;
			char st = status[(SEED + 2 * i + j) % 3];
			addReading(p, senser[(SEED + i + j) % 6], value, st);
		}
	}
}

void loadFleetB(Fleet& f)
{
	destroyFleet(f);
	initFleet(f, 2);

	const char* senser[6] = { "TEMP-A", "PWR-BUS", "RAD-CNT", "GYRO-X", "COMMS-1", "FUEL-P" };
	char status[3] = { 'N', 'W', 'C' };


	int id1 = 1000 + SEED;
	addProbe(f, id1, "Relay-Alpha");
	Probe* p1 = findProbe(f, id1);
	addReading(p1, senser[SEED % 6], (float)SEED + 0.5f, status[SEED % 3]);


	int id2 = 8000 + SEED;
	addProbe(f, id2, "Relay-Beta");
	Probe* p2 = findProbe(f, id2);
	addReading(p2, senser[(SEED + 1) % 6], (float)SEED + 20.5f, status[(SEED + 1) % 3]);
	addReading(p2, senser[(SEED + 2) % 6], (float)SEED + 40.5f, status[(SEED + 2) % 3]);
}



int main()
{
	cout << "-------------------------------------------" << endl;
	cout << "      MISSION CONTROL SYSTEM  " << endl;
	cout << "-------------------------------------------" << endl << endl;

	cout << "NAME : MUHAMMAD FAIQ HAIDER" << endl;
	cout << "ROLL NUMBER : " << ROLL_N << " P1=" << P1 << " P2=" << P2 << " P3=" << P3 << endl;

	Fleet A, B;
	initFleet(A, P1);
	initFleet(B, 2);
	Probe* clone = nullptr;


	cout << "-------------------------------------------" << endl;
	cout << " MISSION CONTROL - COMMAND GUIDE" << endl;
	cout << "-------------------------------------------" << endl;
	cout << " 0  EXIT" << endl;
	cout << " 1  ADD          -> 1 <id> <callSign>" << endl;
	cout << " 2  LOG          -> 2 <id> <sensor> <value> <status>" << endl;
	cout << " 3  REMOVE       -> 3 <id>" << endl;
	cout << " 4  FIND         -> 4 <id>" << endl;
	cout << " 5  PRINT_A      -> 5" << endl;
	cout << " 6  GROW         -> 6" << endl;
	cout << " 7  ADD_BYVAL    -> 7 <id> <callSign>" << endl;
	cout << " 8  CLONE        -> 8 <id>" << endl;
	cout << " 9  PRINT_CLONE  -> 9" << endl;
	cout << "10  ALIAS        -> 10 <id>" << endl;
	cout << "11  SEED_A       -> 11" << endl;
	cout << "12  SEED_B       -> 12" << endl;
	cout << "13  PRINT_B      -> 13" << endl;
	cout << "14  MERGE_B      -> 14" << endl;
	cout << "15  MERGE_SELF   -> 15" << endl;
	cout << "16  DESTROY      -> 16" << endl;
	cout << "17  SIZES        -> 17" << endl;
	cout << "-------------------------------------------" << endl;
	cout << "-------------------------------------------" << endl;

	int cmd;
	do
	{
		system("cls");

		cout << "-------------------------------------------" << endl;
		cout << " MISSION CONTROL - COMMAND GUIDE" << endl;
		cout << "-------------------------------------------" << endl;
		cout << " 0  EXIT" << endl;
		cout << " 1  ADD PROBE (manually) " << endl;
		cout << " 2  ADD LOGs for exsisting Probe " << endl;
		cout << " 3  REMOVE probe by ID " << endl;
		cout << " 4  FIND probe by ID " << endl;
		cout << " 5  PRINT Fleet A " << endl;
		cout << " 6  GROW Fleet Size " << endl;
		cout << " 7  Add PROBE by Value " << endl;
		cout << " 8  CLONE/COPY Probe " << endl;
		cout << " 9  PRINT CLONED PROBE " << endl;
		cout << "10  ALIAS Probe" << endl;
		cout << "11  SEED-A     " << endl;
		cout << "12  SEED-B      " << endl;
		cout << "13  PRINT Fleet B" << endl;
		cout << "14  MERGE Fleet B to Fleet A" << endl;
		cout << "15  MERGE Fleet A to Fleet A " << endl;
		cout << "16  DESTROY Fleet     " << endl;
		cout << "17  Sizes" << endl;
		cout << "-------------------------------------------" << endl;

		cin >> cmd;

		if (cmd == 0)
			break;

		switch (cmd)
		{
		case 1:
		{
			system("cls");
			int id;
			char nameofprobe[20];
			cout << "Enter ID of Probe ( 1 - 9999 ) : ";

			cin >> id;
			cout << "Enter name of the probe : ";
			cin >> nameofprobe;

			if (addProbe(A, id, nameofprobe))
				cout << "Probe ADDED successfully!! " << endl;

			break;
		}
		case 2:
		{
			int id;
			char sensor[30];
			float value;
			char status;
			cout << "Enter ID of Sensor : ";
			cin >> id;
			cout << "Enter name of Sensor: ";
			cin >> sensor;
			cout << "Enter value of Sensor: ";
			cin >> value;
			cout << "Enter Status of Sensor (N/W/C) ";
			cin >> status;

			Probe* p = findProbe(A, id);
			if (p == nullptr)
			{
				cout << "ERR NOT_FOUND" << endl;
			}
			else
			{
				if (addReading(p, sensor, value, status))
					cout << "OK LOG_ADDED " << id << " " << sensor << " " << value << " " << status << endl;
			}
			break;
		}
		case 3:
		{
			int id;
			cout << "Enter Id of Probe You want to remove : ";
			cin >> id;
			if (removeProbe(A, id))
				cout << "OK PROBE_REMOVED " << id << endl;
			break;
		}
		case 4:
		{
			int id;
			cout << "Enter the ID of probe you want to find : ";
			cin >> id;
			Probe* p = findProbe(A, id);
			if (p == nullptr)
			{
				cout << "ERR NOT_FOUND" << endl;
			}
			else
			{
				cout << "OK FOUND " << id << endl;
				printProbe(p);
			}
			break;
		}
		case 5:
		{
			cout << "Fleet A : " << endl;
			printFleet(A);
			break;
		}
		case 6:
		{
			if (growFleet(A))
				cout << "OK FLEET_GROWN capacity=" << A.capacity << endl;
			break;
		}
		case 7:
		{
			int id;
			char buf[30];
			cout << "Enter the ID of the Probe: ";
			cin >> id;
			cout << "Enter the Name of the Probe: ";
			cin >> buf;

			cout << "Probe pre count: " << A.count << " capacity: " << A.capacity << endl;
			bool result = addProbeByValue(A, id, buf);
			cout << "By value Resturned Status: ";
			if (result)
			{
				cout << result << endl;
				cout << "Successfully added probe by value " << endl;;
			}
			else
			{
				cout << result << endl;;
			}
			cout << "Post count: " << A.count << " capacity: " << A.capacity << endl;
			break;
		}
		case 8:
		{
			cout << "Enter ID of probe you want to clone: ";
			int id;
			cin >> id;
			Probe* p = findProbe(A, id);
			if (p == nullptr)
			{
				cout << "ERR NOT_FOUND" << endl;
			}
			else
			{
				destroyProbe(clone);
				deepCopyProbe(p, clone);
				cout << "OK CLONED " << id << endl;
			}
			break;
		}
		case 9:
		{
			if (clone == nullptr)
			{
				cout << "ERR NO_CLONE" << endl;
			}
			else
			{
				cout << "CLONE:" << endl;
				printProbe(clone);
			}
			break;
		}
		case 10:
		{
			cout << "Enter the ID of Probe you want to do Alias of : ";
			int id;
			cin >> id;
			Probe* found = findProbe(A, id);
			if (found == nullptr)
			{
				cout << "ERR NOT_FOUND" << endl;
			}
			else
			{
				Probe dummyPro;
				dummyPro.probeId = 0;
				dummyPro.callSign = nullptr;
				dummyPro.readings = nullptr;
				dummyPro.readingCount = 0;
				dummyPro.readingCapacity = 0;

				aliasCopyProbe(found, &dummyPro);

				int sameName = (dummyPro.callSign == found->callSign);
				int sameReadings = (dummyPro.readings == found->readings);
				cout << "Status Indicator 1 (same) and 0 (different)" << endl;

				cout << "Alias Probe name : " << sameName << " Logs/Readings : " << sameReadings << endl;

				if (dummyPro.callSign != nullptr && myStrLen(dummyPro.callSign) > 0)
					dummyPro.callSign[0] = 'Z';

				char st;
				if (dummyPro.readings != nullptr && dummyPro.readingCount > 0)
				{
					dummyPro.readings[0].status = 'C';
					st = found->readings[0].status;
				}
				else
				{
					st = '-';
				}

				cout << "ALIAS after sign : " << found->callSign << " log " << st << endl;
			}
			break;
		}
		case 11:
		{
			loadFleetA(A);
			cout << "SEED Fleet A count: " << A.count << endl;
			break;
		}
		case 12:
		{
			loadFleetB(B);
			cout << "SEED Fleet B count: " << B.count << endl;
			break;
		}
		case 13:
		{
			cout << "B:" << endl;
			printFleet(B);
			break;
		}
		case 14: // MERGE_B
		{
			int before = A.count;
			if (mergeFleets(A, B))
			{
				int added = A.count - before;
				cout << "OK MERGED added=" << added << " count=" << A.count
					<< " capacity=" << A.capacity << endl;
			}
			else
			{
				cout << "ERR MERGE_FAILED" << endl;
			}
			break;
		}
		case 15: // MERGE_SELF
		{
			mergeFleets(A, A);
			break;
		}
		case 16: // DESTROY
		{
			destroyFleet(A);
			cout << "OK FLEET_DESTROYED" << endl;
			break;
		}
		case 17: // SIZES
		{
			reportSizes();
			break;
		}
		default:
			cout << "ERR BAD_CMD" << endl;
		}

		system("pause");

	} while (true);

	if (clone != nullptr)
		destroyProbe(clone);
	destroyFleet(A);
	destroyFleet(B);
	cout << "BYE" << endl;

	return 0;
}