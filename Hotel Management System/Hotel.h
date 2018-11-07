#pragma once
#include "RoomTypes.h"

#ifndef HOTEL
#define HOTEL

struct Room;

typedef struct Hotel{
	const char *name;
	const char *address;
	int id;
} Hotel;

Hotel* create_hotel(Hotel ***hotels, int *hotel_count, const char* name, const char* address);

void user_create_hotel(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count);

void save_hotels_to_file(Hotel **hotels, int hotel_count);

int load_hotels_from_file(Hotel ***hotels);

void display_all_hotels(Hotel **hotels, int hotel_count,Room **rooms, int room_count);

void display_hotel(Hotel *hotel,Room **rooms, int room_count);

int get_hotel_rooms(Hotel *hotel, RoomType type, Room **rooms, int room_count, Room ***result);

void delete_hotel_by_index(Hotel ***hotels, int *hotel_count, int index);

void delete_hotel_by_id(Hotel ***hotels, int *hotel_count, int index);

#endif // !HOTEL