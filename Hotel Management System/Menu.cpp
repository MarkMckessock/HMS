#include "Menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

void display_enterprise_management_menu(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count,Employee ***employees,int *employee_count) {
	//display the primary menu for admin users allowing them to choose to add, list delete or manage hotels
	bool flag = true,success;
	int choice;
	while (flag) {
		clear();
		printf("Management Menu:\n");
		printf("(1) Create Hotel\n");
		printf("(2) List Hotels\n");
		printf("(3) Delete Hotel\n");
		printf("(4) Choose hotel to manage\n");
		printf("(5) Logout\n");
		printf("(6) Quit\n");
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
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
	//display a list of hotels and allow the user to delete one.
	bool success;
	int choice;
	clear();
	if (!(*hotel_count)) {
		printf("No Hotels Available.\n");
		pause();
		return;
	}
	printf("Choose a hotel to delete:\n");
	for (int i = 0; i < *hotel_count; i++) {
		printf("(%i) ",i+1);
		display_hotel((*hotels)[i], rooms, room_count);
	}
	printf("(%i) Go Back\n",*hotel_count);
	do {
		choice = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
	} while (!success);
	if(choice != *hotel_count)
		delete_hotel_by_index(hotels, hotel_count, choice - 1);
}

void display_hotel_selection_menu(Hotel **hotels, int hotel_count, Room ***rooms, int *room_count,WorkOrder ***work_orders,int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count,Employee ***employees,int *employee_count) {
	//display a list of hotels and allow the user to choose one to manage
	bool success;
	int choice;
	clear();
	if (!hotel_count) {
		printf("No Hotels Available. Create one to begin.\n");
		pause();
		return;
	}
	printf("Choose a hotel to manage:\n");
	for (int i = 0; i < hotel_count; i++) {
		printf("(%i) ", i + 1);
		display_hotel(hotels[i], *rooms, *room_count);
	}
	printf("(%i) Go Back\n",hotel_count+1);
	do {
		choice = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
	} while (!success);
	if(choice != hotel_count+1)
		display_franchise_management_menu(hotels[choice - 1],hotels,hotel_count,rooms,room_count,work_orders,work_order_count,reservations,reservation_count,guests,guest_count,employees,employee_count);
}

void display_franchise_management_menu(Hotel* hotel, Hotel** hotels, int hotel_count,Room ***rooms,int *room_count,WorkOrder ***work_orders,int *work_order_count,Reservation ***reservations,int *reservation_count,Guest ***guests,int *guest_count,Employee ***employees,int *employee_count) {
	//display the options available for each hotel
	bool flag = true,success;
	int choice;
	while (flag) {
		clear();
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
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		switch (choice) {
		case 1:
			hotel_display_rooms(hotel, *rooms, *room_count, *reservations, *reservation_count);
			break;
		case 2:
			hotel_edit_rooms(*rooms, *room_count,hotel);
			break;
		case 3:
			user_create_room(hotel, 0, rooms, room_count);
			break;
		case 4:
			hotel_delete_room(rooms, room_count,reservations,reservation_count,hotel);
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
			hotel_assign_work_order(*employees, *employee_count, *work_orders, *work_order_count,hotel);
			break;
		case 9:
			hotel_delete_work_order(work_orders,work_order_count,*employees,*employee_count,hotel);
			break;
		case 10:
			hotel_display_reservations(*reservations, *reservation_count, hotel);
			break;
		case 11:
			user_create_reservation(*guests, *guest_count, NULL,reservations, reservation_count, hotels,hotel_count,hotel, *rooms, *room_count);
			break;
		case 12:
			hotel_checkout_reservation(reservations, reservation_count);
			break;
		case 13:
			hotel_delete_reservation(reservations, reservation_count,hotel);
			break;
		case 14:
			hotel_display_guests(*guests, *guest_count);
			break;
		case 15:
			user_create_guest(guests, guest_count,*employees,*employee_count);
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
			user_create_employee(employees, employee_count, hotel,*guests,*guest_count);
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
	//display all the rooms at the given hotel
	Room **hotel_rooms = (Room**)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count,&hotel_rooms);
	clear();
	printf("Hotel Rooms:\n");
	if (room_count) {
		for (int i = 0; i < hotel_room_count; i++) {
			printf("Room #%i: Style: %s Status: %s\n", hotel_rooms[i]->number, room_type_names[hotel_rooms[i]->type], get_room_status(hotel_rooms[i], reservations, reservation_count, get_current_date()) ? "Available" : "Booked");
		}
	}
	else {
		printf("No rooms found.\n");
	}
	pause();
}

void hotel_delete_room(Room ***rooms, int *room_count, Reservation ***reservations, int *reservation_count, Hotel *hotel) {
	//display all rooms at a hotel and choose one to delete
	int choice;
	bool success;
	Room **hotel_rooms = (Room**)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, *rooms, *room_count, &hotel_rooms);
	clear();
	printf("Choose a room to delete:\n");
	if (*room_count) {
		for (int i = 0; i < hotel_room_count; i++) {
			printf("(%i) Room #%i: %s\n", i + 1, hotel_rooms[i]->number, room_type_names[hotel_rooms[i]->type]);
		}
		printf("(%i) Go Back\n", hotel_room_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != hotel_room_count+1)
			delete_room_by_id(rooms, room_count, reservations, reservation_count,hotel_rooms[choice - 1]->id);
	}
	else {
		printf("No rooms found.\n");
		pause();
	}
}

void hotel_edit_rooms(Room **rooms,int room_count,Hotel *hotel) {
	//display all the rooms at a hotel and choose one to edit
	bool success;
	int choice;
	Room **hotel_rooms = (Room**)malloc(0);
	int hotel_room_count = get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count, &hotel_rooms);
	clear();
	printf("Choose room to edit:\n");
	if (room_count) {
		for (int i = 0; i < hotel_room_count; i++) {
			printf("(%i) Room #%i: %s\n", i + 1, rooms[i]->number, room_type_names[rooms[i]->type]);
		}
		printf("(%i) Go Back\n", hotel_room_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != hotel_room_count+1)
			edit_room(hotel_rooms[choice - 1], rooms, room_count);
	}
	else {
		printf("No rooms found.\n");
		pause();
	}
}

