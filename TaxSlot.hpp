#ifndef TAXSLOT_HPP
#define TAXSLOT_HPP

#include "Slot.hpp"
#include "Player.hpp"

class TaxSlot : public Slot {
public:
    TaxSlot(int amount);
    void performAction(Player& player) override;
    void display() const override;

private:
    int amount;
};

#endif
