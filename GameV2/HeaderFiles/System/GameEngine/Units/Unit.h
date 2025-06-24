#pragma once
#ifndef UNIT_H
#define UNIT_H

#include "IUnit.h"

#include "../Abilities/IAbility.h"
#include "../Armor/IArmor.h"

#include <string>
#include <vector>

class UnitParser;
class UnitRegistry;


class Unit : public IUnit {
public:

    ~Unit() override;

private:

    Unit(std::string type,
        Faction f,
        unsigned health,
        unsigned attack,
        unsigned goldCost,
        IArmor* armor,
        const std::vector<IAbility*>& abilities,
        unsigned mana,
        bool commander = false
    );

    Unit(const Unit& other);
    Unit& operator=(const Unit& other) = delete;
    Unit* clone() const override;

    //only the parser and registry can clone/create.
    friend class UnitParser;
    friend class UnitRegistry;

public:
    const std::string& getType() const override;
    unsigned getHealth() const override;
    unsigned getAttack() const override;
    unsigned getGoldCost() const override;
    bool isCommander() const override;
    Faction getFaction() const override;

    const IArmor& getArmor() const override;

    const std::vector<IAbility*>& getAbilities() const override;

    unsigned getMana() const override;
    void useMana(unsigned mana) override;

    void takeDamage(unsigned rawDamage) override;
    void attack(IUnit& target) override;
    void useAbility(std::vector<IUnit*> targets, BattleContext& ctx, size_t abilityIndex = 0) override;

    bool isAlive() const override;
    void regenerateHealth(unsigned amount) override;
    void regenerateMana(unsigned amount) override;

    virtual void serialize(std::ostream& out) const override;

private:
    std::string type;
    const unsigned maxHealth;
    unsigned health;
    unsigned attackDmg;
    unsigned goldCost;
    IArmor* armor;
    std::vector<IAbility*> abilities;
    const unsigned maxMana;
    unsigned mana;
    bool commander;
    Faction faction;
};

#endif // UNIT_H