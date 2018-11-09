#pragma once
#include "RoomTypes.h"	
#include "Hotel.h"
#include <string.h>
#include "Date.h"
#include "Reservation.h"

#ifndef ROOM
#define ROOM


typedef struct Room {
	int id;
	int number;
	Hotel *hotel;
	RoomType type;
} Room;

void create_room(Room ***rooms, int *room_count, Hotel *hotel, int number, RoomType type);

void user_create_room(Hotel *hotel, int number, Room ***rooms, int *room_count);

void user_create_all_rooms(Room ***rooms, int *room_count, Hotel *hotel, int hotel_room_count);

bool get_room_status(Room *room, Reservation **reservations, int reservation_count, Date date);

void delete_room_by_index(Room ***rooms, int *room_count, int index);

void edit_room(Room *room);

void save_rooms_to_file(Room **rooms, int room_count);

int load_rooms_from_file(Room ***rooms, Hotel **hotels, int hotel_count);

Room* get_room_by_id(Room **rooms, int room_count, int id);

#endif // !ROOM