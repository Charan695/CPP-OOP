#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string n, int a) : name(std::move(n)), age(a) {}
    void introduce() const { cout << name << ", age " << age << '\n'; }
};

class Student : public Person {
protected:
    int roll;
public:
    Student(string n, int a, int r) : Person(std::move(n), a), roll(r) {}
    void showStudent() const { introduce(); cout << "Roll: " << roll << '\n'; }
};

class GraduateStudent : public Student {
    string researchArea;
public:
    GraduateStudent(string n, int a, int r, string area)
        : Student(std::move(n), a, r), researchArea(std::move(area)) {}
    void display() const { showStudent(); cout << "Research: " << researchArea << '\n'; }
};

int main() {
    GraduateStudent student("Meera", 23, 1042, "Machine Learning");
    student.display();
}
