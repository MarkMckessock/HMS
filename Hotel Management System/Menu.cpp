#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count,Employee ***employees,int *employee_count) {
	bool flag = true;
	while (flag) {
		system("cls");
		printf("Management Menu:\n");
		printf("(1) Create Hotel\n");
		printf("(2) List Hotels\n");
		printf("(3) Delete Hotel\n");
		printf("(4) Choose hotel to manage\n");
		printf("(5) Logout\n");
		printf("(6) Quit\n");
		int choice = get_int();
		switch (choice) {
		case 1:
			user_create_hotel(hotels, hotel_count, rooms, room_count);
			break;
		case 2:
			display_all_hotels(*hotels, *hotel_count, *rooms, *room_count);
			break;
		case 3:
			display_hotel_delete_menu(hotels, hotel_count, *rooms, *room_count);
			break;
		case 4:
			display_hotel_selection_menu(*hotels, *hotel_count, rooms, room_count, work_orders, work_order_count, reservations, reservation_count, guests, guest_count, employees, employee_count);
			break;
		case 5:
			flag = false;
			break;
		case 6:
			exit(EXIT_SUCCESS);
		}
	}
}

void display_hotel_delete_menu(Hotel ***hotels, int *hotel_count,Room **rooms,int room_count) {
	system("cls");
	if (!(*hotel_count)) {
		printf("No Hotels Available.\n");
		system("pause");
		return;
	}
	printf("Choose a hotel to delete:\n");
	for (int i = 0; i < *hotel_count; i++) {
		printf("(%i) ",i+1);
		display_hotel((*hotels)[i], rooms, room_count);
	}
	printf("(%i) Go Back\n",*hotel_count);
	int choice = get_int();
	if(choice != *hotel_count)
		delete_hotel_by_index(hotels, hotel_count, choice - 1);
}

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count,Employee ***employees,int *employee_count) {
	system("cls");
	if (!hotel_count) {
		printf("No Hotels Available. Create one to begin.\n");
		system("pause");
		return;
	}
	printf("Choose a hotel to manage:\n");
	for (int i = 0; i < hotel_count; i++) {
		printf("(%i) ", i + 1);
		display_hotel(hotels[i], *rooms, *room_count);
	}
	printf("(%i) Go Back\n",hotel_count);
	int choice = get_int();
	if(choice != hotel_count)
		display_franchise_management_menu(hotels[choice - 1],rooms,room_count,work_orders,work_order_count,reservations,reservation_count,guests,guest_count,employees,employee_count);
}

void display_franchise_management_menu(Hotel* hotel,Room ***rooms,int *room_count,WorkOrder ***work_orders,int *work_order_count,Reservation ***reservations,int *reservation_count,Guest ***guests,int *guest_count,Employee ***employees,int *employee_count) {
	bool flag = true;
	while (flag) {
		system("cls");
		printf("Franchise Management Menu: Hotel #%i: %s [%s]\n", hotel->id, hotel->name, hotel->address);
		//rooms
		printf("(1) View Rooms\n");
		printf("(2) Edit Rooms\n");
		printf("(3) Add Room\n");
		printf("(4) Delete Room\n");
		printf("(5) Edit Rates\n");
		//work orders
		printf("(6) View Work Orders\n");
		printf("(7) Create Work Order\n");
		printf("(8) Assign Work Orders\n");
		printf("(9) Delete Work Order\n");
		//reservations
		printf("(10) View Reservations\n");
		printf("(11) Create Reservation\n");
		printf("(12) Check-Out Guest\n");
		printf("(13) Delete reservation\n");
		//guests
		printf("(14) View Guests\n");
		printf("(15) Create Guest\n");
		printf("(16) Change Guest Password\n");
		printf("(17) Delete Guest\n");
		//employees
		printf("(18) View Employees\n");
		printf("(19) Create Employee\n");
		printf("(20) Delete Employee\n");
		//return
		printf("(21) Return to Enterprise Managment Menu\n");
		int choice = get_int();
		switch (choice) {
		case 1:
			hotel_display_rooms(hotel, *rooms, *room_count, *reservations, *reservation_count);
			break;
		case 2:
			hotel_edit_rooms(*rooms, *room_count);
			break;
		case 3:
			user_create_room(hotel, 0, rooms, room_count);
			break;
		case 4:
			hotel_delete_room(rooms, room_count,reservations,reservation_count);
			break;
		case 5:
			hotel_edit_room_rate(hotel);
			break;
		case 6:
			hotel_display_work_orders(*work_orders, *work_order_count, hotel);
			break;
		case 7:
			user_create_work_order(hotel, work_orders, work_order_count);
			break;
		case 8:
			hotel_assign_work_order(*employees, *employee_count, *work_orders, *work_order_count);
			break;
		case 9:
			hotel_delete_work_order(work_orders,work_order_count,*employees,*employee_count);
			break;
		case 10:
			hotel_display_reservations(*reservations, *reservation_count, hotel);
			break;
		case 11:
			user_create_reservation(*guests, *guest_count, reservations, reservation_count, hotel, *rooms, *room_count);
			break;
		case 12:
			hotel_checkout_reservation(reservations, reservation_count);
			break;
		case 13:
			hotel_delete_reservation(reservations, reservation_count);
			break;
		case 14:
			hotel_display_guests(*guests, *guest_count);
			break;
		case 15:
			user_create_guest(guests, guest_count);
			break;
		case 16:
			reset_guest_password(*guests, *guest_count);
			break;
		case 17:
			hotel_delete_guest(guests, guest_count,reservations,reservation_count);
			break;
		case 18:
			hotel_display_employees(*employees, *employee_count, hotel);
			break;
		case 19:
			user_create_employee(employees, employee_count, hotel);
			break;
		case 20:
			hotel_delete_employee(employees, employee_count,hotel);
			break;
		case 21:
			flag = false;
			break;
		}

	}
}

