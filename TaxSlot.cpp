#include "TaxSlot.hpp"
#include <iostream>

TaxSlot::TaxSlot(int amount) : amount(amount) {}

void TaxSlot::performAction(Player& player) {
    std::cout << player.getName() << " landed on a Tax Slot and must pay " << amount << ".\n";
    player.pay(amount);
}

void TaxSlot::display() const {
    std::cout << "Tax Slot - Pay " << amount << "\n";
}
