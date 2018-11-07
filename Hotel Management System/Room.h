#pragma once
#include "RoomTypes.h"	
#include "Hotel.h"

#ifndef ROOM
#define ROOM


typedef struct Room {
	int number;
	Hotel *hotel;
	RoomType type;
} Room;

Room* create_room(Hotel *hotel, int number, RoomType type);

Room* user_create_room(Hotel *hotel, int number, Room ***rooms, int *room_count);

void user_create_all_rooms(Room ***rooms, int *room_count, Hotel *hotel, int hotel_room_count);

const char* get_room_status(Room *room);

void delete_room_by_index(Room ***rooms, int *room_count, int index);

void edit_room(Room *room);

#endif // !ROOM