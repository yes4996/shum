#include <iostream>
#include <string>
using namespace std;

const int MAX_EMPLOYEES = 100;

// Employee structure – stored in an array
struct Employee {
    int id;
    string name;
    string position;
    double dailyWage;
};

// Attendance record node – stored in a linked list
struct AttendanceNode {
    int employeeID;
    int day;            // For simplicity, an integer to represent the day.
    bool present;
    AttendanceNode* next;
};

// ========== Employee Array Operations ==========

// Add a new employee to the array
void addEmployee(Employee employees[], int &count) {
    if (count >= MAX_EMPLOYEES) {
        cout << "Employee list is full." << endl;
        return;
    }
    
    Employee emp;
    cout << "Enter employee ID: ";
    cin >> emp.id;
    cin.ignore(); // flush newline character

    cout << "Enter employee name: ";
    getline(cin, emp.name);

    cout << "Enter employee position: ";
    getline(cin, emp.position);

    cout << "Enter employee daily wage: ";
    cin >> emp.dailyWage;
    
    employees[count++] = emp;
    cout << "Employee added successfully." << endl;
}

// Search for an employee by ID; returns the index or -1 if not found.
int searchEmployee(Employee employees[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Update an existing employee's details.
void updateEmployee(Employee employees[], int count, int id) {
    int index = searchEmployee(employees, count, id);
    if (index == -1) {
        cout << "Employee not found." << endl;
        return;
    }
    
    cout << "Updating details for employee " << employees[index].name << endl;
    cin.ignore(); // flush input
    
    cout << "Enter new name (press enter to keep [" << employees[index].name << "]): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) {
        employees[index].name = newName;
    }

    cout << "Enter new position (press enter to keep [" << employees[index].position << "]): ";
    string newPosition;
    getline(cin, newPosition);
    if (!newPosition.empty()) {
        employees[index].position = newPosition;
    }
    
    cout << "Enter new daily wage (or -1 to keep [" << employees[index].dailyWage << "]): ";
    double newWage;
    cin >> newWage;
    if (newWage >= 0) {
        employees[index].dailyWage = newWage;
    }
    
    cout << "Employee updated successfully." << endl;
}

// Delete an employee from the array by ID.
void deleteEmployee(Employee employees[], int &count, int id) {
    int index = searchEmployee(employees, count, id);
    if (index == -1) {
        cout << "Employee not found." << endl;
        return;
    }
    // Shift subsequent elements left
    for (int i = index; i < count - 1; i++) {
        employees[i] = employees[i + 1];
    }
    count--;
    cout << "Employee deleted successfully." << endl;
}

// Display all employees
void displayEmployees(Employee employees[], int count) {
    if (count == 0) {
        cout << "No employees to display." << endl;
        return;
    }
    
    cout << "\nEmployee List:" << endl;
    for (int i = 0; i < count; i++) {
        cout << "ID: " << employees[i].id
             << ", Name: " << employees[i].name
             << ", Position: " << employees[i].position
             << ", Daily Wage: " << employees[i].dailyWage << endl;
    }
}

// ========== Attendance Linked List Operations ==========

// Add an attendance record (inserts at the head of the linked list)
void addAttendanceRecord(AttendanceNode*& head, int employeeID, int day, bool present) {
    AttendanceNode* newNode = new AttendanceNode;
    newNode->employeeID = employeeID;
    newNode->day = day;
    newNode->present = present;
    newNode->next = head;
    head = newNode;
    cout << "Attendance record added." << endl;
}

// Display attendance records for a specific employee
void displayAttendanceForEmployee(AttendanceNode* head, int employeeID) {
    bool found = false;
    AttendanceNode* current = head;
    while (current != nullptr) {
        if (current->employeeID == employeeID) {
            cout << "Day: " << current->day 
                 << ", Attendance: " << (current->present ? "Present" : "Absent") << endl;
            found = true;
        }
        current = current->next;
    }
    if (!found) {
        cout << "No attendance records found for employee ID " << employeeID << endl;
    }
}

// Update an attendance record (by employee ID and day)
bool updateAttendanceRecord(AttendanceNode* head, int employeeID, int day, bool newStatus) {
    AttendanceNode* current = head;
    while (current != nullptr) {
        if (current->employeeID == employeeID && current->day == day) {
            current->present = newStatus;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Delete an attendance record (by employee ID and day)
bool deleteAttendanceRecord(AttendanceNode*& head, int employeeID, int day) {
    AttendanceNode* current = head;
    AttendanceNode* prev = nullptr;
    while (current != nullptr) {
        if (current->employeeID == employeeID && current->day == day) {
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            delete current;
            return true;
        }
        prev = current;
        current = current->next;
    }
    return false;
}

// Display all attendance records in the linked list
void displayAllAttendance(AttendanceNode* head) {
    if (head == nullptr) {
        cout << "No attendance records available." << endl;
        return;
    }
    
    cout << "\nAttendance Records:" << endl;
    AttendanceNode* current = head;
    while (current != nullptr) {
        cout << "Employee ID: " << current->employeeID
             << ", Day: " << current->day
             << ", Attendance: " << (current->present ? "Present" : "Absent") << endl;
        current = current->next;
    }
}

// ========== Payroll Calculation ==========

// Calculate payroll by counting the number of days an employee was present and multiplying by the daily wage.
void calculatePayroll(Employee employees[], int count, AttendanceNode* head) {
    if (count == 0) {
        cout << "No employees available for payroll calculation." << endl;
        return;
    }
    
    cout << "\nPayroll Calculation:" << endl;
    for (int i = 0; i < count; i++) {
        int totalDaysPresent = 0;
        AttendanceNode* current = head;
        while (current != nullptr) {
            if (current->employeeID == employees[i].id && current->present) {
                totalDaysPresent++;
            }
            current = current->next;
        }
        double salary = totalDaysPresent * employees[i].dailyWage;
        cout << "Employee ID: " << employees[i].id
             << ", Name: " << employees[i].name
             << ", Days Present: " << totalDaysPresent
             << ", Salary: " << salary << endl;
    }
}

// ========== Main Menu ==========

int main() {
    Employee employees[MAX_EMPLOYEES];
    int employeeCount = 0;
    AttendanceNode* attendanceHead = nullptr;
    
    int choice;
    do {
        cout << "\n--- Workforce Attendance & Payroll System ---\n";
        cout << "1. Manage Employees\n";
        cout << "2. Manage Attendance\n";
        cout << "3. Calculate Payroll\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int empChoice;
                do {
                    cout << "\n-- Manage Employees --\n";
                    cout << "1. Add Employee\n";
                    cout << "2. Search Employee\n";
                    cout << "3. Update Employee\n";
                    cout << "4. Delete Employee\n";
                    cout << "5. Display All Employees\n";
                    cout << "6. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> empChoice;
                    switch (empChoice) {
                        case 1:
                            addEmployee(employees, employeeCount);
                            break;
                        case 2: {
                            int searchId;
                            cout << "Enter employee ID to search: ";
                            cin >> searchId;
                            int index = searchEmployee(employees, employeeCount, searchId);
                            if (index != -1) {
                                cout << "Employee found:\n";
                                cout << "ID: " << employees[index].id
                                     << ", Name: " << employees[index].name
                                     << ", Position: " << employees[index].position
                                     << ", Daily Wage: " << employees[index].dailyWage << endl;
                            } else {
                                cout << "Employee not found." << endl;
                            }
                            break;
                        }
                        case 3: {
                            int updateId;
                            cout << "Enter employee ID to update: ";
                            cin >> updateId;
                            updateEmployee(employees, employeeCount, updateId);
                            break;
                        }
                        case 4: {
                            int deleteId;
                            cout << "Enter employee ID to delete: ";
                            cin >> deleteId;
                            deleteEmployee(employees, employeeCount, deleteId);
                            break;
                        }
                        case 5:
                            displayEmployees(employees, employeeCount);
                            break;
                        case 6:
                            cout << "Returning to main menu." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (empChoice != 6);
                break;
            }
            case 2: {
                int attChoice;
                do {
                    cout << "\n-- Manage Attendance --\n";
                    cout << "1. Add Attendance Record\n";
                    cout << "2. Search Attendance for an Employee\n";
                    cout << "3. Update Attendance Record\n";
                    cout << "4. Delete Attendance Record\n";
                    cout << "5. Display All Attendance Records\n";
                    cout << "6. Return to Main Menu\n";
                    cout << "Enter your choice: ";
                    cin >> attChoice;
                    switch (attChoice) {
                        case 1: {
                            int empID, day, presChoice;
                            cout << "Enter employee ID: ";
                            cin >> empID;
                            cout << "Enter day (as an integer): ";
                            cin >> day;
                            cout << "Is the employee present? (1 for yes, 0 for no): ";
                            cin >> presChoice;
                            bool present = (presChoice == 1);
                            addAttendanceRecord(attendanceHead, empID, day, present);
                            break;
                        }
                        case 2: {
                            int empID;
                            cout << "Enter employee ID to search attendance: ";
                            cin >> empID;
                            displayAttendanceForEmployee(attendanceHead, empID);
                            break;
                        }
                        case 3: {
                            int empID, day, presChoice;
                            cout << "Enter employee ID: ";
                            cin >> empID;
                            cout << "Enter day of record to update: ";
                            cin >> day;
                            cout << "Enter new attendance status (1 for present, 0 for absent): ";
                            cin >> presChoice;
                            bool newStatus = (presChoice == 1);
                            if (updateAttendanceRecord(attendanceHead, empID, day, newStatus))
                                cout << "Attendance record updated." << endl;
                            else
                                cout << "Attendance record not found." << endl;
                            break;
                        }
                        case 4: {
                            int empID, day;
                            cout << "Enter employee ID: ";
                            cin >> empID;
                            cout << "Enter day of record to delete: ";
                            cin >> day;
                            if (deleteAttendanceRecord(attendanceHead, empID, day))
                                cout << "Attendance record deleted." << endl;
                            else
                                cout << "Attendance record not found." << endl;
                            break;
                        }
                        case 5:
                            displayAllAttendance(attendanceHead);
                            break;
                        case 6:
                            cout << "Returning to main menu." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                } while (attChoice != 6);
                break;
            }
            case 3:
                calculatePayroll(employees, employeeCount, attendanceHead);
                break;
            case 4:
                cout << "Exiting the system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);
    
    // Clean up the attendance linked list to avoid memory leaks.
    AttendanceNode* current = attendanceHead;
    while (current != nullptr) {
        AttendanceNode* temp = current;
        current = current->next;
        delete temp;
    }
    return 0;
}
