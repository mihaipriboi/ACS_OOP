#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
  Animal() {
    specie = "Necunoscuta";
  }

  Animal(const string& s) {
    specie = s;
  }

  string getSpecie() const {
    return specie;
  }

  void afiseazaSpecie() const {
    cout << "Specie: " << specie;
  }

private:
  string specie;
};

class Zburator {
public:
  Zburator() {
    inaltimeZborMaxima = 0.0;
  }

  Zburator(double i) {
    inaltimeZborMaxima = i;
  }

  double getInaltimeZborMaxima() const {
    return inaltimeZborMaxima;
  }

  void afiseazaZbor() const {
    cout << ", Zbor Max: " << inaltimeZborMaxima << "m";
  }

private:
  double inaltimeZborMaxima;
};

class Inotator {
public:
  Inotator() {
    adancimeInotMaxima = 0.0;
  }

  Inotator(double a) {
    adancimeInotMaxima = a;
  }

  double getAdancimeInotMaxima() const {
    return adancimeInotMaxima;
  }

  void afiseazaInot() const {
    cout << ", Inot Max: " << adancimeInotMaxima << "m";
  }

private:
  double adancimeInotMaxima;
};

class AnimalDublu : public Zburator, public Inotator {
public:
  AnimalDublu() : Zburator(), Inotator() {
    nume = "Anonim";
  }

  AnimalDublu(const string& n, double i, double a) : Zburator(i), Inotator(a) {
    nume = n;
  }

  void afiseazaInfo() const {
    cout << "Nume: " << nume;
    afiseazaZbor();
    afiseazaInot();
    cout << '\n';
  }

private:
  string nume;
};

class Rata : public Animal, public Zburator, public Inotator {
public:
  Rata() : Animal("Rata"), Zburator(10.0), Inotator(5.0) {
    culoarePene = "Nedefinita";
  }

  Rata(const string& c) : Animal("Rata"), Zburator(15.0), Inotator(8.0) {
    culoarePene = c;
  }

  void afiseazaDetalii() const {
    afiseazaSpecie();
    afiseazaZbor();
    afiseazaInot();
    cout << ", Culoare: " << culoarePene << '\n';
  }

private:
  string culoarePene;
};

int main() {
  AnimalDublu liliac("Liliac", 50.0, 0.0);
  liliac.afiseazaInfo();

  AnimalDublu pinguin("Pinguin", 0.0, 15.0);
  pinguin.afiseazaInfo();

  Rata rataSalbatica("Maro-Verde");
  rataSalbatica.afiseazaDetalii();

  Rata rataDefault;
  rataDefault.afiseazaDetalii();

  return 0;
}