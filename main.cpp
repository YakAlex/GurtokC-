#include <iostream>
#include <windows.h>
#include <algorithm>
#include <vector>
using namespace std;

struct Transaction {
    string category;
    double amount;
    double expenses;
    int day, month, year;
};


bool isValidDate(int day, int month, int year) {
    if (year < 1999 || year > 2025) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;
    vector<int> daysInMonth = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) daysInMonth[1] = 29;
    return day <= daysInMonth[month - 1];
}


void displayCategories() {
    cout << "Категорії:\n";
    cout << "1. Переказ\n";
    cout << "2. Поповнення мобільного\n";
    cout << "3. Транспорт\n";
}


void addTransaction(vector<Transaction>& transactions, double& balance) {
    Transaction t;
    displayCategories();
    int ch;
    cout << "Оберіть категорію (1-3): ";
    cin >> ch;

    switch (ch) {
        case 1: t.category = "Переказ"; break;
        case 2: t.category = "Поповнення мобільного"; break;
        case 3: t.category = "Транспорт"; break;
        default: t.category = "Невідома категорія"; break;
    }

    cout << "Вкажіть суму: ";
    cin >> t.expenses;

    do {
        cout << "Вкажіть дату (день місяць рік): ";
        cin >> t.day >> t.month >> t.year;
        if (!isValidDate(t.day, t.month, t.year)) {
            cout << "Некоректна дата. Спробуйте ще раз.\n";
        }
    } while (!isValidDate(t.day, t.month, t.year));

    if (balance >= t.expenses) {
        balance -= t.expenses;
        t.amount = balance;
        transactions.push_back(t);
        cout << "Транзакція успішно додана!\n";
    } else {
        cout << "Недостатньо коштів для цієї транзакції.\n";
    }
}

void displayTransactions(const vector<Transaction>& transactions) {
    if (transactions.empty()) {
        cout << "Немає транзакцій для відображення.\n";
        return;
    }
    cout << "\nСписок транзакцій:\n";
    for (const auto& t : transactions) {
        cout << "Категорія: " << t.category
             << ", Сума: " << t.expenses
             << ", Дата: " << t.day << "/" << t.month << "/" << t.year
             << ", Баланс після транзакції: " << t.amount << "$\n";
    }
}


void sortTransactionsByDate(vector<Transaction>& transactions) {
    if (transactions.empty()) {
        cout << "Немає транзакцій для відображення.\n";
        return;
    }
    sort(transactions.begin(), transactions.end(), [](const Transaction& a, const Transaction& b) {
        if (a.year != b.year) return a.year < b.year;
        if (a.month != b.month) return a.month < b.month;
        return a.day < b.day;
    });
    cout << "Транзакції відсортовані за датою.\n";
}


void menu() {
    vector<Transaction> transactions;
    double balance;

    cout << "Введіть початковий баланс: ";
    cin >> balance;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Додати транзакцію\n";
        cout << "2. Вивести всі транзакції\n";
        cout << "3. Відсортувати транзакції за датою\n";
        cout << "4. Вийти\n";
        cout << "Оберіть опцію: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTransaction(transactions, balance);
                break;
            case 2:
                displayTransactions(transactions);
                break;
            case 3:
                sortTransactionsByDate(transactions);
                break;
            case 4:
                break;
            default:
                cout << "Некоректний вибір. Спробуйте ще раз.\n";
                break;
        }
    } while (choice != 4);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);

    menu();

    return 0;
}
