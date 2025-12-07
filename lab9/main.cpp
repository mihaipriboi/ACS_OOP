#include <iostream>
#include "Inventory.h"
#include "MagicBook.h"

// Pass by reference to preserve polymorphism
void inspectItem(Item& i) {
    std::cout << "Inspecting item: " << i.getName() << "\n";
    i.use();
}

void runGameLevel() {
    std::cout << "=== GAME START ===\n";

    Inventory heroInventory;
    heroInventory.addItem(new Sword("Excalibur", 100));
    heroInventory.addItem(new Potion("Healing Potion", "Health"));

    std::cout << "\n[System] Saving game (Copying inventory)...\n";
    Inventory savedInventory = heroInventory; // Deep copy

    heroInventory.listItems();

    std::cout << "\n[System] Inspecting an item...\n";
    if (heroInventory.getItem(0)) {
        inspectItem(*heroInventory.getItem(0));
    }

    // Test MagicBook
    MagicBook book("Grimoire of Doom", 3);
    book.setSpell(0, "Fireball");
    book.setSpell(1, "Ice Spike");
    book.setSpell(2, "Lightning Bolt");
    book.listSpells();

    std::cout << "\n=== GAME OVER (Destructors will be called now) ===\n";
}

int main() {
    try {
        runGameLevel();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
