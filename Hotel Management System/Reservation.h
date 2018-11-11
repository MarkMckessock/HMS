#pragma once
#include "Room.h"
#include "Date.h"
#include "guest.h"
#include <stdio.h>
#include "func.h"

typedef struct Reservation {
	Room *room;
	Guest *guest;
	int id;
	Date start;
	Date end;
}Reservation;

void save_reservations_to_file(Reservation **reservations, int reservation_count);

int load_reservations_from_file(Reservation ***reservations, Room **rooms, int room_count, Guest **guests, int guest_count);

int get_hotel_reservations(Reservation **reservations, int reservation_count, Hotel *hotel, Reservation ***result);

void user_create_reservation(Guest **guests, int guest_count, Reservation ***reservations, int *reservation_count, Hotel *hotel, Room **rooms, int room_count);

void create_reservation(Reservation ***reservations, int *reservation_count, Guest *guest, Room *room, Date start, Date end);

void delete_reservation_by_index(Reservation ***reservations, int *reservation_count, int index);

void delete_reservation_by_id(Reservation ***reservations, int *reservation_count, int id);

void checkout_reservation(Reservation *reservation, Reservation ***reservations, int *reservation_count);