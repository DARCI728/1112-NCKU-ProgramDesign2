#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;

class Employee {
   public:
    int overloading_days = 0;
    int sign_forget_days = 0;
    unordered_map<string, int> sign_ins;
    unordered_map<string, int> sign_outs;

    void process_signing(const string &signing_type, const string &signing_time) {
        string date = signing_time.substr(0, 8);

        if (signing_type == "sign-in") {
            sign_ins[date] = stoi(signing_time.substr(8, 4));
        } else if (signing_type == "sign-out") {
            sign_outs[date] = stoi(signing_time.substr(8, 4));
        }
    }

    void calculate_days() {
        for (const auto &sign_in : sign_ins) {
            const auto &date = sign_in.first;

            if (sign_outs.count(date)) {
                int in_time = sign_in.second;
                int out_time = sign_outs[date];
                int duration = (out_time / 100 - in_time / 100) * 60 + (out_time % 100 - in_time % 100);

                if (duration > 480) {
                    overloading_days++;
                }

                sign_outs.erase(date);
            } else {
                sign_forget_days++;
            }
        }

        sign_forget_days += sign_outs.size();
    }
};

int main(int argc, char *argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    if (argc != 2) {
        cout << "No input file." << '\n';
        return 0;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cout << "Error opening file: " << argv[1] << '\n';
        return 0;
    }

    map<int, Employee> employees;
    string line;
    istringstream iss;

    while (getline(inFile, line)) {
        string token;
        iss.str(line);

        getline(iss, token, ',');
        int employee_id = stoi(token);

        getline(iss, token, ',');
        string signing_type = token;

        getline(iss, token, ',');
        string signing_time = token;

        iss.clear();
        employees[employee_id].process_signing(signing_type, signing_time);
    }

    for (auto &entry : employees) {
        entry.second.calculate_days();
        cout << entry.first << ',' << entry.second.overloading_days << ',' << entry.second.sign_forget_days << '\n';
    }

    return 0;
}
