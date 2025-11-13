#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWORD "charan2055"

int login() {
    char input[50];
    int attempts = 3;

    while (attempts > 0) {
        printf("Enter password to access the system (%d attempts left): ", attempts);
        scanf("%s", input);

        if (strcmp(input, PASSWORD) == 0) {
            printf("Access granted ✅\n");
            return 1;
        } else {
            printf("Incorrect password ❌\n");
            attempts--;
        }
    }

    printf("\nToo many failed attempts. Access denied.\n");
    return 0;
}

typedef struct STUDENT {
    int id;
    char name[50];
    float marks;
} S;

void addRecord();
void displayRecords();
void searchRecord();
void deleteRecord();
void updateRecord();
void sortRecordsByMarks();
void displayTopperRecord();
void countRecords();
void searchByPartialName();

int main() {
    if (!login()) {
        return 0;
    }

    int choice;
    char confirm;

    do {
        printf("\n----STUDENT RECORD SYSTEM----\n");
        printf("1. ADD RECORD\n");
        printf("2. DISPLAY RECORDS\n");
        printf("3. SEARCH RECORD\n");
        printf("4. DELETE RECORD\n");
        printf("5. UPDATE RECORD\n");
        printf("6. SORT RECORDS BY MARKS\n");
        printf("7. DISPLAY TOPPER RECORD\n");
        printf("8. COUNT TOTAL RECORDS\n");
        printf("9. SEARCH BY PARTIAL NAME\n");
        printf("10. EXIT\n");

        printf("ENTER YOUR CHOICE: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: deleteRecord(); break;
            case 5: updateRecord(); break;
            case 6: sortRecordsByMarks(); break;
            case 7: displayTopperRecord(); break;
            case 8: countRecords(); break;
            case 9: searchByPartialName(); break;
            case 10: exit(0);
            default: printf("\nINVALID CHOICE !!\n");
        }

        printf("\nDo you want to continue? (y/n): ");
        scanf(" %c", &confirm);

    } while (confirm == 'y' || confirm == 'Y');

    printf("\nThank you for using the Student Record System!\n");
    return 0;
}

void addRecord() {
    FILE *fp = fopen("student.txt", "ab+");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    printf("\nEnter ID, NAME, MARKS: ");
    scanf("%d %s %f", &s.id, s.name, &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Record added successfully.\n");
}

void displayRecords() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    printf("\n---ALL STUDENT RECORDS---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("ID: %d\nName: %s\nMarks: %.2f\n------------------\n",
               s.id, s.name, s.marks);
    }
    fclose(fp);
}

void searchRecord() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    int id, found = 0;
    printf("\nEnter the ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\n<- RECORD FOUND ->\n");
            printf("ID: %d\nName: %s\nMarks: %.2f\n", s.id, s.name, s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRECORD NOT FOUND\n");

    fclose(fp);
}

void deleteRecord() {
    FILE *fp = fopen("student.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    int id;
    printf("\nEnter the ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        printf("\nRECORD DELETED SUCCESSFULLY\n");
    else
        printf("\nRECORD NOT FOUND\n");
}

void updateRecord() {
    FILE *fp = fopen("student.txt", "rb");
    FILE *temp = fopen("temp.txt", "wb");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    int id, found = 0;
    printf("\nENTER ID TO UPDATE : ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            printf("\n<- RECORD FOUND ->\n");
            printf("Current Name: %s\nCurrent Marks: %.2f\n", s.name, s.marks);

            printf("Enter new Name: ");
            scanf("%s", s.name);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt", "student.txt");

    if (found)
        printf("\nRECORD UPDATED SUCCESSFULLY\n");
    else
        printf("\nRECORD NOT FOUND\n");
}

void sortRecordsByMarks() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s[100];
    int count = 0;

    while (fread(&s[count], sizeof(S), 1, fp)) {
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("\nNo records to sort.\n");
        return;
    }

    int order;
    printf("\nChoose sorting order:\n1. Ascending\n2. Descending\nEnter choice: ");
    scanf("%d", &order);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int shouldSwap = 0;
            if (order == 1 && s[j].marks > s[j + 1].marks)
                shouldSwap = 1;
            else if (order == 2 && s[j].marks < s[j + 1].marks)
                shouldSwap = 1;

            if (shouldSwap) {
                S temp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }

    printf("\n---SORTED RECORDS---\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nName: %s\nMarks: %.2f\n------------------\n",
               s[i].id, s[i].name, s[i].marks);
    }
}

void displayTopperRecord() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s, topper;
    int found = 0;
    float highest = -1.0;

    while (fread(&s, sizeof(s), 1, fp)) {
        if (!found || s.marks > highest) {
            highest = s.marks;
            topper = s;
            found = 1;
        }
    }
    fclose(fp);

    if (!found) {
        printf("\nNO RECORD FOUND\n");
        return;
    }

    printf("\n---TOPPER DETAILS---\n");
    printf("ID: %d\nName: %s\nMarks: %.2f\n", topper.id, topper.name, topper.marks);
}

void searchByPartialName() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    char keyword[50];
    int found = 0;

    printf("\nEnter part of the name to search: ");
    scanf("%s", keyword);

    printf("\n---MATCHING RECORDS---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        if (strstr(s.name, keyword) != NULL) {
            printf("ID: %d\nName: %s\nMarks: %.2f\n------------------\n",
                   s.id, s.name, s.marks);
            found = 1;
        }
    }

    if (!found)
        printf("No matching records found.\n");

    fclose(fp);
}

void countRecords() {
    FILE *fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    S s;
    int count = 0;

    while (fread(&s, sizeof(s), 1, fp)) {
        count++;
    }

    fclose(fp);

    if (count == 0)
        printf("\nNO RECORDS FOUND\n");
    else
        printf("\nTOTAL STUDENT RECORDS: %d\n", count);
}
