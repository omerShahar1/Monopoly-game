#include "SurpriseSlot.hpp"
#include <iostream>
#include <cstdlib>

SurpriseSlot::SurpriseSlot() {}

void SurpriseSlot::performAction(Player& player) {
    int surprise = rand() % 3;
    switch (surprise) {
        case 0:
            std::cout << player.getName() << " found a surprise and got a Get Out of Jail Free card!\n";
            // Implement Get Out of Jail logic if necessary
            break;
        case 1:
            std::cout << player.getName() << " found a surprise and received 200!\n";
            player.receive(200);
            break;
        case 2:
            std::cout << player.getName() << " found a surprise and must pay 100!\n";
            player.pay(100);
            break;
    }
}

void SurpriseSlot::display() const {
    std::cout << "Surprise Slot (Chance or Community Chest)\n";
}
