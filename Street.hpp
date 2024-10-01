#ifndef STREET_HPP
#define STREET_HPP

#include "Slot.hpp"
#include "Player.hpp"
#include <string>

class Street : public Slot {
public:
    Street(const std::string& name, const std::string& color, int price, int rent, int housePrice, int hotelPrice);

    void performAction(Player& player) override;
    void display() const override;
    
    std::string getColor() const;
    std::string getName() const;
    Player* getOwner() const;
    bool get_hasHotel();

    // New methods for building houses and accessing house count
    void buildHouse();  // Allows building houses on this street
    int getHouses() const;  // Returns the current number of houses

private:
    std::string name;
    std::string color;
    int price;
    int rent;
    int housePrice;
    int hotelPrice;
    int houses;  // Track the number of houses
    bool hasHotel;
    Player* owner;
};

#endif
