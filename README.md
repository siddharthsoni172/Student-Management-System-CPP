# Student Management System

A console-based Student Management System developed in C++ that efficiently manages student records using file handling and menu-driven operations. This project was developed as part of an internship to demonstrate core programming, data persistence, and CRUD workflow concepts.

## 🚀 Key Features
*   **Add Student Records:** Dynamically register a student's Roll Number, Name, Course, and GPA.
*   **Display All Records:** View all saved student details in a clean, formatted tabular layout.
*   **Update Student Info:** Search for a specific student by Roll Number and modify their details in real time.
*   **Delete Student Data:** Remove unwanted student profiles safely using stream manipulation.
*   **Persistent Data Storage:** Uses C++ binary file handling (`fstream`) to store data locally in a text file, ensuring data remains safe even after closing the program.
*   **Interactive Menu Interface:** A robust, command-line menu with built-in input validation to prevent crashes from accidental entries.

## 🛠️ Technical Stack
*   **Language:** C++
*   **File Handling:** `ifstream`, `ofstream`, and `fstream` (Binary I/O)
*   **Formatting:** `iomanip` (`setw`, `setprecision`) for clean console outputs

## 📂 Project Structure
*   `main.cpp` - Contains the entire source code and application logic.
*   `students.txt` - The local database file generated automatically at runtime to save records.
