#include "Street.hpp"
#include <iostream>

const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string RESET = "\033[0m";

Street::Street(const std::string& name, const std::string& color, int price, int rent, int housePrice, int hotelPrice)
    : name(name), color(color), price(price), rent(rent), housePrice(housePrice), hotelPrice(hotelPrice), houses(0), hasHotel(false), owner(nullptr) {}

void Street::performAction(Player& player) {
    if (owner == nullptr) {
        // Offer the player to buy the street
        std::cout << "Would you like to " << GREEN << "PURCHASE" << RESET << " this street for $" << price << "? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y') 
        {
            if (player.getMoney() >= price) 
            {
                std::cout << player.getName() << " bought " << name << " for $" << price << "\n";
                player.pay(price);
                owner = &player;
                player.addProperty(this);
            }
        }
    } else if (owner != &player) {
        // Pay rent to the owner
        int rentDue = rent;
        if (houses > 0) {
            rentDue *= (houses);  // Increase rent based on the number of houses
        }
        std::cout << player.getName() << " landed on " << name << " and must pay $" << rentDue << " in rent.\n";
        player.pay(rentDue, owner);
    }
}

void Street::buildHouse() {
    if (owner != nullptr && houses < 4 && !hasHotel) {
        std::cout << owner->getName() << " built a house on " << name << " for $" << housePrice << "\n";
        owner->pay(housePrice);
        houses++;
    } else if (houses == 4 && !hasHotel) {
        std::cout << owner->getName() << " built a hotel on " << name << " for $" << (4 * housePrice + hotelPrice) << "\n";
        owner->pay(4 * housePrice + hotelPrice);
        hasHotel = true;
        houses = 0;  // No more houses, now there is a hotel
    }
}

int Street::getHouses() const {
    return houses;
}

bool Street::get_hasHotel()
{
    return hasHotel;
}

std::string Street::getColor() const {
    return color;
}

std::string Street::getName() const {
    return name;
}

Player* Street::getOwner() const {
    return owner;
}

void Street::display() const {
    std::cout << name << " [" << color << "] Price: $" << price << "\n";
}
