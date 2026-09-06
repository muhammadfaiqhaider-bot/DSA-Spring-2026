#pragma once

#ifndef ROLL_N
#define ROLL_N 3073
#endif

/* your own N goes here */

#define P1 (((ROLL_N) % 4) + 3)
#define P2 (((ROLL_N) % 3) + 2)
#define P3 (((ROLL_N) % 5) + 1)
#define SEED ((ROLL_N) % 100)

struct Appointment {
	int clientId;
	char* clientName;
	char service[9];
	float price;
};
struct DaySchedule {
	Appointment* slots;      
	int	count;
	int capacity;
	// heap block, exactly length + 1
	// 8 chars + '\0', stored IN PLACE
	// heap ARRAY OF STRUCT VALUES

};
struct Week {
	DaySchedule* days; // heap array of 7 DaySchedule VALUES,
	int dayCount; // each owning a slot array of its own length
};
#define DAYS_IN_WEEK 7
#define NAME_LIMIT 14
#define SERVICE_LIMIT 8
#define MAX_SLOTS 40
#define CLIENT_MIN 1
#define CLIENT_MAX 9999