#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "employee.h"

int main(void)
{
    Employee *head = NULL;
    FILE *file = fopen("employees.txt", "r");
    if (!file)
    {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char date[MAX_DATE_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    int hours;

    while (fgets(line, sizeof(line), file))
    {
        if (parse_employee_line(line, date, last_name, first_name, &hours))
        {
            Employee *new_emp = create_employee(date, last_name, first_name, hours);
            if (new_emp)
            {
                head = insert_sorted(head, new_emp);
            }
        }
    }
    fclose(file);

    int count = 0;
    Employee *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    printf("Read %d records\n\n", count);
    int min_hours;
    printf("Enter minimum hours: ");
    scanf("%d", &min_hours);
    print_employees_over_hours(head, min_hours);

    free_employee_list(head);
    return 0;
}
