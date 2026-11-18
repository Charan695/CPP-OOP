#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct Student { int roll; string name; double marks; };

int main() {
    const string filename = "students.csv";
    {
        fstream file(filename, ios::out | ios::trunc);
        if (!file) { cerr << "Cannot open output file\\n"; return 1; }
        file << "roll,name,marks\\n101,Aarav,85.5\\n102,Meera,91.0\\n103,Kabir,78.5\\n";
        file.seekp(0, ios::end);
        cout << "End write position (tellp): " << file.tellp() << '\\n';
    }

    vector<Student> students;
    {
        fstream file(filename, ios::in);
        if (!file) { cerr << "Cannot open input file\\n"; return 1; }
        string line;
        getline(file, line); // Skip header.
        while (getline(file, line)) {
            stringstream row(line);
            string roll, name, marks;
            if (getline(row, roll, ',') && getline(row, name, ',') &&
                getline(row, marks, ',')) {
                try { students.push_back({stoi(roll), name, stod(marks)}); }
                catch (const exception& e) { cerr << "Bad row: " << e.what() << '\\n'; }
            }
        }
        file.clear();
        file.seekg(0, ios::beg);
        cout << "Start read position (tellg): " << file.tellg() << '\\n';
    }

    cout << "Records loaded from CSV:\\n";
    for (const auto& s : students)
        cout << s.roll << ' ' << s.name << ' ' << s.marks << '\\n';
}
