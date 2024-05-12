#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ACCOUNTS = 2;    // maximum two accounts

// Function prototypes
int findAccountIndex(const string& userCardNum, const string bankCardNumber[], int numAccounts);
bool validatePin(int userPin);
void displayMenu();
void displayBalance(double balance);
void deposit(double& balance, string& transactionHistory);
void withdraw(double& balance, string& transactionHistory);
void displayTransactionHistory(const string& transactionHistory);
void updateTransactionHistory(string& transactionHistory, const string& transactionType, double amount);
void generateReport(const string& userCardNum, double balance, const string& transactionHistory);

int main() {
    string bankCardNumber[MAX_ACCOUNTS] = {"1234567890123456", "2345678901234567"};     // bank card Numbers
    int bankCardPins[MAX_ACCOUNTS] = {1234, 5678};										// Pin Numbers
    double balances[MAX_ACCOUNTS] = {1500.0, 2000.0};									// Account balance 
    string transactionHistories[MAX_ACCOUNTS];											// Transaction history

    int numAccounts = 2;						// No of accounts initilize

    string userCardNum;
    int userPin;
    int accountIndex;

    // Input card number
    cout << "Enter 16-digit card number: ";
    cin >> userCardNum;

    // Validate card number and get account index
    accountIndex = findAccountIndex(userCardNum, bankCardNumber, numAccounts);
    if (accountIndex == -1) {
        cout << "Invalid card number. Exiting program." << endl;
        return 0;
    }

    // Input PIN
    cout << "Enter 4-digit PIN: ";
    cin >> userPin;

    // Validate PIN
    if (!validatePin(userPin) || bankCardPins[accountIndex] != userPin) {
        cout << "Invalid PIN. Exiting program." << endl;
        return 1;
    }

    // Main ATM options
char choice;
    do {
        system("cls");					 // For Clear screen
        displayMenu();					//  display Menu
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case '1':
                displayBalance(balances[accountIndex]);     // account index is zero for the first account and 1 for the second
                break;
            case '2':
                deposit(balances[accountIndex], transactionHistories[accountIndex]);
                break;
            case '3':
                withdraw(balances[accountIndex], transactionHistories[accountIndex]);
                break;
            case '4':
                displayTransactionHistory(transactionHistories[accountIndex]);
                break;
            case '5':
                generateReport(bankCardNumber[accountIndex], balances[accountIndex], transactionHistories[accountIndex]);
                break;
            case '6':
                cout << "\nExiting program. Thank you for using the ATM!" << endl;
                break;
            default:
                cout << "\nIdle State! Please try any Service..." << endl;
        }

        // Wait for a key press before showing the result
        cout << "Press Enter to continue...";
        cin.ignore();
        cin.get();

    } while (choice != '6');

    return 0;
}

int findAccountIndex(const string& userCardNum, const string bankCardNumber[], int numAccounts) {
    for (int i = 0; i < numAccounts; ++i) {
        if (bankCardNumber[i] == userCardNum) {
            return i;
        }
    }
    return -1; // Account not found
}

bool validatePin(int userPin) {
    return (userPin >= 1000 && userPin <= 9999);
}

void displayMenu() {
    cout << "\nATM Menu:\n";
    cout << "1. Display Balance\n";
    cout << "2. Deposit\n";
    cout << "3. Withdraw\n";
    cout << "4. Display Transaction History\n";
    cout << "5. Generate Report\n";
    cout << "6. Exit\n";
}

void displayBalance(double balance) {
    cout << "\nYour account balance is: $" << fixed << setprecision(2) << balance << endl;
}

void deposit(double& balance, string& transactionHistory) {
    double amount;
    cout << "Enter the deposit amount: $";
    cin >> amount;

    // Update balance and transaction history
    balance += amount;
    updateTransactionHistory(transactionHistory, "Deposit", amount);

    cout << "\nDeposit successful. New balance: $" << fixed << setprecision(2) << balance << endl;
}

void withdraw(double& balance, string& transactionHistory) {
    double amount;
    cout << "Enter the withdrawal amount: $";
    cin >> amount;

    if (amount > balance) {
        cout << "\nInsufficient funds. Withdrawal canceled." << endl;
    } else {
        // Update balance and transaction history
        balance -= amount;
        updateTransactionHistory(transactionHistory, "Withdrawal", amount);

        cout << "\nWithdrawal successful. New balance: $" << fixed << setprecision(2) << balance << endl;
    }
}

void displayTransactionHistory(const string& transactionHistory) {
    cout << "\nTransaction History:\n" << transactionHistory << endl;
}

void updateTransactionHistory(string& transactionHistory, const string& transactionType, double amount) {
    transactionHistory += transactionType + ": $" + to_string(amount) + "\n";   // convert ammount into string
}

void generateReport(const string& userCardNum, double balance, const string& transactionHistory) {
    cout << "\nTransaction Report:\n";
    cout << "Card Number: " << userCardNum << endl;
    cout << "Account Balance: $" << fixed << setprecision(2) << balance << endl;
    displayTransactionHistory(transactionHistory);
}
