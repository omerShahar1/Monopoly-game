#ifndef GOSLOT_HPP
#define GOSLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class GoSlot : public Slot {
public:
    GoSlot();
    void performAction(Player& player) override;
    void display() const override;
};

#endif
