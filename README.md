# Banking Transaction Simulator

A simple **console-based Banking Transaction Simulator** developed in **C++17**.

The program simulates basic banking operations such as creating accounts, depositing money, withdrawing money, transferring money between accounts, calculating interest and transaction fees, viewing transaction history, and generating mini statements.

---

## 📌 Features

- Create a new bank account
- Display all accounts
- Deposit money
- Withdraw money
- Transfer money between accounts
- Check account balance
- Calculate interest
  - Default interest rate: **4%**
  - Custom interest rate
- Calculate transaction fees
  - Flat fee
  - Percentage-based fee
- View complete transaction history
- View last N transactions
- Filter transactions by transaction type
- Generate a mini statement
- Automatically save account data to a file
- Automatically save transaction data to a file
- Load saved data when the program starts
- Input validation and handling of invalid inputs

---

## 🛠️ Technologies Used

- **Language:** C++
- **Standard:** C++17
- **Compiler:** GCC / MinGW
- **Interface:** Command Line / Terminal
- **Data Storage:** Text files

---

## 📂 Project Structure

``` text
Banking-Transaction-Simulator/
│
├── banking_transaction_simulator.cpp
├── accounts.txt
├── transactions.txt
└── README.md
```

### Files

| File | Description |
| --- | --- |
| `banking_transaction_simulator.cpp` | Main C++ source code |
| `accounts.txt` | Stores account information |
| `transactions.txt` | Stores transaction history |
| `README.md` | Project documentation |

> `accounts.txt` and `transactions.txt` are automatically created by the program when data is saved.

---

## 🧩 Main Concepts Used

The program demonstrates several important C++ concepts:

### Structures

Two structures are used:

``` cpp
struct Account
```

Stores account number, account holder name, and balance.

``` cpp
struct Transaction
```

Stores transaction ID, account number, transaction type, amount, resulting balance, and date/time.

---

### Namespaces

The program uses namespaces to organize functionality:

``` cpp
namespace utils
namespace bank
namespace report
```

- `utils` → input validation, date/time, interest and fee calculations
- `bank` → account and transaction operations
- `report` → mini statement generation

---

### Vectors

Vectors are used to store accounts and transactions:

``` cpp
vector<Account> accounts;
vector<Transaction> transactions;
```

This allows the program to store multiple accounts and transactions dynamically.

---

### Function Overloading

The program uses overloaded functions for interest and fee calculations.

For interest:

``` cpp
calculateInterest(double balance)
calculateInterest(double balance, double rate)
```

For fees:

``` cpp
calculateFee(double amount)
calculateFee(double amount, double rate)
```

This demonstrates **function overloading**.

---

### Pointers

Pointers are used to find and modify accounts:

``` cpp
Account* findAccount(int accountNumber)
```

The function returns the address of the matching account.

---

### File Handling

The program uses:

``` cpp
ofstream
ifstream
```

to save and load account and transaction data.

The files used are:

``` text
accounts.txt
transactions.txt
```

---

### Input Validation

The program validates integer and decimal inputs using:

``` cpp
readInt()
readDouble()
```

It also checks conditions such as:

- Negative account numbers
- Duplicate account numbers
- Empty account holder names
- Negative opening balance
- Zero or negative transaction amounts
- Insufficient balance
- Transfer to the same account
- Invalid menu choices

---

## ▶️ How to Run the Program

### Method 1: Using VS Code Terminal

#### Step 1: Open the Project

Open the folder containing:

``` text
banking_transaction_simulator.cpp
```

in VS Code.

---

#### Step 2: Open Terminal

In VS Code, select:

``` text
Terminal → New Terminal
```

Make sure the terminal is inside your project folder.

For example:

``` text
C:\Users\YourName\Banking-Transaction-Simulator>
```

---

#### Step 3: Compile the Program

Run:

``` bash
g++ -std=c++17 banking_transaction_simulator.cpp -o banking_transaction_simulator
```

If there are no errors, the program has been compiled successfully.

---

#### Step 4: Run the Program

### Windows PowerShell

``` powershell
.\banking_transaction_simulator.exe
```

### Windows CMD

``` cmd
banking_transaction_simulator.exe
```

### Linux / macOS

``` bash
./banking_transaction_simulator
```

---

## 💻 How to Run Using a Single Command

On Windows, you can compile and run using:

``` powershell
g++ -std=c++17 banking_transaction_simulator.cpp -o banking_transaction_simulator; .\banking_transaction_simulator.exe
```

---

## 📋 Main Menu

When the program starts, it displays:

``` text
============================================
       BANKING TRANSACTION SIMULATOR
============================================
1.  Create New Account
2.  Display All Accounts
3.  Deposit Money
4.  Withdraw Money
5.  Transfer Money
6.  Check Account Balance
7.  Calculate Interest
8.  Calculate Transaction Fee
9.  View Transaction History
10. View Last N Transactions
11. Filter Transactions by Type
12. Generate Mini Statement
13. Exit
============================================
```

---

## 🏦 Example Usage

### 1\. Create Account

Select:

``` text
1
```

Enter:

