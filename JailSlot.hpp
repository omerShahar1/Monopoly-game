#ifndef JAILSLOT_HPP
#define JAILSLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class JailSlot : public Slot {
public:
    JailSlot();
    void performAction(Player& player) override;
    void display() const override;
};

#endif
