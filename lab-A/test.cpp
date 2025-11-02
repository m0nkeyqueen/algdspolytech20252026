#include <gtest/gtest.h>
#include <cstring>
#include "employee.h"

TEST(EmployeeTest, CreateEmployee_NormalValues_ValidCreation_no1)
{
    Employee *emp = create_employee("2024-01-15", "Ivanov", "Ivan", 40);

    ASSERT_NE(emp, nullptr);
    EXPECT_STREQ(emp->date, "2024-01-15");
    EXPECT_STREQ(emp->last_name, "Ivanov");
    EXPECT_STREQ(emp->first_name, "Ivan");
    EXPECT_EQ(emp->hours, 40);
    EXPECT_EQ(emp->next, nullptr);
    free_employee_list(emp);
}

TEST(EmployeeTest, CompareEmployees_DifferentHours_HigherHoursFirst_no2)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-16", "Petrov", "Petr", 35, nullptr};

    int result = compare_employees(&emp1, &emp2);
    EXPECT_LT(result, 0);
}

TEST(EmployeeTest, CompareEmployees_SameHoursDifferentLastNames_AlphabeticalOrder_no3)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-16", "Petrov", "Ivan", 40, nullptr};

    int result = compare_employees(&emp1, &emp2);
    EXPECT_LT(result, 0);
}

TEST(EmployeeTest, CompareEmployees_SameHoursSameLastNamesDifferentFirstNames_AlphabeticalOrder_no4)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Alexey", 40, nullptr};
    Employee emp2 = {"2024-01-16", "Ivanov", "Ivan", 40, nullptr};

    int result = compare_employees(&emp1, &emp2);
    EXPECT_LT(result, 0);
}

TEST(EmployeeTest, CompareEmployees_IdenticalEmployees_ReturnZero_no5)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};

    int result = compare_employees(&emp1, &emp2);
    EXPECT_EQ(result, 0);
}

TEST(EmployeeTest, InsertSorted_EmptyList_NewEmployeeBecomesHead_no6)
{
    Employee *head = nullptr;
    Employee new_emp = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};

    head = insert_sorted(head, &new_emp);

    EXPECT_EQ(head, &new_emp);
    EXPECT_EQ(head->hours, 40);
    EXPECT_EQ(head->next, nullptr);
    free_employee_list(head);
}

TEST(EmployeeTest, InsertSorted_HigherHours_InsertAtBeginning_no7)
{
    Employee existing_emp = {"2024-01-16", "Petrov", "Petr", 35, nullptr};
    Employee new_emp = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee *head = &existing_emp;

    head = insert_sorted(head, &new_emp);

    EXPECT_EQ(head, &new_emp);
    EXPECT_EQ(head->hours, 40);
    EXPECT_EQ(head->next, &existing_emp);
    free_employee_list(head);
}

TEST(EmployeeTest, InsertSorted_LowerHours_InsertAtEnd_no8)
{
    Employee existing_emp = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee new_emp = {"2024-01-16", "Petrov", "Petr", 35, nullptr};
    Employee *head = &existing_emp;

    head = insert_sorted(head, &new_emp);

    EXPECT_EQ(head, &existing_emp);
    EXPECT_EQ(head->hours, 40);
    EXPECT_EQ(head->next, &new_emp);
    EXPECT_EQ(head->next->hours, 35);
    EXPECT_EQ(head->next->next, nullptr);
    free_employee_list(head);
}

TEST(EmployeeTest, InsertSorted_MiddlePosition_CorrectOrder_no9)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-17", "Sidorov", "Alexey", 30, nullptr};
    Employee new_emp = {"2024-01-16", "Petrov", "Petr", 35, nullptr};

    Employee *head = &emp1;
    emp1.next = &emp2;

    head = insert_sorted(head, &new_emp);

    EXPECT_EQ(head, &emp1);
    EXPECT_EQ(head->hours, 40);
    EXPECT_EQ(head->next, &new_emp);
    EXPECT_EQ(head->next->hours, 35);
    EXPECT_EQ(head->next->next, &emp2);
    EXPECT_EQ(head->next->next->hours, 30);
    free_employee_list(head);
}

TEST(EmployeeTest, ParseEmployeeLine_ValidLineFourFields_ReturnTrue_no10)
{
    char date[MAX_DATE_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    int hours;

    const char *valid_line = "2024-01-15 Ivanov Ivan 40";
    int result = parse_employee_line(valid_line, date, last_name, first_name, &hours);

    EXPECT_TRUE(result);
    EXPECT_STREQ(date, "2024-01-15");
    EXPECT_STREQ(last_name, "Ivanov");
    EXPECT_STREQ(first_name, "Ivan");
    EXPECT_EQ(hours, 40);
}

TEST(EmployeeTest, ParseEmployeeLine_ThreeFields_ReturnFalse_no11)
{
    char date[MAX_DATE_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char first_name[MAX_NAME_LENGTH];
    int hours;

    const char *invalid_line = "2024-01-15 Ivanov 40";
    int result = parse_employee_line(invalid_line, date, last_name, first_name, &hours);

    EXPECT_FALSE(result);
}

TEST(EmployeeTest, GetEmployeesOverHours_OverThreshold_ReturnNull_no12)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee *result = get_employees_over_hours(&emp1, 40);
    EXPECT_EQ(result, nullptr);
    free_employee_list(result);
}

TEST(EmployeeTest, GetEmployeesOverHours_UnderThreshold_ReturnNull_no13)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee *result = get_employees_over_hours(&emp1, 40);
    EXPECT_EQ(result, nullptr);
    free_employee_list(result);
}

TEST(EmployeeTest, GetEmployeesOverHours_ExactThreshold_ReturnNull_no14)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee *result = get_employees_over_hours(&emp1, 40);
    EXPECT_EQ(result, nullptr);
    free_employee_list(result);
}

TEST(EmployeeTest, GetEmployeesOverHours_EmptyList_ReturnNull_no15)
{
    Employee *result = get_employees_over_hours(nullptr, 10);
    EXPECT_EQ(result, nullptr);
}

TEST(EmployeeTest, GetEmployeesOverHours_BothMatch_ReturnFilteredList_16)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-16", "Petrov", "Petr", 35, nullptr};

    emp1.next = &emp2;

    Employee *result = get_employees_over_hours(&emp1, 30);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->hours, 40);
    EXPECT_STREQ(result->last_name, "Ivanov");
    EXPECT_NE(result->next, nullptr);
    EXPECT_EQ(result->next->hours, 35);
    EXPECT_STREQ(result->next->last_name, "Petrov");
    EXPECT_EQ(result->next->next, nullptr);
    free_employee_list(result);
}

TEST(EmployeeTest, GetEmployeesOverHours_OneMatch_ReturnFilteredList_17)
{
    Employee emp1 = {"2024-01-15", "Ivanov", "Ivan", 40, nullptr};
    Employee emp2 = {"2024-01-16", "Petrov", "Petr", 35, nullptr};

    emp1.next = &emp2;

    Employee *result = get_employees_over_hours(&emp1, 38);

    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->hours, 40);
    EXPECT_STREQ(result->last_name, "Ivanov");
    EXPECT_EQ(result->next, nullptr);
    free_employee_list(result);
}
