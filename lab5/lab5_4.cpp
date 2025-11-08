#include <iostream>
#include <string>

using namespace std;

class Animal {
public:
  Animal() {}

  virtual void sound() const {
    cout << "Every animal has a specific sound\n";
  }
};

class Cat : public Animal {
public:
  Cat() {}

  void sond() const override {
    cout << "Meow\n";
  }
};

class Dog : public Animal {
public:
  Dog() {}

  void sound() const override {
    cout << "Woof\n";
  }
};

int main() {
  Animal unknown;
  Cat kitty;
  Dog doggy;

  unknown.sound();
  kitty.sound();
  doggy.sound();
  
  kitty.Animal::sound();
  doggy.Animal::sound();

  return 0;
}