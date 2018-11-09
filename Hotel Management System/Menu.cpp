#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count) {
	system("cls");
	printf("Management Menu:\n");
	printf("(1) Create Hotel\n");
	printf("(2) List Hotels\n");
	printf("(3) Delete Hotel\n");
	printf("(4) Choose hotel to manage\n");
	printf("(5) Quit\n");
	//printf("(5) View/Edit Room Rates\n"); - move to franchise management
	int choice = get_int();
	switch (choice) {
	case 1:
		user_create_hotel(hotels, hotel_count, rooms, room_count);
		break;
	case 2:
		display_all_hotels(*hotels, *hotel_count, *rooms, *room_count);
		break;
	case 3:
		display_hotel_delete_menu(hotels, hotel_count,*rooms,*room_count);
		break;
	case 4:
		display_hotel_selection_menu(*hotels, *hotel_count, rooms, room_count,work_orders,work_order_count,reservations,reservation_count,guests,guest_count);
		break;
	case 5:
		exit(EXIT_SUCCESS);
	}
}

void display_hotel_delete_menu(Hotel ***hotels, int *hotel_count,Room **rooms,int room_count) {
	printf("Choose a hotel to delete:\n");
	for (int i = 0; i < *hotel_count; i++) {
		printf("(%i) ",i+1);
		display_hotel((*hotels)[i], rooms, room_count);
	}
	int choice = get_int();
	delete_hotel_by_index(hotels, hotel_count, choice - 1);
}

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count) {
	printf("Choose a hotel to delete:\n");
	for (int i = 0; i < hotel_count; i++) {
		printf("(%i) ", i + 1);
		display_hotel(hotels[i], *rooms, *room_count);
	}
	int choice = get_int();
	display_franchise_management_menu(hotels[choice - 1],rooms,room_count,work_orders,work_order_count,reservations,reservation_count,guests,guest_count);
}

void display_franchise_management_menu(Hotel* hotel,Room ***rooms,int *room_count,WorkOrder ***work_orders,int *work_order_count,Reservation ***reservations,int *reservation_count,Guest ***guests,int *guest_count) {
	bool flag = true;
	while (flag) {
		system("cls");
		printf("Franchise Management Menu: Hotel #%i: %s [%s]\n", hotel->id, hotel->name, hotel->address);
		//rooms
		printf("(1) View Rooms\n");
		printf("(2) Edit/Delete Rooms\n");
		printf("(3) Add Room\n");
		printf("(4) Edit Rates\n");
		//work orders
		printf("(5) View Work Orders\n");
		printf("(6) Create Work Order\n");
		printf("(7) Assign Work Orders:\n");
		//reservations
		printf("(7) View Reservations\n");
		printf("(8) Create Reservation\n");
		printf("(9) Check-Out / Process Payment\n");//
		printf("(10) Delete reservation\n");//
		//guests
		printf("(11) View Guests\n");
		printf("(12) Create Guest\n");
		printf("(13) Change Guest Password:\n");//
		//employees
		printf("(14) View Employees\n");
		printf("(15) Create Employee\n");
		//return
		printf("(16) Return to Enterprise Managment Menu\n");
		int choice = get_int();
		switch (choice) {
		case 1:
			hotel_display_rooms(hotel, *rooms, *room_count, *reservations, *reservation_count);
			break;
		case 2:
			hotel_display_edit_rooms(hotel, rooms, room_count);
			break;
		case 3:
			user_create_room(hotel, 0, rooms, room_count);
			break;
		case 4:
			hotel_edit_room_rate(hotel);
			break;
		case 5:
			hotel_display_work_orders(*work_orders, *work_order_count, hotel);
			break;
		case 6:
			user_create_work_order(hotel, work_orders, work_order_count);
			break;
		case 7:
			hotel_display_reservations(*reservations, *reservation_count, hotel);
			break;
		case 8:
			user_create_reservation(*guests, *guest_count, reservations, reservation_count, hotel, *rooms, *room_count);
			break;
		case 11:
			hotel_display_guests(*guests, *guest_count);
			break;
		case 12:
			user_create_guest(guests, guest_count);
			break;
		case 16:
			flag = false;
			break;
		}

	}
}

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count,Reservation **reservations,int reservation_count) {
	Room ***hotel_rooms = (Room***)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count,hotel_rooms);
	for (int i = 0; i < hotel_room_count; i++) {
		printf("Room #%i: Style: %s Status: %s\n", rooms[i]->number, room_type_names[rooms[i]->type], get_room_status(rooms[i],reservations,reservation_count,get_current_date()) ? "Available" : "Booked");
	}
	system("pause");
}

