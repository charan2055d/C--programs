#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>


#define YES "FREE"
#define NO  "BOOKED"

#define MAX_ROOMS 15
#define MAX_BOOKINGS 50

struct Room {
    int roomNumber;
    char type[20];
    float pricePerDay;
    int isBooked; 
};

struct Customer {
    char name[50];
    char phone[15];
    int roomnumber;
    int daysStayed;
    float totalBill;
    char paymentMethod[10]; // Cash/Card/Online
};

struct Booking {
    struct Customer cust;
    struct Room room;
};

int findRoomIndex(struct Room rooms[], int roomNo) {
    for(int i = 0; i < MAX_ROOMS; i++) {
        if(rooms[i].roomNumber == roomNo) return i;
    }
    return -1;
}

int findBookingIndex(struct Booking bookings[], int bookingCount, int roomNo) {
    for(int i = 0; i < bookingCount; i++) {
        if(bookings[i].room.roomNumber == roomNo) return i;
    }
    return -1;
}

int login() {
    char user[20], pass[20];
    printf("Enter username: ");
    scanf("%19s", user);
    printf("Enter password: ");
    scanf("%19s", pass);

    if(strcmp(user, "admin") == 0 && strcmp(pass, "1234") == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Login failed!\n");
        return 0;
    }
}

void initializeRooms(struct Room rooms[]) {
    int floors[3] = {5, 5, 5};
    int index = 0;

    for(int k = 0; k < 3; k++) {
        for(int i = 0; i < floors[k]; i++) {
            rooms[index].roomNumber = (k+1)*100 + (i+1);
            rooms[index].isBooked = 0;

            if(i == 0 || i == 1) {
                strcpy(rooms[index].type, "SINGLE");
                rooms[index].pricePerDay = 2500;
            } else if(i == 2 || i == 3) {
                strcpy(rooms[index].type, "DOUBLE");
                rooms[index].pricePerDay = 4000;
            } else {
                strcpy(rooms[index].type, "SUITE");
                rooms[index].pricePerDay = 6500;
            }
            index++;
        }
    }
}

void showRooms(struct Room rooms[]){
    for(int i = 0; i < MAX_ROOMS; i++){
        printf("\nROOM NUMBER  : %d\n", rooms[i].roomNumber);
        printf("ROOM TYPE    : %s\n", rooms[i].type);
        printf("ROOM PRICE   : %.2f\n", rooms[i].pricePerDay);
        printf("AVAILABILITY : %s\n", rooms[i].isBooked ? NO : YES);
    }
}

float applyDiscount(float bill, int daysStayed) {
    if(daysStayed >= 7) {
        printf("Applied 10%% discount for long stay!\n");
        bill *= 0.90f;
    }
    return bill;
}

void choosePaymentMethod(struct Customer *cust) {
    int choice;
    printf("Select Payment Method:\n1. Cash\n2. Card\n3. Online\nChoice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: strcpy(cust->paymentMethod, "Cash"); break;
        case 2: strcpy(cust->paymentMethod, "Card"); break;
        case 3: strcpy(cust->paymentMethod, "Online"); break;
        default: printf("Invalid choice, defaulting to Cash.\n");
                 strcpy(cust->paymentMethod, "Cash");
    }
}

void printBill(struct Customer cust, struct Room room) {
    printf("\n--- BILL RECEIPT ---\n");
    printf("Customer Name : %s\n", cust.name);
    printf("Phone Number  : %s\n", cust.phone);
    printf("Room Number   : %d\n", room.roomNumber);
    printf("Room Type     : %s\n", room.type);
    printf("Days Stayed   : %d\n", cust.daysStayed);
    printf("Price/Day     : %.2f\n", room.pricePerDay);
    printf("Payment Method: %s\n", cust.paymentMethod);
    printf("Total Bill    : %.2f\n", cust.totalBill);
    printf("---------------------\n");
}

