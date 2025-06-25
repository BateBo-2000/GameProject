#include "../../HeaderFiles/System/GameEngine/Abilities/SummonAbility.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"
#include <stdexcept>

SummonAbility::SummonAbility(const std::string& name,
    unsigned manaCost,
    const std::string& unitType,
    unsigned count)
    : name(name)
    , manaCost(manaCost)
    , unitType(unitType)
    , count(count)
{
}

IAbility* SummonAbility::clone() const {
    return new SummonAbility(*this);
}

const std::string& SummonAbility::getName() const {
    return name;
}

unsigned SummonAbility::getManaCost() const {
    return manaCost;
}

void SummonAbility::apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx)
{
    if (!user) throw std::invalid_argument(name + ": user is null");

    if (!user->isAlive()) throw std::invalid_argument(name + ": caster is dead");
    user->useMana(manaCost);

    std::vector<IUnit*> buffer;

    for (size_t i = 0; i < count; ++i) {
        IUnit* u = ctx.unitRegistry.createByName(unitType);

        //if something bad happens 
        if (!u) {
            for (size_t j = 0; j < buffer.size(); ++j) {
                delete buffer[j];
            }
            user->regenerateMana(manaCost);
            throw std::runtime_error(name + ": failed to summon " + unitType);
        }

        buffer.push_back(u);
    }

    for (size_t i = 0; i < buffer.size(); ++i) {
        ctx.spawnedUnitsToBeAdded.push_back(buffer[i]);
    }
}
