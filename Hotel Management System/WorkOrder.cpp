#include "WorkOrder.h"
#include <string>

int load_work_orders_from_file(WorkOrder ***work_orders,Hotel **hotels,int hotel_count) {
	//load work orders from file and parse them into an array
	//return number of work orders found
	int work_order_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "work_orders.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			work_order_count = atoi(strstr(line, "Work Order Count: ") + 18);
		}
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			WorkOrder *work_order = (WorkOrder *)malloc(sizeof(WorkOrder));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			work_order->id = atoi(splits[0]);
			work_order->name = splits[1];
			work_order->description = splits[2];
			work_order->hotel = get_hotel_by_id(hotels,hotel_count,atoi(splits[3]));
			work_order->date_created.day = atoi(splits[4]);
			work_order->date_created.month = (Month)atoi(splits[5]);
			work_order->date_created.year = atoi(splits[6]);
			(*work_orders) = (WorkOrder **)realloc(*work_orders, (i + 1) * sizeof(WorkOrder*));
			(*work_orders)[i] = work_order;
			i++;
		}
		fclose(fp);
		return work_order_count;
	}
	else {
		return 0;
	}
}

void save_work_orders_to_file(WorkOrder **work_orders, int work_order_count) {
	//save all work orders to file
	FILE *fp;
	fopen_s(&fp, "work_orders.txt", "w");
	fprintf(fp, "Work Order Count: %i\n", work_order_count);
	for (int i = 0; i < work_order_count; i++)
		fprintf(fp, "%i,%s,%s,%i,%i,%i,%i\n", work_orders[i]->id, work_orders[i]->name, work_orders[i]->description, work_orders[i]->hotel->id, work_orders[i]->date_created.day, work_orders[i]->date_created.month, work_orders[i]->date_created.year);
	fclose(fp);
}

int get_hotel_work_orders(WorkOrder **work_orders, int work_order_count, Hotel *hotel, WorkOrder ***result) {
	//get all work orders assigned to a given hotel
	int count = 0;
	*result = (WorkOrder**)malloc(0);
	for (int i = 0; i < work_order_count; i++) {
		if (work_orders[i]->hotel == hotel) {
			*result = (WorkOrder**)realloc(*result, (count + 1) * sizeof(WorkOrder*));
			(*result)[count] = work_orders[i];
			count++;
		}
	}
	return count;
}

void user_create_work_order(Hotel* hotel, WorkOrder ***work_orders, int *work_order_count){
	//prompt user for information to create work order
	clear();
	printf("Please enter a short name for this work-order: (Hit 'enter' to go back)\n");
	char *name = get_string("Work Order Name");
	if (!strcmp(name, ""))
		return;
	printf("Please enter a short description:\n");
	char *description = get_string("Description");
	create_work_order(hotel, work_orders, work_order_count, name, description);
	printf("Work Order Created.\n");
	pause();
}

void create_work_order(Hotel *hotel, WorkOrder ***work_orders, int *work_order_count, char* name, char *description) {
	//create work order from given data
	WorkOrder *work_order = (WorkOrder*)malloc(sizeof(WorkOrder));
	work_order->name = name;
	work_order->description = description;
	work_order->hotel = hotel;
	work_order->date_created = get_current_date();
	work_order->id = *work_order_count == 0 ? 1 : ((*work_orders)[*work_order_count - 1]->id)+1;
	*work_orders = (WorkOrder**)realloc(*work_orders, (*work_order_count + 1)*sizeof(WorkOrder*));
	(*work_orders)[*work_order_count] = work_order;
	(*work_order_count)++;
	save_work_orders_to_file(*work_orders, *work_order_count);
}

WorkOrder* get_work_order_by_id(WorkOrder **work_orders, int work_order_count, int id) {
	//get the work order with the given id and return a pointer to it
	for (int i = 0; i < work_order_count; i++) {
		if (work_orders[i]->id == id)
			return work_orders[i];
	}
}

void delete_work_order_by_index(WorkOrder ***work_orders, int *work_order_count, int index,Employee **employees,int employee_count) {
	//delete a work order from the array by index
	for (int i = 0; i < employee_count; i++)
		if (employees[i]->task == (*work_orders)[index])
			employees[i]->task = NULL;
	free((*work_orders)[index]);
	for (int i = index; i < (*work_order_count) - 1; i++) {
		(*work_orders)[i] = (*work_orders)[i + 1];
	}
	(*work_order_count)--;
	*work_orders = (WorkOrder**)realloc(*work_orders, (*work_order_count) * sizeof(WorkOrder*));
	save_work_orders_to_file(*work_orders, *work_order_count);
}

void delete_work_order_by_id(WorkOrder ***work_orders, int *work_order_count, int id, Employee **employees, int emplyee_count) {
	//delete the specified work order by id
	for (int i = 0; i < *work_order_count; i++)
		if ((*work_orders)[i]->id == id)
			delete_work_order_by_index(work_orders, work_order_count, i, employees, emplyee_count);
}