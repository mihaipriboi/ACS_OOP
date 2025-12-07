#pragma once
#include <vector>
#include <iostream>
#include "Item.h"

class Inventory {
private:
    std::vector<Item*> items;

public:
    Inventory() {
        std::cout << "Inventory created (Empty)\n";
    }

    // Copy constructor (deep copy)
    Inventory(const Inventory& other) {
        std::cout << "Inventory copy constructor (Deep Copy)\n";
        for (auto i : other.items) {
            items.push_back(i->clone());
        }
    }

    // Copy assignment (deep copy)
    Inventory& operator=(const Inventory& other) {
        if (this != &other) {
            for (auto i : items) delete i;
            items.clear();
            for (auto i : other.items) {
                items.push_back(i->clone());
            }
        }
        return *this;
    }

    ~Inventory() {
        std::cout << "Inventory destructor: Cleaning up " << items.size() << " items...\n";
        for (auto i : items) delete i;
        items.clear();
    }

    void addItem(Item* item) {
        items.push_back(item);
    }

    void listItems() const {
        std::cout << "\n--- Inventory Contents ---\n";
        for (auto item : items) {
            std::cout << "- " << item->getName() << "\n";
        }
        std::cout << "--------------------------\n";
    }

    Item* getItem(int index) {
    if (index >= 0 && static_cast<size_t>(index) < items.size())
        return items[index];
    return nullptr;
}
};
