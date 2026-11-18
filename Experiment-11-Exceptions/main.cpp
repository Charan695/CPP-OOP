#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class BankingException : public runtime_error {
public:
    explicit BankingException(const string& message) : runtime_error(message) {}
};
class InsufficientFunds : public BankingException {
public:
    InsufficientFunds() : BankingException("Insufficient account balance") {}
};
class InvalidAmount : public BankingException {
public:
    InvalidAmount() : BankingException("Amount must be greater than zero") {}
};

class BankAccount {
    double balance;
public:
    explicit BankAccount(double opening) : balance(opening) {}
    void withdraw(double amount) {
        if (amount <= 0) throw InvalidAmount();
        if (amount > balance) throw InsufficientFunds();
        balance -= amount;
        cout << "Withdrawal successful. Balance: " << balance << '\n';
    }
};

int main() {
    BankAccount account(2500);
    for (double amount : {500.0, 3000.0, -50.0}) {
        try { account.withdraw(amount); }
        catch (const InvalidAmount& e) { cerr << "Invalid amount: " << e.what() << '\n'; }
        catch (const InsufficientFunds& e) { cerr << "Declined: " << e.what() << '\n'; }
        catch (const BankingException& e) { cerr << "Bank error: " << e.what() << '\n'; }
    }
}
