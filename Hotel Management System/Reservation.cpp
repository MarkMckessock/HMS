#include "Reservation.h"

void save_reservations_to_file(Reservation **reservations, int reservation_count) {
	FILE *fp;
	fopen_s(&fp, "reservations.txt", "w");
	fprintf(fp, "Reservation Count: %i\n", reservation_count);
	for (int i = 0; i < reservation_count; i++)
		fprintf(fp,"%i,%i,%i,%i,%i,%i,%i,%i,%i\n", reservations[i]->id, reservations[i]->room->id, reservations[i]->guest->id, reservations[i]->start.day, reservations[i]->start.month, reservations[i]->start.year, reservations[i]->end.day, reservations[i]->end.month, reservations[i]->end.year);
	fclose(fp);
}

int load_reservations_from_file(Reservation ***reservations,Room **rooms,int room_count,Guest **guests,int guest_count) {
	int reservation_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "reservations.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			reservation_count = atoi(strstr(line, "Reservation Count: ") + 19);
		}
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Reservation *reservation = (Reservation *)malloc(sizeof(Reservation));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			reservation->id = atoi(splits[0]);
			reservation->room = get_room_by_id(rooms,room_count,atoi(splits[1]));
			reservation->guest = get_guest_by_id(guests, guest_count, atoi(splits[2]));
			reservation->start.day = atoi(splits[3]);
			reservation->start.month = (Month)atoi(splits[4]);
			reservation->start.year = atoi(splits[5]);
			reservation->end.day = atoi(splits[6]);
			reservation->end.month = (Month)atoi(splits[7]);
			reservation->end.year = atoi(splits[8]);
			(*reservations) = (Reservation **)realloc(*reservations, (i + 1) * sizeof(Reservation*));
			(*reservations)[i] = reservation;
			i++;
		}
		fclose(fp);
		return reservation_count;
	}
	else {
		return 0;
	}
}

int get_hotel_reservations(Reservation **reservations, int reservation_count, Hotel *hotel, Reservation ***result) {
	int count = 0;
	*result = (Reservation**)malloc(0);
	for (int i = 0; i < reservation_count; i++) {
		if (reservations[i]->room->hotel == hotel) {
			*result = (Reservation**)realloc(*result, (count + 1) * sizeof(Reservation*));
			(*result)[count] = reservations[i];
			count++;
		}
	}
	return count;
}

void create_reservation(Reservation ***reservations, int *reservation_count,Guest *guest,Room *room,Date start,Date end) {
	Reservation *reservation = (Reservation*)malloc(sizeof(Reservation));
	reservation->guest = guest;
	reservation->room = room;
	reservation->start = start;
	reservation->end = end;
	reservation->id = *reservation_count == 0 ? 1 : (*reservations)[*reservation_count - 1]->id + 1;
	*reservations = (Reservation**)realloc(*reservations, (*reservation_count + 1) * sizeof(Reservation*));
	(*reservations)[*reservation_count] = reservation;
	(*reservation_count)++;
	save_reservations_to_file(*reservations, *reservation_count);
}

void user_create_reservation(Guest **guests,int guest_count,Reservation ***reservations,int *reservation_count,Hotel *hotel,Room **rooms,int room_count) {
	printf("Create reservation:\n");
	//get guest
	printf("Choose a guest:\n");
	for (int i = 0; i < guest_count; i++)
		printf("(%i) Guest: %s, %s\n", i + 1, guests[i]->last_name, guests[i]->first_name);
	int choice = get_int();
	Guest* guest = guests[choice - 1];

	//get dates
	printf("Enter Check-In Date in the form dd/mm/yy:\n");
	char *date_str = get_string();
	Date start = create_date_from_string(date_str);
	printf("Enter Check-Out Date in the form dd/mm/yy:\n");
	date_str = get_string();
	Date end = create_date_from_string(date_str);

	//get room
	Room ***single_rooms = (Room***)malloc(0);
	int single_room_count = get_hotel_rooms_available(hotel, single_bed,rooms, room_count,*reservations,*reservation_count,single_rooms,start,end);
	Room ***double_rooms = (Room***)malloc(0);
	int double_room_count = get_hotel_rooms_available(hotel, double_bed, rooms, room_count, *reservations, *reservation_count, double_rooms,start,end);
	Room ***suites = (Room***)malloc(0);
	int suite_count = get_hotel_rooms_available(hotel, suite, rooms, room_count, *reservations, *reservation_count, suites,start,end);

	Room **first_choice = NULL, **second_choice = NULL, **third_choice = NULL;
	const char *first_name = NULL, *second_name = NULL, *third_name=NULL;
	if (single_room_count) {
		first_choice = *single_rooms;
		first_name = "Single Room";
	}
	if (double_room_count) {
		if (first_choice) {
			second_choice = *double_rooms;
			second_name = "Double Room";
		}
		else if (double_room_count) {
			first_choice = *double_rooms;
			first_name = "Double Room";
		}
	}
	if (suite_count) {
		if (second_choice) {
			third_choice = *suites;
			third_name = "Suite";
		}
		else if (first_choice) {
			second_choice = *suites;
			second_name = "Suite";
		}
		else {
			first_choice = *suites;
			first_name = "Suite";
		}
	}
	printf("Choose a room type:\n");
	if (first_choice || second_choice || third_choice) {
		if (first_choice)
			printf("(1) %s\n", first_name);
		if (second_choice)
			printf("(2) %s\n", second_name);
		if (third_name)
			printf("(3) %s\n", third_name);
		choice = get_int();
		Room *room = NULL;
		switch (choice) {
		case 1:
			room = first_choice[0];
			break;
		case 2:
			room = second_choice[0];
			break;
		case 3:
			room = third_choice[0];
			break;
		}
		create_reservation(reservations, reservation_count, guest, room, start, end);
	}
	else {
		printf("There are no rooms available for this period.\n");
		system("pause");
	}
}