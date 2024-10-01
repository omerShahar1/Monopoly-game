#ifndef UTILITY_HPP
#define UTILITY_HPP

#include "Slot.hpp"
#include "Player.hpp"
#include <string>

class Utility : public Slot {
public:
    Utility(const std::string& name, int price);
    void performAction(Player& player) override;
    void display() const override;
    Player* getOwner() const;

private:
    std::string name;
    int price;
    Player* owner;
};

#endif
