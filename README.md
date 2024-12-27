
# Library Management System

This project is a **console-based library management system** written in C++. It allows library administrators to manage books, members, and borrowing activities efficiently. The system uses file storage to persist data across sessions, ensuring that all records are retained even after the program exits.

## Features

1. **Add a Book**  
   - Register new books in the library.
   - Stores details like title, author, translator, total copies, and a unique book ID.

2. **Register a Member**  
   - Add new library members by storing their name, national code, and phone number.
   - Prevents duplicate member registrations based on the national code.

3. **Borrow a Book**  
   - Allows members to borrow books, provided:
     - The book has available copies.
     - The member has borrowed fewer than 3 books.

4. **Return a Book**  
   - Processes book returns by verifying the member's borrow record.
   - Updates the available copies of the book and the member's borrowing count.

5. **File Storage**  
   - Data is saved to and loaded from text files:
     - `books.txt`: Stores book details.
     - `members.txt`: Stores member details.
     - `borrow_records.txt`: Tracks borrowing history.

## How It Works

- The program starts with a main menu offering the above options.
- Input validation ensures the user provides correct and consistent data.
- Borrowing rules and member-book relationships are enforced to maintain the integrity of library operations.
- On program exit, all data is saved to the corresponding text files.

## Requirements

- **Platform**: Windows
- **Compiler**: Any C++ compiler that supports C++11 or later
- **Libraries**: Standard C++ library and Windows-specific headers (`windows.h`)

## File Format

### `books.txt`
Each line represents a book:  
`<Title> <Author> <Translator> <AvailableCopies> <ID> <TotalCopies>`

### `members.txt`
Each line represents a member:  
`<FirstName> <LastName> <NationalCode> <PhoneNumber> <BorrowedBooksCount>`

### `borrow_records.txt`
Each line represents a borrowing record:  
`<NationalCode> <BookID>`

## Usage Instructions

1. Clone the repository:
   ```bash
   https://github.com/AliSalsali/Library-structure-.git
   cd Library-structure-
   ```
2. Compile the code using a C++ compiler:
   ```bash
   g++ -o Library-structure- Library-structure-.cpp
   ```
3. Run the program:
   ```bash
   ./Library-structure-
   ```
4. Follow the on-screen instructions to manage the library.

