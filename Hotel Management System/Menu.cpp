#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count) {
	system("cls");
	printf("Management Menu:\n");
	printf("(1) Create Hotel\n");
	printf("(2) List Hotels\n");
	printf("(3) Delete Hotel\n");
	printf("(4) Choose hotel to manage\n");
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
		display_hotel_selection_menu(*hotels, *hotel_count, rooms, room_count);
		break;
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

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count) {
	printf("Choose a hotel to delete:\n");
	for (int i = 0; i < hotel_count; i++) {
		printf("(%i) ", i + 1);
		display_hotel(hotels[i], *rooms, *room_count);
	}
	int choice = get_int();
	display_franchise_management_menu(hotels[choice - 1],rooms,room_count);
}

void display_franchise_management_menu(Hotel* hotel,Room ***rooms,int *room_count) {
	printf("Franchise Management Menu: Hotel #%i: %s [%s]\n", hotel->id, hotel->name, hotel->address);
	printf("(1) View Rooms\n");
	printf("(2) Edit/Delete Rooms\n");
	printf("(3) Add Room\n");
	printf("(4) Edit Rates\n");
	printf("(5) View Work Orders\n");
	printf("(6) View Reservations\n");
	printf("(7) View Guests\n");
	printf("(8) View Employees\n");
	printf("(8) Return to Enterprise Managment Menu\n");
	int choice = get_int();
	switch (choice) {
	case 1:
		hotel_display_rooms(hotel, *rooms, *room_count);
		break;
	case 2:
		hotel_display_edit_rooms(hotel, rooms, room_count);
		break;
	case 3:
		user_create_room(hotel, 0,rooms,room_count);
		break;
	}
}

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count) {
	Room ***hotel_rooms = (Room***)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count,hotel_rooms);
	for (int i = 0; i < hotel_room_count; i++) {
		printf("Room #%i: Style: %s Status: %s\n", rooms[i]->number, room_type_names[rooms[i]->type], get_room_status(rooms[i]));
	}
	system("pause");
}

void hotel_display_edit_rooms(Hotel *hotel, Room ***rooms, int *room_count) {
	printf("Choose a room to edit/delete:\n");
	Room ***hotel_rooms = (Room***)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, *rooms, *room_count, hotel_rooms);
	for (int i = 0; i < hotel_room_count; i++) {
		printf("(%i) Room #%i: Style: %s Status: %s\n",i+1, (*rooms)[i]->number, room_type_names[(*rooms)[i]->type], get_room_status((*rooms)[i]));
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