#include "guest.h"
#include "Reservation.h"

Guest* get_guest_by_id(Guest **guests, int guest_count, int id) {
	for (int i = 0; i < guest_count; i++) {
		if (guests[i]->id == id)
			return guests[i];
	}
	return NULL;
}

void save_guests_to_file(Guest **guests, int guest_count) {
	FILE *fp;
	fopen_s(&fp, "guests.txt", "w");
	fprintf(fp, "Guest Count: %i\n", guest_count);
	for (int i = 0; i < guest_count; i++)
		fprintf(fp, "%i,%s,%s,%i,%s,%s\n",guests[i]->id,guests[i]->first_name,guests[i]->last_name,guests[i]->age,guests[i]->username,guests[i]->password);
	fclose(fp);
}

int load_guests_from_file(Guest ***guests) {
	int guest_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "guests.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			guest_count = atoi(strstr(line, "Guest Count: ") + 13);
		}
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Guest *guest = (Guest *)malloc(sizeof(Guest));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			guest->id = atoi(splits[0]);
			guest->first_name = splits[1];
			guest->last_name = splits[2];
			guest->age = atoi(splits[3]);
			guest->username = splits[4];
			guest->password = splits[5];
			(*guests) = (Guest **)realloc(*guests, (i + 1) * sizeof(Guest*));
			(*guests)[i] = guest;
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
	Guest *guest = (Guest*)malloc(sizeof(Guest));
	guest->first_name = first_name;
	guest->last_name = last_name;
	guest->age = age;
	guest->username = username;
	guest->password = password;
	guest->id = *guest_count == 0 ? 1 : (*guests)[*guest_count]->id + 1;
	*guests = (Guest**)realloc(*guests, (1 + *guest_count) * sizeof(Guest*));
	(*guests)[*guest_count] = guest;
	(*guest_count)++;
	save_guests_to_file(*guests, *guest_count);
}

void user_create_guest(Guest ***guests, int *guest_count) {
	system("cls");
	printf("Create new guest:\n");
	printf("Please enter first name (Hit 'enter' to go back):\n");
	char *first_name = get_string();
	if (!strcmp(first_name, ""))
		return;
	printf("Please enter last name:\n");
	char *last_name = get_string();
	printf("Enter guest age:\n");
	int age = get_int();
	printf("Please enter a username for this guest:\n");
	char *username = get_string();
	printf("Please enter a password for this user:\n");
	char *password = get_string();
	create_guest(guests, guest_count, first_name, last_name, age,username,password);
}

void delete_guest(Guest ***guests, int *guest_count, int index,Reservation ***reservations,int *reservation_count) {
	for (int i = 0; i < *reservation_count; i++)
		if ((*reservations)[i]->guest == (*guests)[index]) {
			delete_reservation_by_index(reservations, reservation_count, i);
			i--;
		}
	free((*guests)[index]);
	for (int i = index; i < (*guest_count) - 1; i++) {
		(*guests)[i] = (*guests)[i + 1];
	}
	(*guest_count)--;
	*guests = (Guest**)realloc(*guests, (*guest_count) * sizeof(Guest*));
	save_guests_to_file(*guests, *guest_count);
}