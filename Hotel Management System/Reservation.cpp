#include "Reservation.h"
#include <stdio.h>
#include "func.h"
#include <string>

void save_reservations_to_file(Reservation **reservations, int reservation_count) {
	//save reservation array to file
	//Format: id,room id,guest id,start day, start month, start year,end day,end month,end year
	FILE *fp;
	fopen_s(&fp, "reservations.txt", "w");
	fprintf(fp, "Reservation Count: %i\n", reservation_count);
	for (int i = 0; i < reservation_count; i++)
		fprintf(fp,"%i,%i,%i,%i,%i,%i,%i,%i,%i\n", reservations[i]->id, reservations[i]->room->id, reservations[i]->guest->id, reservations[i]->start.day, reservations[i]->start.month, reservations[i]->start.year, reservations[i]->end.day, reservations[i]->end.month, reservations[i]->end.year);
	fclose(fp);
}

int load_reservations_from_file(Reservation ***reservations,Room **rooms,int room_count,Guest **guests,int guest_count) {
	//load reservations from file and parse into reservation objects
	//Return: number of reservations found
	int reservation_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "reservations.txt", "r");
	//check if file exists
	if (fp) {
		char line[81];
		//if file is not empty, get the reservation count from the first line
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			reservation_count = atoi(strstr(line, "Reservation Count: ") + 19);
		}
		//read from file not at EOF
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Reservation *reservation = (Reservation *)malloc(sizeof(Reservation));//allocate reservation pointer
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);//split each line of the file on the ',' delimeter
			reservation->id = atoi(splits[0]);
			reservation->room = get_room_by_id(rooms,room_count,atoi(splits[1]));
			reservation->guest = get_guest_by_id(guests, guest_count, atoi(splits[2]));
			reservation->start.day = atoi(splits[3]);
			reservation->start.month = (Month)atoi(splits[4]);
			reservation->start.year = atoi(splits[5]);
			reservation->end.day = atoi(splits[6]);
			reservation->end.month = (Month)atoi(splits[7]);
			reservation->end.year = atoi(splits[8]);
			(*reservations) = (Reservation **)realloc(*reservations, (i + 1) * sizeof(Reservation*));//increase array size by one
			(*reservations)[i] = reservation;//append reservation to array
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
	//get all reservations at a specified hotel
	//Return: number of hotel reservations
	int count = 0;
	*result = (Reservation**)malloc(0);//allocate an empty array
	for (int i = 0; i < reservation_count; i++) {
		if (reservations[i]->room->hotel == hotel) {
			*result = (Reservation**)realloc(*result, (count + 1) * sizeof(Reservation*));// increase array size by 1 element
			(*result)[count] = reservations[i];
			count++;
		}
	}
	return count;
}

int get_guest_reservations(Reservation **reservations, int reservation_count, Guest *guest, Reservation ***result) {
	//get the reservations of a specified guest
	//Return: number of reservations found
	int count = 0;
	*result = (Reservation**)malloc(0);
	for (int i = 0; i < reservation_count; i++) {
		if (reservations[i]->guest == guest) {
			*result = (Reservation**)realloc(*result, (count + 1) * sizeof(Reservation*));
			(*result)[count] = reservations[i];
			count++;
		}
	}
	return count;
}

void create_reservation(Reservation ***reservations, int *reservation_count,Guest *guest,Room *room,Date start,Date end) {
	//create reservation and add it to the array of reservations
	Reservation *reservation = (Reservation*)malloc(sizeof(Reservation));//allocate memory for reservation
	reservation->guest = guest;
	reservation->room = room;
	reservation->start = start;
	reservation->end = end;
	reservation->id = *reservation_count == 0 ? 1 : (*reservations)[*reservation_count - 1]->id + 1; //set id to 1 or 1+previous id
	*reservations = (Reservation**)realloc(*reservations, (*reservation_count + 1) * sizeof(Reservation*)); //increase array size by 1
	(*reservations)[*reservation_count] = reservation; //append reservation to array
	(*reservation_count)++;
	save_reservations_to_file(*reservations, *reservation_count);
}

