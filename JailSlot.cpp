#include "JailSlot.hpp"
#include <iostream>

JailSlot::JailSlot() {}

void JailSlot::performAction(Player& player) {
    std::cout << player.getName() << " is just visiting jail.\n";
}

void JailSlot::display() const {
    std::cout << "Jail Slot\n";
}
