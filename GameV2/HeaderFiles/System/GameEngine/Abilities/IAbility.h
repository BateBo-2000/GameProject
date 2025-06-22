#pragma once
#ifndef I_ABILITY_H
#define I_ABILITY_H

#include <string>
#include <vector>
class IUnit;
struct BattleContext;

class IAbility {
public:
    virtual ~IAbility() = default;

    virtual IAbility* clone() const = 0;

    virtual const std::string& getName()    const = 0;
    virtual unsigned getManaCost() const = 0;   

    virtual void apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx) = 0;
};

#endif // I_ABILITY_H
