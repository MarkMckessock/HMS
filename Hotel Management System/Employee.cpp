#include "Employee.h"

void save_employees_to_file(Employee **employees, int employee_count) {
	FILE *fp;
	fopen_s(&fp, "employee.txt", "w");
	fprintf(fp, "Employee Count: %i\n", employee_count);
	for (int i = 0; i < employee_count; i++)
		fprintf(fp, "%i,%s,%s,%s,%s,%i,%i,%i,%f\n", employees[i]->id, employees[i]->first_name, employees[i]->last_name, employees[i]->username, employees[i]->password, employees[i]->hotel->id, employees[i]->task ? employees[i]->task->id : 0, employees[i]->role, employees[i]->salary);
	fclose(fp);
}

int load_employees_from_file(Employee ***employees,Hotel **hotels,int hotel_count,WorkOrder **work_orders,int work_order_count) {
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
	int count = 0;
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->hotel == hotel) {
			*result = (Employee**)realloc(*result, (1 + count * sizeof(Employee*)));
			(*result)[count] = employees[i];
			count++;
		}
	}
	return count;
}

void create_employee(Employee ***employees, int *employee_count, char *first_name, char *last_name, float salary, char *username, char *password, Hotel* hotel, Role role) {
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
}

void user_create_employee(Employee ***employees, int *employee_count, Hotel *hotel) {
	printf("Create Employee:\n");
	printf("Please enter a first name:\n");
	char *first_name = get_string();
	printf("Please enter a last name:\n");
	char *last_name = get_string();
	printf("Please enter a salary for this employee:\n$");
	float salary = get_float();
	printf("Please choose a username for this employee:\n");
	char *username = get_string();
	printf("Please choose a password for this employee:\n");
	char *password = get_string();
	create_employee(employees, employee_count, first_name, last_name, salary, username, password, hotel, worker);
	save_employees_to_file(*employees, *employee_count);
}

void assign_workorder(WorkOrder *work_order, Employee *employee, Employee **employees, int employee_count) {
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->task == work_order)
			employees[i]->task = NULL;
	}
	employee->task = work_order;
	save_employees_to_file(employees, employee_count);
}

Employee** get_unassigned_employees(Employee **employees, int employee_count) {
	Employee **result = (Employee**)malloc(sizeof(Employee*));
	result[0] = NULL;
	int count = 0;
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->task) {
			result = (Employee**)realloc(result, (2 + count) * sizeof(Employee*));
			result[count] = employees[i];
			count++;
			result[count] = NULL;
		}
	}
	return result;
}

Employee* get_work_order_employee(WorkOrder *work_order, Employee **employees, int employee_count) {
	for (int i = 0; i < employee_count; i++) {
		if (employees[i]->task == work_order)
			return employees[i];
	}
	return NULL;
}

void delete_employee(Employee ***employees, int *employee_count, int index) {
	free((*employees)[index]);
	for (int i = index; i < (*employee_count) - 1; i++) {
		(*employees)[i] = (*employees)[i + 1];
	}
	(*employee_count)--;
	*employees = (Employee**)realloc(*employees, (*employee_count) * sizeof(Employee*));
}