#pragma once
#ifndef ARMOR_H
#define ARMOR_H

#include "IArmor.h"
#include <string>

class Armor : public IArmor {
public:
    Armor(std::string name, int defense);
    Armor* clone() const override;

    const std::string& getName() const override;
    unsigned getDefense() const override;
    unsigned getDurability() const override;

    void setDurability(unsigned dur) override;
    
    void use() override;
    unsigned calculateMitigatedDamage(unsigned rawDamage) const override;
private:
    std::string name;
    unsigned defensePercentage;
    unsigned usesLeft;
};

#endif // ARMOR_H
