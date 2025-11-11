#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class City {
public:
  virtual void displayInfo() const = 0;
  virtual void calculateArea() = 0;
  virtual void celebrateFestival() const = 0;

  virtual void setName(const string& cityName) {
    name = cityName;
  }

protected:
  string name;
  double area;
};

class SquareCity : public City {
public:
  SquareCity(const string& cityName, double side, int pop) {
    name = cityName;
    sideLength = side;
    population = pop;
    area = sideLength * sideLength;
  }

  void displayInfo() const override {
    cout << "Square City: " << name << ", Area: " << area << ", Population: " << population << '\n';
  }

  void calculateArea() override {
    area = sideLength * sideLength;
  }

  void celebrateFestival() const override {
    cout << name << " is celebrating the Square Festival!\n";
  }

  void setPopulation(int pop) {
    population = pop;
  }

  void setSideLength(double side) {
    sideLength = side;
  }

private:
  double sideLength;
  int population;
};

class CircularCity : public City {
public:
  CircularCity(const string& cityName, double rad, int bridges) {
    name = cityName;
    radius = rad;
    area = M_PI * radius * radius;
    numberOfBridges = bridges;
  }

  void displayInfo() const override {
    cout << "Circular City: " << name << ", Area: " << area << ", Number of Bridges: " << numberOfBridges << '\n';
  }

  void calculateArea() override {
    area = M_PI * radius * radius;
  }

  void celebrateFestival() const override {
    cout << name << " is celebrating the Circular Festival!\n";
  }

  void setNumberOfBridges(int bridges) {
    numberOfBridges = bridges;
  }

  void setRadius(double rad) {
    radius = rad;
  }

private:
  double radius;
  int numberOfBridges;
};

class StarCity : public City {
public:
  StarCity(const string& cityName, double armLen, int wheels, int doors) {
    name = cityName;
    armLength = armLen;
    numberOfWheels = wheels;
    numberOfDoors = doors;
    area = (5.0 / 2.0) * armLength * armLength * sin(72 * M_PI / 180);
  }

  void displayInfo() const override {
    cout << "Star City: " << name << ", Area: " << area << ", Wheels: " << numberOfWheels << ", Doors: " << numberOfDoors << '\n';
  }

  void calculateArea() override {
    area = (5.0 / 2.0) * armLength * armLength * sin(72 * M_PI / 180);
  }

  void celebrateFestival() const override {
    cout << name << " is celebrating the Star Festival!\n";
  }

  void compareWheelsAndDoors() const {
    if(numberOfWheels > numberOfDoors) {
      cout << name << " has more wheels than doors.\n";
    } else if(numberOfWheels < numberOfDoors) {
      cout << name << " has more doors than wheels.\n";
    } else {
      cout << name << " has an equal number of wheels and doors.\n";
    }
  }

  void setNumberOfWheels(int wheels) {
    numberOfWheels = wheels;
  }

  void setNumberOfDoors(int doors) {
    numberOfDoors = doors;
  }

private:
  double armLength;
  int numberOfWheels;
  int numberOfDoors;
};

int main() {
  SquareCity squareCity("SquareVille", 4.0, 1000);
  CircularCity circularCity("CircleTown", 3.0, 12);
  StarCity starCity("StarCity", 2.0, 7'043'212, 3'912'784);

  squareCity.displayInfo();
  squareCity.celebrateFestival();
  cout << '\n';

  circularCity.displayInfo();
  circularCity.celebrateFestival();
  cout << '\n';

  starCity.displayInfo();
  starCity.celebrateFestival();
  starCity.compareWheelsAndDoors();

  return 0;
}