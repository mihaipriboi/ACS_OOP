#pragma once
#include <iostream>
#include <string>

class MagicBook {
private:
    std::string title;
    std::string* spells;
    int spellCount;

public:
    MagicBook(std::string t, int count) : title(t), spellCount(count) {
        spells = new std::string[spellCount];
        std::cout << "MagicBook constructor: " << title << "\n";
    }

    ~MagicBook() {
        delete[] spells;
        std::cout << "MagicBook destructor: " << title << "\n";
    }

    // Copy constructor
    MagicBook(const MagicBook& other) : title(other.title), spellCount(other.spellCount) {
        spells = new std::string[spellCount];
        for (int i = 0; i < spellCount; i++) spells[i] = other.spells[i];
    }

    // Copy assignment
    MagicBook& operator=(const MagicBook& other) {
        if (this != &other) {
            delete[] spells;
            title = other.title;
            spellCount = other.spellCount;
            spells = new std::string[spellCount];
            for (int i = 0; i < spellCount; i++) spells[i] = other.spells[i];
        }
        return *this;
    }

    void setSpell(int index, const std::string& spell) {
        if (index >= 0 && index < spellCount) spells[index] = spell;
    }

    void listSpells() const {
        std::cout << "MagicBook: " << title << "\n";
        for (int i = 0; i < spellCount; i++) {
            std::cout << "- " << spells[i] << "\n";
        }
    }
};
