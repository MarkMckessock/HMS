#pragma once
#include <stdio.h>
#include <string>
#include "func.h"
#include "Role.h"
#include "Hotel.h"

struct WorkOrder;

typedef struct Employee {
	char *first_name;
	char *last_name;
	char *username;
	char *password;
	float salary;
	int id;
	Hotel *hotel;
	WorkOrder *task;
	Role role;
} Employee;

int load_employees_from_file(Employee ***employees, Hotel **hotels, int hotel_count, WorkOrder **work_orders, int work_order_count);

void save_employees_to_file(Employee **employees, int employee_count);

int get_hotel_employees(Hotel *hotel, Employee **employees, int employee_count, Employee ***result);

void user_create_employee(Employee ***employees, int *employee_count, Hotel *hotel);

void create_employee(Employee ***employees, int *employee_count, char *first_name, char *last_name, float salary, char *username, char *password, Hotel* hotel, Role role);

Employee** get_unassigned_employees(Employee **employees, int employee_count);

Employee* get_work_order_employee(WorkOrder *work_order, Employee **employees, int employee_count);

void assign_workorder(WorkOrder *work_order, Employee *employee, Employee **employees, int employee_count);

void delete_employee_by_index(Employee ***employees, int *employee_count, int index);

void delete_employee_by_id(Employee ***employees, int *employee_count, int id);