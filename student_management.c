#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;

    while (1) {
        printf("\n==== Student Management System ====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Update Student\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("File error\n");
        return;
    }

    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully\n");
}

void viewStudents() {
    FILE *fp;
    struct Student s;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found\n");
        return;
    }

    printf("\n--- Student Records ---\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Age: %d\n", s.age);
        printf("Marks: %.2f\n", s.marks);
        printf("----------------------\n");
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Student found\n");
            printf("Name: %s\n", s.name);
            printf("Age: %d\n", s.age);
            printf("Marks: %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int id, found = 0;

    fp = fopen(FILE_NAME, "rb");
    temp = fopen("temp.dat", "wb");

    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Student deleted\n");
    else
        printf("Student not found\n");
}

void updateStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    fp = fopen(FILE_NAME, "rb+");

    if (fp == NULL) {
        printf("File not found\n");
        return;
    }

    printf("Enter ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new age: ");
            scanf("%d", &s.age);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record updated\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found\n");

    fclose(fp);
}