void user_create_reservation(Guest **guests,int guest_count, Guest *guest, Reservation ***reservations,int *reservation_count,Hotel **hotels, int hotel_count,Hotel *hotel,Room **rooms,int room_count) {
	//prompt user for data to create reservation
	clear();
	int choice = 0;
	bool success;
	printf("Create reservation:\n");
	if (!guest) {
		//get guest if guest has not been passed
		printf("Choose a guest:\n");
		for (int i = 0; i < guest_count; i++)
			printf("(%i) Guest: %s, %s\n", i + 1, guests[i]->last_name, guests[i]->first_name);
		printf("(%i) Go Back\n", guest_count + 1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice == guest_count + 1)
			return;
		guest = guests[choice - 1];
	}
	else {
		//get hotel if guest has been specified
		printf("Choose a hotel:\n");
		for (int i = 0; i < hotel_count; i++) {
			printf("(%i) Hotel: %s @ %s\n",i+1, hotels[i]->name, hotels[i]->address);
		}
		printf("(%i) Go Back\n", hotel_count + 1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice == hotel_count + 1)
			return;
		hotel = hotels[choice - 1];
	}

	//get dates
	clear();
	Date end,start;
	char *date_str;
	printf("Enter Check-In Date in the form dd/mm/yy:\n");
	//validate start date
	do {
		date_str = get_string("Date");
		start = create_date_from_string(date_str);
		if (!date_is_valid(start))
			printf("Invalid Date\n");
	} while (!date_is_valid(start));
	printf("Enter Check-Out Date in the form dd/mm/yy:\n");
	//validate end date and ensure it is after start date
	do {
		date_str = get_string("Date");
		end = create_date_from_string(date_str);
		if (is_before(end, start))
			printf("End date must be after start date.\n");
		if (!date_is_valid(end))
			printf("Invalid Date\n");
	} while (is_before(end, start) || !date_is_valid(end));

	//get rooms available based on guest start and end date
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
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
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
		pause();
	}
}

void delete_reservation_by_index(Reservation ***reservations, int *reservation_count, int index) {
	//delete reservation by index and remove from array
	free((*reservations)[index]);
	for (int i = index; i < (*reservation_count) - 1; i++) {
		(*reservations)[i] = (*reservations)[i + 1];
	}
	(*reservation_count)--;
	*reservations = (Reservation**)realloc(*reservations, (*reservation_count) * sizeof(Reservation*));
	save_reservations_to_file(*reservations, *reservation_count);
}

void delete_reservation_by_id(Reservation ***reservations, int *reservation_count, int id) {
	//delete reservation by id and remove from array
	for (int i = 0; i < *reservation_count; i++)
		if ((*reservations)[i]->id == id)
			delete_reservation_by_index(reservations, reservation_count, i);
	save_reservations_to_file(*reservations, *reservation_count);
}

void checkout_reservation(Reservation *reservation,Reservation ***reservations,int *reservation_count) {
	//calculate length of reservation and cost based on room rates
	int days = get_date_difference(reservation->start, reservation->end);//get reservation length
	float price = days * (reservation->room->type == single_bed ? reservation->room->hotel->single_rate : (reservation->room->type == double_bed ? reservation->room->hotel->double_rate : reservation->room->hotel->suite_rate));
	printf("Check-Out Reservation #%i: Guest: %s, %s Room: #%i\n", reservation->id, reservation->guest->last_name, reservation->guest->first_name, reservation->room->number);
	printf("\tPrice for %i %s: $%0.2f\n", days, days > 1 ? "days" : "day", price);
	printf("Accept transaction and close reservation (y/n):");
	char *choice = get_string("Choice");
	if (choice[0] == 'y' || choice[0] == 'Y') {
		printf("Transaction Complete.\n");
		pause();
		delete_reservation_by_id(reservations, reservation_count, reservation->id);//delete reservation after checkout
	}
}