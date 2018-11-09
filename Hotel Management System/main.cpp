#include <stdio.h>
#include <stdlib.h>
#include "WorkOrder.h"
#include "Hotel.h"
#include "guest.h"
#include "Menu.h"




int main() {
	//init hotels
	Hotel **hotels = (Hotel**)malloc(0);
	int hotel_count = load_hotels_from_file(&hotels);
	//init rooms
	Room **rooms = (Room**)malloc(0);
	int room_count = load_rooms_from_file(&rooms, hotels, hotel_count);
	//init guests
	Guest **guests = (Guest**)malloc(0);
	int guest_count = load_guests_from_file(&guests);
	//init reservations
	Reservation **reservations = (Reservation**)malloc(0);
	int reservation_count = load_reservations_from_file(&reservations,rooms,room_count,guests,guest_count);
	//init employees
	//init work orders
	WorkOrder **work_orders = (WorkOrder**)malloc(0);
	int work_order_count = load_work_orders_from_file(&work_orders,hotels,hotel_count);

	while (true) {
		display_enterprise_management_menu(&hotels, &hotel_count, &rooms, &room_count,&work_orders,&work_order_count,&reservations,&reservation_count,&guests,&guest_count);
	}
}