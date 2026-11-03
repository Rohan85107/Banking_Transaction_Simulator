/* Project: Banking Transaction Simulator | Language: C++17 Features: accounts, deposit/withdraw/transfer, overloaded interest & fees,
   vector history, filtering, mini-statements, file saving */
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>
using namespace std; struct Account {
    int accountNumber; string accountHolder; double balance; };
struct Transaction { int transactionID; int accountNumber;
    string type; double amount; double resultingBalance; string dateTime; };
namespace utils { int readInt(const string& message) {
        int value; string line; while (true) {
            cout << message; getline(cin, line); stringstream input(line); char extra;
            if (input >> value && !(input >> extra)) return value; cout << "Invalid input. Please enter a whole number.\n"; }
    } double readDouble(const string& message) {
        double value; string line; while (true) {
            cout << message; getline(cin, line); stringstream input(line); char extra;
            if (input >> value && !(input >> extra)) return value; cout << "Invalid input. Please enter a valid number.\n"; }
    } string getCurrentDateTime() {
        time_t now = time(nullptr); tm* localTime = localtime(&now); stringstream result; result << put_time(localTime, "%d-%m-%Y %H:%M:%S");
        return result.str(); }
    // Overloaded interest: default 4% rate / custom rate
    double calculateInterest(double balance) { const double DEFAULT_RATE = 4.0; return balance * DEFAULT_RATE / 100.0; }
    double calculateInterest(double balance, double rate) { return balance * rate / 100.0; }
    // Overloaded fee: flat fee / percentage fee
    double calculateFee(double amount) { (void)amount; const double FLAT_FEE = 10.0;
        return FLAT_FEE; } double calculateFee(double amount, double rate) {
        return amount * rate / 100.0; } inline bool isPositive(double amount) {
        return amount > 0; } }
