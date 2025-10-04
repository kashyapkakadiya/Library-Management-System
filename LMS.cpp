#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book() : id(0), title(""), author(""), isIssued(false) {}

    void input() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Book Title: ";
        getline(cin, title);
        cout << "Enter Author Name: ";
        getline(cin, author);
        isIssued = false;
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(30) << title
             << setw(20) << author
             << setw(10) << (isIssued ? "Yes" : "No") << endl;
    }
};

class Library {
private:
    vector<Book> books;

    void loadFromFile() {
        ifstream inFile("library.txt", ios::binary);
        Book b;
        while (inFile.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
            books.push_back(b);
        }
        inFile.close();
    }

    void saveToFile() {
        ofstream outFile("library.txt", ios::binary);
        for (const auto& b : books) {
            outFile.write(reinterpret_cast<const char*>(&b), sizeof(Book));
        }
        outFile.close();
    }

public:
    Library() { loadFromFile(); }
    ~Library() { saveToFile(); }

    void addBook() {
        Book b;
        b.input();
        books.push_back(b);
        cout << "Book added successfully!\n";
    }

    void displayBooks() const {
        if (books.empty()) {
            cout << "No books available!\n";
            return;
        }
        cout << left << setw(10) << "ID" 
             << setw(30) << "Title" 
             << setw(20) << "Author" 
             << setw(10) << "Issued" << endl;
        cout << string(70, '-') << endl;
        for (const auto& b : books) b.display();
    }

    void searchBook() const {
        int searchId;
        cout << "Enter Book ID to search: ";
        cin >> searchId;
        for (const auto& b : books) {
            if (b.id == searchId) {
                cout << "Book found:\n";
                cout << left << setw(10) << "ID" 
                     << setw(30) << "Title" 
                     << setw(20) << "Author" 
                     << setw(10) << "Issued" << endl;
                cout << string(70, '-') << endl;
                b.display();
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;
        for (auto& b : books) {
            if (b.id == id) {
                if (b.isIssued) {
                    cout << "Book is already issued!\n";
                    return;
                }
                b.isIssued = true;
                cout << "Book issued successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;
        for (auto& b : books) {
            if (b.id == id) {
                if (!b.isIssued) {
                    cout << "Book was not issued!\n";
                    return;
                }
                b.isIssued = false;
                cout << "Book returned successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->id == id) {
                books.erase(it);
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void sortBooks() {
        int option;
        cout << "\nSort Books By:\n";
        cout << "1. ID\n2. Title\n3. Author\nEnter your choice: ";
        cin >> option;

        switch(option) {
            case 1:
                sort(books.begin(), books.end(), [](Book a, Book b){ return a.id < b.id; });
                cout << "Books sorted by ID.\n";
                break;
            case 2:
                sort(books.begin(), books.end(), [](Book a, Book b){ return a.title < b.title; });
                cout << "Books sorted by Title.\n";
                break;
            case 3:
                sort(books.begin(), books.end(), [](Book a, Book b){ return a.author < b.author; });
                cout << "Books sorted by Author.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }
};

int main() {
    Library lib;
    int choice;

    do {
        cout << "\n====== Library Management System ======\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Sort Books\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.issueBook(); break;
            case 5: lib.returnBook(); break;
            case 6: lib.deleteBook(); break;
            case 7: lib.sortBooks(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while(choice != 8);

    return 0;
}