void hotel_display_rooms(Hotel *hotel, Room **rooms, int room_count,Reservation **reservations,int reservation_count) {
	Room ***hotel_rooms = (Room***)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count,hotel_rooms);
	system("cls");
	printf("Hotel Rooms:\n");
	if (room_count) {
		for (int i = 0; i < hotel_room_count; i++) {
			printf("Room #%i: Style: %s Status: %s\n", rooms[i]->number, room_type_names[rooms[i]->type], get_room_status(rooms[i], reservations, reservation_count, get_current_date()) ? "Available" : "Booked");
		}
	}
	else {
		printf("No rooms found.\n");
	}
	system("pause");
}

void hotel_delete_room(Room ***rooms, int *room_count,Reservation ***reservations,int *reservation_count) {
	system("cls");
	printf("Choose a room to delete:\n");
	if (*room_count) {
		for (int i = 0; i < *room_count; i++) {
			printf("(%i) Room #%i: %s\n", i + 1, (*rooms)[i]->number, room_type_names[(*rooms)[i]->type]);
		}
		printf("(%i) Go Back\n", *room_count);
		int choice = get_int();
		if (choice != *room_count)
			delete_room_by_index(rooms, room_count, choice - 1, reservations, reservation_count);
	}
	else {
		printf("No rooms found.\n");
		system("pause");
	}
}

void hotel_edit_rooms(Room **rooms,int room_count) {
	system("cls");
	printf("Choose room to edit:\n");
	if (room_count) {
		for (int i = 0; i < room_count; i++) {
			printf("(%i) Room #%i: %s\n", i + 1, rooms[i]->number, room_type_names[rooms[i]->type]);
		}
		printf("(%i) Go Back\n", room_count+1);
		int choice = get_int();
		if (choice != room_count+1)
			edit_room(rooms[choice - 1], rooms, room_count);
	}
	else {
		printf("No rooms found.\n");
		system("pause");
	}
}

void hotel_edit_room_rate(Hotel *hotel) {
	system("cls");
	printf("Edit rate for hotel \"%s\"\n", hotel->name);
	printf("(1) Single Room Rate [$%0.2f]\n", hotel->single_rate);
	printf("(2) Double Room Rate [$%0.2f]\n", hotel->double_rate);
	printf("(3) Suite Rate [$%0.2f]\n", hotel->suite_rate);
	printf("(4) Go Back\n");
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
	system("cls");
	printf("Hotel Work Orders:\n");
	if (work_order_count) {
		for (int i = 0; i < hotel_work_order_count; i++) {
			printf("Work Order #%i: \"%s\" Created %s\n\t%s\n", (*result)[i]->id, (*result)[i]->name, print_date((*result)[i]->date_created), (*result)[i]->description);
		}
	}
	else {
		printf("No work orders found.\n");
	}
	system("pause");
}

