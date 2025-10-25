#include <iostream>
#include <string>

using namespace std;

class ContBancar {
public:
  enum RetragereStatus {
    SUCCES = 0,
    FONDURI_INSUFICIENTE = 1
  };

  static void seteazaRataDobanda(double rataNoua);

  ContBancar(const string& titular, double soldInitial)
            : titularCont(titular), sold(soldInitial) {}

  void depune(double suma);
  RetragereStatus retrage(double suma);

  void aplicaDobanda();

  const string& getTitular() const;
  double getSold() const;

private:
  static double rataDobanda;

  string titularCont;
  double sold;
};

double ContBancar::rataDobanda = 0.0;

void ContBancar::seteazaRataDobanda(double rataNoua) {
  rataDobanda = rataNoua;
}

void ContBancar::depune(double suma) {
  sold += suma;
}

ContBancar::RetragereStatus ContBancar::retrage(double suma) {
  if(suma > sold) {
    return FONDURI_INSUFICIENTE;
  }

  sold -= suma;
  return SUCCES;
}

void ContBancar::aplicaDobanda() {
  sold += sold * rataDobanda;
}

const string& ContBancar::getTitular() const {
  return titularCont;
}

double ContBancar::getSold() const {
  return sold;
}

int main() {
  ContBancar cont1("Liviu", 1000.0);
  ContBancar cont2("Adrian", 2000.0);

  cout << "Sold initial cont1: " << cont1.getSold() << '\n';
  cout << "Sold initial cont2: " << cont2.getSold() << '\n';

  cont1.depune(500.0);
  cout << "Sold cont1 dupa depunere: " << cont1.getSold() << '\n';

  switch(cont2.retrage(2500.0)) {
    case ContBancar::SUCCES:
      cout << "Retragere cu succes din cont2.\n";
      break;
    case ContBancar::FONDURI_INSUFICIENTE:
      cout << "Fonduri insuficiente pentru retragere din cont2.\n";
      break;
  }
  cout << "Sold cont2 dupa tentativa de retragere: " << cont2.getSold() << '\n';

  switch(cont2.retrage(1500.0)) {
    case ContBancar::SUCCES:
      cout << "Retragere cu succes din cont2.\n";
      break;
    case ContBancar::FONDURI_INSUFICIENTE:
      cout << "Fonduri insuficiente pentru retragere din cont2.\n";
      break;
  }
  cout << "Sold cont2 dupa tentativa de retragere: " << cont2.getSold() << '\n';

  ContBancar::seteazaRataDobanda(0.07);

  cont1.aplicaDobanda();
  cont2.aplicaDobanda();

  cout << "Sold cont1 dupa aplicarea dobanzii: " << cont1.getSold() << '\n';
  cout << "Sold cont2 dupa aplicarea dobanzii: " << cont2.getSold() << '\n';

  return 0;
}