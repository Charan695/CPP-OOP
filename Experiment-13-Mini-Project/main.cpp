#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
using namespace std;

class Student {
    int roll;
    string name;
    double marks;
public:
    Student(int r, string n, double m) : roll(r), name(std::move(n)), marks(m) {}
    int getRoll() const { return roll; }
    void display() const {
        cout << "Roll: " << roll << " | Name: " << name << " | Marks: " << marks << '\\n';
    }
    string serialize() const { return to_string(roll) + "," + name + "," + to_string(marks); }
    static Student parse(const string& line) {
        size_t a = line.find(','), b = line.find(',', a == string::npos ? a : a + 1);
        if (a == string::npos || b == string::npos) throw runtime_error("Malformed record");
        return Student(stoi(line.substr(0,a)), line.substr(a+1,b-a-1), stod(line.substr(b+1)));
    }
};

class StudentPortal {
    map<int,Student> students;
    const string filename = "portal_students.csv";
    void save() const {
        ofstream out(filename);
        if (!out) throw runtime_error("Could not save records");
        for (const auto& item : students) out << item.second.serialize() << '\\n';
    }
    void load() {
        ifstream in(filename);
        string line;
        while (getline(in,line)) {
            try { Student s = Student::parse(line); students[s.getRoll()] = s; }
            catch (const exception& e) { cerr << "Skipping row: " << e.what() << '\\n'; }
        }
    }
public:
    StudentPortal() { load(); }
    void add() {
        int roll; double marks; string name;
        cout << "Roll number: ";
        if (!(cin >> roll) || roll <= 0) throw invalid_argument("Invalid roll number");
        cin.ignore(10000,'\\n');
        cout << "Name (no commas): "; getline(cin,name);
        if (name.empty() || name.find(',') != string::npos) throw invalid_argument("Invalid name");
        cout << "Marks (0-100): ";
        if (!(cin >> marks) || marks < 0 || marks > 100) throw invalid_argument("Invalid marks");
        if (students.count(roll)) throw runtime_error("Roll number already exists");
        students.emplace(roll,Student(roll,name,marks));
        save();
        cout << "Student saved.\\n";
    }
    void show() const {
        if (students.empty()) cout << "No records.\\n";
        for (const auto& item : students) item.second.display();
    }
    void search() const {
        int roll; cout << "Roll number to find: ";
        if (!(cin >> roll)) throw invalid_argument("Invalid roll number");
        auto it = students.find(roll);
        if (it == students.end()) cout << "Student not found.\\n";
        else it->second.display();
    }
};

int main() {
    StudentPortal portal;
    int choice = 0;
    do {
        cout << "\\n1. Add student\\n2. Display all\\n3. Search\\n4. Exit\\nChoice: ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(10000,'\\n');
            cout << "Enter a valid menu number.\\n"; continue;
        }
        try {
            switch (choice) {
                case 1: portal.add(); break;
                case 2: portal.show(); break;
                case 3: portal.search(); break;
                case 4: cout << "Goodbye.\\n"; break;
                default: cout << "Invalid choice.\\n";
            }
        } catch (const exception& e) { cerr << "Error: " << e.what() << '\\n'; }
    } while (choice != 4);
}