void hotel_delete_work_order(WorkOrder ***work_orders, int *work_order_count,Employee **employees,int employee_count) {
	system("cls");
	printf("Choose a work order to delete:\n");
	if (*work_order_count) {
		for (int i = 0; i < *work_order_count; i++) {
			printf("(%i) %s\n", i + 1, (*work_orders)[i]->name);
		}
		printf("(%i) Go Back\n", *work_order_count+1);
		int choice = get_int();
		if (choice != *work_order_count+1)
			delete_work_order_by_index(work_orders, work_order_count, choice - 1, employees, employee_count);
	}
	else {
		printf("No work orders found.\n");
		system("pause");
	}
}

void hotel_display_reservations(Reservation **reservations, int reservation_count, Hotel *hotel) {
	Reservation ***result = (Reservation***)malloc(0);
	int hotel_reservation_count = get_hotel_reservations(reservations, reservation_count, hotel, result);
	system("cls");
	printf("Hotel Reservations:\n");
	if (reservation_count) {
		for (int i = 0; i < hotel_reservation_count; i++) {
			printf("Reservation #%i: Guest: \"%s %s\" Room: #%i [%s - %s]\n", (*result)[i]->id, (*result)[i]->guest->first_name, (*result)[i]->guest->last_name, (*result)[i]->room->number, print_date((*result)[i]->start), print_date((*result)[i]->end));
		}
	}
	else {
		printf("No reservations found.\n");
	}
	system("pause");
}

void hotel_delete_reservation(Reservation ***reservations, int *reservation_count) {
	system("cls");
	printf("Choose a reservation to delete:\n");
	if (*reservation_count) {
		for (int i = 0; i < *reservation_count; i++) {
			printf("(%i) Guest: %s %s Room #%i\n", i + 1, (*reservations)[i]->guest->first_name, (*reservations)[i]->guest->last_name, (*reservations)[i]->room->number);
		}
		printf("(%i) Go Back\n", *reservation_count+1);
		int choice = get_int();
		if (choice != *reservation_count+1)
			delete_reservation_by_index(reservations, reservation_count, choice - 1);
	}
	else {
		printf("No reservations found.\n");
		system("pause");
	}
}

void hotel_display_guests(Guest **guests, int guest_count) {
	system("cls");
	printf("Hotel Guests:\n");
	if (guest_count) {
		for (int i = 0; i < guest_count; i++) {
			printf("Guest #%i: %s, %s\n", guests[i]->id, guests[i]->last_name, guests[i]->first_name);
		}
	}
	else {
		printf("No guests found.\n");
	}
	system("pause");
}

void hotel_delete_guest(Guest ***guests, int *guest_count,Reservation ***reservations,int *reservation_count) {
	system("cls");
	printf("Choose a guest to delete:\n");
	if (*guest_count) {
		for (int i = 0; i < *guest_count; i++) {
			printf("(%i) %s, %s\n", i + 1, (*guests)[i]->last_name, (*guests)[i]->first_name);
		}
		printf("(%i) Go Back\n", *guest_count+1);
		int choice = get_int();
		if (choice != *guest_count+1)
			delete_guest(guests, guest_count, choice - 1, reservations, reservation_count);
	}
	else {
		printf("No guests found.\n");
		system("pause");
	}
}

void hotel_display_employees(Employee **employees, int employee_count, Hotel *hotel) {
	Employee **result = (Employee**)malloc(0);
	int hotel_employee_count = get_hotel_employees(hotel, employees, employee_count, &result);
	system("cls");
	printf("Hotel Employees:\n");
	if (hotel_employee_count) {
		for (int i = 0; i < hotel_employee_count; i++) {
			printf("Employee #%i: %s, %s Salary: $%0.f Current Task: ", employees[i]->id, employees[i]->last_name, employees[i]->first_name, employees[i]->salary);
			if (employees[i]->task) {
				printf("Work Order #%i\n", employees[i]->task->id);
			}
			else {
				printf("None\n");
			}
		}
	}
	else {
		printf("No employees found.\n");
	}
	system("pause");
}

void hotel_delete_employee(Employee ***employees, int *employee_count,Hotel *hotel) {
	Employee **result = (Employee**)malloc(0);
	int hotel_employee_count = get_hotel_employees(hotel, *employees, *employee_count, &result);
	system("cls");
	printf("Choose an employee to delete:\n");
	if (hotel_employee_count) {
		for (int i = 0; i < hotel_employee_count; i++) {
			printf("(%i) %s, %s\n", i + 1, result[i]->last_name, result[i]->first_name);
		}
		printf("(%i) Go Back\n", hotel_employee_count+1);
		int choice = get_int();
		if (choice != hotel_employee_count+1)
			delete_employee_by_id(employees, employee_count, result[choice - 1]->id);
	}
	else {
		printf("No employees found.\n");
		system("pause");
	}
}

