#include "func.h"
#include <string>
#include <stdlib.h>

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

char* get_string() {
	char *str = (char*)malloc(81);
	fgets(str, 80, stdin);
	str[strcspn(str, "\n")] = 0;//strip \n
	return str;
}

int get_int() {
	int num;
	scanf_s("%i", &num);
	getc(stdin);
	return num;
}

float get_float() {
	float num;
	scanf_s("%f", &num);
	getc(stdin);
	return num;
}