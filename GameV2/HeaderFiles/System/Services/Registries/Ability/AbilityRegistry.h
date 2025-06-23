#pragma once
#ifndef ABILITY_REGISTRY_H
#define ABILITY_REGISTRY_H

#include "IAbilityRegistry.h"
#include <vector>
#include <string>

class IAbility;

class AbilityRegistry : public IAbilityRegistry {
public:
    AbilityRegistry();
    AbilityRegistry(const AbilityRegistry& other);
    AbilityRegistry& operator=(const AbilityRegistry& other);
    ~AbilityRegistry() override;

    void registerPrototype(IAbility* ability) override;
    IAbility* createByName(const std::string& name) const override;

private:
    std::vector<IAbility*> prototypes;

    void clear();
};

#endif // ABILITY_REGISTRY_H