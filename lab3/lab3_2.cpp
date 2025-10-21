/*
Să se realizeze o clasă Student. Această clasă trebuie să aibă următoarele atribute: nume, prenume, CNP, anul nașterii toate de tipul private, dar și numele facultății și anul înființării acesteia (tot private). 
- Creați o funcție care să genereze automat CNP-uri. Explicați algoritmul din spate.
- Creați metodele de get și set pentru Student. 0.5p
- Creați o metodă care să întoarcă sexul studentului în funcție de CNP. 0.5p
- Creați o metodă care să întoarcă vârsta studentului. 0.5p
- Creați o metodă care să întoarcă diferența de ani dintre anul înființării facultății și data nașterii studentului. 0.5. p
Utilizați this Pointer. 0.5p  Testați codul creând mai mulți studenți.
*/

#include <stdio.h>
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

    if (an >= 1800 && an <= 1899)
      S = rand() % 2 == 0 ? "2" : "1";
    else if (an >= 1900 && an <= 1999)
      S = rand() % 2 == 0 ? "4" : "3";
    else if (an >= 2000 && an <= 2099)
      S = rand() % 2 == 0 ? "6" : "5";

    AA = to_string(an % 100);
    if (AA.length() == 1)
      AA = "0" + AA;
    
    // random
    LL = to_string(rand() % 12 + 1);
    if (LL.length() == 1)
      LL = "0" + LL;
    
    ZZ = to_string(rand() % 28 + 1);
    if (ZZ.length() == 1)
      ZZ = "0" + ZZ;

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
  Student(string nume, string prenume, int anul_nasterii,
          string nume_facultate, int anul_infiintarii) {
    
    this->nume = nume;
    this->prenume = prenume;
    this->anul_nasterii = anul_nasterii;
    this->nume_facultate = nume_facultate;
    this->anul_infiintarii = anul_infiintarii;
    this->CNP = genereazaCNP();
  }

  // Setters

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

  // Getters

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
};

int main() {
  srand(time(0));

  printf("schema ț");

  return 0;
}


