#ifndef ROLL_N
#define ROLL_N 3073
#endif

/* your own N goes here */

#define P1 (((ROLL_N) % 4) + 3)
#define P2 (((ROLL_N) % 3) + 2)
#define P3 (((ROLL_N) % 5) + 1)
#define SEED ((ROLL_N) % 100)


struct Reading {
	char sensor[9];
	float value;
	char status;
};
struct Probe {

	// 8 chars + '\0', stored IN PLACE
	// 'N' nominal, 'W' warning, 'C' critical

	int probeId;
	char* callSign; // heap block, exactly length + 1
	Reading* readings; // heap ARRAY OF STRUCT VALUES
	int readingCount;
	int readingCapacity;
};
struct Fleet {
	Probe** probes;
	int count;
	int capacity;
};

// heap array of POINTERS to Probe

#define SIGN_LIMIT 20
#define SENSOR_LIMIT 8
#define MAX_PROBES 4096
#define MAX_READINGS 64
#define ID_MIN 1
#define ID_MAX 9999

int myStrLen(const char* s);
void myStrCopy(char* dest, const char* src);
int myStrCompare(const char* a, const char* b);