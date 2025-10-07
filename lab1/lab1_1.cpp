#include <iostream>
#include <string>

using namespace std;

class Student {
private:
  string nume, prenume;
  string grupa;
  string pozitivLabSDA, negativLabSDA;
  string activitatiVara;
  string dorintaPostFacultate;

public:
  Student(const string& nume, const string& prenume, const string& grupa,
          const string& pozitivLabSDA, const string& negativLabSDA,
          const string& activitatiVara, const string& dorintaPostFacultate) {
    this->nume = nume;
    this->prenume = prenume;
    this->grupa = grupa;
    this->pozitivLabSDA = pozitivLabSDA;
    this->negativLabSDA = negativLabSDA;
    this->activitatiVara = activitatiVara;
    this->dorintaPostFacultate = dorintaPostFacultate;
  }

  void printInfo() const {
    cout << "Informatii student:\n";
    cout << "Nume, grupa: " << this->nume << " " << this->prenume << " " 
          << this->grupa << "\n";
    cout << "Ce i-a plăcut la laboratorul de SDA și vrea să fie păstrat: " 
          << pozitivLabSDA << "\n";
    cout << "Ce nu i-a plăcut la laboratorul de SDA sau ce poate fi îmbunătățit: "
          << negativLabSDA << "\n";
    cout << "Ce a făcut vara aceasta ca să mă dezvolt personal: "
          << activitatiVara << "\n";
    cout << "Ce își dorește să facă după ce termină facultatea: "
          << dorintaPostFacultate << "\n\n";
  }
};

int main() {
  Student eu("Priboi", "Luca Mihai", "321AC",
             "Laboratorul a fost interactiv și temele au ajutat la aprofundarea "
              "subiectelor parcurse.",
             "Mi-ar fi plăcut o temă suplimentară, de exemplu introducerea unui "
              "limbaj nou, pentru cei care stăpânesc deja majoritatea informațiilor",
             "Proiecte freelancing: site-uri (wordpress, angular), web crawler (python)",
             "Software dev în FAANG sau alte firme mari.");
  
  eu.printInfo();
}