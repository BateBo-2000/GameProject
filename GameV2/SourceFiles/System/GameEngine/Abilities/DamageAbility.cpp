#include "../../HeaderFiles/System/GameEngine/Abilities/DamageAbility.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

#include <stdexcept>

DamageAbility::DamageAbility(const std::string& name,
    unsigned manaCost,
    unsigned damage)
    : name(name)
    , manaCost(manaCost)
    , damage(damage)
{
}

IAbility* DamageAbility::clone() const {
    return new DamageAbility(*this);
}

const std::string& DamageAbility::getName() const {
    return name;
}

unsigned DamageAbility::getManaCost() const {
    return manaCost;
}

void DamageAbility::apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx)
{
    if (!user) throw std::invalid_argument(name + ": user is null");

    if (targets.size() != 1) throw std::invalid_argument( name + ": requires exactly one target, got " + std::to_string(targets.size()));
    
    if (!targets[0]) throw std::invalid_argument(name + ": target is undefined");

    if(user->getFaction() == targets[0]->getFaction()) throw std::invalid_argument(name + ": friendly fire not tolerated");
    
    if(!targets[0]->isAlive()) throw std::invalid_argument(name + ": target already dead");

    user->useMana(manaCost);

    targets[0]->takeDamage(damage);
}