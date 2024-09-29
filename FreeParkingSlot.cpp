#include "FreeParkingSlot.hpp"
#include <iostream>

const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

FreeParkingSlot::FreeParkingSlot() {}

void FreeParkingSlot::performAction(Player& player) {
    std::cout << YELLOW << player.getName() << " landed on Free Parking! No action required." << RESET << "\n";
}

void FreeParkingSlot::display() const {
    std::cout << "🅿️ Free Parking Slot\n";
}
