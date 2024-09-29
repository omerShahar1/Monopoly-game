#ifndef GOTOJAILSLOT_HPP
#define GOTOJAILSLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class GoToJailSlot : public Slot {
public:
    GoToJailSlot();
    void performAction(Player& player) override;
    void display() const override;
};

#endif
