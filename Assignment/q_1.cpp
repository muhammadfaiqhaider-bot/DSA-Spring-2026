#include <iostream>
#include "Q_1.h"
using namespace std;

//QUESTION - 01 (PART-A)


int myStrLen(const char* s) {
	int count = 0;
	int index = 0;
	while (*(s + index) != '\0') {
		count++;
		index++;
	}
	return count;
}

void myStrCopy(char* dest, const char* src) {
	int index = 0;
	while (*(src + index) != '\0') {
		*(dest + index) = *(src + index);
		index++;
	}
	*(dest + index) = '\0';
}


int myStrCompare(const char* a, const char* b) {
	int diff = 0;
	int index = 0;

	while (*(a + index) != '\0' || *(b + index) != '\0')
	{
		if (*(a + index) == *(b + index)) {
			index++;
		}
		else {
			diff = (int)(unsigned char)*(a + index) - (int)(unsigned char)*(b + index);
			return diff;
		}
	}
	return 0;
}


char* cloneCString(const char* src) {
	char* clone = new char [myStrLen(src) + 1];
	int index = 0;
	while (*(src + index) != '\0')
	{
		*(clone + index) = *(src + index);
		index++;
	}
	*(clone + index) = '\0';
	return clone;
}


void reportSizes() {
	// for Reading 
	int paddingReading = 0;
	int payloadReading = 0;
	int sizeOfReading = 0;

	payloadReading = 9 * sizeof(char) + sizeof(char) + sizeof(float);
	sizeOfReading = sizeof(Reading);
	paddingReading = sizeOfReading - payloadReading;

	

	//for Probe
	int paddingProbe = 0;
	int payloadProbe = 0;
	int sizeOfProbe = 0;

	payloadProbe = sizeof(int) + sizeof(int) + sizeof(int) + (int)sizeof(Reading*) + (int)sizeof(char*);
	sizeOfProbe = sizeof(Probe);
	paddingProbe = sizeOfProbe - payloadProbe;

	//for Fleet

	int paddingFleet = 0;
	int payloadFleet = 0;
	int sizeOfFleet = 0;

	payloadFleet = sizeof(int) + sizeof(int) + sizeof(Probe**);
	sizeOfFleet = sizeof(Fleet);
	paddingFleet = sizeOfFleet - payloadFleet;

	cout << "Size of: " << endl;
	cout << "char: " << (int)sizeof(char) << " int: " << (int)sizeof(int)<< " float: " << (int)sizeof(float)<< " ptr: " << (int)sizeof(char*) << "\n";
	

	cout << "------------------------------------------------------" << endl;
	cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "   Reading     |        " << sizeOfReading << "         |    " << payloadReading << "   |    " << paddingReading << endl;
	cout << "   Probe       |        " << sizeOfProbe << "         |    " << payloadProbe << "   |    " << paddingProbe << endl;
	cout << "   Fleet       |        " << sizeOfFleet << "         |    " << payloadFleet << "   |    " << paddingFleet << endl;

}





//PART B



void initFleet(Fleet& f, int initialCapacity) {
	
	if (initialCapacity < 1)initialCapacity = 1;
	f.capacity = initialCapacity;
	f.count = 0;

	f.probes = new Probe * [initialCapacity];
	for (int i = 0; i < initialCapacity; i++) {
		f.probes[i] = nullptr;
	}
}




bool growFleet(Fleet& f) {

	int newCapacity = 0;
	if (f.capacity <= 0)
		newCapacity = P1;
	else
		newCapacity = f.capacity * 2;

	if (newCapacity > MAX_PROBES) {
		cout << "ERR FLEET_FULL" << endl;
		return false;
	}


	Probe** newProbes = new Probe * [newCapacity];
	for (int i = 0; i < newCapacity; i++) {
		newProbes[i] = nullptr;
	}


	for (int i = 0; i < f.count; i++) {
		newProbes[i] = f.probes[i];
	}

	delete[]f.probes;

	f.capacity = newCapacity;
	f.probes = newProbes;

	return true;
	
}



bool addProbe(Fleet& f, int probeId, const char* callSign) {


	int  count = 0;


	if (probeId < ID_MIN || probeId > ID_MAX) {
		cout << "ERR BAD_ID" << endl;
		return false;
	}

	count = myStrLen(callSign);

	if (count < 1 || count > SIGN_LIMIT) {
		cout << "ERR BAD_SIGN" << endl;
		return false;
	}

	for (int i = 0; i < f.count; i++) {
		if (f.probes[i]->probeId == probeId) {
			cout << "ERR DUP_ID" << endl;
			return false;
		}
	}

	if (f.count == f.capacity) {
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

int main()
{
	char name[10] = { 'f','a','i','q' };
	char name2[10] = { 'a','a','k','q' };

	reportSizes();


	

	return 0;
}