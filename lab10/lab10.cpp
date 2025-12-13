#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

/*
Sursa informatii:
- https://cplusplus.com
- https://stackoverflow.com
*/

// 1.

class Avion {
public:
  virtual ~Avion() {}
  virtual void descriere() const = 0;
};

class AvionCalatori : public Avion {
public:
  void descriere() const override {
    cout << "Avion de calatori - Boeing\n";
  }
};

class AvionLupta : public Avion {
public:
  void descriere() const override {
    cout << "Avion de lupta - F16\n";
  }
};

class AvionTransport : public Avion {
public:
  void descriere() const override {
    cout << "Avion de transport - Cargo\n";
  }
};

class AvionFactory {
public:
  static Avion* createAvion(const string& tip) {
    if(tip == "calatori") return new AvionCalatori();
    if(tip == "lupta") return new AvionLupta();
    if(tip == "transport") return new AvionTransport();
    return nullptr;
  }
};

/*
PROS:
- separa crearea obiectelor de utilizare
- cod extensibil
- reduce dependentele

CONS:
- mai multe clase
- complexitate mai mare
*/


// 2.

class Pizza {
public:
  string blat;
  string sos;
  vector<string> toppinguri;

  void afisare() const {
    cout << "Pizza:\n";
    cout << " Blat: " << blat << "\n";
    cout << " Sos: " << sos << "\n";
    cout << " Toppinguri: ";
    for(auto& t : toppinguri)
      cout << t << " ";
    cout << "\n\n";
  }
};

class PizzaBuilder {
public:
  virtual ~PizzaBuilder() {}
  virtual void setBlat() = 0;
  virtual void setSos() = 0;
  virtual void addTopping() = 0;
  virtual Pizza getPizza() = 0;
};

class MargheritaBuilder : public PizzaBuilder {
public:
  MargheritaBuilder() { p = Pizza(); }

  void setBlat() override { p.blat = "subtire"; }
  void setSos() override { p.sos = "rosii"; }
  void addTopping() override {
    p.toppinguri.push_back("mozzarella");
    p.toppinguri.push_back("busuioc");
  }

  Pizza getPizza() override { return p; }
private:
  Pizza p;
};

class QuattroStagioniBuilder : public PizzaBuilder {
public:
  QuattroStagioniBuilder() { p = Pizza(); }

  void setBlat() override { p.blat = "pufos"; }
  void setSos() override { p.sos = "rosii"; }
  void addTopping() override {
    p.toppinguri.push_back("sunca");
    p.toppinguri.push_back("ciuperci");
    p.toppinguri.push_back("masline");
    p.toppinguri.push_back("anghinare");
  }

  Pizza getPizza() override { return p; }
private:
  Pizza p;
};

class PizzaDirector {
public:
  void buildPizza(PizzaBuilder& builder) {
    builder.setBlat();
    builder.setSos();
    builder.addTopping();
  }
};

/*
PROS:
- control pas cu pas
- usor de creat obiecte complexe
- permite configuratii custom

CONS:
- multe clase
- cod mai lung
*/


// 3.

class Logger {
public:
  static Logger& getInstance() {
    if(instance == nullptr) {
      instance = new Logger();
    }
    return *const_cast<Logger*>(instance);
  }

  void log(const string& mesaj) {
    cout << "[LOG] " << mesaj << "\n";
  }
 
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

private:
  static volatile Logger* instance;

  Logger() {
    cout << "Sistemul de Jurnalizare a pornit.\n";
  }
};

volatile Logger* Logger::instance = nullptr;

/*
PROS Singleton:
- un singur punct de acces
- economie de memorie
- control total asupra instantei

CONS Singleton:
- greu de testat
- dependenta globala
- poate deveni anti-pattern
*/


int main() {
  cout << "--- 1. FACTORY ---\n";
  Avion* a1 = AvionFactory::createAvion("calatori");
  Avion* a2 = AvionFactory::createAvion("lupta");
  Avion* a3 = AvionFactory::createAvion("transport");

  a1->descriere();
  a2->descriere();
  a3->descriere();

  delete a1;
  delete a2;
  delete a3;

  cout << "\n--- 2. BUILDER ---\n";
  PizzaDirector director;

  MargheritaBuilder m;
  director.buildPizza(m);
  Pizza p1 = m.getPizza();
  p1.afisare();

  QuattroStagioniBuilder q;
  director.buildPizza(q);
  Pizza p2 = q.getPizza();
  p2.afisare();

  cout << "--- 3. SINGLETON ---\n";

  // Logger l; // EROARE DE COMPILARE

  Logger& log1 = Logger::getInstance();
  Logger& log2 = Logger::getInstance();

  log1.log("Salut din prima referinta");
  log2.log("Salut din a doua referinta");

  cout << &log1 << " vs " << &log2 << "\n";

  return 0;
}
