#include <iostream>
#include <string>
using namespace std;

int main() {
    int age = 19;
    double cgpa = 8.4;
    char grade = 'A';
    bool enrolled = true;
    string name = "Student";
    const int semester = 3;

    cout << "Name: " << name << "\\nAge: " << age
         << "\\nCGPA: " << cgpa << "\\nGrade: " << grade
         << "\\nEnrolled: " << boolalpha << enrolled
         << "\\nSemester: " << semester << '\\n';

    int a = 12, b = 5;
    cout << "Addition: " << a + b << "\\nGreater: " << (a > b)
         << "\\nLogical AND: " << (a > 0 && b > 0) << '\\n';

    int input{};
    cout << "Enter an integer: ";
    if (!(cin >> input)) {
        cerr << "Invalid input\\n";
        return 1;
    }
    cout << "You entered: " << input << '\\n';
    return 0;
}
