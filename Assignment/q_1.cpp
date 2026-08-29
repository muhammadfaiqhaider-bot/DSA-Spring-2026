#include <iostream>
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
int main()
{
	char name[10] = { 'f','a','i','q' };
	char name2[10] = { 'a','a','k','q' };

	char* ans = cloneCString(name);
	cout << ans << endl;
	cout << myStrLen(ans);

	

	return 0;
}