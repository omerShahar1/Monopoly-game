#ifndef SURPRISESLOT_HPP
#define SURPRISESLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class SurpriseSlot : public Slot {
public:
    SurpriseSlot();
    void performAction(Player& player) override;
    void display() const override;
};

#endif
