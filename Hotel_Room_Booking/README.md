# Hotel Management System (C Project)

A menu-driven **Hotel Management System** built in C that allows hotel staff to manage room bookings, customer details, payments, room service, and more.  
The project uses file handling to store and retrieve booking records.

---

## 🔐 Login System
The program includes a simple login:

- **Default Username:** admin  
- **Default Password:** 1234  

Only authenticated users can access the hotel management menu.

---

## 📌 Features (Based on Program Menu)

### 1️⃣ **Show Rooms**
- Displays all available rooms  
- Shows room numbers, types (Single/Double/Deluxe), and status (Available/Booked)

### 2️⃣ **Book Room**
- Add a new customer  
- Select room type  
- Automatically assigns an empty room  
- Stores customer details in memory

### 3️⃣ **Cancel Booking**
- Remove booking using room number  
- Frees up the room for future customers

### 4️⃣ **Search Room by Type**
- Check availability for a specific room type  
- Useful for quick room lookup

### 5️⃣ **Show All Bookings**
- Displays full customer list  
- Shows name, phone, room number, room type, bill, etc.

### 6️⃣ **Save Bookings to File**
- Saves all current bookings to a text or binary file  
- Prevents data loss after program exit

### 7️⃣ **Open Bookings File**
- Loads previously saved customer data from file  
- Restores previous hotel state

### 8️⃣ **Search Customer (Name/Phone)**
- Search records by:  
  - Customer name  
  - Phone number  
- Helps quickly find customer stay details

### 9️⃣ **Add Extra Charges (Room Service)**  
- Add room service expenses  
- Adds charges to the final bill  
- Stores extra bill details

### 🔟 **Checkout (Final Bill & Release Room)**
- Calculates bill based on:
  - Room type  
  - Stay duration  
  - Extra charges  
- Displays final bill  
- Releases room after checkout

### 1️⃣1️⃣ **Room Service Menu**
- Extra services like:
  - Food orders  
  - Laundry  
  - Housekeeping  
- Charges added to customer bill

### 1️⃣2️⃣ **Exit**
- Ends the program safely

---

## 🗂 Technical Details

- **Language:** C  
- **Concepts Used:**  
  - File Handling (save/load bookings)  
  - Structures (`struct`)  
  - String manipulation  
  - Menu-driven programming  
  - Authentication system  
- **Storage:** File-based (text/binary)

---

## ▶️ How to Compile & Run

### **Compile**
```bash
gcc hotel_management.c -o hotel_management.exe
