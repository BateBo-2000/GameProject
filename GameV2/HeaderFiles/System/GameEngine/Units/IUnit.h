#pragma once

#ifndef I_UNIT_H
#define I_UNIT_H


#include <string>
#include <vector>

class IArmor;
class IAbility;
struct BattleContext;

enum class Faction {
    Living,
    Undead
};

class IUnit {
public:
    
    virtual ~IUnit() = default;
    //deep copy
    virtual IUnit* clone() const = 0;

    // identity and stats
    virtual const std::string& getType() const = 0;
    virtual unsigned getHealth() const = 0;
    virtual unsigned getAttack() const = 0;
    virtual unsigned getGoldCost() const = 0;
    virtual bool isCommander() const = 0;
    virtual Faction getFaction() const = 0;
    // armor
    virtual const IArmor& getArmor() const = 0;

    // abilities (0, 1 or many)
    virtual const std::vector<IAbility*>& getAbilities() const = 0;

    //mana
    virtual unsigned getMana() const = 0;
    virtual void useMana(unsigned mana) = 0;

    // combat
    virtual void takeDamage(unsigned rawDamage) = 0;
    virtual void attack(IUnit& target) = 0;
    virtual void useAbility(std::vector<IUnit*> targets, BattleContext& ctx, size_t abilityIndex = 0) = 0;

    virtual bool isAlive() const = 0;
    virtual void regenerateHealth(unsigned amount) = 0;
    virtual void regenerateMana(unsigned amount) = 0;
};

#endif // !IUNIT_H
