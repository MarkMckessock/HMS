#pragma once
#include "Hotel.h"
#include "Room.h"
#include "Date.h"
#include "Employee.h"
#include "WorkOrder.h"
#include "Reservation.h"
#include <string>

struct WorkOrder;

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count);

void display_hotel_delete_menu(Hotel ***hotels, int *hotel_count,Room **rooms, int room_count);

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count);

void display_franchise_management_menu(Hotel* hotel, Hotel** hotels, int hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count);

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count, Reservation **reservations, int reservation_count);

void hotel_edit_room_rate(Hotel *hotel);

void hotel_display_work_orders(WorkOrder **work_order, int work_order_count, Hotel *hotel);

void hotel_display_guests(Guest **guests, int guest_count);

void hotel_display_reservations(Reservation **reservations, int reservation_count, Hotel *hotel);

void hotel_display_employees(Employee **employees, int employee_count, Hotel *hotel);

void hotel_assign_work_order(Employee **employees, int employee_count, WorkOrder **work_orders, int work_order_count,Hotel *hotel);

void hotel_delete_work_order(WorkOrder ***work_orders, int *work_order_count, Employee **employees, int employee_count,Hotel *hotel);

void hotel_delete_guest(Guest ***guests, int *guest_count, Reservation ***reservations, int *reservation_count);

void hotel_edit_rooms(Room **rooms, int room_count, Hotel *hotel);

void hotel_delete_room(Room ***rooms, int *room_count, Reservation ***reservations, int *reservation_count, Hotel *hotel);

void hotel_delete_reservation(Reservation ***reservations, int *reservation_count,Hotel *hotel);

void hotel_delete_employee(Employee ***employees, int *employee_count, Hotel *hotel);

void hotel_checkout_reservation(Reservation ***reservations, int *reservation_count);

void reset_guest_password(Guest **guests, int guest_count);

void login_screen(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count);

Role authenticate(char *username, char *password, Guest **guests, int guest_count, Employee **employees, int employee_count, Guest **user, Employee **employee);

void display_guest_menu(Guest *guest, Reservation ***reservations, int *reservation_count, Room **rooms, int room_count, Hotel **hotels, int hotel_count);

void display_employee_menu(Employee *employee);

