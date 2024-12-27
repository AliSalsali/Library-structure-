#include <iostream>
#include <cstdlib>
#include <string>
// #include <windows.h>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

// Function declarations
void addBook();
void registerMember();
void borrowBook();
void returnBook();
void processUserChoice(int choice);
void validateUserChoice(int choice);
void loadDataFromFile();
void removeBorrowRecord(int index);
void saveDataToFile();

// Struct definitions
struct Book {
    string title;
    string author;
    string translator;
    string id;
    int totalCopies;
    int availableCopies;
};

struct Member {
    string firstName;
    string lastName;
    string nationalCode;
    string phoneNumber;
    int borrowedBooksCount = 0;
};

struct BorrowRecord {
    string nationalCode;
    string bookId;
};

struct RecordCount {
    int books = 0;
    int members = 0;
    int borrowRecords = 0;
};

// Global variables
Book books[10];
Member members[10];
BorrowRecord borrowRecords[10];
RecordCount recordCount;

// Main function
int main() {
    loadDataFromFile();
    int userChoice;

    cout << "Welcome to the Library System\n";
    cout << "1- Add a Book\n";
    cout << "2- Register a Member\n";
    cout << "3- Borrow a Book\n";
    cout << "4- Return a Book\n";
    cout << "5- Exit\n";
    cin >> userChoice;

    validateUserChoice(userChoice);
    processUserChoice(userChoice);
    saveDataToFile();

    return 0;
}

string removeSpace(string& str)
{
    for (int i = 0; str[i] != '\0' ; i++)
    {
        if (str[i] == ' ') str[i] = '_';
    }
    
    return str;
}

void validateUserChoice(int choice) {
    if (choice < 1 || choice > 5) {
        cout << "Invalid choice. Please select a valid option.\n";
        main();
    }
}

void loadDataFromFile() {
    string line;

    // Load books data
    ifstream bookFile("books.txt");
    if (!bookFile) {
        cerr << "Error: Could not open books.txt\n";
        return;
    }
    int bookCounter = 0;
    while (getline(bookFile, line)) {
        istringstream iss(line);
        if (!(iss >> books[bookCounter].title >> books[bookCounter].author >> books[bookCounter].translator
              >> books[bookCounter].availableCopies >> books[bookCounter].id >> books[bookCounter].totalCopies)) {
            cerr << "Error: Invalid format in books.txt\n";
            continue;
        }
        bookCounter++;
    }
    recordCount.books = bookCounter;
    bookFile.close();

    // Load members data
    ifstream memberFile("members.txt");
    if (!memberFile) {
        cerr << "Error: Could not open members.txt\n";
        return;
    }
    int memberCounter = 0;
    while (getline(memberFile, line)) {
        istringstream iss(line);
        if (!(iss >> members[memberCounter].firstName >> members[memberCounter].lastName
              >> members[memberCounter].nationalCode >> members[memberCounter].phoneNumber
              >> members[memberCounter].borrowedBooksCount)) {
            cerr << "Error: Invalid format in members.txt\n";
            continue;
        }
        memberCounter++;
    }
    recordCount.members = memberCounter;
    memberFile.close();

    // Load borrow records data
    ifstream borrowFile("borrow_records.txt");
    if (!borrowFile) {
        cerr << "Error: Could not open borrow_records.txt\n";
        return;
    }
    int borrowCounter = 0;
    while (getline(borrowFile, line)) {
        istringstream iss(line);
        if (!(iss >> borrowRecords[borrowCounter].nationalCode >> borrowRecords[borrowCounter].bookId)) {
            cerr << "Error: Invalid format in borrow_records.txt\n";
            continue;
        }
        borrowCounter++;
    }
    recordCount.borrowRecords = borrowCounter;
    borrowFile.close();
}

void saveDataToFile() {
    // Save books data
    ofstream bookFile("books.txt");
    if (!bookFile) {
        cerr << "Error: Could not open books.txt for writing\n";
        return;
    }
    for (int i = 0; i < recordCount.books; i++) {
        bookFile << books[i].title << "\t" << books[i].author << "\t" << books[i].translator
                 << "\t" << books[i].availableCopies << "\t" << books[i].id << "\t" << books[i].totalCopies << endl;
    }
    bookFile.close();

    // Save members data
    ofstream memberFile("members.txt");
    if (!memberFile) {
        cerr << "Error: Could not open members.txt for writing\n";
        return;
    }
    for (int i = 0; i < recordCount.members; i++) {
        memberFile << members[i].firstName << "\t" << members[i].lastName << "\t"
                   << members[i].nationalCode << "\t" << members[i].phoneNumber << "\t"
                   << members[i].borrowedBooksCount << endl;
    }
    memberFile.close();

    // Save borrow records data
    ofstream borrowFile("borrow_records.txt");
    if (!borrowFile) {
        cerr << "Error: Could not open borrow_records.txt for writing\n";
        return;
    }
    for (int i = 0; i < recordCount.borrowRecords; i++) {
        borrowFile << borrowRecords[i].nationalCode << "\t" << borrowRecords[i].bookId << endl;
    }
    borrowFile.close();
}

