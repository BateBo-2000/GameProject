#include "../../HeaderFiles/System/GameEngine/Armor/Armor.h"

Armor::Armor(std::string name, int defense) : name(std::move(name)), defensePercentage(defense), usesLeft(0)
{ }

Armor* Armor::clone() const {
    return new Armor(*this);
}

const std::string& Armor::getName() const {
    return name;
}

unsigned Armor::getDefense() const {
    return usesLeft>0 ? defensePercentage : 0;
}

unsigned Armor::getDurability() const
{
    return usesLeft;
}

void Armor::setDurability(unsigned dur)
{
    usesLeft = dur;
}

void Armor::use()
{
    if (usesLeft > 0) usesLeft--;
}

unsigned Armor::calculateMitigatedDamage(unsigned rawDamage) const
{
    return rawDamage * defensePercentage / 100;
}
