#pragma once
#include "RoomTypes.h"
#include "Date.h"
#ifndef HOTEL
#define HOTEL

struct Room;
struct Reservation;

typedef struct Hotel{
	const char *name;
	const char *address;
	int id;
	float single_rate;
	float double_rate;
	float suite_rate;
} Hotel;

Hotel* create_hotel(Hotel ***hotels, int *hotel_count, const char* name, const char* address, float single_rate, float double_rate, float suite_rate);

void user_create_hotel(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count);

void save_hotels_to_file(Hotel **hotels, int hotel_count);

int load_hotels_from_file(Hotel ***hotels);

void display_all_hotels(Hotel **hotels, int hotel_count,Room **rooms, int room_count);

void display_hotel(Hotel *hotel,Room **rooms, int room_count);

int get_hotel_rooms(Hotel *hotel, RoomType type, Room **rooms, int room_count, Room ***result);

void delete_hotel_by_index(Hotel ***hotels, int *hotel_count, int index);

void delete_hotel_by_id(Hotel ***hotels, int *hotel_count, int index);

Hotel* get_hotel_by_id(Hotel **hotels, int hotel_count, int id);

int get_hotel_rooms_available(Hotel *hotel, RoomType type, Room **rooms, int room_count, Reservation **reservations, int reservation_count, Room *** result, Date start, Date end);

#endif // !HOTEL