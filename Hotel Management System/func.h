#pragma once

struct Guest;
struct Employee;

char** split(char* str, const char* delimeter, int *count);

char* get_string(const char *type);

int get_int(bool *success);

float get_float();

bool validate_username(char *username, Guest **guests, int guest_count, Employee **employees, int employee_count);

void pause();

void clear();