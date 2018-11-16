#include "Employee.h"
#include "WorkOrder.h"
#include <stdio.h>
#include <string>
#include "func.h"

void save_employees_to_file(Employee **employees, int employee_count) {
	//save all employees to file
	FILE *fp;
	fopen_s(&fp, "employee.txt", "w");
	fprintf(fp, "Employee Count: %i\n", employee_count);
	for (int i = 0; i < employee_count; i++)
		fprintf(fp, "%i,%s,%s,%s,%s,%i,%i,%i,%f\n", employees[i]->id, employees[i]->first_name, employees[i]->last_name, employees[i]->username, employees[i]->password, employees[i]->hotel->id, employees[i]->task ? employees[i]->task->id : 0, employees[i]->role, employees[i]->salary);
	fclose(fp);
}

int load_employees_from_file(Employee ***employees,Hotel **hotels,int hotel_count,WorkOrder **work_orders,int work_order_count) {
	//load employees from file and parse into array
	int employee_count = 0, i = 0;
	FILE *fp;
	fopen_s(&fp, "employee.txt", "r");
	if (fp) {
		char line[81];
		if (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0;
			employee_count = atoi(strstr(line, "Employee Count: ") + 16);
		}
		while (fgets(line, sizeof(line), fp)) {
			line[strcspn(line, "\n")] = 0; //strip newline character
			Employee *employee = (Employee *)malloc(sizeof(Employee));
			char** splits;
			int count = 0;
			splits = split(line, ",", &count);
			employee->id = atoi(splits[0]);
			employee->first_name = splits[1];
			employee->last_name = splits[2];
			employee->username = splits[3];
			employee->password = splits[4];
			employee->hotel = get_hotel_by_id(hotels,hotel_count,atoi(splits[5]));
			employee->task = atoi(splits[6]) ? get_work_order_by_id(work_orders, work_order_count, atoi(splits[6])) : 0;
			employee->role = (Role)atoi(splits[7]);
			employee->salary = atof(splits[8]);
			(*employees) = (Employee **)realloc(*employees, (i + 1) * sizeof(Employee*));
			(*employees)[i] = employee;
			i++;
		}
		fclose(fp);
		return employee_count;
	}
	else {
		return 0;
	}
}

int get_hotel_employees(Hotel *hotel, Employee **employees, int employee_count, Employee ***result) {
	//get the employees of a specified hotel
	int count = 0;
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->hotel == hotel) {
			*result = (Employee**)realloc(*result, (1 + count) * sizeof(Employee*));
			(*result)[count] = employees[i];
			count++;
		}
	}
	return count;
}

void create_employee(Employee ***employees, int *employee_count, char *first_name, char *last_name, float salary, char *username, char *password, Hotel* hotel, Role role) {
	//create an employee from the provided arguments and add it to array
	Employee *employee = (Employee*)malloc(sizeof(Employee));
	employee->first_name = first_name;
	employee->last_name = last_name;
	employee->salary = salary;
	employee->username = username;
	employee->password = password;
	employee->hotel = hotel;
	employee->role = role;
	employee->id = *employee_count ? (*employees)[*employee_count - 1]->id + 1 : 1;
	employee->task = NULL;
	*employees = (Employee**)realloc(*employees, (1 + *employee_count) * sizeof(Employee*));
	(*employees)[*employee_count] = employee;
	(*employee_count)++;
	save_employees_to_file(*employees, *employee_count);
}

void user_create_employee(Employee ***employees, int *employee_count, Hotel *hotel, Guest **guests,int guest_count) {
	//prompt user to enter values to create employee
	bool valid = true;
	char *username;
	clear();
	printf("Create Employee:\n");
	//get first name
	printf("Please enter a first name: (Hit 'enter' to go back)\n");
	char *first_name = get_string("Name");
	//check for empty string
	if (!strcmp(first_name, ""))
		return;
	//get last name
	printf("Please enter a last name:\n");
	char *last_name = get_string("Name");
	//get salary
	printf("Please enter a salary for this employee:\n$");
	float salary = get_float();
	//get username
	printf("Please choose a username for this employee:\n");
	do {
		if (!valid) {
			printf("Username already used. Please choose another.\n");
		}
		username = get_string("Name");
		valid = validate_username(username, guests, guest_count, *employees, *employee_count);
	} while (!valid);
	//get password
	printf("Please choose a password for this employee:\n");
	char *password = get_string("Password");
	//create employee
	create_employee(employees, employee_count, first_name, last_name, salary, username, password, hotel, worker);
	save_employees_to_file(*employees, *employee_count);
}

void assign_workorder(WorkOrder *work_order, Employee *employee, Employee **employees, int employee_count) {
	//assign a work order to an employee
	//de-assign it from any employees it was previously assigned to
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->task == work_order)
			employees[i]->task = NULL;
	}
	employee->task = work_order;
	save_employees_to_file(employees, employee_count);
}

Employee* get_work_order_employee(WorkOrder *work_order, Employee **employees, int employee_count) {
	//get the employee assigned to a specified work order
	//if none is assigned, return NULL
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->task == work_order)
			return employees[i];
	}
	return NULL;
}

void delete_employee_by_index(Employee ***employees, int *employee_count, int index) {
	//delete an employee by index and remove it from the array
	if ((*employees)[index]->role == admin) {
		printf("Cannot delete 'admin' employee.\n");
		pause();
		return;
	}
	free((*employees)[index]);
	for (int i = index; i < (*employee_count) - 1; i++) {
		(*employees)[i] = (*employees)[i + 1];
	}
	(*employee_count)--;
	*employees = (Employee**)realloc(*employees, (*employee_count) * sizeof(Employee*));
	save_employees_to_file(*employees, *employee_count);
}

void delete_employee_by_id(Employee ***employees, int *employee_count, int id) {
	//delete an employee by id and remove it from the array
	for (int i = 0; i < *employee_count; i++)
		if ((*employees)[i]->id == id)
			delete_employee_by_index(employees, employee_count, i);
}