void hotel_edit_room_rate(Hotel *hotel) {
	//edit the rate for any given room type
	bool success;
	int choice;
	clear();
	printf("Edit rate for hotel \"%s\"\n", hotel->name);
	printf("(1) Single Room Rate [$%0.2f]\n", hotel->single_rate);
	printf("(2) Double Room Rate [$%0.2f]\n", hotel->double_rate);
	printf("(3) Suite Rate [$%0.2f]\n", hotel->suite_rate);
	printf("(4) Go Back\n");
	do {
		choice = get_int(&success);
		if (!success)
			printf("Invalid Choice\n");
	} while (!success);
	clear();
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
	//display all work orders at a given hotel
	WorkOrder ***result = (WorkOrder***)malloc(0);
	int hotel_work_order_count = get_hotel_work_orders(work_orders, work_order_count, hotel, result);
	clear();
	printf("Hotel Work Orders:\n");
	if (hotel_work_order_count) {
		for (int i = 0; i < hotel_work_order_count; i++) {
			printf("Work Order #%i: \"%s\" Created %s\n\t%s\n", (*result)[i]->id, (*result)[i]->name, print_date((*result)[i]->date_created), (*result)[i]->description);
		}
	}
	else {
		printf("No work orders found.\n");
	}
	pause();
}

void hotel_delete_work_order(WorkOrder ***work_orders, int *work_order_count,Employee **employees,int employee_count,Hotel *hotel) {
	//display all work orders and choose one to delete
	int choice;
	bool success;
	WorkOrder **result = (WorkOrder**)malloc(0);
	int hotel_work_order_count = get_hotel_work_orders(*work_orders, *work_order_count, hotel, &result);
	clear();
	printf("Choose a work order to delete:\n");
	if (hotel_work_order_count) {
		for (int i = 0; i < hotel_work_order_count; i++) {
			printf("(%i) %s\n", i + 1, result[i]->name);
		}
		printf("(%i) Go Back\n", hotel_work_order_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != hotel_work_order_count+1)
			delete_work_order_by_id(work_orders, work_order_count, result[choice - 1]->id, employees, employee_count);
	}
	else {
		printf("No work orders found.\n");
		pause();
	}
}

void hotel_display_reservations(Reservation **reservations, int reservation_count, Hotel *hotel) {
	//display all reservations at a given hotel
	Reservation ***result = (Reservation***)malloc(0);
	int hotel_reservation_count = get_hotel_reservations(reservations, reservation_count, hotel, result);
	clear();
	printf("Hotel Reservations:\n");
	if (hotel_reservation_count) {
		for (int i = 0; i < hotel_reservation_count; i++) {
			printf("Reservation #%i: Guest: \"%s %s\" Room: #%i [%s - %s]\n", (*result)[i]->id, (*result)[i]->guest->first_name, (*result)[i]->guest->last_name, (*result)[i]->room->number, print_date((*result)[i]->start), print_date((*result)[i]->end));
		}
	}
	else {
		printf("No reservations found.\n");
	}
	pause();
}

