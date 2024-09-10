#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <istream>

// Gotta have some number for an array right?
const int EMP_MAX = 100;

using namespace std;

struct Employee {
    string name;                // Employee name
    int nKeysPossessed;         // Number of keys possessed by employee
    string keys[5];             // String array of key names
};

bool reader(string input_filename, Employee employees[], int& numEmployees) {
    ifstream inFS;
    Employee tempEmployee;
    string str;
    int numKeysPossessed;
    int i = 0;

    inFS.open(input_filename);

    if(!inFS.is_open()) {
        return false;
    }

    inFS >> numEmployees;
    // inFS.ignore();
    while (i < numEmployees){ 
        inFS.ignore();
        getline(inFS, str);
        tempEmployee.name = str;

        inFS >> numKeysPossessed;
        tempEmployee.nKeysPossessed = numKeysPossessed;

        for (int j = 0; j < tempEmployee.nKeysPossessed; j++) {
            string keyName;
            inFS >> keyName;
            tempEmployee.keys[j] = keyName;
        }
        employees[i] = tempEmployee;
        i++;
    }
    inFS.close();
    return true;
}

void writer(string output_filename, Employee employees[], int numEmployees) {
    ofstream outFS;
    outFS.open(output_filename);

    outFS << numEmployees << endl;
    for (int i = 0; i < numEmployees; i++) {
        outFS << employees[i].name << endl;
        outFS << employees[i].nKeysPossessed << " ";
        for (int j = 0; j < employees[i].nKeysPossessed; j++) {
            outFS << employees[i].keys[j];
            if (j < employees[i].nKeysPossessed - 1) {
                outFS << " ";
            }
        }
        outFS << endl;
    }

    outFS.close();
}

bool addKeyForEmployee(Employee employees[], int nEmployees, string emp_name, string newKey) {
    // Locate the index of the employee + Return values if employee not found
    int index = -1;
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        cout << "Cannot find the specified employee!" << endl;
        return false;
    }

    /*
    Write conditions prior to adding a key (check priority levels of each condition)
    - If less than 5 keys, add key
    - If key is duplicated, return respective statement
    */
   if (employees[index].nKeysPossessed >= 5) {
        cout << "This employee already has 5 keys!" << endl;
        return false;
   } 
    // Attempt to check for duplications
    for (int i = 0; i < employees[index].nKeysPossessed; i++) {
        if(employees[index].keys[i] == newKey) {
            cout << "This employee already has this key!" << endl;
            return false;
        } 
    }   

   // Add key; Return true once done
   employees[index].keys[employees[index].nKeysPossessed] = newKey;
   employees[index].nKeysPossessed++;
   return true;
}

// Deletes a key from employees & reduces owned keys by 1; Similar to addKeyForEmployee
bool returnAKey(Employee employees[], int nEmployees, string emp_name, string returnKey) {
    // Locate the index of the employee + Return values if employee not found
    int emp_index = -1;
    for (int i = 0; i < nEmployees; i++) {
        if (employees[i].name == emp_name) {
            emp_index = i;
            break;
        }
    }
    if (emp_index == -1) {
        cout << "Cannot find the specified employee!" << endl;
        return false;
    }

    /*
        Conditions for deleting keys from Employees:
        - Employee not found -> Return false ("Cannot find the specified employee!")
        - Key not found -> Return false ("This employee does not have this key!")
    */
   // Similar to finding employee, develop smthn close, tweak; Find the index of the key
   int keyIndex = -1;
   for (int i = 0; i < employees[emp_index].nKeysPossessed; i++) {
        if (employees[emp_index].keys[i] == returnKey) {
            keyIndex = i;
        }
   }
   if (keyIndex == -1) {
        cout << "This employee does not have the specified key!" << endl;
        return false;
   }

   // Overwrite array (WIP, dumb idea but HEY, if it works, it works)
   for (int i = keyIndex; i < employees[emp_index].nKeysPossessed; i++) {
        employees[emp_index].keys[i] = employees[emp_index].keys[i+1];
   }
   employees[emp_index].nKeysPossessed--;
   return true;
};

