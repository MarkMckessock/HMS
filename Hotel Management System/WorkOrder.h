#pragma once
#include "Date.h"
#include <stdio.h>
#include "func.h"
#include "MonthTypes.h"
#include "Hotel.h"
#include <time.h>

#ifndef WORKORDER
#define WORKORDER

typedef struct WorkOrder {
	char* name;
	int id;
	char* description;
	Date date_created;
	Hotel *hotel;
} WorkOrder;

int load_work_orders_from_file(WorkOrder ***work_orders, Hotel **hotels, int hotel_count);

void save_work_orders_to_file(WorkOrder **work_orders, int work_order_count);

int get_hotel_work_orders(WorkOrder **work_orders, int work_order_count, Hotel *hotel, WorkOrder ***result);

void user_create_work_order(Hotel* hotel, WorkOrder ***work_orders, int *work_order_count);

void create_work_order(Hotel *hotel, WorkOrder ***work_order, int *work_order_count, char* name, char *description);

#endif // !WORKORDER
