#include "Utility.hpp"
#include <iostream>

Utility::Utility(const std::string& name, int price) : name(name), price(price), owner(nullptr) {}

void Utility::performAction(Player& player) {
    if (owner == nullptr) {
        if (player.getMoney() >= price) {
            std::cout << "Do you want to buy " << name << " for " << price << "? (y/n): ";
            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                player.pay(price);
                owner = &player;
                std::cout << player.getName() << " bought " << name << "!\n";
                player.addProperty(this);
            }
        }
    } else if (owner != &player) {
        int rentDue = (rand() % 6 + 1) * 10;  // Random roll of one die times 10
        std::cout << player.getName() << " landed on " << owner->getName() << "'s utility and must pay rent of " << rentDue << ".\n";
        player.pay(rentDue, owner);
    } else {
        std::cout << player.getName() << " landed on their own utility.\n";
    }
}

void Utility::display() const { // how it will be printed
    if (owner) {
        std::cout << name << " - Owned by " << owner->getName() << ", Price: " << price << "\n";
    } else {
        std::cout << name << " - Price: " << price << "\n";
    }
}

Player* Utility::getOwner() const { //retuen owner name
    return owner;
}

std::string Utility::getName() const {
    return name;
}