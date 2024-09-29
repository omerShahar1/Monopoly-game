#include "GoToJailSlot.hpp"
#include <iostream>

const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

GoToJailSlot::GoToJailSlot() {}

void GoToJailSlot::performAction(Player& player) {
    std::cout << RED << player.getName() << " is sent to jail!" << RESET << "\n";
    player.goToJail();
}

void GoToJailSlot::display() const {
    std::cout << "🚔 Go to Jail Slot\n";
}