void hotel_delete_reservation(Reservation ***reservations, int *reservation_count,Hotel *hotel) {
	//display all reservations and choose one to delete
	int choice;
	bool success;
	Reservation **result = (Reservation**)malloc(0);
	int hotel_reservation_count = get_hotel_reservations(*reservations, *reservation_count, hotel, &result);
	clear();
	printf("Choose a reservation to delete:\n");
	if (hotel_reservation_count) {
		for (int i = 0; i < hotel_reservation_count; i++) {
			printf("(%i) Guest: %s %s Room #%i\n", i + 1, result[i]->guest->first_name, result[i]->guest->last_name, result[i]->room->number);
		}
		printf("(%i) Go Back\n", hotel_reservation_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != hotel_reservation_count+1)
			delete_reservation_by_id(reservations, reservation_count, result[choice - 1]->id);
	}
	else {
		printf("No reservations found.\n");
		pause();
	}
}

void hotel_display_guests(Guest **guests, int guest_count) {
	//display all guests
	clear();
	printf("Hotel Guests:\n");
	if (guest_count) {
		for (int i = 0; i < guest_count; i++) {
			printf("Guest #%i: %s, %s\n", guests[i]->id, guests[i]->last_name, guests[i]->first_name);
		}
	}
	else {
		printf("No guests found.\n");
	}
	pause();
}

void hotel_delete_guest(Guest ***guests, int *guest_count,Reservation ***reservations,int *reservation_count) {
	//display all guests and choose one to delete
	int choice;
	bool success;
	clear();
	printf("Choose a guest to delete:\n");
	if (*guest_count) {
		for (int i = 0; i < *guest_count; i++) {
			printf("(%i) %s, %s\n", i + 1, (*guests)[i]->last_name, (*guests)[i]->first_name);
		}
		printf("(%i) Go Back\n", *guest_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != *guest_count+1)
			delete_guest(guests, guest_count, choice - 1, reservations, reservation_count);
	}
	else {
		printf("No guests found.\n");
		pause();
	}
}

void hotel_display_employees(Employee **employees, int employee_count, Hotel *hotel) {
	//display all employees at a given hotel
	Employee **result = (Employee**)malloc(0);
	int hotel_employee_count = get_hotel_employees(hotel, employees, employee_count, &result);
	clear();
	printf("Hotel Employees:\n");
	if (hotel_employee_count) {
		for (int i = 0; i < hotel_employee_count; i++) {
			printf("Employee #%i: %s, %s Salary: $%0.f Current Task: ", result[i]->id, result[i]->last_name, result[i]->first_name, result[i]->salary);
			if (result[i]->task) {
				printf("Work Order #%i\n", result[i]->task->id);
			}
			else {
				printf("None\n");
			}
		}
	}
	else {
		printf("No employees found.\n");
	}
	pause();
}

void hotel_delete_employee(Employee ***employees, int *employee_count,Hotel *hotel) {
	//display all employees at a given hotel and choose one to delete
	bool success;
	int choice;
	Employee **result = (Employee**)malloc(0);
	int hotel_employee_count = get_hotel_employees(hotel, *employees, *employee_count, &result);
	clear();
	printf("Choose an employee to delete:\n");
	if (hotel_employee_count) {
		for (int i = 0; i < hotel_employee_count; i++) {
			printf("(%i) %s, %s\n", i + 1, result[i]->last_name, result[i]->first_name);
		}
		printf("(%i) Go Back\n", hotel_employee_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != hotel_employee_count+1)
			delete_employee_by_id(employees, employee_count, result[choice - 1]->id);
	}
	else {
		printf("No employees found.\n");
		pause();
	}
}

