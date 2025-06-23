#include "../../HeaderFiles/System/GameEngine/Abilities/ResurrectAbilit.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

#include <stdexcept>

ResurrectAbility::ResurrectAbility(const std::string& name,
    unsigned manaCost,
    const std::string& targetType,
    const std::string& resultType)
    : name(name)
    , manaCost(manaCost)
    , targetType(targetType)
    , resultType(resultType)
{
}

IAbility* ResurrectAbility::clone() const {
    return new ResurrectAbility(*this);
}

const std::string& ResurrectAbility::getName() const {
    return name;
}

unsigned ResurrectAbility::getManaCost() const {
    return manaCost;
}

void ResurrectAbility::apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx)
{
    if (!user) throw std::invalid_argument(name + ": user is null");

    if (targets.size() != 1) throw std::invalid_argument(name + ": requires exactly one target, got " + std::to_string(targets.size()));

    if (!targets[0]) throw std::invalid_argument(name + ": target is undefined");

    if (user->getFaction() == targets[0]->getFaction()) throw std::invalid_argument(name + ": cannot resurrect from the same faction");

    if (targets[0]->isAlive()) throw std::invalid_argument(name + ": target is not dead");

    if (targets[0]->getType() != targetType) throw std::invalid_argument(name + ": can only work on " + targetType);

    user->useMana(manaCost);

    IUnit* newUnit = ctx.unitRegistry.createByName(resultType);

    if (!newUnit) {
        user->regenerateMana(manaCost);
        throw std::runtime_error(name + ": Something went wrong while resurrecting " + targetType + " to " + resultType);
    }

    ctx.spawnedUnitsToBeAdded.push_back(newUnit);
}