void hotel_display_edit_rooms(Hotel *hotel, Room ***rooms, int *room_count) {
	printf("Choose a room to edit/delete:\n");
	Room ***hotel_rooms = (Room***)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, *rooms, *room_count, hotel_rooms);
	for (int i = 0; i < hotel_room_count; i++) {
		printf("(%i) Room #%i: Style: %s\n",i+1, (*rooms)[i]->number, room_type_names[(*rooms)[i]->type]);
	}
	int choice = get_int();
	hotel_edit_delete_room(rooms, room_count, choice - 1);
}

void hotel_edit_delete_room(Room ***rooms,int *room_count,int index) {
	printf("Room #%i:\n", (*rooms)[index]->number);
	printf("(1) Edit Room Style\n");
	printf("(2) Delete Room\n");
	int choice = get_int();
	switch (choice) {
	case 1:
		edit_room((*rooms)[index]);
		break;
	case 2:
		delete_room_by_index(rooms, room_count,index);
		break;
	}
}

void hotel_edit_room_rate(Hotel *hotel) {
	printf("Edit rate for hotel \"%s\"\n", hotel->name);
	printf("(1) Single Room Rate [$%0.2f]\n", hotel->single_rate);
	printf("(2) Double Room Rate [$%0.2f]\n", hotel->double_rate);
	printf("(3) Suite Rate [$%0.2f]\n", hotel->suite_rate);
	printf("(4) Exit\n");
	int choice = get_int();
	system("cls");
	switch (choice) {
	case 1:
		printf("Edit Single Room rate for hotel \"%s\"\n$", hotel->name);
		hotel->single_rate = get_float();
		break;
	case 2:
		printf("Edit Double Room rate for hotel \"%s\"\n$", hotel->name);
		hotel->double_rate = get_float();
		break;
	case 3:
		printf("Edit Suite rate for hotel \"%s\"\n$", hotel->name);
		hotel->suite_rate = get_float();
	case 4:
		break;
	}

}

void hotel_display_work_orders(WorkOrder **work_orders, int work_order_count, Hotel *hotel) {
	WorkOrder ***result = (WorkOrder***)malloc(0);
	int hotel_work_order_count = get_hotel_work_orders(work_orders, work_order_count, hotel, result);
	for (int i = 0; i < hotel_work_order_count; i++) {
		printf("Work Order #%i: \"%s\" Created %s\n\t%s\n", (*result)[i]->id, (*result)[i]->name, print_date((*result)[i]->date_created),(*result)[i]->description);
	}
	system("pause");
}

void hotel_display_reservations(Reservation **reservations, int reservation_count, Hotel *hotel) {
	Reservation ***result = (Reservation***)malloc(0);
	int hotel_reservation_count = get_hotel_reservations(reservations, reservation_count, hotel, result);
	for (int i = 0; i < hotel_reservation_count; i++) {
		printf("Reservation #%i: Guest: \"%s %s\" Room: #%i [%s - %s]\n", (*result)[i]->id,(*result)[i]->guest->first_name,(*result)[i]->guest->last_name,(*result)[i]->room->number,print_date((*result)[i]->start),print_date((*result)[i]->end));
	}
	system("pause");
}

void hotel_display_guests(Guest **guests, int guest_count) {
	for (int i = 0; i < guest_count; i++) {
		printf("Guest #%i: %s, %s\n", guests[i]->id, guests[i]->last_name, guests[i]->first_name);
	}
	system("pause");
}