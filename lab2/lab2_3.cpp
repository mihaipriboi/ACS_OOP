#include <stdio.h>
#include <string>

using namespace std;

class Sibling {
private:
  string* nume;
  string* prenume;
  int* varsta;

public:
  Sibling(string nume, string prenume, int varsta) {
    this->nume = new string(nume);
    this->prenume = new string(prenume);
    this->varsta = new int(varsta);
  }

  Sibling(const Sibling& other) {
    nume = new string(*other.nume);
    prenume = new string(*other.prenume);
    varsta = new int(*other.varsta);
  }

  ~Sibling() {
    delete nume;
    delete prenume;
    delete varsta;
  }

  void afisare() {
    printf("Nume: %s, Prenume: %s, Varsta: %d\n", nume->c_str(), prenume->c_str(), *varsta);
  }
};

int main() {
  Sibling* sibling1 = new Sibling("Ion", "Popescu", 25);
  sibling1->afisare();

  Sibling* sibling2 = new Sibling(*sibling1);
  sibling2->afisare();

  return 0;
}