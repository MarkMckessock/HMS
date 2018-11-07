#include "Hotel.h"
#include "Room.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "func.h"

Hotel* create_hotel(Hotel ***hotels, int *hotel_count,const char* name, const char* address) {
	//create a hotel object and add it to an array of hotels. Return a pointer to the newly created hotel
	Hotel *hotel = (Hotel *)malloc(sizeof(Hotel));
	hotel->address = address;
	hotel->name = name;
	hotel->id = *hotel_count == 0 ? 1 : (*hotels)[*hotel_count - 1]->id + 1;
	*hotels = (Hotel **)realloc(*hotels, (*hotel_count+1) * sizeof(Hotel*));
	(*hotels)[*hotel_count] = hotel;
	(*hotel_count)++;
	return hotel;
}

void save_hotels_to_file(Hotel **hotels, int hotel_count) {
	FILE *fp;
	fopen_s(&fp,"hotels.txt", "w");
	fprintf(fp, "Hotel Count: %i\n", hotel_count);
	for (int i = 0; i < hotel_count; i++)
		fprintf(fp, "%i,%s,%s\n", hotels[i]->id, hotels[i]->name, hotels[i]->address);
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
	printf("Create a new hotel:\n");
	printf("Enter hotel name:");
	char *name = get_string();
	printf("Enter hotel address:");
	char *address = get_string();
	Hotel *hotel = create_hotel(hotels, hotel_count, name, address);
	save_hotels_to_file(*hotels, *hotel_count);
	printf("Enter number of rooms:");
	int hotel_room_count = get_int();
	user_create_all_rooms(rooms, room_count, hotel, hotel_room_count);
	
}

void display_hotel(Hotel *hotel,Room **rooms,int room_count) {
	Room ***ptr = (Room***)malloc(0);
	printf("Hotel #%i: %s [%s]\n", hotel->id, hotel->name, hotel->address);
	printf("\t%i Rooms: %i Singles, %i Doubles, %i Suites.\n\n", get_hotel_rooms(hotel, (RoomType)-1, rooms, room_count, ptr), get_hotel_rooms(hotel, single_bed, rooms, room_count, ptr), get_hotel_rooms(hotel, double_bed, rooms, room_count, ptr), get_hotel_rooms(hotel, suite, rooms, room_count, ptr));
}

void display_all_hotels(Hotel **hotels, int hotel_count,Room **rooms,int room_count) {
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

void delete_hotel_by_index(Hotel ***hotels, int *hotel_count, int index) {
	//deletes the specifies hotel and removes it from the array
	free((*hotels)[index]);
	for (int i = index; i < (*hotel_count)-1; i++) {
		(*hotels)[i] = (*hotels)[i + 1];
	}
	(*hotel_count)--;
	*hotels = (Hotel**)realloc(*hotels, (*hotel_count) * sizeof(Hotel*));
}