#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

time_t convert(int year, int month, int day);

class Employee {
   public:
    int id;
    int workdays = 0, max_workdays = 0;
    int start_date, max_start_date;
    int from_date = static_cast<int>(convert(2012, 1, 1));
    vector<int> signs = vector<int>(5000, 0);

    void process_signing(const int &employee_id, const int &signing_time);
    void calculate_days();
};

void read_file(const string &fileName, map<int, Employee> &employees);
bool mycomp(const Employee &a, const Employee &b);

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    if (argc != 2) {
        cout << "No input file." << '\n';
        return 0;
    }

    map<int, Employee> employees;
    vector<Employee> employees_sort;

    read_file(argv[1], employees);

    for (auto &entry : employees) {
        entry.second.calculate_days();
    }

    employees_sort.reserve(employees.size());
    for (auto &entry : employees) {
        employees_sort.push_back(entry.second);
    }

    partial_sort(employees_sort.begin(), employees_sort.begin() + 3, employees_sort.end(), mycomp);

    int cnt = 0;
    for (auto &entry : employees_sort) {
        int from = entry.max_start_date, to = entry.max_start_date + entry.max_workdays - 1;
        cout << entry.id << ',' << entry.max_workdays << ',' << entry.signs[from] << ',' << entry.signs[to] << '\n';
        if (++cnt == 3) {
            break;
        }
    }
    return 0;
}

time_t convert(int year, int month, int day) {
    tm info = {0};
    info.tm_year = year - 2000;
    info.tm_mon = month - 1;
    info.tm_mday = day;
    return mktime(&info);
}

void read_file(const string &fileName, map<int, Employee> &employees) {
    ifstream inFile(fileName);

    if (!inFile) {
        cout << "Error opening file: " << fileName << '\n';
        exit(1);
    }

    istringstream iss;
    string line;

    while (getline(inFile, line)) {
        string token;
        iss.str(line);

        getline(iss, token, ',');
        int employee_id = stoi(token);

        getline(iss, token, ',');

        getline(iss, token, ',');
        int signing_time = stoll(token) / 10000;

        iss.clear();
        employees[employee_id].process_signing(employee_id, signing_time);
    }
}

void Employee::process_signing(const int &employee_id, const int &signing_time) {
    id = employee_id;

    int year = signing_time / 10000;
    int month = signing_time / 100 % 100;
    int day = signing_time % 100;
    int to_date = static_cast<int>(convert(year, month, day));
    int day_diff = (to_date - from_date) / 86400;
    signs[day_diff] = signing_time;
}

void Employee::calculate_days() {
    for (int i = 0; i < 5000; ++i) {
        if (signs[i] > 0) {
            if (workdays == 0) {
                start_date = i;
            }
            ++workdays;
        } else {
            if (workdays >= max_workdays) {
                max_workdays = workdays;
                max_start_date = start_date;
            }
            workdays = 0;
        }
    }
}

bool mycomp(const Employee &a, const Employee &b) {
    if (a.max_workdays == b.max_workdays) {
        return a.id < b.id;
    } else {
        return a.max_workdays > b.max_workdays;
    }
}