void hotel_assign_work_order(Employee **employees, int employee_count, WorkOrder **work_orders,int work_order_count,Hotel *hotel) {
	//display all work orders and choose one to assign to a chosen employee
	int choice;
	bool success;
	WorkOrder **result;
	int hotel_work_order_count = get_hotel_work_orders(work_orders, work_order_count, hotel, &result);
	clear();
	printf("Choose a work order to assign:\n");
	if (hotel_work_order_count) {
		for (int i = 0; i < hotel_work_order_count; i++) {
			Employee *employee = get_work_order_employee(result[i], employees, employee_count);
			if (employee) {
				printf("(%i) %s [Assigned to %s %s]\n", i + 1, result[i]->name, employee->first_name, employee->last_name);
			}
			else {
				printf("(%i) %s\n", i + 1, result[i]->name);
			}
		}
		printf("(%i) Go Back\n", hotel_work_order_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice == hotel_work_order_count+1)
				return;
		WorkOrder *work_order = result[choice - 1];
		clear();
		printf("Choose an employee to assign this work order to:\n");
		for (int i = 0; i<employee_count; i++) {
			if (employees[i]->task) {
				printf("(%i) %s %s [Assigned to Work Order #%i]\n", i + 1, employees[i]->first_name, employees[i]->last_name, employees[i]->task->id);
			}
			else {
				printf("(%i) %s %s\n", i + 1, employees[i]->first_name, employees[i]->last_name);
			}
		}
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		Employee *employee = employees[choice - 1];
		assign_workorder(work_order, employee, employees, employee_count);
	}
	else {
		printf("No work order found.\n");
		pause();
		return;
	}
}

void hotel_checkout_reservation(Reservation ***reservations, int *reservation_count) {
	//process a reservation an calculate the amount due
	int choice;
	bool success;
	clear();
	printf("Choose a reservation to check-out:\n");
	if (*reservation_count) {
		for (int i = 0; i < *reservation_count; i++) {
			printf("(%i) Reservation #%i: Guest: %s, %s Room: #%i\n", i + 1, (*reservations)[i]->id, (*reservations)[i]->guest->last_name, (*reservations)[i]->guest->first_name, (*reservations)[i]->room->number);
		}
		printf("(%i) Go Back\n", *reservation_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != *reservation_count+1)
			checkout_reservation((*reservations)[choice - 1], reservations, reservation_count);
	}
	else {
		printf("No reservations found.\n");
		pause();
	}
}

void reset_guest_password(Guest **guests, int guest_count) {
	//display all guests and choose one to reset their password
	int choice;
	bool success;
	clear();
	printf("Choose a guest to reset their password:\n");
	//if there are guests, list them
	if (guest_count) {
		for (int i = 0; i < guest_count; i++) {
			printf("(%i) %s, %s\n", i + 1, guests[i]->last_name, guests[i]->first_name);
		}
		printf("(%i) Go Back\n", guest_count+1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice == guest_count+1)
			return;
		Guest *guest = guests[choice - 1];
		printf("Please enter new password for guest %s, %s:\n", guest->last_name, guest->first_name);
		//validate that there are no ',' in password
		char *password = get_string("Password");
		guest->password = password;
		save_guests_to_file(guests, guest_count);
	}
	else {
		printf("No guests found.\n");
		pause();
	}
}

Role authenticate(char *username, char *password,Guest **guests, int guest_count, Employee **employees,int employee_count,Guest **user,Employee **employee) {
	//take a username and password and return a role corresponding to whether the user exists
	for (int i = 0; i < employee_count; i++)
		if (!strcmp(employees[i]->username,username) && !strcmp(employees[i]->password,password)) {
			*employee = employees[i];
			if (employees[i]->role == admin) {
				return admin;
			}
			else if (employees[i]->role == worker) {
				return worker;
			}
		}
	for (int i = 0; i < guest_count; i++) {
		if (!strcmp(guests[i]->username, username) && !strcmp(guests[i]->password, password)) {
			*user = guests[i];
			return guest;
		}
	}
	return invalid_credentials;
}

void login_screen(Hotel ***hotels, int *hotel_count, Room ***rooms, int *room_count, WorkOrder ***work_orders, int *work_order_count, Reservation ***reservations, int *reservation_count, Guest ***guests, int *guest_count, Employee ***employees, int *employee_count) {
	//prompt the user to enter a username and password or to create an account
	Role role = none;
	Guest *user = NULL;
	Employee *employee = NULL;
	bool flag = true,success;
	int choice;
	while (flag) {
		clear();
		printf("Welcome to HMS: (Admin Account: Username: 'tsmith' Password: 'password')\n");
		printf("(1) Login\n");
		printf("(2) Register\n");
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		switch (choice) {
		case 1:
			while (role == none || role == invalid_credentials) {
				user = NULL;
				employee = NULL;
				clear();
				printf("Login to HMS (Admin Account: Username: 'tsmith' Password: 'password'):\n");
				if (role == invalid_credentials) {
					printf("Invalid username or password!\n");
					role = none;
				}
				printf("Enter Username (Hit 'enter' to go back): ");
				char *username = get_string("Username");
				if (!strcmp(username, ""))
					break;
				printf("Enter Password: ");
				char *password = get_string("Password");
				role = authenticate(username, password, *guests, *guest_count, *employees, *employee_count, &user, &employee);
			}
			switch (role) {
			case admin:
				display_enterprise_management_menu(hotels, hotel_count, rooms, room_count, work_orders, work_order_count, reservations, reservation_count, guests, guest_count, employees, employee_count);
				break;
			case worker:
				display_employee_menu(employee);
				break;
			case guest:
				display_guest_menu(user, reservations, reservation_count, *rooms, *room_count, *hotels, *hotel_count);
				break;
			}
			role = none;
			break;
		case 2:
			user_create_guest(guests, guest_count,*employees,*employee_count);
			continue;
		}
	}

}

