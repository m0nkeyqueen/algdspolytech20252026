#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#define MAX_NAME_LENGTH 50
#define MAX_DATE_LENGTH 11
#define MAX_LINE_LENGTH 300

typedef struct Employee
{
    char date[MAX_DATE_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    int hours;
    struct Employee *next;
} Employee;

Employee *create_employee(const char *date, const char *last_name, const char *first_name, int hours);
void free_employee_list(Employee *head);
int compare_employees(const Employee *a, const Employee *b);
Employee *insert_sorted(Employee *head, Employee *new_emp);
int parse_employee_line(const char *line, char *date, char *last_name, char *first_name, int *hours);
void print_employees_over_hours(Employee *head, int min_hours);
Employee *get_employees_over_hours(Employee *head, int min_hours);

#endif