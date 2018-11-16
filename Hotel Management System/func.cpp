#include "func.h"
#include <string>
#include <stdlib.h>
#include "guest.h"
#include "Employee.h"

char** split(char* str, const char* delimeter, int  *count) {
	//splits a string on a delimiter and returns an array of strings
	char *context,*token;
	char **result = (char**)malloc(0);
	int i = 0;

	 token = strtok_s(str, delimeter,&context);

	while (token != NULL) {
		
		result = (char**)realloc(result, sizeof(char*)*(i+1));
		result[i] = (char*)malloc(sizeof(char)*strlen(token)+1);
		strcpy_s(result[i], strlen(token)+1,token);
		token = strtok_s(NULL, delimeter,&context);
		i++;
	}
	*count = i+1;
	return result;
}

char* get_string(const char *type) {
	//read in a string from the user
	//don't allow entry of ',' chars because they cannot be parsed properly when written to file
	char *str = (char*)malloc(81);
	do {
		if (strstr(str, ","))
			printf("%s cannot contain ',' character.\n",type);
		fgets(str, 80, stdin);
		str[strcspn(str, "\n")] = 0;//strip \n
	} while (strstr(str, ","));
	return str;
}

int get_int(bool *success) {
	//read in an int from the user
	char *int_str = get_string("Number");
	char *endprt;
	int num = strtol(int_str,&endprt,10);
	if (num != 0 || endprt != int_str) {
		*success = true;
		return num;
	}
	else {
		*success = false;
		return 1;
	}
}

float get_float() {
	//read in a float from the user
	float num;
	scanf_s("%f", &num);
	getc(stdin);
	return num;
}

bool validate_username(char *username, Guest **guests, int guest_count, Employee **employees, int employee_count) {
	//determine if a username is unique base on existing guest and employee accounts
	for (int i = 0; i < guest_count; i++)
		if (!strcmp(guests[i]->username, username))
			return false;
	for (int i = 0; i < employee_count; i++)
		if (!strcmp(employees[i]->username, username))
			return false;
	return true;
}

void pause() {
	printf("Press enter to Continue\n");
	getchar();
}

void clear() {
	system("cls||clear");
}