#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Account {
public:
    int accountNumber;
    string name;
    double balance;
};

const string FILE_NAME = "accounts.txt";

vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream file(FILE_NAME);

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        Account acc;
        string accNo, bal;

        getline(ss, accNo, '|');
        getline(ss, acc.name, '|');
        getline(ss, bal, '|');

        acc.accountNumber = stoi(accNo);
        acc.balance = stod(bal);

        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}

void saveAccounts(vector<Account>& accounts) {
    ofstream file(FILE_NAME);

    for (auto &acc : accounts) {
        file << acc.accountNumber << "|"
             << acc.name << "|"
             << acc.balance << endl;
    }

    file.close();
}

void createAccount() {
    Account acc;

    cout << "\nEnter Account Number: ";
    cin >> acc.accountNumber;
    cin.ignore();

    cout << "Enter Customer Name: ";
    getline(cin, acc.name);

    cout << "Enter Initial Balance: ";
    cin >> acc.balance;

    ofstream file(FILE_NAME, ios::app);

    file << acc.accountNumber << "|"
         << acc.name << "|"
         << acc.balance << endl;

    file.close();

    cout << "\nAccount Created Successfully!\n";
}

void displayAccounts() {
    vector<Account> accounts = loadAccounts();

    if (accounts.empty()) {
        cout << "\nNo Accounts Found!\n";
        return;
    }

    cout << "\n===== ACCOUNT DETAILS =====\n";

    for (auto &acc : accounts) {
        cout << "\nAccount Number : " << acc.accountNumber;
        cout << "\nCustomer Name  : " << acc.name;
        cout << "\nBalance        : Rs. " << acc.balance;
        cout << "\n--------------------------";
    }
}

void depositMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    bool found = false;

    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {
            cout << "Enter Deposit Amount: ";
            cin >> amount;

            acc.balance += amount;
            found = true;

            cout << "\nAmount Deposited Successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nAccount Not Found!\n";
        return;
    }

    saveAccounts(accounts);
}

void withdrawMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    bool found = false;

    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {

            cout << "Enter Withdrawal Amount: ";
            cin >> amount;

            if (amount > acc.balance) {
                cout << "\nInsufficient Balance!\n";
                return;
            }

            acc.balance -= amount;
            found = true;

            cout << "\nWithdrawal Successful!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nAccount Not Found!\n";
        return;
    }

    saveAccounts(accounts);
}

void checkBalance() {
    int accNo;

    cout << "\nEnter Account Number: ";
    cin >> accNo;

    vector<Account> accounts = loadAccounts();

    for (auto &acc : accounts) {
        if (acc.accountNumber == accNo) {
            cout << "\nCustomer Name : " << acc.name;
            cout << "\nCurrent Balance : Rs. " << acc.balance << endl;
            return;
        }
    }

    cout << "\nAccount Not Found!\n";
}

int main() {

    int choice;

    do {
        cout << "\n\n===== BANK MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Display Accounts";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Check Balance";
        cout << "\n6. Exit";

        cout << "\n\nEnter Choice: ";
        cin >> choice;

        switch(choice) {

            case 1:
                createAccount();
                break;

            case 2:
                displayAccounts();
                break;

            case 3:
                depositMoney();
                break;

            case 4:
                withdrawMoney();
                break;

            case 5:
                checkBalance();
                break;

            case 6:
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while(choice != 6);

    return 0;
}
