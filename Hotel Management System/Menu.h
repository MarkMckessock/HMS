#pragma once
#include "Hotel.h"
#include "Room.h"
#include "Date.h"
#include "WorkOrder.h"
#include "Reservation.h"

struct WorkOrder;

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count);

void display_hotel_delete_menu(Hotel ***hotels, int *hotel_count,Room **rooms, int room_count);

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count);

void display_franchise_management_menu(Hotel* hotel, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count);

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count, Reservation **reservations, int reservation_count);

void hotel_display_edit_rooms(Hotel *hotel, Room ***rooms, int *room_count);

void hotel_edit_delete_room(Room ***rooms, int *room_count, int index);

void hotel_edit_room_rate(Hotel *hotel);

void hotel_display_work_orders(WorkOrder **work_order, int work_order_count, Hotel *hotel);

void hotel_display_guests(Guest **guests, int guest_count);

void hotel_display_reservations(Reservation **reservations, int reservation_count, Hotel *hotel);