namespace bank { vector<Account> accounts; vector<Transaction> transactions;
    int nextTransactionID = 1; Account* findAccount(int accountNumber) {
        for (Account& account : accounts) {
            if (account.accountNumber == accountNumber)
                return &account; }
        return nullptr; }
    void saveAccounts() {
        ofstream file("accounts.txt");
        for (const Account& account : accounts) {
            file << account.accountNumber << " "
                 << quoted(account.accountHolder) << " "
                 << fixed << setprecision(2) << account.balance << "\n"; }
    }
    void loadAccounts() {
        ifstream file("accounts.txt"); Account account;
        while (file >> account.accountNumber
                    >> quoted(account.accountHolder)
                    >> account.balance) {
            accounts.push_back(account); }
    }
    void saveTransactions() {
        ofstream file("transactions.txt");
        for (const Transaction& transaction : transactions) {
            file << transaction.transactionID << " "
                 << transaction.accountNumber << " "
                 << quoted(transaction.type) << " "
                 << fixed << setprecision(2) << transaction.amount << " "
                 << transaction.resultingBalance << " "
                 << quoted(transaction.dateTime) << "\n"; }
    }
    void loadTransactions() {
        ifstream file("transactions.txt"); Transaction transaction;
        while (file >> transaction.transactionID
                    >> transaction.accountNumber
                    >> quoted(transaction.type)
                    >> transaction.amount
                    >> transaction.resultingBalance
                    >> quoted(transaction.dateTime)) {
            transactions.push_back(transaction);
            if (transaction.transactionID >= nextTransactionID)
                nextTransactionID = transaction.transactionID + 1; }
    }
    void recordTransaction(
        int accountNumber,
        const string& type,
        double amount,
        double balance
    ) {
        Transaction transaction; transaction.transactionID = nextTransactionID++;
        transaction.accountNumber = accountNumber; transaction.type = type;
        transaction.amount = amount; transaction.resultingBalance = balance;
        transaction.dateTime = utils::getCurrentDateTime(); transactions.push_back(transaction);
        saveTransactions(); }
    void createAccount() {
        Account newAccount;
        newAccount.accountNumber =
            utils::readInt("Enter account number: ");
        if (newAccount.accountNumber <= 0) {
            cout << "Account number must be positive.\n"; return; }
        if (findAccount(newAccount.accountNumber) != nullptr) {
            cout << "This account number already exists.\n"; return; }
        cout << "Enter account holder name: "; getline(cin, newAccount.accountHolder);
        if (newAccount.accountHolder.empty()) {
            cout << "Name cannot be empty.\n"; return; }
        newAccount.balance =
            utils::readDouble("Enter opening balance: ");
        if (newAccount.balance < 0) {
            cout << "Opening balance cannot be negative.\n"; return; }
        accounts.push_back(newAccount); saveAccounts();
        cout << "Account created successfully.\n"; }
    void displayAccounts() {
        if (accounts.empty()) {
            cout << "No accounts are available.\n"; return; }
        cout << "\n--------------- ALL ACCOUNTS ---------------\n";
        cout << left << setw(15) << "Account No."
             << setw(25) << "Account Holder"
             << right << setw(15) << "Balance\n";
        for (const Account& account : accounts) {
            cout << left << setw(15) << account.accountNumber
                 << setw(25) << account.accountHolder
                 << right << setw(15)
                 << fixed << setprecision(2) << account.balance
                 << "\n"; }
    }
    void deposit(Account& account, double amount) {
        if (!utils::isPositive(amount)) {
            cout << "Deposit amount must be greater than zero.\n"; return; }
        account.balance += amount; saveAccounts();
        recordTransaction(
            account.accountNumber,
            "Deposit",
            amount,
            account.balance
        );
        cout << "Deposit successful. New balance: "
             << fixed << setprecision(2)
             << account.balance << "\n"; }
    void withdraw(Account& account, double amount) {
        if (!utils::isPositive(amount)) {
            cout << "Withdrawal amount must be greater than zero.\n"; return; }
        if (amount > account.balance) {
            cout << "Insufficient balance. Withdrawal cancelled.\n"; return; }
        account.balance -= amount; saveAccounts();
        recordTransaction(
            account.accountNumber,
            "Withdrawal",
            amount,
            account.balance
        );
        cout << "Withdrawal successful. New balance: "
             << fixed << setprecision(2)
             << account.balance << "\n"; }
    void transferMoney(
        Account& sender,
        Account& receiver,
        double amount
    ) {
        if (sender.accountNumber == receiver.accountNumber) {
            cout << "You cannot transfer money to the same account.\n"; return; }
        if (!utils::isPositive(amount)) {
            cout << "Transfer amount must be greater than zero.\n"; return; }
        if (amount > sender.balance) {
            cout << "Insufficient balance. Transfer cancelled.\n"; return; }
        sender.balance -= amount; receiver.balance += amount;
        saveAccounts();
        recordTransaction(
            sender.accountNumber,
            "Transfer Sent",
            amount,
            sender.balance
        );
        recordTransaction(
            receiver.accountNumber,
            "Transfer Received",
            amount,
            receiver.balance
        ); cout << "Transfer completed successfully.\n"; }
    void depositMenu() {
        Account* account =
            findAccount(utils::readInt("Enter account number: "));
        if (account == nullptr) {
            cout << "Account not found.\n"; return; }
        deposit(
            *account,
            utils::readDouble("Enter deposit amount: ")
        ); }
    void withdrawMenu() {
        Account* account =
            findAccount(utils::readInt("Enter account number: "));
        if (account == nullptr) {
            cout << "Account not found.\n"; return; }
        withdraw(
            *account,
            utils::readDouble("Enter withdrawal amount: ")
        ); }
    void transferMenu() {
        Account* sender =
            findAccount(utils::readInt("Enter sender account number: "));
        if (sender == nullptr) {
            cout << "Sender account not found.\n"; return; }
        Account* receiver =
            findAccount(utils::readInt("Enter receiver account number: "));
        if (receiver == nullptr) {
            cout << "Receiver account not found.\n"; return; }
        transferMoney(
            *sender,
            *receiver,
            utils::readDouble("Enter transfer amount: ")
        ); }
    void checkBalance() {
        Account* account =
            findAccount(utils::readInt("Enter account number: "));
        if (account == nullptr) {
            cout << "Account not found.\n"; return; }
        cout << "Account holder: "
             << account->accountHolder << "\n";
        cout << "Available balance: "
             << fixed << setprecision(2)
             << account->balance << "\n"; }
    void showInterest() {
        Account* account =
            findAccount(utils::readInt("Enter account number: "));
        if (account == nullptr) {
            cout << "Account not found.\n"; return; }
        cout << "1. Default interest rate (4%)\n"; cout << "2. Enter a custom interest rate\n";
        int choice = utils::readInt("Choose an option: "); double interest = 0;
        if (choice == 1) {
            interest = utils::calculateInterest(account->balance); }
        else if (choice == 2) {
            double rate =
                utils::readDouble("Enter interest rate (%): ");
            if (rate < 0) {
                cout << "Interest rate cannot be negative.\n"; return; }
            interest =
                utils::calculateInterest(account->balance, rate); }
        else {
            cout << "Invalid choice.\n"; return; }
        cout << "Calculated interest: "
             << fixed << setprecision(2)
             << interest << "\n"; cout << "Note: This calculation does not add interest to the balance.\n"; }
    void showFee() {
        cout << "1. Flat fee\n"; cout << "2. Percentage fee\n";
        int choice = utils::readInt("Choose an option: ");
        double amount =
            utils::readDouble("Enter transaction amount: ");
        if (amount <= 0) {
            cout << "Amount must be greater than zero.\n"; return; }
        double fee = 0;
        if (choice == 1) {
            fee = utils::calculateFee(amount); }
        else if (choice == 2) {
            double rate =
                utils::readDouble("Enter fee rate (%): ");
            if (rate < 0) {
                cout << "Fee rate cannot be negative.\n"; return; }
            fee = utils::calculateFee(amount, rate); }
        else {
            cout << "Invalid choice.\n"; return; }
        cout << "Transaction fee: "
             << fixed << setprecision(2)
             << fee << "\n"; }
    void showTransactionHistory() {
        int number =
            utils::readInt("Enter account number: ");
        if (findAccount(number) == nullptr) {
            cout << "Account not found.\n"; return; }
        bool found = false; cout << "\n------------- TRANSACTION HISTORY -------------\n";
        for (const Transaction& transaction : transactions) {
            if (transaction.accountNumber == number) {
                found = true;
                cout << "Transaction ID: "
                     << transaction.transactionID
                     << "\nType: " << transaction.type
                     << "\nAmount: " << fixed << setprecision(2)
                     << transaction.amount
                     << "\nBalance after transaction: "
                     << transaction.resultingBalance
                     << "\nDate and time: " << transaction.dateTime
                     << "\n-----------------------------------------------\n"; }
        }
        if (!found) {
            cout << "No transactions found for this account.\n"; }
    }
    void showLastNTransactions() {
        int number =
            utils::readInt("Enter account number: ");
        if (findAccount(number) == nullptr) {
            cout << "Account not found.\n"; return; }
        int count =
            utils::readInt("How many recent transactions? ");
        if (count <= 0) {
            cout << "Enter a number greater than zero.\n"; return; }
        int shown = 0; cout << "\n------------- RECENT TRANSACTIONS -------------\n";
        for (int i = static_cast<int>(transactions.size()) - 1; i >= 0 && shown < count;
             --i) {
            const Transaction& transaction = transactions[i];
            if (transaction.accountNumber == number) {
                cout << "ID: " << transaction.transactionID
                     << " | " << transaction.type
                     << " | Amount: " << fixed << setprecision(2)
                     << transaction.amount
                     << " | Balance: " << transaction.resultingBalance
                     << " | " << transaction.dateTime << "\n"; shown++; }
        }
        if (shown == 0) {
            cout << "No transactions found.\n"; }
    }
    void filterTransactionsByType() {
        int number =
            utils::readInt("Enter account number: ");
        if (findAccount(number) == nullptr) {
            cout << "Account not found.\n"; return; }
        cout << "Enter type (Deposit, Withdrawal, Transfer Sent, Transfer Received): "; string requiredType;
        getline(cin, requiredType); bool found = false;
        for (const Transaction& transaction : transactions) {
            if (transaction.accountNumber == number
                && transaction.type == requiredType) {
                found = true;
                cout << "ID: " << transaction.transactionID
                     << " | Type: " << transaction.type
                     << " | Amount: " << fixed << setprecision(2)
                     << transaction.amount
                     << " | Balance: " << transaction.resultingBalance
                     << " | " << transaction.dateTime << "\n"; }
        }
        if (!found) {
            cout << "No matching transactions found.\n"; }
    } }
