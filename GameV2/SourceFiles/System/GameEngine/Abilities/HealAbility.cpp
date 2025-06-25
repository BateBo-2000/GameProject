#include "../../HeaderFiles/System/GameEngine/Abilities/HealAbility.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

#include <stdexcept>

HealAbility::HealAbility(const std::string& name,
    unsigned manaCost,
    unsigned healAmount)
    : name(name)
    , manaCost(manaCost)
    , healAmount(healAmount)
{
}

IAbility* HealAbility::clone() const {
    return new HealAbility(*this);
}

const std::string& HealAbility::getName() const {
    return name;
}

unsigned HealAbility::getManaCost() const {
    return manaCost;
}

void HealAbility::apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx)
{
    if (!user) throw std::invalid_argument(name + ": user is null");

    if (targets.size() < 1) throw std::invalid_argument(name + ": requires exactly one target, got " + std::to_string(targets.size()));

    if (!targets[0]) throw std::invalid_argument(name + ": target is undefined");

    if (user->getFaction() != targets[0]->getFaction()) throw std::invalid_argument(name + ": cannot heal enemy units");

    if (!targets[0]->isAlive()) throw std::invalid_argument(name + ": target is dead");
    if (!user->isAlive()) throw std::invalid_argument(name + ": caster is dead");

    user->useMana(manaCost);

    targets[0]->regenerateHealth(healAmount);
}
