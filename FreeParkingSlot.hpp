#ifndef FREEPARKINGSLOT_HPP
#define FREEPARKINGSLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class FreeParkingSlot : public Slot {
public:
    FreeParkingSlot();
    void performAction(Player& player) override;
    void display() const override;
};

#endif