void hotel_assign_work_order(Employee **employees, int employee_count, WorkOrder **work_orders,int work_order_count) {
	//Employee **unassigned_employees = get_unassigned_employees(employees, employee_count);
	system("cls");
	printf("Choose a work order to assign:\n");
	if (work_order_count) {
		for (int i = 0; i < work_order_count; i++) {
			Employee *employee = get_work_order_employee(work_orders[i], employees, employee_count);
			if (employee) {
				printf("(%i) %s [Assigned to %s %s]\n", i + 1, work_orders[i]->name, employee->first_name, employee->last_name);
			}
			else {
				printf("(%i) %s\n", i + 1, work_orders[i]->name);
			}
		}
		printf("(%i) Go Back\n", work_order_count+1);
		int choice = get_int();
		if (choice == work_order_count+1)
				return;
		WorkOrder *work_order = work_orders[choice - 1];
		system("cls");
		printf("Choose an employee to assign this work order to:\n");
		for (int i = 0; i<employee_count; i++) {
			if (employees[i]->task) {
				printf("(%i) %s %s [Assigned to Work Order #%i]\n", i + 1, employees[i]->first_name, employees[i]->last_name, employees[i]->task->id);
			}
			else {
				printf("(%i) %s %s\n", i + 1, employees[i]->first_name, employees[i]->last_name);
			}
		}
		choice = get_int();
		Employee *employee = employees[choice - 1];
		assign_workorder(work_order, employee, employees, employee_count);
	}
	else {
		printf("No work order found.\n");
		system("pause");
		return;
	}
}

void hotel_checkout_reservation(Reservation ***reservations, int *reservation_count) {
	system("cls");
	printf("Choose a reservation to check-out:\n");
	if (*reservation_count) {
		for (int i = 0; i < *reservation_count; i++) {
			printf("(%i) Reservation #%i: Guest: %s, %s Room: #%i\n", i + 1, (*reservations)[i]->id, (*reservations)[i]->guest->last_name, (*reservations)[i]->guest->first_name, (*reservations)[i]->room->number);
		}
		printf("(%i) Go Back\n", *reservation_count+1);
		int choice = get_int();
		if (choice != *reservation_count+1)
			checkout_reservation((*reservations)[choice - 1], reservations, reservation_count);
	}
	else {
		printf("No reservations found.\n");
		system("pause");
	}
}

void reset_guest_password(Guest **guests, int guest_count) {
	system("cls");
	printf("Choose a guest to reset their password:\n");
	if (guest_count) {
		for (int i = 0; i < guest_count; i++) {
			printf("(%i) %s, %s\n", i + 1, guests[i]->last_name, guests[i]->first_name);
		}
		printf("(%i) Go Back\n", guest_count+1);
		int choice = get_int();
		if (choice == guest_count+1)
			return;
		Guest *guest = guests[choice - 1];
		printf("Please enter new password for guest %s, %s:\n", guest->last_name, guest->first_name);
		char *password = get_string();
		guest->password = password;
		save_guests_to_file(guests, guest_count);
	}
	else {
		printf("No guests found.\n");
		system("pause");
	}
}

Role authenticate(char *username, char *password,Guest **guests, int guest_count, Employee **employees,int employee_count) {
	for (int i = 0; i < employee_count; i++)
		if (!strcmp(employees[i]->username,username) && !strcmp(employees[i]->password,password)) {
			if (employees[i]->role == admin) {
				return admin;
			}
			else if (employees[i]->role == worker) {
				return worker;
			}
		}
	for (int i = 0; i < guest_count; i++) {
		if (!strcmp(guests[i]->username,username) && !strcmp(guests[i]->password,password))
			return guest;
	}
	return invalid_credentials;
}

void login_screen(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count) {
	Role role = none;
	while (role == none || role == invalid_credentials) {
		system("cls");
		printf("Welcome to HMS:\n");
		if (role == invalid_credentials) {
			printf("Invalid username or password!\n");
			role = none;
		}
		printf("Enter Username: ");
		char *username = get_string();
		printf("Enter Password: ");
		char *password = get_string();
		role = authenticate(username, password,*guests,*guest_count,*employees,*employee_count);
	}
	switch (role) {
	case admin:
		display_enterprise_management_menu(hotels, hotel_count, rooms, room_count, work_orders, work_order_count, reservations, reservation_count, guests,guest_count, employees, employee_count);
		break;
	case worker:
		break;
	case guest:
		break;
	}
}