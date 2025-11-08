#include <iostream>
#include <string>

using namespace std;

class Baza {
public:
  void metodaPublica() {
    cout << "Apel Baza::metodaPublica" << '\n';
  }

protected:
  void metodaProtected() {
    cout << "Apel Baza::metodaProtected" << '\n';
  }

private:
  void metodaPrivata() {
    cout << "Apel Baza::metodaPrivata" << '\n';
  }
};

class DerivataProtected : protected Baza {
public:
  void testAccesInterior() {
    cout << "\n--- In DerivataProtected::testAccesInterior ---" << '\n';

    // Apelul 1: Public in Baza, devine protected in DerivataProtected
    metodaPublica();

    // Apelul 2: Protected in Baza, ramane protected in DerivataProtected
    metodaProtected();

    // Apelul 3: Privat in Baza, inaccesibil
    // metodaPrivata(); // Eroare de compilare

    cout << "--- Sfarsit DerivataProtected::testAccesInterior ---" << '\n';
  }
};

class DerivataPrivata : private Baza {
public:
  void testAccesInterior() {
    cout << "\n--- In DerivataPrivata::testAccesInterior ---" << '\n';

    // Apelul 1: Public in Baza, devine private in DerivataPrivata
    metodaPublica();

    // Apelul 2: Protected in Baza, devine private in DerivataPrivata
    metodaProtected();

    // Apelul 3: Privat in Baza, inaccesibil
    // metodaPrivata(); // Eroare de compilare

    cout << "--- Sfarsit DerivataPrivata::testAccesInterior ---" << '\n';
  }
};

int main() {
  cout << "--- Test Main ---" << '\n';

  DerivataProtected objProt;
  // Apel direct din exterior (main)

  // objProt.metodaPublica(); // Eroare de compilare

  objProt.testAccesInterior();

  DerivataPrivata objPriv;
  // Apel direct din exterior (main)

  // objPriv.metodaPublica(); // Eroare de compilare

  objPriv.testAccesInterior();

  return 0;
}