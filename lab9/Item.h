#pragma once
#include <iostream>
#include <string>

// INTERN NOTE: Base class for all things in the game
class Item {
protected:
    std::string name;

public:
    Item(std::string n) : name(n) {
        std::cout << "Item constructor: " << name << "\n";
    }

    // TODO: Boss said something about virtual here?
    // But it works fine without it on my machine.
    ~Item() {
        std::cout << "Item destructor: " << name << "\n";
    }

    std::string getName() const { return name; }

    // This should be overridden, right?
    virtual void use() {
        std::cout << "Using a generic item: " << name << "\n";
    }
};

class Sword : public Item {
private:
    int damage;

public:
    Sword(std::string n, int dmg) : Item(n), damage(dmg) {
        std::cout << "Sword constructor\n";
    }

    ~Sword() {
        std::cout << "Sword destructor (Cleaning up blade oil...)\n";
    }

    void use() override {
        std::cout << "Swinging sword " << name << " for " << damage << " damage!\n";
    }
};

class Potion : public Item {
private:
    std::string type; // e.g., "Health", "Mana"

public:
    Potion(std::string n, std::string t) : Item(n), type(t) {
        std::cout << "Potion constructor\n";
    }

    ~Potion() {
        std::cout << "Potion destructor (Glass shattered)\n";
    }

    void use() override {
        std::cout << "Drinking " << type << " potion: " << name << "\n";
    }
};
