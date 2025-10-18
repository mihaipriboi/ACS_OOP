#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ManagerFisier {
private:
  ofstream file;

public:
  ManagerFisier(const char* nume_fisier);
  ~ManagerFisier();
  void scrie(const std::string& mesaj);
};

ManagerFisier::ManagerFisier(const char* nume_fisier) {
  file.open(nume_fisier);
  if(file.is_open())
    cout << "Fisier deschis.\n";
  else
    cerr << "Eroare la deschiderea fisierului.\n";
}

ManagerFisier::~ManagerFisier() {
  if(file.is_open()) {
    file.close();
    cout << "Fisier inchis.\n";
  }
}

void ManagerFisier::scrie(const std::string& mesaj) {
  if(file.is_open())
    file << mesaj << endl;
  else
    cerr << "Fisierul nu este deschis pentru scriere.\n";
}

int main() {
  ManagerFisier* mngPointer;
  {
    ManagerFisier manager("lab2_4.txt");
    manager.scrie("Scris in scop.");

    mngPointer = &manager;
  }
  // Posibil sa dea eroare in functie de argumentele
  // de compilare si rulare.
  mngPointer->scrie("Scris prin pointer.");

  /* In terminal:
  Fisier deschis.
  Fisier inchis.
  Fisierul nu este deschis pentru scriere.
  */

  return 0;
}