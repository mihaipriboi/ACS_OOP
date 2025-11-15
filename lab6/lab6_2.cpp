#include <iostream>
#include <string>

using namespace std;

class Reader;

class Book {
public:
  Book(const string& t, int pag) : title(t), pages(pag) {}

  virtual void displayInfo() const = 0;

protected:
  string title;
  int pages;

  friend class Reader;
  friend void comparePages(const Book& b1, const Book& b2);
};

class Novel : public Book {
public:
  Novel(const string& t, int pag, const string& g)
    : Book(t, pag), genre(g) {}

  void displayInfo() const override {
    cout << "Roman: " << title << "\n";
    cout << "Gen: " << genre << "\n";
    cout << "Pagini: " << pages << "\n\n";
  }

private:
  string genre;
};

class Reader {
public:
  void readBook(const Book& book) {
    cout << "Cititorul citeste: " << book.title << "\n";
    cout << "Numarul de pagini citite: " << book.pages << "\n";
  }
};

void comparePages(const Book& b1, const Book& b2) {
  if(b1.pages > b2.pages)
    cout << "'" << b1.title << "' are mai multe pagini decat '" << b2.title << "'.\n";
  else if(b1.pages < b2.pages)
    cout << "'" << b1.title << "' are mai putine pagini decat '" << b2.title << "'.\n";
  else
    cout << "'" << b1.title << "' si '" << b2.title << "' au acelasi numar de pagini.\n";
}

int main() {
  Novel dune("Dune", 412, "Science Fiction");
  Novel stapanulInelelor("Stapanul Inelelor", 1178, "Fantasy");

  Book* ptrBook1 = &dune;
  Book* ptrBook2 = &stapanulInelelor;

  ptrBook1->displayInfo();
  ptrBook2->displayInfo();

  comparePages(dune, stapanulInelelor);
  cout << "\n";

  Reader reader;
  reader.readBook(dune);

  return 0;
}