#include <stdio.h>
#include <stdlib.h>
#include "guest.h"
#include "Hotel.h"
#include "Menu.h"



int main() {
	Guest *guests;
	//init hotels
	Hotel **hotels = (Hotel**)malloc(0);
	int hotel_count;
	hotel_count = load_hotels_from_file(&hotels);
	//init rooms
	Room **rooms = (Room**)malloc(0);
	int room_count = 0;
	while (true) {
		display_enterprise_management_menu(&hotels, &hotel_count, &rooms, &room_count);
	}
}