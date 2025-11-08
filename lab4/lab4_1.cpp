#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Beer {
public:
  Beer() {
    type = "Unknown";
    origin = "Unknown";
  }

  Beer(const string& t, const string& o) {
    type = t;
    origin = o;
  }

  virtual double getLabelArea() const = 0;

  void displayInfo() const {
    cout << "Type: " << getType() << ", Origin: " << getOrigin() 
         << ", Label Area: " << getLabelArea() << "cm^2" << '\n';
  }

  string getType() const {
    return type;
  }

  string getOrigin() const {
    return origin;
  }

protected:
  string type;
  string origin;
};

class BeerTypeA : public Beer {
public:
  BeerTypeA() : Beer(), length(0) {}

  BeerTypeA(const string& t, const string& o, double l) : Beer(t, o), length(l) {}

  double getLabelArea() const {
    return length * length;
  }

private:
  double length;
};

class BeerTypeB : public Beer {
public:
  BeerTypeB() : Beer(), radius(0) {}

  BeerTypeB(const string& t, const string& o, double r) : Beer(t, o), radius(r) {}

  double getLabelArea() const {
    return M_PI * radius * radius;
  }

private:
  double radius;
};

class BeerTypeC : public Beer {
public:
  BeerTypeC() : Beer(), base(0), height(0) {}

  BeerTypeC(const string& t, const string& o, double b, double h) : Beer(t, o), base(b), height(h) {}

  double getLabelArea() const {
    return 0.5 * base * height;
  }

private:
  double base;
  double height;
};

int main() {
  cout.precision(2);
  cout << fixed;

  BeerTypeA beerA("Calsberg", "Denmark", 5.0);
  beerA.displayInfo();

  BeerTypeB beerB("Timisoreana", "Romania", 3.0);
  beerB.displayInfo();

  BeerTypeC beerC("Guinness", "Ireland", 4.0, 6.0);
  beerC.displayInfo();

  return 0;
}