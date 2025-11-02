#include "employee.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Employee *create_employee(const char *date, const char *last_name,
                          const char *first_name, int hours)
{
    Employee *new_emp = (Employee *)malloc(sizeof(Employee));
    if (new_emp)
    {
        strcpy(new_emp->date, date);
        strcpy(new_emp->last_name, last_name);
        strcpy(new_emp->first_name, first_name);
        new_emp->hours = hours;
        new_emp->next = NULL;
    }
    return new_emp;
}

void free_employee_list(Employee *head)
{
    Employee *current = head;
    while (current != NULL)
    {
        Employee *next = current->next;
        free(current);
        current = next;
    }
}

int compare_employees(const Employee *a, const Employee *b)
{
    if (!a || !b)
        return 0;
    if (a->hours > b->hours)
        return -1;
    if (a->hours < b->hours)
        return 1;
    int last_name_cmp = strcmp(a->last_name, b->last_name);
    if (last_name_cmp != 0)
        return last_name_cmp;
    return strcmp(a->first_name, b->first_name);
}

Employee *insert_sorted(Employee *head, Employee *new_emp)
{
    if (!new_emp)
        return head;
    if (head == NULL || compare_employees(new_emp, head) < 0)
    {
        new_emp->next = head;
        return new_emp;
    }
    Employee *current = head;
    while (current->next != NULL &&
           compare_employees(new_emp, current->next) >= 0)
    {
        current = current->next;
    }
    new_emp->next = current->next;
    current->next = new_emp;
    return head;
}

int parse_employee_line(const char *line, char *date, char *last_name,
                        char *first_name, int *hours)
{
    return sscanf(line, "%s %s %s %d", date, last_name, first_name, hours) == 4;
}

Employee *get_employees_over_hours(Employee *head, int min_hours)
{
    Employee *result_head = NULL;
    Employee *result_tail = NULL;
    Employee *current = head;

    while (current != NULL)
    {
        if (current->hours > min_hours)
        {
            // Create a copy of the employee
            Employee *new_emp = create_employee(current->date, current->last_name,
                                                current->first_name, current->hours);
            if (new_emp)
            {
                if (result_head == NULL)
                {
                    result_head = new_emp;
                    result_tail = new_emp;
                }
                else
                {
                    result_tail->next = new_emp;
                    result_tail = new_emp;
                }
            }
        }
        current = current->next;
    }

    return result_head;
}

void print_employees_over_hours(Employee *head, int min_hours)
{
    Employee *filtered_list = get_employees_over_hours(head, min_hours);
    if (filtered_list)
    {
        printf("Employees who worked more than %d hours:\n", min_hours);
        Employee *current = filtered_list;
        int found = 0;
        while (current != NULL)
        {
            printf("%s: %s\n", current->last_name, current->date);
            found = 1;
            current = current->next;
        }
        free_employee_list(filtered_list);
    }
    else
    {
        printf("No employees worked more than %d hours\n", min_hours);
    }
}
