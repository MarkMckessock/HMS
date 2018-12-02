#include "Room.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Date.h"

void create_room(Hotel *hotel,int number,RoomType type, Room ***rooms, int *room_count) {
	//create room object and add to array
	Room *room = (Room*)malloc(sizeof(Room));
	room->hotel = hotel;
	room->number = number;
	room->type = type;
	room->id = *room_count == 0 ? 1 : (*rooms)[*room_count - 1]->id + 1;
	(*room_count)++;
	*rooms = (Room**)realloc(*rooms, (*room_count) * sizeof(Room*));
	(*rooms)[*room_count - 1] = room;
	save_rooms_to_file(*rooms, *room_count);
}

void user_create_room(Hotel *hotel,int number,Room ***rooms,int *room_count) {
	//prompt user for date to create room
	int choice,num;
	bool valid = true,success;
	char* int_str, *endptr;
	clear();
	if (number) {//if room number is given, us it
		printf("Create Room #%i for hotel \"%s\":\n", number, hotel->name);
		num = number;
	}
	else {//if no room number is given, get from user
			printf("Create Room for hotel \"%s\": (Hit 'Enter' to go back)\n", hotel->name);
		do {
			//validate room number is unique
			if (!valid) {
				printf("Room number already in use. Please choose another:\n");
				valid = true;
			}
			else {
				printf("Please enter room number:\n");
			}
			do {
				int_str = get_string("Number");
				if (!strcmp(int_str, "")) {
					return;
				}
				num = strtol(int_str, &endptr, 10);
				if (num == 0 && int_str == endptr)
					printf("Invalid Number\n");
			} while (num == 0 && int_str == endptr);
			for (int i = 0; i < *room_count; i++)
				if ((*rooms)[i]->number == num)
					valid = false;
		} while (!valid);

	}
	//get room type
	printf("Please choose room type:\n(1)\tSingle\n(2)\tDouble\n(3)\tSuite\n");
	do {
		choice = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
		if (choice < 1 || choice > 3)
			printf("Invalid Room Type\n");
	} while (!success || choice <1 || choice >3);
	RoomType type;
	switch (choice) {
	case 1:
		type = single_bed;
		break;
	case 2:
		type = double_bed;
		break;
	case 3:
		type = suite;
		break;
	}
	create_room(hotel, num, type,rooms,room_count);
}

void user_create_all_rooms(Room ***rooms, int *room_count, Hotel *hotel, int hotel_room_count) {
	//prompt user to create a specified number of rooms for a hotel, on creation
	int count = *room_count;
	for (int i = count; i < hotel_room_count+count; i++) {
		user_create_room(hotel, i - count + 1,rooms,room_count);
	}
}

bool get_room_status(Room *room,Reservation **reservations,int reservation_count,Date date) {
	//get the status of a room at the current date
	//Return: true if room is available else false
	for (int i = 0; i < reservation_count; i++) {
		if (reservations[i]->room == room)
			if (is_before(reservations[i]->start, date) && is_before(date, reservations[i]->end))
				return false;
	}
	return true;
}

void edit_room(Room *room,Room **rooms,int room_count) {
	int choice;
	bool success;
	//change the type of a given room
	printf("Edit Hotel %s: Room #%i\n", room->hotel->name, room->number);
	printf("Choose room style:\n");
	printf("(1) Single\n");
	printf("(2) Double\n");
	printf("(3) Suite\n");
	printf("(4) Go Back\n");
	do {
		choice = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
	} while (!success);
	switch (choice) {
	case 1:
		room->type = single_bed;
		break;
	case 2:
		room->type = double_bed;
		break;
	case 3:
		room->type = suite;
		break;
	case 4:
		break;
	}
	save_rooms_to_file(rooms, room_count);
}

void delete_room_by_index(Room ***rooms, int *room_count, int index,Reservation ***reservations,int *reservation_count) {
	//deletes the specified room and removes it from the array
	for (int i = 0; i < *reservation_count; i++) {
		if ((*reservations)[i]->room == (*rooms)[index]) {
			delete_reservation_by_index(reservations, reservation_count, i);
			i--;
		}
	}
	free((*rooms)[index]);
	for (int i = index; i < (*room_count) - 1; i++) {
		(*rooms)[i] = (*rooms)[i + 1];
	}
	(*room_count)--;
	*rooms = (Room**)realloc(*rooms, (*room_count) * sizeof(Room*));
	save_rooms_to_file(*rooms, *room_count);
}

void delete_room_by_id(Room ***rooms, int *rooms_count, Reservation ***reservations, int *reservation_count, int id) {
	//deletes a room by id and remove it from the array
	for (int i = 0; i < *rooms_count; i++) {
		if ((*rooms)[i]->id == id)
			delete_room_by_index(rooms, rooms_count, i, reservations, reservation_count);
	}
}

void save_rooms_to_file(Room **rooms, int room_count) {
	//save all rooms to file
	//Format: room id,room number,hotel id, room type
	FILE *fp;
	fopen_s(&fp, "rooms.txt", "w");
	fprintf(fp, "Room Count: %i\n", room_count);
	for (int i = 0; i < room_count; i++)
		fprintf(fp, "%i,%i,%i,%i\n", rooms[i]->id,rooms[i]->number,rooms[i]->hotel->id,rooms[i]->type);
	fclose(fp);
}

int load_rooms_from_file(Room ***rooms,Hotel **hotels,int hotel_count) {
	//save all rooms to file
	int room_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "rooms.txt", "r");
	//check that file exists
	if (fp) {
		char line[81];
		//check that file is not empty and get room count
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			room_count = atoi(strstr(line, "Room Count: ") + 12);
		}
		//read file while not at EOF
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Room *room = (Room *)malloc(sizeof(Room));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			room->id = atoi(splits[0]);
			room->number = atoi(splits[1]);
			room->hotel = get_hotel_by_id(hotels,hotel_count,atoi(splits[2]));
			room->type = (RoomType)atoi(splits[3]);
			(*rooms) = (Room **)realloc(*rooms, (i + 1) * sizeof(Room*));
			(*rooms)[i] = room;
			i++;
		}
		fclose(fp);
		return room_count;
	}
	else {
		return 0;
	}
}

Room* get_room_by_id(Room **rooms,int room_count,int id) {
	//get a room by its id
	//Return: pointer to room or null if not found
	for (int i = 0; i < room_count; i++) {
		if (rooms[i]->id == id) {
			return rooms[i];
		}
	}
	return NULL;
}