void saveBookingsToFile(struct Booking bookings[], int bookingCount) {
    static int firstTime = 1; 
    FILE *fp;

    if(firstTime) {
        fp = fopen("bookings.txt", "w"); 
        firstTime = 0;                    
    } else {
        fp = fopen("bookings.txt", "a");  
    }

    if(fp == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }

    for(int i = 0; i < bookingCount; i++) {
        fprintf(fp,
                "Name: %s | Phone: %s | RoomNo: %d | Days: %d | Bill: %.2f | Payment: %s | RoomType: %s | Price/Day: %.2f\n",
                bookings[i].cust.name,
                bookings[i].cust.phone,
                bookings[i].cust.roomnumber,
                bookings[i].cust.daysStayed,
                bookings[i].cust.totalBill,
                bookings[i].cust.paymentMethod,
                bookings[i].room.type,
                bookings[i].room.pricePerDay);
    }

    fclose(fp);
    printf("Bookings saved to file successfully!\n");
}

int loadBookingsFromFile(struct Booking bookings[], struct Room rooms[]) {
    FILE *fp = fopen("bookings.txt", "r");
    if(fp == NULL) {
        return 0; 
    }

    int count = 0;
    while(count < MAX_BOOKINGS &&
          fscanf(fp, "NAME : %49s | PHONE NUMBER : %14s | ROOMNUMBER : %d | DAYS STAYED : %d | TOTAL BILL : %f | PAYMENT METHOD : %9s | ROOM NUMBER : %d | TYPE : %19s | PRICE PER DAY : %f",
                 bookings[count].cust.name,
                 bookings[count].cust.phone,
                 &bookings[count].cust.roomnumber,
                 &bookings[count].cust.daysStayed,
                 &bookings[count].cust.totalBill,
                 bookings[count].cust.paymentMethod,
                 &bookings[count].room.roomNumber,
                 bookings[count].room.type,
                 &bookings[count].room.pricePerDay) == 9) {

        
        int rIdx = findRoomIndex(rooms, bookings[count].room.roomNumber);
        if(rIdx != -1) {
            rooms[rIdx].isBooked = 1;
            strcpy(bookings[count].room.type, rooms[rIdx].type);
            bookings[count].room.pricePerDay = rooms[rIdx].pricePerDay;
        }
        count++;
    }

    fclose(fp);
    return count;
}

