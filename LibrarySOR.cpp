#include <iostream>
#include <string>
#include <regex>
#include <limits>
using namespace std;

struct Book {
    string title;
    string author;
    string genre;
    int year;

    Book(string t, string a, string g, int y) : title(t), author(a), genre(g), year(y) {}
};

struct Tnode {
    int year;
    Tnode* left;
    Tnode* right;
    Tnode* next;
    Book* book;

    Tnode(int y) : year(y), left(nullptr), right(nullptr), next(nullptr), book(nullptr) {}
};

class Library {
private:
    Tnode* root;

public:
    Library() : root(nullptr) {}
    ~Library() {
        clrtree(root);
    }

    void addBook(const Book& book) {
        root = insertBook(root, book);
        cout << endl;
        cout << "Book added to the system." << endl;
    }

    Tnode* insertBook(Tnode* node, const Book& book) {
    if (!node) {
        Tnode* newNode = new Tnode(book.year);
        newNode->book = new Book(book.title, book.author, book.genre, book.year);
        return newNode;
    }

    if (book.year < node->year) {
        node->left = insertBook(node->left, book);
    } else if (book.year > node->year) {
        node->right = insertBook(node->right, book);
    } else {
        Tnode* newBookNode = new Tnode(book.year);
        newBookNode->next = node->next;
        newBookNode->book = new Book(book.title, book.author, book.genre, book.year);
        node->next = newBookNode;
    }
    return node;
}

