# Student Record System (C Project)

A complete file-based **Student Record Management System** written in C.  
This project allows users to store, update, search, and manage student academic records using a simple menu-driven interface.

---

## 📌 Features

### ➤ **Add Student Record**
- Enter name, roll number, marks, and other details  
- Saves automatically to file

### ➤ **Display All Records**
- Shows the list of all saved student data  
- Proper formatted table output

### ➤ **Search Student**
- Search using roll number  
- Search using partial name  

### ➤ **Update Student Record**
- Modify existing student details  
- Updates the file without losing other data

### ➤ **Delete Student**
- Removes a student's record safely  
- Rewrites file after deletion

### ➤ **Sorting**
- Sort records by marks or name  
- Display sorted results

### ➤ **Count Students**
- Shows the total number of records stored

### ➤ **Topper Details**
- Automatically identifies and displays the topper

---

## 🗂 File Information
- **Language:** C  
- **Lines of Code:** ~348 (approx)  
- **File Handling:** Uses `fopen()`, `fread()`, `fwrite()`  
- **Data Structure:** Struct-based student record

---

## ▶️ How to Compile & Run

### **Compile**
```bash
gcc student_record_system.c -o student_record_system.exe
