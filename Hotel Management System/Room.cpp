#include "Room.h"
#include "RoomTypes.h"
#include "func.h"
#include <stdlib.h>
#include <stdio.h>

Room* create_room(Hotel *hotel,int number,RoomType type) {
	Room *room = (Room*)malloc(sizeof(Room));
	room->hotel = hotel;
	room->number = number;
	room->type = type;
	return room;
}

Room* user_create_room(Hotel *hotel,int number,Room ***rooms,int *room_count) {
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
	Room *room = create_room(hotel, number, type);
	(*room_count)++;
	*rooms = (Room**)realloc(*rooms, (*room_count) * sizeof(Room*));
	(*rooms)[*room_count - 1] = room;
	return room;
}

void user_create_all_rooms(Room ***rooms, int *room_count, Hotel *hotel, int hotel_room_count) {
	int count = *room_count;
	for (int i = count; i < hotel_room_count+count; i++) {
		user_create_room(hotel, i - count + 1,rooms,room_count);
	}
}

const char* get_room_status(Room *room) {
	//TODO
	const char *str = "Available";
	return str;
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