void guest_cancel_reservation(Guest *guest, Reservation ***reservations, int *reservation_count) {
	//display all reservations created by a given guest and choose one to cancel
	int choice;
	bool success;
	clear();
	Reservation **result;
	int guest_reservation_count = get_guest_reservations(*reservations, *reservation_count, guest, &result);
	if (guest_reservation_count) {
		for (int i = 0; i < guest_reservation_count; i++) {
			printf("(%i) Hotel: %s Room: #%i [%s - %s]\n", i + 1, result[i]->room->hotel->name, result[i]->room->number, print_date(result[i]->start), print_date(result[i]->end));
		}
		printf("(%i) Go Back\n", guest_reservation_count + 1);
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		if (choice != guest_reservation_count + 1) {
			delete_reservation_by_id(reservations, reservation_count, result[choice - 1]->id);
		}
	}
	else {
		printf("No Reservations found.\n");
		pause();
	}
}


void display_employee_menu(Employee *employee) {
	//display the options for an employee
	bool flag = true;
	int choice;
	char* password;
	while (flag) {
		clear();
		printf("Welcome employee %s %s,\n",employee->first_name,employee->last_name);
		printf("(1) View Current Task\n");
		printf("(2) View Salary\n");
		printf("(3) Reset Password\n");
		printf("(4) Logout\n");
		printf("(5) Quit\n");
		bool success;
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		switch (choice) {
		case 1:
			clear();
			printf("Current Employee Task:\n");
			if (employee->task)
				printf("Task #%i: %s\n", employee->task->id, employee->task->name);
			else
				printf("Task: None\n");
			pause();
			break;
		case 2:
			clear();
			printf("Employee Salary:\n");
			printf("Current Salary: %0.2f\n",employee->salary);
			pause();
			break;
		case 3:
			clear();
			printf("Reset Employee Password:\n");
			printf("Please enter new password\n");
			password = get_string("Password");
			employee->password = password;
			break;
		case 4:
			flag = false;
			break;
		case 5:
			exit(EXIT_SUCCESS);
			break;
		}
	}
}

void display_guest_reservations(Guest *guest, Reservation **reservations, int reservation_count) {
	//display all the reservations created by a given guest
	clear();
	Reservation **result;
	int guest_reservation_count = get_guest_reservations(reservations, reservation_count, guest, &result);
	printf("Guest Reservations:\n");
	for (int i = 0; i < guest_reservation_count; i++) {
		printf("Reservation #%i: Hotel: %s Room: #%i [%s - %s]\n", result[i]->id, result[i]->room->hotel->name,result[i]->room->number,print_date(result[i]->start), print_date(result[i]->end));
	}
	pause();
}

void display_guest_menu(Guest *guest,Reservation ***reservations,int *reservation_count,Room **rooms,int room_count,Hotel **hotels,int hotel_count) {
	//display the options available to guest
	bool flag = true,success;
	char *password;
	int choice;
	while (flag) {
		clear();
		printf("Welcome guest %s %s:\n", guest->first_name, guest->last_name);
		printf("(1) View my Reservations\n");
		printf("(2) Create new Reservation\n");
		printf("(3) Cancel Reservation\n");
		printf("(4) Reset my Password\n");
		printf("(5) Logout\n");
		printf("(6) Quit\n");
		do {
			choice = get_int(&success);
			if (!success)
				printf("Invalid Choice\n");
		} while (!success);
		switch (choice) {
		case 1:
			display_guest_reservations(guest, *reservations, *reservation_count);
			break;
		case 2:
			user_create_reservation(NULL, NULL, guest,reservations, reservation_count, hotels,hotel_count,NULL,rooms, room_count);
			break;
		case 3:
			guest_cancel_reservation(guest, reservations, reservation_count);
			break;
		case 4:
			clear();
			printf("Please enter new password: (Hit 'enter' to go back)\n");
			password = get_string("Password");
			if (strcmp(password, ""))
				guest->password = password;
			break;
		case 5:
			flag = false;
			break;
		case 6:
			exit(EXIT_SUCCESS);
			break;
		}
	}
}