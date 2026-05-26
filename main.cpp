#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Structure to represent student data
struct Student {
    int rollNumber;
    char name[50];
    char course[50];
    float gpa;
};

// Function declarations
void addStudent();
void displayAllStudents();
void updateStudent();
void deleteStudent();
void mainMenu();

int main() {
    mainMenu();
    return 0;
}

void mainMenu() {
    int choice;
    do {
        cout << "\n======================================";
        cout << "\n      STUDENT MANAGEMENT SYSTEM       ";
        cout << "\n======================================";
        cout << "\n1. Add New Student Record";
        cout << "\n2. Display All Student Records";
        cout << "\n3. Update Student Record";
        cout << "\n4. Delete Student Record";
        cout << "\n5. Exit";
        cout << "\n======================================";
        cout << "\nEnter your choice (1-5): ";
        cin >> choice;

        // Clear input buffer to handle potential stream issues
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAllStudents(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: cout << "\nExiting system. Goodbye!\n"; break;
            default: cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 5);
}

void addStudent() {
    Student s;
    ofstream outFile("students.txt", ios::app | ios::binary);

    if (!outFile) {
        cout << "\nError opening file for writing!\n";
        return;
    }

    cout << "\n--- Add New Student ---";
    cout << "\nEnter Roll Number: ";
    cin >> s.rollNumber;
    cin.ignore(); // Clear newline character from buffer

    cout << "Enter Full Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Course/Branch: ";
    cin.getline(s.course, 50);

    cout << "Enter GPA: ";
    cin >> s.gpa;

    // Write the structure block to the file
    outFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
    outFile.close();

    cout << "\nRecord added successfully!\n";
}

void displayAllStudents() {
    Student s;
    ifstream inFile("students.txt", ios::binary);

    if (!inFile) {
        cout << "\nNo records found. Please add a record first.\n";
        return;
    }

    cout << "\n-----------------------------------------------------------------\n";
    cout << left << setw(12) << "Roll No" 
         << setw(25) << "Name" 
         << setw(15) << "Course" 
         << setw(8) << "GPA" << endl;
    cout << "-----------------------------------------------------------------\n";

    // Read record by record until End-Of-File
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        cout << left << setw(12) << s.rollNumber 
             << setw(25) << s.name 
             << setw(15) << s.course 
             << setw(8) << fixed << setprecision(2) << s.gpa << endl;
    }
    cout << "-----------------------------------------------------------------\n";
    inFile.close();
}

void updateStudent() {
    Student s;
    fstream file("students.txt", ios::in | ios::out | ios::binary);
    int targetRoll;
    bool found = false;

    if (!file) {
        cout << "\nError opening file or no records exist!\n";
        return;
    }

    cout << "\n--- Update Student Record ---";
    cout << "\nEnter the Roll Number to update: ";
    cin >> targetRoll;

    // Search and modify in-place using file stream positioning
    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNumber == targetRoll) {
            found = true;
            cout << "\nCurrent Record Details:\n";
            cout << "Name: " << s.name << " | Course: " << s.course << " | GPA: " << s.gpa << endl;

            cin.ignore();
            cout << "\nEnter New Name: ";
            cin.getline(s.name, 50);
            cout << "Enter New Course: ";
            cin.getline(s.course, 50);
            cout << "Enter New GPA: ";
            cin >> s.gpa;

            // Move the put pointer back by one record size to overwrite
            int pos = -1 * static_cast<int>(sizeof(Student));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));
            
            cout << "\nRecord updated successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nRecord with Roll Number " << targetRoll << " not found.\n";
    }
    file.close();
}

void deleteStudent() {
    Student s;
    ifstream inFile("students.txt", ios::binary);
    int targetRoll;
    bool found = false;

    if (!inFile) {
        cout << "\nError opening file or no records exist!\n";
        return;
    }

    cout << "\n--- Delete Student Record ---";
    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    // Create a temporary file to copy all records except the deleted one
    ofstream tempFile("temp.txt", ios::binary);

    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.rollNumber == targetRoll) {
            found = true; // Skip writing this record to temp file
        } else {
            tempFile.write(reinterpret_cast<char*>(&s), sizeof(Student));
        }
    }

    inFile.close();
    tempFile.close();

    // Replace old file with updated temp file
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found) {
        cout << "\nRecord deleted successfully!\n";
    } else {
        cout << "\nRecord with Roll Number " << targetRoll << " not found.\n";
    }
}
