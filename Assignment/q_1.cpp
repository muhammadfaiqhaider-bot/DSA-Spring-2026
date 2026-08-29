#include <iostream>
#include "Q_1.h"
using namespace std;


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

	payloadFleet = sizeof(int) + sizeof(int) + sizeof(Fleet**);
	sizeOfFleet = sizeof(Fleet);
	paddingFleet = sizeOfFleet - payloadFleet;

	cout << "------------------------------------------------------" << endl;
	cout << "Structure Name | Size of Structure | Payload | Padding" << endl;
	cout << "------------------------------------------------------" << endl;
	cout << "   Reading     |        " << sizeOfReading << "         |    " << payloadReading << "   |    " << paddingReading << endl;
	cout << "   Probe       |        " << sizeOfProbe << "         |    " << payloadProbe << "   |    " << paddingProbe << endl;
	cout << "   Fleet       |        " << sizeOfFleet << "         |    " << payloadFleet << "   |    " << paddingFleet << endl;

}
int main()
{
	char name[10] = { 'f','a','i','q' };
	char name2[10] = { 'a','a','k','q' };

	reportSizes();


	

	return 0;
}