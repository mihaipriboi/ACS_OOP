#include <iostream>
#include "Inventory.h"

// A helper function to simulate "inspecting" an item
// BUG ALERT: Pass by value causes slicing!
void inspectItem(Item i) {
    std::cout << "Inspecting item: " << i.getName() << "\n";
    // Even if 'i' was a Sword, here it's just an Item.
    // The polymorphic behavior is lost.
}

void runGameLevel() {
    std::cout << "=== GAME START ===\n";

    // 1. Create original inventory
    Inventory heroInventory;
    heroInventory.addItem(new Sword("Excalibur", 100));
    heroInventory.addItem(new Potion("Healing Potion", "Health"));

    // 2. The Bug Trigger: Copying the inventory
    // Since we didn't write a copy constructor, this does a SHALLOW COPY.
    // Both inventories now point to the SAME memory addresses on the heap.
    std::cout << "\n[System] Saving game (Copying inventory)...\n";
    Inventory savedInventory = heroInventory;

    heroInventory.listItems();

    // 3. Testing Slicing
    std::cout << "\n[System] Inspecting an item...\n";
    // We are passing a Sword object, but the function takes 'Item' by value
    if (heroInventory.getItem(0)) {
        inspectItem(*heroInventory.getItem(0));
    }

    std::cout << "\n=== GAME OVER (Destructors will be called now) ===\n";
    
    // CRASH EXPECTED HERE:
    // 1. 'savedInventory' goes out of scope first. It deletes the pointers (Sword, Potion).
    // 2. 'heroInventory' goes out of scope next. It tries to delete THE SAME pointers.
    // -> Double Free Error -> Crash!
}

int main() {
    try {
        runGameLevel();
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}
