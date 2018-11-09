#include "Room.h"
#include "RoomTypes.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>
#include "Reservation.h"

void create_room(Hotel *hotel,int number,RoomType type, Room ***rooms, int *room_count) {
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
	if (number) {
		printf("Create Room #%i for hotel \"%s\":\n", number, hotel->name);
	}
	else {
		printf("Create Room for hotel \"%s\":\n", hotel->name);
		printf("Please enter room number:");
		number = get_int();
	}
	printf("Please choose room type:\n(1)\tSingle\n(2)\tDouble\n(3)\tSuite\n");
	int choice = get_int();
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
	create_room(hotel, number, type,rooms,room_count);
}

void user_create_all_rooms(Room ***rooms, int *room_count, Hotel *hotel, int hotel_room_count) {
	int count = *room_count;
	for (int i = count; i < hotel_room_count+count; i++) {
		user_create_room(hotel, i - count + 1,rooms,room_count);
	}
}

bool get_room_status(Room *room,Reservation **reservations,int reservation_count,Date date) {
	//TODO
	for (int i = 0; i < reservation_count; i++) {
		if (reservations[i]->room == room)
			if (is_before(reservations[i]->start, date) && is_before(date, reservations[i]->end))
				return false;
	}
	return true;
}

void edit_room(Room *room) {
	printf("Edit Hotel %s: Room #%i\n", room->hotel->name, room->number);
	printf("Choose room style:\n");
	printf("(1) Single\n");
	printf("(2) Double\n");
	printf("(3) Suite\n");
	printf("(4) Go Back\n");
	int choice = get_int();
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
}

void delete_room_by_index(Room ***rooms, int *room_count, int index) {
	//deletes the specified room and removes it from the array
	free((*rooms)[index]);
	for (int i = index; i < (*room_count) - 1; i++) {
		(*rooms)[i] = (*rooms)[i + 1];
	}
	(*room_count)--;
	*rooms = (Room**)realloc(*rooms, (*room_count) * sizeof(Room*));
}

void save_rooms_to_file(Room **rooms, int room_count) {
	FILE *fp;
	fopen_s(&fp, "rooms.txt", "w");
	fprintf(fp, "Room Count: %i\n", room_count);
	for (int i = 0; i < room_count; i++)
		fprintf(fp, "%i,%i,%i,%i\n", rooms[i]->id,rooms[i]->number,rooms[i]->hotel->id,rooms[i]->type);
	fclose(fp);
}

int load_rooms_from_file(Room ***rooms,Hotel **hotels,int hotel_count) {
	int room_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "rooms.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			room_count = atoi(strstr(line, "Room Count: ") + 12);
		}
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
	for (int i = 0; i < room_count; i++) {
		if (rooms[i]->id == id) {
			return rooms[i];
		}
	}
	return NULL;
}