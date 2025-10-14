#include <stdio.h>
#include <string>

using namespace std;

class Motorbike {
private:
  string brand;
  string model;
  int year;
  double engineCC;

public:
  Motorbike();
  Motorbike(string brand, string model, int year, double engineCC);
  Motorbike(string brand, string model);
  Motorbike(string brand);

  void displayInfo();
};

Motorbike::Motorbike() {
  brand = "Unknown";
  model = "Unknown";
  year = 0;
  engineCC = 0.0;
}

Motorbike::Motorbike(string brand, string model, int year, double engineCC) {
  this->brand = brand;
  this->model = model;
  this->year = year;
  this->engineCC = engineCC;
}

Motorbike::Motorbike(string brand, string model) {
  this->brand = brand;
  this->model = model;
  year = 0;
  engineCC = 0.0;
}

Motorbike::Motorbike(string brand) {
  this->brand = brand;
  model = "Unknown";
  year = 0;
  engineCC = 0.0;
}

void Motorbike::displayInfo() {
  printf("Motorbike Information:\n");
  printf("Brand: %s\n", brand.c_str());
  printf("Model: %s\n", model.c_str());
  printf("Year: %d\n", year);
  printf("Engine CC: %.1f\n\n", engineCC);
}

int main() {
  Motorbike bike1;
  Motorbike bike2("Yamaha", "MT-07", 2023, 689.0);
  Motorbike bike3("Kawasaki", "ZX-6R");
  Motorbike bike4("Ducati");

  bike1.displayInfo();
  bike2.displayInfo();
  bike3.displayInfo();
  bike4.displayInfo();

  return 0;
}