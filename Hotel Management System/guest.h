#pragma once

struct Reservation;
struct Employee;

typedef struct Guest{
	const char *first_name;
	const char *last_name;
	char* username;
	char* password;
	int age;
	int id;
} Guest;

void create_guest(Guest ***guests, int *guest_count, char *first_name, char *last_name, int age, char *username, char *password);

Guest* get_guest_by_id(Guest **guests, int guest_count, int id);

int load_guests_from_file(Guest ***guests);

void save_guests_to_file(Guest **guests, int guest_count);

void user_create_guest(Guest ***guests, int *guest_count, Employee **employees, int employee_count);

void delete_guest(Guest ***guests, int *guest_count, int index, Reservation ***reservations, int *reservation_count);