``` text
Account number: 101
Account holder name: Rohan
Opening balance: 10000
```

The account will be created and saved.

---

### 2\. Deposit Money

Select:

``` text
3
```

Enter the account number and deposit amount.

Example:

``` text
Account number: 101
Deposit amount: 2000
```

New balance:

``` text
12000
```

---

### 3\. Withdraw Money

Select:

``` text
4
```

Example:

``` text
Account number: 101
Withdrawal amount: 1000
```

New balance:

``` text
11000
```

The program prevents withdrawal when the account does not have sufficient balance.

---

### 4\. Transfer Money

Select:

``` text
5
```

Enter:

``` text
Sender account number
Receiver account number
Transfer amount
```

The sender's balance decreases and the receiver's balance increases.

The program records two transactions:

``` text
Transfer Sent
Transfer Received
```

---

### 5\. Calculate Interest

Select:

``` text
7
```

You can choose:

``` text
1. Default interest rate (4%)
2. Enter a custom interest rate
```

For example, if the balance is:

``` text
10000
```

and the interest rate is:

``` text
4%
```

calculated interest is:

``` text
400
```

> The calculated interest is displayed but is **not added to the account balance**.

---

### 6\. Calculate Transaction Fee

Select:

``` text
8
```

You can select:

``` text
1. Flat fee
2. Percentage fee
```

The default flat fee is:

``` text
10
```

For a percentage fee, you can enter your own rate.

---

### 7\. View Transaction History

Select:

``` text
9
```

Enter an account number to see transactions including:

- Transaction ID
- Transaction type
- Amount
- Balance after transaction
- Date and time

---

### 8\. View Last N Transactions

Select:

``` text
10
```

Enter the account number and number of recent transactions.

For example:

``` text
How many recent transactions? 5
```

The program displays the latest five matching transactions.

---

### 9\. Filter Transactions

Select:

``` text
11
```

Available transaction types are:

``` text
Deposit
Withdrawal
Transfer Sent
Transfer Received
```

The program displays only transactions matching the selected type.

---

### 10\. Generate Mini Statement

Select:

``` text
12
```

The program displays:

- Account number
- Account holder
- Current balance
- Last 5 transactions

---

## 💾 Data Persistence

The program automatically saves data into two files.

### `accounts.txt`

Stores account information such as:

``` text
Account Number
Account Holder
Balance
```

### `transactions.txt`

Stores:

``` text
Transaction ID
Account Number
Transaction Type
Amount
Resulting Balance
Date and Time
```

When the program starts, it loads previously saved data automatically.

---

## ⚠️ Edge Cases Handled

The program handles several invalid situations.

### Invalid Account Number

``` text
Account number must be positive.
```

### Duplicate Account

``` text
This account number already exists.
```

### Empty Name

``` text
Name cannot be empty.
```

### Nega.      ..  .  ive Op.

. mm .. ..



&#32;&#32;

&#32;mm. . aa aa. . &#32;

&#32; .

app. ... ..  &#32;



&#32;. .

&#32;.?  . . . . ..

&#32;

&#32;   &#32;

&#32;

&#32;, .  ..&#32;

ening Balance

``` text
Opening balance cannot be negative.
```

### Invalid Deposit

``` text
Deposit amount must be greater than zero.
```

### Invalid Withdrawal

``` text
Withdrawal amount must be greater than zero.
```

### Insufficient Balance

``` text
Insufficient balance. Withdrawal cancelled.
```

### Same Account Transfer

``` text
You cannot transfer money to the same account.
```

### Account Not Found

``` text
Account not found.
```

### Invalid Menu Choice

``` text
Invalid choice. Please select 1 to 13.
```

These validations are implemented throughout the account and transaction operations.

---

## 🔄 Program Flow

``` text
Start
  │
  ▼
Load saved accounts and transactions
  │
  ▼
Display Main Menu
  │
  ├── Create Account
  ├── Display Accounts
  ├── Deposit
  ├── Withdraw
  ├── Transfer
  ├── Check Balance
  ├── Calculate Interest
  ├── Calculate Fee
  ├── Transaction History
  ├── Last N Transactions
  ├── Filter Transactions
  ├── Mini Statement
  │
  ▼
Exit
  │
  ▼
Save Accounts & Transactions
  │
  ▼
End
```

---

## 🎯 Learning Objectives

This project demonstrates practical use of:

- C++17
- Structures
- Functions
- Function overloading
- Namespaces
- Pointers
- References
- Vectors
- Loops
- Conditional statements
- Switch-case
- Input validation
- File handling
- Date and time
- Basic object-oriented programming concepts

---

## 🚀 Future Improvements

Possible improvements include:

- PIN/password authentication
- Multiple account types
- Interest automatically added to balance
- Account deletion
- Account search
- Transaction export to CSV
- Better user authentication
- Admin and customer roles
- Database integration
- Graphical user interface
- Encryption for sensitive data

---

## 👨‍💻 Author

**Rohan Nevage**

**Course:** Computer Science \& Engineering

---

## 📄 License

This project is created for **educational and academic purposes**.