#include "Hotel.h"
#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "func.h"

Hotel* create_hotel(Hotel ***hotels, int *hotel_count,const char* name, const char* address,float single_rate,float double_rate,float suite_rate) {
	//create a hotel object and add it to an array of hotels. Return a pointer to the newly created hotel
	Hotel *hotel = (Hotel *)malloc(sizeof(Hotel));
	hotel->address = address;
	hotel->name = name;
	hotel->id = *hotel_count == 0 ? 1 : (*hotels)[*hotel_count - 1]->id + 1;
	hotel->single_rate = single_rate;
	hotel->double_rate = double_rate;
	hotel->suite_rate = suite_rate;
	*hotels = (Hotel **)realloc(*hotels, (*hotel_count+1) * sizeof(Hotel*));
	(*hotels)[*hotel_count] = hotel;
	(*hotel_count)++;
	save_hotels_to_file(*hotels, *hotel_count);
	return hotel;
}

void save_hotels_to_file(Hotel **hotels, int hotel_count) {
	FILE *fp;
	fopen_s(&fp,"hotels.txt", "w");
	fprintf(fp, "Hotel Count: %i\n", hotel_count);
	for (int i = 0; i < hotel_count; i++)
		fprintf(fp, "%i,%s,%s,%f,%f,%f\n", hotels[i]->id, hotels[i]->name, hotels[i]->address,hotels[i]->single_rate,hotels[i]->double_rate,hotels[i]->suite_rate);
	fclose(fp);
}

int load_hotels_from_file(Hotel ***hotels) {
	int hotel_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp,"hotels.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)){
			line[strcspn(line, "\n")] = 0;
			hotel_count = atoi(strstr(line, "Hotel Count: ") + 13);
		}
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Hotel *hotel = (Hotel *)malloc(sizeof(Hotel));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			hotel->id = atoi(splits[0]);
			hotel->name = splits[1];
			hotel->address = splits[2];
			hotel->single_rate = atof(splits[3]);
			hotel->double_rate = atof(splits[4]);
			hotel->suite_rate = atof(splits[5]);
			(*hotels) = (Hotel **)realloc(*hotels, (i + 1) * sizeof(Hotel*));
			(*hotels)[i] = hotel;
			i++;
		}
		fclose(fp);
		return hotel_count;
	}
	else {
		return 0;
	}
}

void user_create_hotel(Hotel ***hotels, int *hotel_count,Room ***rooms,int *room_count) {
	system("cls");
	printf("Create a new hotel:\n");
	printf("Enter hotel name:");
	char *name = get_string();
	printf("Enter hotel address:");
	char *address = get_string();
	printf("Enter Single Room Rate:\n$");
	float single_rate = get_float();
	printf("Enter Double Room Rate:\n$");
	float double_rate = get_float();
	printf("Enter Suite Rate:\n$");
	float suite_rate = get_float();
	Hotel *hotel = create_hotel(hotels, hotel_count, name, address,single_rate,double_rate,suite_rate);
	printf("Enter number of rooms:");
	int hotel_room_count = get_int();
	user_create_all_rooms(rooms, room_count, hotel, hotel_room_count);
}

void display_hotel(Hotel *hotel,Room **rooms,int room_count) {
	Room ***ptr = (Room***)malloc(0);
	printf("Hotel #%i: %s [%s]\n", hotel->id, hotel->name, hotel->address);
	printf("\t%i Rooms: %i Singles @ $%0.2f, %i Doubles @ $%0.2f, %i Suites @ $%0.2f.\n\n", get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count, ptr), get_hotel_rooms(hotel, single_bed, rooms, room_count, ptr), hotel->single_rate, get_hotel_rooms(hotel, double_bed, rooms, room_count, ptr),hotel->double_rate, get_hotel_rooms(hotel, suite, rooms, room_count, ptr),hotel->suite_rate);
}

void display_all_hotels(Hotel **hotels, int hotel_count,Room **rooms,int room_count) {
	system("cls");
	printf("Hotel List:\n");
	for (int i = 0; i < hotel_count; i++) {
		display_hotel(hotels[i],rooms,room_count);
	}
	system("pause");
}

int get_hotel_rooms(Hotel *hotel, RoomType type,Room **rooms,int room_count,Room *** result) {
	//returns the number of rooms of a given type for a given hotel and returns an array of said rooms. 
	//Returns an array of all rooms at a given hotel and the count if type = '-1'
	*result = (Room**)malloc(0);
	int count = 0;
	for (int i = 0; i < room_count; i++) {
		if (rooms[i]->hotel == hotel && (type == -1 || rooms[i]->type == type)) {
			*result = (Room**)realloc(*result, (count+1) * sizeof(Room*));
			(*result)[count] = rooms[i];
			count++;
		}
	}
	return count;
}

int get_hotel_rooms_available(Hotel *hotel, RoomType type, Room **rooms, int room_count, Reservation **reservations, int reservation_count, Room *** result, Date start,Date end) {
	*result = (Room**)malloc(0);
	int count = 0;
	bool available;
	for (int i = 0; i < room_count; i++) {
		available = true;
		if (rooms[i]->hotel == hotel && (type == -1 || rooms[i]->type == type)) {
			for (int j = 0; j < reservation_count; j++) {
				if (reservations[j]->room == rooms[i] && ((is_before(reservations[j]->start, start) && !is_before(reservations[j]->end, start)) || (is_before(start, reservations[j]->start) && is_before(reservations[j]->start, end)) || (is_before(end, reservations[j]->end) && !is_before(end, reservations[j]->start))))
					available = false;
			}
			if (available) {
				*result = (Room**)realloc(*result, (count + 1) * sizeof(Room*));
				(*result)[count] = rooms[i];
				count++;
			}
		}
	}
	return count;
}

void delete_hotel_by_index(Hotel ***hotels, int *hotel_count, int index) {
	//deletes the specifies hotel and removes it from the array
	free((*hotels)[index]);
	for (int i = index; i < (*hotel_count)-1; i++) {
		(*hotels)[i] = (*hotels)[i + 1];
	}
	(*hotel_count)--;
	*hotels = (Hotel**)realloc(*hotels, (*hotel_count) * sizeof(Hotel*));
	save_hotels_to_file(*hotels, *hotel_count);
}

Hotel* get_hotel_by_id(Hotel **hotels, int hotel_count, int id) {
	for (int i = 0; i < hotel_count; i++)
		if (hotels[i]->id == id)
			return hotels[i];
	return NULL;
}