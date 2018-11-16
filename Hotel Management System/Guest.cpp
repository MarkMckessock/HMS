#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "func.h"
#include "guest.h"
#include "Reservation.h"

Guest* get_guest_by_id(Guest **guests, int guest_count, int id) {
	//get guest with the specified id
	//Return: pointer to guest or NULL if not found
	for (int i = 0; i < guest_count; i++) {
		if (guests[i]->id == id)
			return guests[i];
	}
	return NULL;
}

void save_guests_to_file(Guest **guests, int guest_count) {
	//save all guests to file
	//Format: id,first name,last name,age,username,password
	FILE *fp;
	fopen_s(&fp, "guests.txt", "w");
	fprintf(fp, "Guest Count: %i\n", guest_count);
	for (int i = 0; i < guest_count; i++)
		fprintf(fp, "%i,%s,%s,%i,%s,%s\n",guests[i]->id,guests[i]->first_name,guests[i]->last_name,guests[i]->age,guests[i]->username,guests[i]->password);
	fclose(fp);
}

int load_guests_from_file(Guest ***guests) {
	//load guests from file and parse data into guest array
	//Return: number of guests loaded
	int guest_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "guests.txt", "r");
	if (fp) {//check if file exists
		char line[81];
		//if file is not empty, get the guest count
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			guest_count = atoi(strstr(line, "Guest Count: ") + 13);
		}
		//read file while not at EOF
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Guest *guest = (Guest *)malloc(sizeof(Guest)); //allocate new guest pointer in memory
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);//split the string from the file based on ',' delimiter
			guest->id = atoi(splits[0]);
			guest->first_name = splits[1];
			guest->last_name = splits[2];
			guest->age = atoi(splits[3]);
			guest->username = splits[4];
			guest->password = splits[5];
			(*guests) = (Guest **)realloc(*guests, (i + 1) * sizeof(Guest*)); //increase guests array size by one
			(*guests)[i] = guest;//append guest to array
			i++;
		}
		fclose(fp);
		return guest_count;
	}
	else {
		return 0;
	}
}

void create_guest(Guest ***guests, int *guest_count, char *first_name, char *last_name, int age,char *username,char *password) {
	//Creates a guest object and adds it to the array
	Guest *guest = (Guest*)malloc(sizeof(Guest));
	guest->first_name = first_name;
	guest->last_name = last_name;
	guest->age = age;
	guest->username = username;
	guest->password = password;
	guest->id = *guest_count == 0 ? 1 : (*guests)[*guest_count-1]->id + 1; //assign guest id to 1 if there are no other guests or the 1 plus the previous id
	*guests = (Guest**)realloc(*guests, (1 + *guest_count) * sizeof(Guest*));
	(*guests)[*guest_count] = guest;
	(*guest_count)++;
	save_guests_to_file(*guests, *guest_count);
}

void user_create_guest(Guest ***guests, int *guest_count,Employee **employees, int employee_count) {
	//prompt user for data to create guest
	bool valid = true,success;
	int age;
	char *username;
	clear();
	printf("Create new guest:\n");
	printf("Please enter first name (Hit 'enter' to go back):\n");
	char *first_name = get_string("Name");
	//check if string is empty and return to menu if it is
	if (!strcmp(first_name, ""))
		return;
	printf("Please enter last name:\n");
	char *last_name = get_string("Name");
	printf("Enter guest age:\n");
	do {
		age = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
	} while (!success);
	//check that username is not a duplicate
	do {
		if (!valid) {
			printf("Username already in use. Please choose another:\n");
		}
		else {
			printf("Please enter a username:\n");
		}
		username = get_string("Username");
		valid = validate_username(username, *guests, *guest_count, employees, employee_count);
	} while (!valid);
	printf("Please enter a password:\n");
	char *password = get_string("Password");
	create_guest(guests, guest_count, first_name, last_name, age,username,password);
}

void delete_guest(Guest ***guests, int *guest_count, int index,Reservation ***reservations,int *reservation_count) {
	//deletes a guest object by index and any dependant reservations
	for (int i = 0; i < *reservation_count; i++)
		if ((*reservations)[i]->guest == (*guests)[index]) {//if reservation guest is current guest, delete reservation
			delete_reservation_by_index(reservations, reservation_count, i);
			i--;
		}
	free((*guests)[index]);//frees allocated memory
	for (int i = index; i < (*guest_count) - 1; i++) {
		(*guests)[i] = (*guests)[i + 1];
	}
	(*guest_count)--;
	*guests = (Guest**)realloc(*guests, (*guest_count) * sizeof(Guest*));//shrink the array by one element
	save_guests_to_file(*guests, *guest_count);
}