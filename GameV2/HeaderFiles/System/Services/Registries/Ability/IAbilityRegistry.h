#pragma once
#ifndef I_ABILITY_REGISTRY_H
#define I_ABILITY_REGISTRY_H

#include <string>
class IAbility;

class IAbilityRegistry {
public:
    virtual ~IAbilityRegistry() = default;
    //takes ownership
    virtual void registerPrototype(IAbility* armor) = 0;
    //gives ownership
    virtual IAbility* createByName(const std::string& name) const = 0;
};

#endif // I_ABILITY_REGISTRY_H