#pragma once
#include <iostream>
#include <string>

class Item {
protected:
    std::string name;

public:
    Item(std::string n) : name(n) {
        std::cout << "Item constructor: " << name << "\n";
    }

    virtual ~Item() {
        std::cout << "Item destructor: " << name << "\n";
    }

    std::string getName() const { return name; }

    virtual void use() {
        std::cout << "Using a generic item: " << name << "\n";
    }

    // Pentru deep copy
    virtual Item* clone() const = 0;
};

class Sword : public Item {
private:
    int damage;

public:
    Sword(std::string n, int dmg) : Item(n), damage(dmg) {
        std::cout << "Sword constructor\n";
    }

    ~Sword() override {
        std::cout << "Sword destructor (Cleaning up blade oil...)\n";
    }

    void use() override {
        std::cout << "Swinging sword " << name << " for " << damage << " damage!\n";
    }

    Item* clone() const override {
        return new Sword(*this);
    }
};

class Potion : public Item {
private:
    std::string type;

public:
    Potion(std::string n, std::string t) : Item(n), type(t) {
        std::cout << "Potion constructor\n";
    }

    ~Potion() override {
        std::cout << "Potion destructor (Glass shattered)\n";
    }

    void use() override {
        std::cout << "Drinking " << type << " potion: " << name << "\n";
    }

    Item* clone() const override {
        return new Potion(*this);
    }
};
