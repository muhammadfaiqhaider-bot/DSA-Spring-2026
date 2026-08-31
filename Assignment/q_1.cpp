#include <iostream>
#include "Q_1.h"
using namespace std;

// QUESTION - 01 (PART-A)

int myStrLen(const char *s)
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

void myStrCopy(char *dest, const char *src)
{
	int index = 0;
	while (*(src + index) != '\0')
	{
		*(dest + index) = *(src + index);
		index++;
	}
	*(dest + index) = '\0';
}

int myStrCompare(const char *a, const char *b)
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

char *cloneCString(const char *src)
{
	char *clone = new char[myStrLen(src) + 1];
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

	payloadProbe = sizeof(int) + sizeof(int) + sizeof(int) + (int)sizeof(Reading *) + (int)sizeof(char *);
	sizeOfProbe = sizeof(Probe);
	paddingProbe = sizeOfProbe - payloadProbe;

	// for Fleet

	int paddingFleet = 0;
	int payloadFleet = 0;
	int sizeOfFleet = 0;

	payloadFleet = sizeof(int) + sizeof(int) + sizeof(Probe **);
	sizeOfFleet = sizeof(Fleet);
	paddingFleet = sizeOfFleet - payloadFleet;

	cout << "Size of: " << endl;
	cout << "char: " << (int)sizeof(char) << " int: " << (int)sizeof(int) << " float: " << (int)sizeof(float) << " ptr: " << (int)sizeof(char *) << "\n";

	cout << "------------------------------------------------------" << endl;
	cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "   Reading     |        " << sizeOfReading << "         |    " << payloadReading << "   |    " << paddingReading << endl;
	cout << "   Probe       |        " << sizeOfProbe << "         |    " << payloadProbe << "   |    " << paddingProbe << endl;
	cout << "   Fleet       |        " << sizeOfFleet << "         |    " << payloadFleet << "   |    " << paddingFleet << endl;
}

// PART B

void initFleet(Fleet &f, int initialCapacity)
{

	if (initialCapacity < 1)
		initialCapacity = 1;
	f.capacity = initialCapacity;
	f.count = 0;

	f.probes = new Probe *[initialCapacity];
	for (int i = 0; i < initialCapacity; i++)
	{
		f.probes[i] = nullptr;
	}
}

bool growFleet(Fleet &f)
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

	Probe **newProbes = new Probe *[newCapacity];
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

bool addProbe(Fleet &f, int probeId, const char *callSign)
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

	Probe *pro = new Probe;
	pro->probeId = probeId;
	pro->callSign = cloneCString(callSign);
	pro->readingCapacity = 0;
	pro->readingCount = 0;
	pro->readings = nullptr;

	f.probes[f.count] = pro;
	f.count++;

	return true;
}

bool growReadings(Probe *p)
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

	Reading *newReading = new Reading[newCapacity];

	for (int i = 0; i < p->readingCount; i++)
	{
		newReading[i] = p->readings[i];
	}

	delete[] p->readings;
	p->readingCapacity = newCapacity;
	p->readings = newReading;

	return true;
}

bool addReading(Probe *p, const char *sensor, float value, char status)
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

Probe **findSlot(const Fleet &f, int probeId)
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

Probe *findProbe(const Fleet &f, int probeId)
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

float probeHealth(const Probe *p)
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

void printProbe(const Probe *p)
{
	cout << "============================================================" << endl;
	cout << "ProbeID           Call Sign          LOGS       Health   " << endl;
	cout << p->probeId << "          " << p->callSign << "         " << p->readingCount << "         " << probeHealth(p) << endl;
	cout << "------------------------------------------------------------" << endl;
	for (int i = 0; i < p->readingCount; i++)
	{
		cout << "Log -" << i + 1 << "  " << p->readings[i].sensor << "  " << p->readings[i].status << "  " << p->readings[i].value << endl;
	}
}

void printFleet(const Fleet &f)
{
	for (int i = 0; i < f.count; i++)
	{
		cout << "FLEET " << char(65 + i) << endl;
		for (int j=0; j<f.count; j++)
		{
			printProbe(f.probes[i]);
		}
	}
}

void destroyProbe(Probe *&p)
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

void compactFleet(Fleet &f, int removedIndex)
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

bool removeProbe(Fleet &f, int probeId)
{
	int index = 0;
	Probe **temp = findSlot(f, probeId);
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

void deepCopyProbe(const Probe *src, Probe *&dest)
{

	if (src == nullptr)
	{
		dest = nullptr;
	}
	else
	{
		Probe *temp = new Probe;
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

void aliasCopyProbe(Probe *src, Probe *dest)
{
	if (src != nullptr && dest != nullptr)
	{
		dest->probeId = src->probeId;
		dest->callSign = src->callSign;
		dest->readingCapacity = src->readingCapacity;
		dest->readingCount = src->readingCount;
		if (src->readingCapacity > 0)
		{
			for (int i = 0; i < src->readingCount; i++)
			{
				myStrCopy(dest->readings[i].sensor, src->readings[i].sensor);
				dest->readings[i].status = src->readings[i].status;
				dest->readings[i].value = src->readings[i].value;
			}
		}
	}
}

void destroyFleet(Fleet &f)
{
	for (int i = 0; i < f.count; i++)
	{
		for (int j = 0; j < f.probes[i]->readingCount; j++)
		{

			delete f.probes[i]->readings[j].sensor;
		}
		f.probes[i]->readingCount = 0;
		f.probes[i]->readingCapacity = 0;
		delete[] f.probes[i]->readings;
		delete[] f.probes[i]->callSign;
		delete f.probes[i];
	}

	delete[] f.probes;

	f.probes = nullptr;
	f.count = 0;
	f.capacity = 0;
}

bool addProbeByValue(Fleet f, int probeId, const char *callSign)
{
	addProbe(f, probeId, callSign);
	return true;
}

int main()
{
	char name[10] = {'f', 'a', 'i', 'q'};
	char name2[10] = {'a', 'a', 'k', 'q'};

	Fleet f;
	printFleet(f);

	return 0;
}