void openBookingsFile() {
    FILE *fp = fopen("bookings.txt", "r");
    if(fp == NULL) {
        printf("No bookings file found!\n");
        return;
    }

    char line[256];
    printf("\n--- BOOKINGS FILE CONTENT ---\n");
    while(fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    printf("-----------------------------\n");

    fclose(fp);
}



void bookRoom(struct Room rooms[], struct Booking bookings[], int *bookingCount) {
    if(*bookingCount >= MAX_BOOKINGS) {
        printf("Booking capacity full!\n");
        return;
    }

    int roomNo;
    printf("Enter room number to book: ");
    scanf("%d", &roomNo);

    int rIdx = findRoomIndex(rooms, roomNo);
    if(rIdx == -1) {
        printf("Room not found!\n");
        return;
    }
    if(rooms[rIdx].isBooked) {
        printf("Sorry, Room %d is already booked.\n", roomNo);
        return;
    }

    struct Customer cust;
    printf("Enter customer name: ");
    scanf("%49s", cust.name);
    printf("Enter phone number: ");
    scanf("%14s", cust.phone);
    printf("Enter number of days stayed: ");
    scanf("%d", &cust.daysStayed);

    cust.roomnumber = roomNo;
    cust.totalBill = cust.daysStayed * rooms[rIdx].pricePerDay;
    cust.totalBill = applyDiscount(cust.totalBill, cust.daysStayed);
    choosePaymentMethod(&cust);

    rooms[rIdx].isBooked = 1;

    bookings[*bookingCount].cust = cust;
    bookings[*bookingCount].room = rooms[rIdx];
    (*bookingCount)++;

    printf("Room %d booked successfully for %s!\n", roomNo, cust.name);
    printBill(cust, rooms[rIdx]);
}

void cancelBooking(struct Room rooms[], struct Booking bookings[], int *bookingCount) {
    int roomNo;
    printf("Enter room number to cancel booking: ");
    scanf("%d", &roomNo);

    int bIdx = findBookingIndex(bookings, *bookingCount, roomNo);
    if(bIdx == -1) {
        printf("No booking found for Room %d.\n", roomNo);
        return;
    }

    int rIdx = findRoomIndex(rooms, roomNo);
    if(rIdx != -1) rooms[rIdx].isBooked = 0;

    for(int j = bIdx; j < *bookingCount - 1; j++) {
        bookings[j] = bookings[j+1];
    }
    (*bookingCount)--;

    printf("Booking for Room %d cancelled successfully!\n", roomNo);
}

void searchRoomByType(struct Room rooms[], char type[]) {
    int found = 0;
    for(int i = 0; i < MAX_ROOMS; i++) {
        if(strcmp(rooms[i].type, type) == 0 && !rooms[i].isBooked) {
            printf("Room %d (%s) is available at %.2f per day.\n",
                   rooms[i].roomNumber, rooms[i].type, rooms[i].pricePerDay);
            found = 1;
        }
    }
    if(!found) {
        printf("No available %s rooms.\n", type);
    }
}

void showBookings(struct Booking bookings[], int bookingCount) {
    if(bookingCount == 0) {
        printf("No bookings yet.\n");
        return;
    }
    for(int i = 0; i < bookingCount; i++) {
        printf("\nCustomer: %s\nPhone: %s\nRoom: %d (%s)\nDays: %d\nPayment: %s\nBill: %.2f\n",
               bookings[i].cust.name,
               bookings[i].cust.phone,
               bookings[i].room.roomNumber,
               bookings[i].room.type,
               bookings[i].cust.daysStayed,
               bookings[i].cust.paymentMethod,
               bookings[i].cust.totalBill);
    }
}

void searchCustomer(struct Booking bookings[], int bookingCount) {
    int mode;
    printf("Search by: 1) Name  2) Phone : ");
    scanf("%d", &mode);

    int found = 0;
    if(mode == 1) {
        char name[50];
        printf("Enter customer name: ");
        scanf("%49s", name);
        for(int i = 0; i < bookingCount; i++) {
            if(strcmp(bookings[i].cust.name, name) == 0) {
                printf("\nCustomer: %s\nPhone: %s\nRoom: %d (%s)\nDays: %d\nPayment: %s\nBill: %.2f\n",
                       bookings[i].cust.name,
                       bookings[i].cust.phone,
                       bookings[i].room.roomNumber,
                       bookings[i].room.type,
                       bookings[i].cust.daysStayed,
                       bookings[i].cust.paymentMethod,
                       bookings[i].cust.totalBill);
                found = 1;
            }
        }
    } else if(mode == 2) {
        char phone[15];
        printf("Enter phone number: ");
        scanf("%14s", phone);
        for(int i = 0; i < bookingCount; i++) {
            if(strcmp(bookings[i].cust.phone, phone) == 0) {
                printf("\nCustomer: %s\nPhone: %s\nRoom: %d (%s)\nDays: %d\nPayment: %s\nBill: %.2f\n",
                       bookings[i].cust.name,
                       bookings[i].cust.phone,
                       bookings[i].room.roomNumber,
                       bookings[i].room.type,
                       bookings[i].cust.daysStayed,
                       bookings[i].cust.paymentMethod,
                       bookings[i].cust.totalBill);
                found = 1;
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if(!found) {
        printf("No matching customer found.\n");
    }
}

void addExtraCharges(struct Booking bookings[], int bookingCount) {
    int roomNo;
    float extra;
    printf("Enter room number: ");
    scanf("%d", &roomNo);
    printf("Enter extra charges: ");
    scanf("%f", &extra);

    int bIdx = findBookingIndex(bookings, bookingCount, roomNo);
    if(bIdx == -1) {
        printf("No booking found for Room %d.\n", roomNo);
        return;
    }

    bookings[bIdx].cust.totalBill += extra;
    printf("Extra charges added! New Bill: %.2f\n", bookings[bIdx].cust.totalBill);
}

void checkout(struct Room rooms[], struct Booking bookings[], int *bookingCount) {
    int roomNo;
    printf("Enter room number to checkout: ");
    scanf("%d", &roomNo);

    int bIdx = findBookingIndex(bookings, *bookingCount, roomNo);
    if(bIdx == -1) {
        printf("No booking found for Room %d.\n", roomNo);
        return;
    }

    printBill(bookings[bIdx].cust, bookings[bIdx].room);

    int rIdx = findRoomIndex(rooms, roomNo);
    if(rIdx != -1) rooms[rIdx].isBooked = 0;

    for(int j = bIdx; j < *bookingCount - 1; j++) {
        bookings[j] = bookings[j+1];
    }
    (*bookingCount)--;

    printf("Room %d checked out successfully!\n", roomNo);
}


void roomServiceMenu(struct Booking bookings[], int bookingCount) {
    int roomNo;
    printf("Enter room number for room service: ");
    scanf("%d", &roomNo);

    int bIdx = findBookingIndex(bookings, bookingCount, roomNo);
    if(bIdx == -1) {
        printf("No booking found for Room %d.\n", roomNo);
        return;
    }

    int choice;
    printf("\n--- ROOM SERVICE MENU ---\n");
    printf("1. Breakfast - 500\n");
    printf("2. Lunch     - 800\n");
    printf("3. Dinner    - 1000\n");
    printf("4. Laundry   - 300\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    float charge = 0;
    switch(choice) {
        case 1: charge = 500; break;
        case 2: charge = 800; break;
        case 3: charge = 1000; break;
        case 4: charge = 300; break;
        default: printf("Invalid choice!\n"); return;
    }

    bookings[bIdx].cust.totalBill += charge;
    printf("Service added! New Bill: %.2f\n", bookings[bIdx].cust.totalBill);
}


int main() {
    struct Room rooms[MAX_ROOMS];
    struct Booking bookings[MAX_BOOKINGS];
    int bookingCount = 0;
    int choice;

    if(!login()) return 0;

    initializeRooms(rooms);
    bookingCount = loadBookingsFromFile(bookings, rooms);

    do {
        printf("\n--- HOTEL MANAGEMENT SYSTEM ---\n");
        printf("1. Show Rooms\n");
        printf("2. Book Room\n");
        printf("3. Cancel Booking\n");
        printf("4. Search Room by Type\n");
        printf("5. Show All Bookings\n");
        printf("6. Save Bookings to File\n");
        printf("7. Open Bookings File\n");
        printf("8. Search Customer (Name/Phone)\n");
        printf("9. Add Extra Charges (Room Service)\n");
        printf("10. Checkout (Final Bill & Release)\n");
        printf("11. Room Service Menu\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        if(scanf("%d", &choice) != 1) { 
            printf("Invalid input. Exiting.\n");
            break;
        }

        switch(choice) {
            case 1: showRooms(rooms); break;
            case 2: bookRoom(rooms, bookings, &bookingCount); break;
            case 3: cancelBooking(rooms, bookings, &bookingCount); break;
            case 4: {
                char type[20];
                printf("Enter room type (SINGLE/DOUBLE/SUITE): ");
                scanf("%19s", type);
                searchRoomByType(rooms, type);
                break;
            }
            case 5: showBookings(bookings, bookingCount); break;
            case 6: saveBookingsToFile(bookings, bookingCount); break;
            case 7: openBookingsFile(); break;
            case 8: searchCustomer(bookings, bookingCount); break;
            case 9: addExtraCharges(bookings, bookingCount); break;
            case 10: checkout(rooms, bookings, &bookingCount); break;
            case 11: roomServiceMenu(bookings, bookingCount); break;
            case 12:
                saveBookingsToFile(bookings, bookingCount); 
                printf("Exiting...\n");
                break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 12);

    return 0;
}