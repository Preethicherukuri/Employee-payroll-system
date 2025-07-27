#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/stat.h> // For directory creation
using namespace std;

class Person {
protected:
    string id;
    string name;

public:
    Person(string person_id, string person_name) : id(person_id), name(person_name) {}

    string getId() const {
        return id;
    }

    string getName() const {
        return name;
    }
};

class Employee : public Person {
private:
    string designation;
    double working_hr;
    double hourly_rate;
    double salary;

public:
    int totalPresent;

    Employee(string emp_id, string namee, string desig, double work_hr, double hr_rate)
        : Person(emp_id, namee), designation(desig), working_hr(work_hr), hourly_rate(hr_rate) {}

    void calculateSalary(int absents) {
        totalPresent = 30 - absents;
        double hrPresent = totalPresent * working_hr;
        salary = hrPresent * hourly_rate;
    }

    void display() {
        cout << "\nEmployee Details:\n";
        cout << "Employee Id: " << getId() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Designation: " << designation << endl;
        cout << "Working Hours per Day: " << working_hr << endl;
        cout << "Hourly Wage: ₹" << hourly_rate << endl;
        cout << "Total Present Days: " << totalPresent << endl;
        cout << fixed << setprecision(2);
        cout << "Salary: ₹" << salary << endl;
    }

    string getDesignation() const {
        return designation;
    }

    double getHourlyRate() const {
        return hourly_rate;
    }

    double getWorkingHours() const {
        return working_hr;
    }
};

bool createDirectory(const string& path) {
#ifdef _WIN32
    return _mkdir(path.c_str()) == 0;
#else 
    return mkdir(path.c_str(), 0777) == 0;
#endif
}

void saveEmployeeData(const Employee& emp, const string& fileName) {
    ofstream file(fileName, ios::app);
    if (file.is_open()) {
        file << emp.getId() << ' '
             << emp.getName() << ' '
             << emp.getDesignation() << ' '
             << emp.getHourlyRate() << ' '
             << emp.getWorkingHours() << '\n';
        file.close();
    } else {
        cerr << "Error: Could not open the file for writing." << endl;
    }
}

void displayAllEmployeeData(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: File not found or cannot be opened." << endl;
        return;
    }

    string id, name, designation;
    double hourly_rate, working_hr;
    while (file >> id >> name >> designation >> hourly_rate >> working_hr) {
        Employee emp(id, name, designation, working_hr, hourly_rate);
        emp.calculateSalary(0);
        emp.display();
    }
    file.close();
}

void displayEmployeeData(const string& fileName, const string& empId) {
    ifstream file(fileName);
    if (!file) {
        cerr << "Error: File not found or cannot be opened." << endl;
        return;
    }

    string id, name, designation;
    double hourly_rate, working_hr;
    bool found = false;
    while (file >> id >> name >> designation >> hourly_rate >> working_hr) {
        if (id == empId) {
            found = true;
            Employee emp(id, name, designation, working_hr, hourly_rate);
            emp.calculateSalary(0);
            emp.display();
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Employee not found with the given ID." << endl;
    }
}

int main() {
    // Create payroll_data directory if it doesn't exist
    if (!createDirectory("payroll_data")) {
        // Directory already exists or we don't have permissions - continue anyway
    }

    int choice;
    string dataFileName;

    cout << "Employee Payroll System" << endl;
    cout << "1. Create New Payroll Data File" << endl;
    cout << "2. Open Existing Payroll Data File" << endl;
    cout << "3. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter File Name (without extension): ";
        cin >> dataFileName;
        dataFileName = "payroll_data/" + dataFileName + ".txt";
        
        ofstream newFile(dataFileName);
        if (newFile.is_open()) {
            newFile.close();
            cout << "New data file '" << dataFileName << "' created successfully." << endl;
        } else {
            cerr << "Error: Could not create the new data file." << endl;
            cerr << "Please check if you have write permissions." << endl;
            return 1;
        }
    } else if (choice == 2) {
        cout << "Enter File Name (without extension): ";
        cin >> dataFileName;
        dataFileName = "payroll_data/" + dataFileName + ".txt";
        
        ifstream checkFile(dataFileName);
        if (!checkFile) {
            cerr << "Error: The specified data file does not exist." << endl;
            return 1;
        }
        checkFile.close();
    } else if (choice == 3) {
        cout << "Goodbye!" << endl;
        return 0;
    } else {
        cerr << "Invalid choice. Exiting." << endl;
        return 1;
    }

    do {
        cout << endl;
        cout << "Employee Payroll System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Calculate Salary" << endl;
        cout << "3. Display All Employees Data" << endl;
        cout << "4. Display One Employee Data" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id, name, designation;
                double wrking_hr, hr_wage;
                cout << "Enter Employee Id: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Employee Name: ";
                getline(cin, name);
                cout << "Employee Designation: ";
                getline(cin, designation);
                cout << "Enter Hourly Wage: ₹";
                cin >> hr_wage;
                cout << "Enter Working Hours per Day: ";
                cin >> wrking_hr;
                Employee emp(id, name, designation, wrking_hr, hr_wage);
                saveEmployeeData(emp, dataFileName);
                cout << "Employee data saved successfully." << endl;
                break;
            }
            case 2: {
                string emp_id;
                cout << "Enter Employee ID to calculate salary: ";
                cin >> emp_id;
                int absents;
                bool found = false;
                ifstream file(dataFileName);
                if (file.is_open()) {
                    string id, name, designation;
                    double hourly_rate, working_hr;
                    while (file >> id >> name >> designation >> hourly_rate >> working_hr) {
                        if (id == emp_id) {
                            found = true;
                            cout << "Enter the number of absences: ";
                            cin >> absents;
                            Employee emp(id, name, designation, working_hr, hourly_rate);
                            emp.calculateSalary(absents);
                            emp.display();
                            break;
                        }
                    }
                    file.close();
                }
                if (!found) {
                    cout << "Employee not found with the given ID." << endl;
                }
                break;
            }
            case 3:
                displayAllEmployeeData(dataFileName);
                break;
            case 4: {
                string emp_id;
                cout << "Enter Employee ID to display data: ";
                cin >> emp_id;
                displayEmployeeData(dataFileName, emp_id);
                break;
            }
            case 5:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
