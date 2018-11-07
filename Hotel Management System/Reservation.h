#pragma once
#include "Room.h"
#include "Date.h"
#include "guest.h"

typedef struct Reservation {
	Room *room;
	Guest *guest;
	int id;
	Date start;
	Date end;
}Reservation;