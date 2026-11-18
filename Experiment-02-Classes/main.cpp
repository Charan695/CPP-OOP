#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string holder;
    double balance;
protected:
    string accountType;
public:
    BankAccount(string name, double opening, string type)
        : holder(std::move(name)), balance(opening), accountType(std::move(type)) {}
    void deposit(double amount) { if (amount > 0) balance += amount; }
    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        return true;
    }
    double getBalance() const { return balance; }
    void display() const {
        cout << holder << " (" << accountType << ") balance: " << balance << '\n';
    }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(string name, double opening)
        : BankAccount(std::move(name), opening, "Savings") {}
    void addInterest(double percent) {
        if (percent > 0) deposit(getBalance() * percent / 100.0);
    }
};

int main() {
    SavingsAccount account("Aarav", 5000);
    account.deposit(1500);
    account.withdraw(750);
    account.addInterest(5);
    account.display();
}
