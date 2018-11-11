#include "Date.h"

char* print_date(Date date) {
	char *str = (char*)malloc(81);
	strcpy_s(str, 80,month_type_names[date.month]);
	strcat_s(str, 80, " ");
	char day[3];
	_itoa_s(date.day, day, 10);
	strcat_s(str, 80,day);
	strcat_s(str, 80, ", ");
	char year[5];
	_itoa_s(date.year, year, 10);
	strcat_s(str, 80, year);
	return str;
}

Date get_current_date() {
	time_t t = time(NULL);
	struct tm tm; 
	localtime_s(&tm,&t);
	Date date;
	date.day = tm.tm_mday;
	date.month = (Month)(tm.tm_mon);
	date.year = tm.tm_year + 1900;
	return date;
}

Date create_date_from_string(char *str) {
	Date date;
	int count;
	char **splits = split(str, "/", &count);
	date.day = atoi(splits[0]);
	date.month = (Month)(atoi(splits[1])-1);
	date.year = 2000 + atoi(splits[2]);
	return date;
}

bool is_before(Date date_1, Date date_2) {
	if (date_1.year < date_2.day) 
		return 1;
	if (date_1.year == date_2.year && date_1.month < date_2.month)
		return 1;
	if (date_1.year == date_2.year && date_1.month == date_2.month && date_1.day < date_2.day) 
		return 1;
	return 0;
}

Date create_date(int day, Month month, int year) {
	Date date;
	date.day = day;
	date.month = month;
	date.year = year;
	return date;
}

int get_date_difference(Date date_1, Date date_2) {
	struct tm date1, date2;
	date1.tm_year = date_1.year - 1900;
	date1.tm_mday = date_1.day;
	date1.tm_mon = date_1.month;
	date1.tm_sec = 0;
	date1.tm_min = 0;
	date1.tm_hour = 0;
	date2.tm_year = date_2.year - 1900;
	date2.tm_mday = date_2.day;
	date2.tm_mon = date_2.month;
	date2.tm_sec = 0;
	date2.tm_min = 0;
	date2.tm_hour = 0;
	double seconds = difftime(mktime(&date1), mktime(&date2));
	int days = (fabs(seconds) / (float)86400)+1;
	return days;
}