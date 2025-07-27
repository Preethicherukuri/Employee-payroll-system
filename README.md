# 🧾 Employee Payroll System

A simple C++ console-based application to manage employee payrolls, store data in text files, and perform salary calculations based on working hours and absences.

---

## 📌 Features

- Create a new payroll data file or open an existing one
- Add employee details including ID, name, designation, hourly wage, and daily working hours
- Calculate monthly salary based on number of absences
- Display data for all employees or a specific employee
- Persistent data storage using file system (text file)

---

## 🛠️ Technologies Used

- C++ (OOP Concepts: Inheritance, Encapsulation)
- File I/O using `fstream`
- Console-based interface

---

## 📂 Project Structure
```
EmployeePayrollSystem/
├── main.cpp           # Main source code file
├── README.md          # Project documentation

```
📝 At runtime:
```
+ payroll_data.txt     # Auto-generated file (excluded from Git)
```
---

## 🚀 How to Run

### 1. Clone the repository

```bash
git clone https://github.com/your-username/EmployeePayroll.git
cd EmployeePayroll
```
### 2. Compile the program
```
g++ -o payroll payroll.cpp
```
### 3. Run the executable
```
./payroll
```

## 📷 Sample Output

```
Employee Payroll System
1. Create New Payroll Data File
2. Open Existing Payroll Data File
3. Quit
Enter your choice:
```
After selecting an option:
```
1. Add Employee
2. Calculate Salary
3. Display All Employee Data
4. Display One Employee Data
5. Quit
Enter your choice:
```

## 📄 File Format
Each employee's data is stored in the following format:
```
<id> <name> <designation> <hourly_rate> <working_hours>
```
Example:
```
E101 John Manager 500 8
```

## 🧠 Concepts Demonstrated

- Object-Oriented Programming (Inheritance between Person and Employee)
- File handling in C++
- User input validation
- Console-based user interface design

## Contribution

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.
