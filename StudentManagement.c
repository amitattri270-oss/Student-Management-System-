/*
 * Student Management System
 * Language: C (standard C)
 * Features: Add, display, search, update, and delete student records.
 *
 * Compile:
 *   gcc StudentManagement.c -o student_management
 * Run:
 *   ./student_management
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

typedef struct {
    int rollNumber;
    char name[NAME_LENGTH];
    int age;
    float marks;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void clearInputBuffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard extra input */
    }
}

int readInteger(const char *prompt) {
    int value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%d", &value);

        if (result == 1) {
            clearInputBuffer();
            return value;
        }

        printf("Please enter a valid whole number.\n");
        clearInputBuffer();
    }
}

float readMarks(const char *prompt) {
    float value;
    int result;

    while (1) {
        printf("%s", prompt);
        result = scanf("%f", &value);

        if (result == 1 && value >= 0.0f && value <= 100.0f) {
            clearInputBuffer();
            return value;
        }

        printf("Please enter marks between 0 and 100.\n");
        clearInputBuffer();
    }
}

void readName(char name[], int size) {
    printf("Enter student name: ");

    if (fgets(name, size, stdin) != NULL) {
        name[strcspn(name, "\n")] = '\0';
    } else {
        name[0] = '\0';
    }
}

int findStudentIndex(int rollNumber) {
    int i;

    for (i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            return i;
        }
    }

    return -1;
}

void addStudent(void) {
    Student newStudent;

    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent record limit reached.\n");
        return;
    }

    printf("\n--- Add Student ---\n");
    newStudent.rollNumber = readInteger("Enter roll number: ");

    if (findStudentIndex(newStudent.rollNumber) != -1) {
        printf("This roll number already exists.\n");
        return;
    }

    readName(newStudent.name, NAME_LENGTH);
    newStudent.age = readInteger("Enter age: ");
    newStudent.marks = readMarks("Enter marks (0-100): ");

    students[studentCount] = newStudent;
    studentCount++;

    printf("Student record added successfully!\n");
}

void displayStudents(void) {
    int i;

    printf("\n--- Student Records ---\n");

    if (studentCount == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("%-12s %-25s %-8s %-8s\n", "Roll No.", "Name", "Age", "Marks");
    printf("----------------------------------------------------------\n");

    for (i = 0; i < studentCount; i++) {
        printf("%-12d %-25s %-8d %-8.2f\n",
               students[i].rollNumber,
               students[i].name,
               students[i].age,
               students[i].marks);
    }
}

void searchStudent(void) {
    int rollNumber;
    int index;

    printf("\n--- Search Student ---\n");
    rollNumber = readInteger("Enter roll number to search: ");
    index = findStudentIndex(rollNumber);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("\nStudent found:\n");
    printf("Roll number: %d\n", students[index].rollNumber);
    printf("Name       : %s\n", students[index].name);
    printf("Age        : %d\n", students[index].age);
    printf("Marks      : %.2f\n", students[index].marks);
}

void updateStudent(void) {
    int rollNumber;
    int index;

    printf("\n--- Update Student ---\n");
    rollNumber = readInteger("Enter roll number to update: ");
    index = findStudentIndex(rollNumber);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter the updated details.\n");
    readName(students[index].name, NAME_LENGTH);
    students[index].age = readInteger("Enter new age: ");
    students[index].marks = readMarks("Enter new marks (0-100): ");

    printf("Student record updated successfully!\n");
}

void deleteStudent(void) {
    int rollNumber;
    int index;
    int i;

    printf("\n--- Delete Student ---\n");
    rollNumber = readInteger("Enter roll number to delete: ");
    index = findStudentIndex(rollNumber);

    if (index == -1) {
        printf("Student not found.\n");
        return;
    }

    for (i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    printf("Student record deleted successfully!\n");
}

int main(void) {
    int choice;

    do {
        printf("\n====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("====================================\n");

        choice = readInteger("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 0:
                printf("Thank you for using Student Management System!\n");
                break;
            default:
                printf("Invalid choice. Please select 0 to 5.\n");
        }
    } while (choice != 0);

    return 0;
}
