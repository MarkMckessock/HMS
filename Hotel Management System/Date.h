#pragma once
#include "MonthTypes.h"
#include "stdlib.h"
#include <string.h>
#include <time.h>
#include "func.h"
#include <math.h>

typedef struct Date {
	int day;
	int year;
	Month month;
} Date;

char* print_date(Date date);

Date get_current_date();

Date create_date_from_string(char *str);

bool is_before(Date date_1, Date date_2);

Date create_date(int day, Month month, int year);

int get_date_difference(Date date_1, Date date_2);