void addBook() {
    system("cls");
    string title, author, translator, id;
    int totalCopies;

    cout << "Enter book title: ";
    getline(cin >> ws, title);
    removeSpace(title);
    cout << "Enter author: ";
    getline(cin >> ws, author);
    removeSpace(author);
    cout << "Enter translator: ";
    getline(cin >> ws, translator);
    removeSpace(translator);
    cout << "Enter total copies: ";
    cin >> totalCopies;
    cout << "Enter book ID: ";
    cin >> id;

    for (int i = 0; i < recordCount.books; i++) {
        if (id == books[i].id) {
            cout << "This book is already registered.\n";
            return;
        }
    }

    books[recordCount.books].title = title;
    books[recordCount.books].author = author;
    books[recordCount.books].translator = translator;
    books[recordCount.books].totalCopies = totalCopies;
    books[recordCount.books].availableCopies = totalCopies;
    books[recordCount.books].id = id;
    recordCount.books++;
    cout << "Book added successfully!\n";
}

void registerMember() {
    system("cls");
    string firstName, lastName, nationalCode, phoneNumber;

    cout << "Enter first name: ";
    getline(cin >> ws, firstName);
    removeSpace(firstName);
    cout << "Enter last name: ";
    getline(cin >> ws, lastName);
    removeSpace(lastName);
    cout << "Enter national code: ";
    cin >> nationalCode;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    for (int i = 0; i < recordCount.members; i++) {
        if (nationalCode == members[i].nationalCode) {
            cout << "This member is already registered.\n";
            return;
        }
    }

    members[recordCount.members].firstName = firstName;
    members[recordCount.members].lastName = lastName;
    members[recordCount.members].nationalCode = nationalCode;
    members[recordCount.members].phoneNumber = phoneNumber;
    recordCount.members++;
    cout << "Member registered successfully!\n";
}

void borrowBook() {
    system("cls");
    string bookId, nationalCode;
    int bookIndex = -1, memberIndex = -1;

    cout << "Enter book ID: ";
    cin >> bookId;
    cout << "Enter member national code: ";
    cin >> nationalCode;

    for (int i = 0; i < recordCount.books; i++) {
        if (books[i].id == bookId && books[i].availableCopies > 0) {
            bookIndex = i;
            break;
        }
    }

    for (int i = 0; i < recordCount.members; i++) {
        if (members[i].nationalCode == nationalCode && members[i].borrowedBooksCount < 3) {
            memberIndex = i;
            break;
        }
    }

    if (bookIndex != -1 && memberIndex != -1) {
        borrowRecords[recordCount.borrowRecords].nationalCode = nationalCode;
        borrowRecords[recordCount.borrowRecords].bookId = bookId;
        recordCount.borrowRecords++;
        books[bookIndex].availableCopies--;
        members[memberIndex].borrowedBooksCount++;
        cout << "Book borrowed successfully!\n";
    } else {
        cout << "Invalid book ID or member eligibility.\n";
    }
}

void returnBook() {
    system("cls");
    string bookId, nationalCode;
    bool found = false;

    cout << "Enter book ID: ";
    cin >> bookId;
    cout << "Enter member national code: ";
    cin >> nationalCode;

    for (int i = 0; i < recordCount.borrowRecords; i++) {
        if (borrowRecords[i].bookId == bookId && borrowRecords[i].nationalCode == nationalCode) {
            removeBorrowRecord(i);
            found = true;
            break;
        }
    }

    if (found) {
        for (int i = 0; i < recordCount.books; i++) {
            if (books[i].id == bookId) {
                books[i].availableCopies++;
                break;
            }
        }

        for (int i = 0; i < recordCount.members; i++) {
            if (members[i].nationalCode == nationalCode) {
                members[i].borrowedBooksCount--;
                break;
            }
        }

        cout << "Book returned successfully!\n";
    } else {
        cout << "No matching borrow record found.\n";
    }
}

void removeBorrowRecord(int index) {
    for (int i = index; i < recordCount.borrowRecords - 1; i++) {
        borrowRecords[i] = borrowRecords[i + 1];
    }
    recordCount.borrowRecords--;
}

void processUserChoice(int choice) {
    system("cls");
    switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            registerMember();
            break;
        case 3:
            borrowBook();
            break;
        case 4:
            returnBook();
            break;
        case 5:
            cout << "Goodbye!\n";
            exit(0);
        default:
            cout << "Invalid choice.\n";
            main();
            break;
    }
}
