#include <stdio.h>
#include <string>

using namespace std;

class Sibling {
private:
  string* prenume;
  string* nume;
  int* varsta;

public:
  Sibling(string prenume, string nume, int varsta);
  Sibling(const Sibling& other);
  ~Sibling();

  void displayInfo();

  void setPrenume(string prenume);
  void setNume(string nume);
  void setVarsta(int varsta);
};

Sibling::Sibling(string prenume, string nume, int varsta) {
  this->prenume = new string(prenume);
  this->nume = new string(nume);
  this->varsta = new int(varsta);
}

Sibling::Sibling(const Sibling& other) {
  prenume = new string(*other.prenume);
  nume = new string(*other.nume);
  varsta = new int(*other.varsta);
}

Sibling::~Sibling() {
  delete prenume;
  delete nume;
  delete varsta;
}

void Sibling::displayInfo() {
  printf("%s %s, varsta: %d\n",
         prenume->c_str(), nume->c_str(), *varsta);
}

void Sibling::setPrenume(string prenume) { *(this->prenume) = prenume; }
void Sibling::setNume(string nume) { *(this->nume) = nume; }
void Sibling::setVarsta(int varsta) { *(this->varsta) = varsta; }

int main() {
  Sibling sibling1("Ovidiu", "Zanoaga", 20);
  sibling1.displayInfo();

  Sibling sibling2 = sibling1;
  sibling2.setPrenume("Razvan");
  sibling2.setVarsta(14);
  sibling2.displayInfo();

  return 0;
}