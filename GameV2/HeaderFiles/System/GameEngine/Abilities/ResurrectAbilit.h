#pragma once
#ifndef RESURRECT_ABILITY_H
#define RESURRECT_ABILITY_H

#include "IAbility.h"

class ResurrectAbility : public IAbility {
public:
    ResurrectAbility(const std::string& name,
        unsigned manaCost,
        const std::string& targetType,
        const std::string& resultType
        );

    IAbility* clone() const override;
    const std::string& getName() const override;
    unsigned getManaCost() const override;
    void apply(IUnit* user, const std::vector<IUnit*>& targets, BattleContext& ctx) override;

private:
    std::string name;
    unsigned manaCost;
    std::string targetType;
    std::string resultType;
};

#endif // RESURRECTABILITY_H