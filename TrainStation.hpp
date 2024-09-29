#ifndef TRAINSTATION_HPP
#define TRAINSTATION_HPP

#include "Slot.hpp"
#include "Player.hpp"

class TrainStation : public Slot {
public:
    TrainStation(int price);
    void performAction(Player& player) override;
    void display() const override;

private:
    int price;
    Player* owner;
};

#endif
