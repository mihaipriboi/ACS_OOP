#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Student {
private:
  string nume;
  string prenume;
  string CNP;
  int anul_nasterii;
  string nume_facultate;
  int anul_infiintarii;

  string genereazaCNP() {
    /*
    SAALLZZJJNNNC
    S - sexul si secolul nasterii
        1,2 - secolul 19 (1800-1899) (1-masculin, 2-feminin)
        3,4 - secolul 20 (1900-1999) (3-masculin, 4-feminin)
        5,6 - secolul 21 (2000-2099) (5-masculin, 6-feminin)
    AA - ultimele doua cifre ale anului nasterii
    LL - luna nasterii
    ZZ - ziua nasterii
    JJJ - codul judetului
    NNN - numar de ordine
    C - cifra de control
        primele 12 cifre sunt inmultite cu un vector de constante
        (279146358279) si se face suma rezultatelor
        suma se imparte la 11, restul este cifra de control
    */
    string S, AA, LL, ZZ, JJJ = "001", NNN = "001";
    int an = anul_nasterii;

    if(an >= 1800 && an <= 1899)
      S = rand() % 2 == 0 ? "2" : "1";
    else if(an >= 1900 && an <= 1999)
      S = rand() % 2 == 0 ? "4" : "3";
    else if(an >= 2000 && an <= 2099)
      S = rand() % 2 == 0 ? "6" : "5";

    AA = to_string(an % 100);
    if(AA.length() == 1)
      AA = "0" + AA;

    LL = "01";
    ZZ = "01";

    // Cifra de control
    string CNP_partial = S + AA + LL + ZZ + JJJ + NNN;
    string constante = "279146358279";

    int suma = 0;
    for(int i = 0; i < 12; i++)
      suma += (CNP_partial[i] - '0') * (constante[i] - '0');
    
    int C = suma % 11;
    if(C == 10)
      C = 1;

    return CNP_partial + to_string(C);
  }

public:
  Student() {
    this->nume = "Anonim";
    this->prenume = "Anonim";
    this->anul_nasterii = 2000;
    this->nume_facultate = "Necunoscut";
    this->anul_infiintarii = 2000;
    this->CNP = genereazaCNP();
  }

  Student(string nume, string prenume, int anul_nasterii,
          string nume_facultate, int anul_infiintarii) {
    
    this->nume = nume;
    this->prenume = prenume;
    this->anul_nasterii = anul_nasterii;
    this->nume_facultate = nume_facultate;
    this->anul_infiintarii = anul_infiintarii;
    this->CNP = genereazaCNP();
  }

  /* Setters */

  void setNume(string nume) {
    this->nume = nume;
    this->CNP = genereazaCNP();
  }

  void setPrenume(string prenume) {
    this->prenume = prenume;
    this->CNP = genereazaCNP();
  }

  void setAnulNasterii(int anul_nasterii) {
    this->anul_nasterii = anul_nasterii;
    this->CNP = genereazaCNP();
  }

  void setNumeFacultate(string nume_facultate) {
    this->nume_facultate = nume_facultate;
  }

  void setAnulInfiintarii(int anul_infiintarii) {
    this->anul_infiintarii = anul_infiintarii;
  }

  /* Getters */

  string getNume() { return this->nume; }
  string getPrenume() { return this->prenume; }
  string getCNP() { return this->CNP; }
  int getAnulNasterii() { return this->anul_nasterii; }
  string getNumeFacultate() { return this->nume_facultate; }
  int getAnulInfiintarii() { return this->anul_infiintarii; }

  string getSex() {
    char S = this->CNP[0];
    return (S % 2 == 1) ? "Masculin" : "Feminin";
  }

  int getVarsta() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    return now->tm_year + 1900 - this->anul_nasterii;
  }

  int getDiferentaAni() {
    return abs(this->anul_infiintarii - this->anul_nasterii);
  }

  void displayInfo() {
    cout << "Nume: " << this->nume << '\n';
    cout << "Prenume: " << this->prenume << '\n';
    cout << "CNP: " << this->CNP << '\n';
    cout << "Anul nasterii: " << this->anul_nasterii << '\n';
    cout << "Nume facultate: " << this->nume_facultate << '\n';
    cout << "Anul infiintarii: " << this->anul_infiintarii << '\n';
    cout << "Sex: " << getSex() << '\n';
    cout << "Varsta: " << getVarsta() << '\n';
    cout << "Diferenta ani: " << getDiferentaAni() << "\n\n";
  }
};

int main() {
  srand(time(0));

  Student st1("Zanoaga", "Ovidiu", 2007, "UPB", 1818);
  Student st2;
  Student st3("Klimt", "Gustav", 1960, "ASE", 1913);

  st1.displayInfo();
  st2.displayInfo();
  st3.displayInfo();

  st2.setNume("Musk");
  st2.setPrenume("X Æ A-12");
  st2.setAnulNasterii(2020);
  st2.setNumeFacultate("SpaceX University");
  st2.setAnulInfiintarii(2020);
  st2.displayInfo();

  cout << "Schimbare anul nasterii pentru st3 (se va schimba si prima cifra):\n";
  cout << st3.getCNP() << '\n';
  st3.setAnulNasterii(2000);
  cout << st3.getCNP() << '\n';

  return 0;
}


