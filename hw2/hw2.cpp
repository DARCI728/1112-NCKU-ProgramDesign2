#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class Employee {
   public:
    int id;
    int age;
    char gender;
    int salary;
};

bool compare_employee(const Employee &a, const Employee &b) {
    if (a.salary == b.salary) {
        if (a.age == b.age) {
            if (a.gender == b.gender)
                return a.id < b.id;
            else if (a.gender == 'f' && b.gender == 'm')
                return true;
            else if (a.gender == 'm' && b.gender == 'f')
                return false;
        }
        return a.age < b.age;
    } else
        return a.salary < b.salary;
}

class EmployeeInfo {
   public:
    vector<Employee> employees;

    void readFile(string fileName) {
        ifstream inFile;
        inFile.open(fileName);

        if (!inFile) {
            cout << "input file opening failed";
            exit(1);
        }

        string line;
        while (getline(inFile, line)) {
            Employee emp;
            sscanf(line.c_str(), "%d,%d,%c,%d", &emp.id, &emp.age, &emp.gender, &emp.salary);
            employees.push_back(emp);
        }

        inFile.close();
    }

    void sortBySalary() {
        sort(employees.begin(), employees.end(), compare_employee);

        int lastSalary = -1;
        for (int i = 0; i < employees.size(); i++) {
            if (employees[i].salary != lastSalary) {
                if (lastSalary != -1) cout << endl;
                cout << employees[i].salary << ",";
                lastSalary = employees[i].salary;
            }
            cout << employees[i].id;
            if (employees[i].salary == employees[i + 1].salary) {
                cout << ",";
            }
        }
        cout << endl;
    }
};

int main(int argc, char **argv) {
    if (argc < 2) {
        cout << "No input file.\n";
        return 0;
    }

    string fileName(argv[1]);
    EmployeeInfo employeeInfo;
    employeeInfo.readFile(fileName);
    employeeInfo.sortBySalary();
    return 0;
}
