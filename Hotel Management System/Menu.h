#pragma once
#include "Hotel.h"
#include "Room.h"

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count);

void display_hotel_delete_menu(Hotel ***hotels, int *hotel_count,Room **rooms, int room_count);

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count);

void display_franchise_management_menu(Hotel* hotel, Room ***rooms, int *room_count);

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count);

void hotel_display_edit_rooms(Hotel *hotel, Room ***rooms, int *room_count);

void hotel_edit_delete_room(Room ***rooms, int *room_count, int index);