namespace report {
    void printMiniStatement(int accountNumber) {
        Account* account = bank::findAccount(accountNumber);
        if (account == nullptr) {
            cout << "Account not found.\n"; return; }
        cout << "\n===============================================\n"; cout << "                 MINI STATEMENT                \n";
        cout << "===============================================\n";
        cout << "Account Number : "
             << account->accountNumber << "\n";
        cout << "Account Holder : "
             << account->accountHolder << "\n";
        cout << "Current Balance: "
             << fixed << setprecision(2)
             << account->balance << "\n"; cout << "-----------------------------------------------\n";
        int count = 0; for (int i = static_cast<int>(bank::transactions.size()) - 1;
             i >= 0 && count < 5;
             --i) {
            const Transaction& transaction = bank::transactions[i];
            if (transaction.accountNumber == accountNumber) {
                cout << transaction.dateTime
                     << " | " << transaction.type
                     << " | " << fixed << setprecision(2)
                     << transaction.amount
                     << " | Balance: "
                     << transaction.resultingBalance << "\n"; count++; }
        }
        if (count == 0) {
            cout << "No transactions available.\n"; }
        cout << "===============================================\n"; }
    void miniStatementMenu() {
        printMiniStatement(
            utils::readInt("Enter account number: ")
        ); }
}
int main() {
    bank::loadAccounts(); bank::loadTransactions();
    int choice;
    do {
        cout << "\n============================================\n"; cout << "       BANKING TRANSACTION SIMULATOR\n";
        cout << "============================================\n"; cout << "1.  Create New Account\n";
        cout << "2.  Display All Accounts\n"; cout << "3.  Deposit Money\n";
        cout << "4.  Withdraw Money\n"; cout << "5.  Transfer Money\n";
        cout << "6.  Check Account Balance\n"; cout << "7.  Calculate Interest\n";
        cout << "8.  Calculate Transaction Fee\n"; cout << "9.  View Transaction History\n";
        cout << "10. View Last N Transactions\n"; cout << "11. Filter Transactions by Type\n";
        cout << "12. Generate Mini Statement\n"; cout << "13. Exit\n";
        cout << "============================================\n"; choice = utils::readInt("Enter your choice: ");
        switch (choice) {
            case 1:
                bank::createAccount(); break;
            case 2:
                bank::displayAccounts(); break;
            case 3:
                bank::depositMenu(); break;
            case 4:
                bank::withdrawMenu(); break;
            case 5:
                bank::transferMenu(); break;
            case 6:
                bank::checkBalance(); break;
            case 7:
                bank::showInterest(); break;
            case 8:
                bank::showFee(); break;
            case 9:
                bank::showTransactionHistory(); break;
            case 10:
                bank::showLastNTransactions(); break;
            case 11:
                bank::filterTransactionsByType(); break;
            case 12:
                report::miniStatementMenu(); break;
            case 13:
                cout << "Thank you for using Banking Transaction Simulator.\n"; break;
            default:
                cout << "Invalid choice. Please select 1 to 13.\n"; }
    } while (choice != 13); bank::saveAccounts();
    bank::saveTransactions(); return 0; }