int main() {
    string fileName;
    int numEmployees = 0; 
    Employee arrEmployees[EMP_MAX];
    int choice = 0;

    cout << "Please enter key file name to start: ";
    cin >> fileName;

    // Reads data from file into respective Employees
    if (reader(fileName, arrEmployees, numEmployees) == false) {
        cout << "File not found, exiting the program..." << endl;
        exit(1);
    } else {
        while (choice != 7) {
            cout << "Please select from the following options: " << endl;
            cout << "  1. show all employees and their keys" << endl;
            cout << "  2. show the keys an employee possesses" << endl;
            cout << "  3. show which employees possess a specific key" << endl;
            cout << "  4. add a key to an employee" << endl;
            cout << "  5. return a key by an employee" << endl;
            cout << "  6. save the current key status" << endl;
            cout << "  7. exit the program" << endl;
            cin >> choice;

            switch (choice) {
                case 1: {
                    // Print employees
                    for (int i = 0; i < numEmployees; i++) {
                        cout << "Name: " << arrEmployees[i].name << endl;
                        cout << "Keys possessed: ";
                        for (int j = 0; j < arrEmployees[i].nKeysPossessed; j++) {
                            cout << arrEmployees[i].keys[j] << " ";
                        }
                        cout << endl;
                    }
                    cout << endl;
                    break;
                }
                case 2: {
                    // Search for a specific employee and print out their name and keys
                    string name2;
                    int indexOfEmployeeCase2 = -1;
                    cout << "Please enter employee's name: ";
                    cin.ignore();
                    getline(cin, name2);

                    // Locate the index of the employee + Return values if employee not found
                    for (int i = 0; i < numEmployees; i++) {
                        if (arrEmployees[i].name == name2) {
                            indexOfEmployeeCase2 = i;
                            break;
                        }
                    }
                    if (indexOfEmployeeCase2 == -1) {
                        cout << "Cannot find the specified employee!" << endl;
                        cout << endl;
                        break;
                    }

                    // Print out keys
                    cout << name2 << " possess the following keys: ";
                    for (int i = 0; i < arrEmployees[indexOfEmployeeCase2].nKeysPossessed; i++) {
                        cout << arrEmployees[indexOfEmployeeCase2].keys[i] << " ";
                    }
                    cout << endl;
                    cout << endl;
                    break;
                }
                case 3: {
                    // Find which employees have the inputted key
                    string keyNameCase3;
                    int employeeCount = 0;
                    cout << "Please enter a key: ";
                    cin >> keyNameCase3;
                    
                    // Loop through employees
                    for (int i = 0; i < numEmployees; i++) {
                        // Loop through their keys
                        for (int j = 0; j < arrEmployees[i].nKeysPossessed; j++) {
                            if (arrEmployees[i].keys[j] == keyNameCase3) {
                                cout << arrEmployees[i].name << ", ";
                                employeeCount++;
                            }
                        }
                    }
                    if (employeeCount > 0) {
                        cout << "possess this key." << endl;
                    } else {
                        cout << "No one possesses this key." << endl;
                    }
                    cout << endl;
                    break;
                }

                case 4: {
                    // Add a key to employee
                    cout << "Please enter employee's name: ";
                    string inputName;
                    cin.ignore();
                    getline(cin, inputName);

                    cout << "Please enter a new key: ";
                    string inputKeyName;
                    cin >> inputKeyName;

                    if (addKeyForEmployee(arrEmployees, numEmployees, inputName, inputKeyName)) {
                        cout << "Key added successfully." << endl;
                    };
                    cout << endl;
                    break;
                }

                case 5: {
                    // Return/Deleting key from employee
                    string nameCase5;
                    cout << "Please enter employee's name: ";
                    cin.ignore();
                    getline(cin, nameCase5);

                    string keyNameCase5;
                    cout << "Please enter the returned key: ";
                    cin >> keyNameCase5;

                    if (returnAKey(arrEmployees, numEmployees, nameCase5, keyNameCase5)) {
                        cout << "Key returned successfully." << endl;
                    }
                    cout << endl;
                    break;
                }

                case 6: {
                    // Output to output.txt
                    string outputText;
                    cout << "Please enter output file name: " << endl;
                    cin >> outputText;

                    writer(outputText, arrEmployees, numEmployees);
                    break;
                }

                case 7: {
                    writer("keys_updated.txt", arrEmployees, numEmployees);
                    cout << "Thank you for using the system! Goodbye!" << endl;
                    break;
                }

                default: {
                    cout << "Not a valid option. Please try again." << endl;
                    cout << endl;
                    break;
                }
            }
        }
    }


    return 0;
};