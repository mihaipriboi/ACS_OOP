#include <iostream>
#include <string>

using namespace std;

class iLogger {
public:
  virtual void logMessage(string msg) = 0;
};

class Dispozitiv {
public:
  string getNume() {
    return numeDispozitiv;
  }

  virtual bool esteConectat() = 0;

protected:
  string numeDispozitiv;
};

class Imprimanta : public iLogger, public Dispozitiv {
public:
  Imprimanta(string nume) {
    numeDispozitiv = nume;
    conectat = false;
  }

  void conectare() {
    conectat = true;
    logMessage("Imprimanta este acum conectata.");
  }

  void deconectare() {
    conectat = false;
    logMessage("Imprimanta a fost deconectata.");
  }

  void logMessage(string msg) override {
    cout << "[LOG " << numeDispozitiv << "]: " << msg << "\n";
  }

  bool esteConectat() override {
    return conectat;
  }

private:
  bool conectat;
};

int main() {
  Imprimanta hp("HP LaserJet");

  cout << "Nume dispozitiv: " << hp.getNume() << "\n";

  if(!hp.esteConectat())
    cout << "Dispozitivul nu este conectat.\n";

  hp.conectare();

  if(hp.esteConectat())
    cout << "Dispozitivul este acum conectat.\n";

  hp.logMessage("Se printeaza un document test.");
  hp.deconectare();

  return 0;
}