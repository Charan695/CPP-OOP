#include <iostream>
using namespace std;

class Complex {
    double real, imaginary;
public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    void display() const { cout << real << " + " << imaginary << "i\n"; }
    void display(const string& label) const { cout << label << ": "; display(); }
    Complex operator+(const Complex& other) const {
        return {real + other.real, imaginary + other.imaginary};
    }
};

int main() {
    Complex first(2, 3), second(4, 5);
    first.display("First");
    second.display("Second");
    (first + second).display("Sum");
}
