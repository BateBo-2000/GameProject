#pragma once
#ifndef I_UNIT_REGISTRY_H
#define I_UNIT_REGISTRY_H

#include <string>
class IUnit;

class IUnitRegistry {
public:
    virtual ~IUnitRegistry() = default;
    virtual void registerPrototype(IUnit* armor) = 0;
    virtual IUnit* createByName(const std::string& name) const = 0;
};

#endif // IUNITREGISTRY_H