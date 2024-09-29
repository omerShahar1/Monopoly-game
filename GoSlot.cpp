#include "GoSlot.hpp"
#include <iostream>

const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";

GoSlot::GoSlot() {}

void GoSlot::performAction(Player& player) {
    std::cout << GREEN << player.getName() << " landed on Go! Collect $200." << RESET << "\n";
    player.receive(200);
}

void GoSlot::display() const {
    std::cout << "🚦 Go Slot (Collect $200 when passing)\n";
}
