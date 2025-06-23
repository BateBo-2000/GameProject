#pragma once
#ifndef I_UNIT_REGISTRY_H
#define I_UNIT_REGISTRY_H

#include <string>
class IUnit;

class IUnitRegistry {
public:
    virtual ~IUnitRegistry() = default;
    //takes ownership
    virtual void registerPrototype(IUnit* armor) = 0;
    //gives ownership
    virtual IUnit* createByName(const std::string& name) const = 0;
};

#endif // I_UNIT_REGISTRY_H