    void deleteBook(int year, const string& title) {
        bool deleted = false;
        root = deleteBook(root, year, title, deleted);
        if (deleted) {
            cout << endl;
            cout << "Book deleted from the system." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void displayBooks() const {
        if (!root) {
            cout << "No books found in the system." << endl;
            return;
        }
        cout << endl;
        cout << "Books in the library:" << endl;
        inOrderTraversal(root);
    }

    void srchbook(int year, const string& title) const {
        Tnode* yearNode = findYearNode(root, year);
        if (yearNode) {
            bool found = srchbookInYearList(yearNode, title);
            if (!found) {
                cout << "Book not recorded." << endl;
            }
        } else {
            cout << "No books recorded for the given year." << endl;
        }
    }

    bool srchbookInYearList(Tnode* yearNode, const string& title) const {
    Tnode* current = yearNode;
    while (current) {
        if (current->book->title == title) {
            displayBook(current->book);
            return true;
        }
        current = current->next;
    }
    return false;
}

    void inOrderTraversal(Tnode* node) const {
        if (node) {
            inOrderTraversal(node->left);
            displayBook(node->book);
            Tnode* current = node->next;
            while (current) {
                displayBook(current->book);
                current = current->next;
            }
            inOrderTraversal(node->right);
        }
    }

    void displayBook(const Book* book) const {
        cout << "\n======================================\n\n";
        cout << "Title: " << book->title << endl;
        cout << "Author: " << book->author << endl;
        cout << "Year: " << book->year << endl;
        cout << "Genre: " << book->genre << endl;
               
    }

    Tnode* findYearNode(Tnode* node, int year) const {
        if (!node || node->year == year) {
            return node;
        }

        if (year < node->year) {
            return findYearNode(node->left, year);
        } else {
            return findYearNode(node->right, year);
        }
    }

   

    Tnode* deleteBook(Tnode* node, int year, const string& title, bool& deleted) {
        if (!node) return node;

        if (year < node->year) {
            node->left = deleteBook(node->left, year, title, deleted);
        } else if (year > node->year) {
            node->right = deleteBook(node->right, year, title, deleted);
        } else {
            Tnode* prev = nullptr;
            Tnode* current = node;
            while (current && current->book->title != title) {
                prev = current;
                current = current->next;
            }
            if (current) {
                deleted = true;
                if (prev) {
                    prev->next = current->next;
                    delete current->book;
                    delete current;
                } 
                else {                                             
                    if (node->next) {
                        Tnode* temp = node->next;
                        node->year = temp->year;
                        node->book = temp->book;
                        node->next = temp->next;
                        delete temp;
                    } 
                    else {
                        Tnode* temp = node;
                        if (!node->left && !node->right) {
                            node = nullptr;
                        }
                        else if (!node->left) {
                            node = node->right;
                        } 
                        else if (!node->right) {
                            node = node->left;
                        } 
                        else {
                            Tnode* minNode = findMin(node->right);
                            node->year = minNode->year;
                            node->book = minNode->book;
                            node->right = deleteBook(node->right, minNode->year, minNode->book->title, deleted);
                        }
                        delete temp;
                    }
                }
            }
        }
        return node;
    }

    Tnode* findMin(Tnode* node) const {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    void clrtree(Tnode* node) {
        if (node) {
            clrtree(node->left);
            clrtree(node->right);
            delete node->book;
            delete node;
        }
    }
};


bool isValidTitle(const string& title) {
    return regex_match(title, regex("^[A-Za-z0-9 ]+$"));
}

bool isValidAuthor(const string& author) {
    return regex_match(author, regex("^[A-Za-z ]+$"));
}

bool isValidGenre(const string& genre) {
    return regex_match(genre, regex("^[A-Za-z ]+$"));
}

bool isValidYear(int year) {
    return year > 0;
}

void getValidTitle(string& title) {
    while (true) {
        cout << "Enter title: ";
        getline(cin, title);
        if (isValidTitle(title)) break;
        cout << "Invalid title! Please enter a valid title (alphanumeric characters only)." << endl;
    }
}

void getValidAuthor(string& author) {
    while (true) {
        cout << "Enter author: ";
        getline(cin, author);
        if (isValidAuthor(author)) break;
        cout << "Invalid author! Please enter a valid author (alphabetic characters and spaces only)." << endl;
    }
}

void getValidGenre(string& genre) {
    while (true) {
        cout << "Enter genre: ";
        getline(cin, genre);
        if (isValidGenre(genre)) break;
        cout << "Invalid genre! Please enter a valid genre (alphabetic characters and spaces only)." << endl;
    }
}

int getValidYear() {
    string input;
    int year;
    bool valid = false;

    while (!valid) {
        cout << "Enter year: ";
        getline(cin, input);

        try {
            year = stoi(input);

            // Check if the entered year is valid (for example, between a reasonable range)
            if (year < 1000 || year > 3000) {
                cout << "Invalid year! Please enter a valid year." << endl;
            } else {
                valid = true;
            }
        } catch (const invalid_argument& e) {
            cout << "Invalid input! Please enter a valid year." << endl;
        } catch (const out_of_range& e) {
            cout << "Invalid input! Year is out of range." << endl;
        }
    }

    return year;
}

int displayMenuAndGetChoice() {
    string input;
    int choice;
    while (true) {
        cout << "\n============== Main Menu ==============\n" << endl;
        cout << "[1.]     Add a book" << endl;
        cout << "[2.]     Display all books" << endl;
        cout << "[3.]     Search a book [year, title]" << endl;
        cout << "[4.]     Delete a book [year, title]" << endl;
        cout << "[5.]     Exit" << endl;
        cout << "\n=======================================\n";
        cout << "Enter your choice: ";
        getline(cin, input);

        if (!regex_match(input, regex("^[1-5]$"))) {
            cout << "Invalid choice! Please enter a valid choice." << endl;
        } else {
            choice = stoi(input);
            break;
        }
    }
    return choice;
}

int main() {
    Library lib;

    int choice;
    do {
        choice = displayMenuAndGetChoice();

        switch (choice) {
            case 1: {
                string title, author, genre;
                int year;
                cout << "=======================================\n";
                cout << "Enter title: ";
                getline(cin, title);
                cout << "Enter author: ";
                getline(cin, author);
                year = getValidYear(); // Use the modified function to get a valid year
                cout << "Enter genre: ";
                getline(cin, genre);
                Book newBook(title, author, genre, year);
                lib.addBook(newBook);
                cout << "=======================================\n";
                break;
            }
            case 2:
                cout << "=======================================\n";
                lib.displayBooks();
                break;
            case 3: {
                int year;
                string title;
                cout << "=======================================\n\n";
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter title: ";
                getline(cin, title);
                lib.srchbook(year, title);
                cout << "=======================================\n";
                break;
                
            }
            case 4: {
                int year;
                string title;
                cout << "=======================================\n\n";
                cout << "Enter year: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter title: ";
                getline(cin, title);
                lib.deleteBook(year, title);
                cout << "=======================================\n";
                break;
            }
            case 5:
                cout << "=======================================\n\n";
                cout << "Thank you for using the Library System!" << endl;
                break;
            default:
                cout << "=======================================\n\n";
                cout << "Invalid Choice! Try again." << endl;
                cout << "=======================================\n";
        }

    } while (choice != 5);

    return 0;
}