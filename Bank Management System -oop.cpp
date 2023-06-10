#include <iostream>
#include <vector>

using namespace std;

class Account {
protected:
    string account_number;
    double balance;
    
public:
    Account(const string &account_number, double balance)
        : account_number(account_number), balance(balance) {}
    
    string get_account_number() const {
        return account_number;
    }
    
    double get_balance() const {
        return balance;
    }
    
    virtual void deposit(double amount) {
        balance += amount;
    }
    
    virtual void withdraw(double amount) = 0;
    
    virtual ~Account() {}
};

class SavingsAccount : public Account {
private:
    double interest_rate;
    
public:
    SavingsAccount(const string& account_number, double balance, double interest_rate)
        : Account(account_number, balance), interest_rate(interest_rate) {}
    
    double calculate_interest() const {
        return balance * interest_rate;
    }
    
    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }
};

class CurrentAccount : public Account {
private:
    double overdraft_limit;
    
public:
    CurrentAccount(const string& account_number, double balance, double overdraft_limit)
        : Account(account_number, balance), overdraft_limit(overdraft_limit) {}
    
    void withdraw(double amount) override {
        if (balance + overdraft_limit >= amount) {
            balance -= amount;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }
};

class Cheques : public Account {
private:
    int available_cheques;
    
public:
    Cheques(const string& account_number, double balance, int available_cheques)
        : Account(account_number, balance), available_cheques(available_cheques) {}
    
    void withdraw(double amount) override {
        if (balance >= amount) {
            balance -= amount;
            available_cheques--;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }
    
    void deposit(double amount) override {
        balance += amount;
        available_cheques++;
    }
    
    int get_available_cheques() const {
        return available_cheques;
    }
};

class Financing : public Account {
private:
    double loan_amount;
    
public:
    Financing(const string& account_number, double balance, double loan_amount)
        : Account(account_number, balance), loan_amount(loan_amount) {}
    
    void withdraw(double amount) override {
        cout << "Cannot withdraw from a financing account." << endl;
    }
    
    void deposit(double amount) override {
        balance += amount;
    }
    
    double get_loan_amount() const {
        return loan_amount;
    }
};

class Customer {
private:
    string name;
    Account* account;
    
public:
    Customer(const string& name, Account* account)
        : name(name), account(account) {}
    
    string get_name() const {
        return name;
    }
    
    Account* get_account() const {
        return account;
    }
    
    ~Customer() {
        delete account;
    }
};

class Bank {
private:
    string name;
    vector<Customer*> customers;
    
public:
    Bank(const string& name)
        : name(name) {}
    
    void add_customer(Customer* customer) {
        customers.push_back(customer);
    }
    
    vector<Customer*> get_customers() const {
        return customers;
    }
    
    ~Bank() {
        for (Customer* customer : customers) {
            delete customer;
        }
    }
};

class InterestCalculator {
public:
    static double calculate_interest(const Customer* customer) {
        Account* account = customer->get_account();
        if (SavingsAccount* savings_account = dynamic_cast<SavingsAccount*>(account)) {
            return savings_account->calculate_interest();
        } else {
            return 0.0;  // Return 0 for non-savings accounts
        }
    }
};

double operator+(const Account& account1, const Account& account2) {
    return account1.get_balance() + account2.get_balance();
}
int main() {
    Bank bank("MyBank");

    Customer* customer1 = new Customer("Talha", new SavingsAccount("SA3243", 5343245, 0.05));
    Customer* customer2 = new Customer("Aima", new CurrentAccount("CA2342", 134532, 5000));
    Customer* customer3 = new Customer("Momina", new Cheques("CH041", 77624545, 15));
    Customer* customer4 = new Customer("Fatima", new Financing("FI35671", 535553, 50000));
    Customer* customer5 = new Customer("Faizan ", new Financing("FI0658", 957634, 20000));
    Customer* customer6 = new Customer("Sarah ", new Financing("FI253423", 1500087, 100000));
    Customer* customer7 = new Customer("Saad ", new SavingsAccount("SAt54y1", 50345, 0.05));
    Customer* customer8 = new Customer(" Faheem", new CurrentAccount("CA045341", 747652, 5000));
    Customer* customer9 = new Customer("Anique", new Cheques("CH060531", 29986, 10));
    Customer* customer10 = new Customer("Taha", new Financing("FI3687301", 1000, 50000));
    Customer* customer11 = new Customer("Mikal", new Financing("FI5362", 503000, 20000));
    Customer* customer12 = new Customer(" Ahmad", new Financing("FI65323", 1523090, 100000));
    Customer* customer13 = new Customer("Khalil", new SavingsAccount("SA078977", 768500, 0.05));
    Customer* customer14 = new Customer("Aima", new CurrentAccount("CA00786957", 12360, 5000));
    Customer* customer15 = new Customer("Ammar", new Cheques("CH3445", 200896, 10));
    Customer* customer16 = new Customer("Jamshed", new Financing("FI453", 105900, 50000));
    Customer* customer17 = new Customer("Sana", new Financing("FI5432", 555900, 20000));
    Customer* customer18 = new Customer("Abiha", new Financing("FI45t03", 1533300, 100000));
    

    bank.add_customer(customer1);
    bank.add_customer(customer2);
    bank.add_customer(customer3);
    bank.add_customer(customer4);
    bank.add_customer(customer5);
    bank.add_customer(customer6);
    bank.add_customer(customer7);
    bank.add_customer(customer8);
    bank.add_customer(customer9);
    bank.add_customer(customer10);
    bank.add_customer(customer11);
    bank.add_customer(customer12);
    bank.add_customer(customer13);
    bank.add_customer(customer14);
    bank.add_customer(customer15);
    bank.add_customer(customer16);
    bank.add_customer(customer17);
    bank.add_customer(customer18);
    
    vector<Customer*> customers = bank.get_customers();
    for (Customer* customer : customers) {
        cout << "Customer Name: " << customer->get_name() << endl;
        cout << "Account Number: " << customer->get_account()->get_account_number() << endl;
        cout << "Balance: " << customer->get_account()->get_balance() << endl;
        
        if (Cheques* cheques_account = dynamic_cast<Cheques*>(customer->get_account())) {
            cout << "Available Cheques: " << cheques_account->get_available_cheques() << endl;
        }
        
        if (Financing* financing_account = dynamic_cast<Financing*>(customer->get_account())) {
            cout << "Loan Amount: " << financing_account->get_loan_amount() << endl;
        }
        
        double interest = InterestCalculator::calculate_interest(customer);
        cout << "Interest: " << interest << endl;
        cout << endl;
    }

    // Operator overloading example
    SavingsAccount savings_account1("SA002", 10000, 0.03);
    SavingsAccount savings_account2("SA003", 20000, 0.03);
    double total_balance = savings_account1 + savings_account2;
    cout << "Total Balance: " << total_balance << endl;

    return 0;
}


/*
https://github.com/MUHAMMADTALHA9626/Bank_Managemnt_System_C-
*/