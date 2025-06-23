#pragma once
#ifndef UNIT_REGISTRY_H
#define UNIT_REGISTRY_H

#include "IUnitRegistry.h"
#include <vector>
#include <string>

class IUnit;

class UnitRegistry : public IUnitRegistry {
public:
    UnitRegistry();
    UnitRegistry(const UnitRegistry& other);
    UnitRegistry& operator=(const UnitRegistry& other);
    ~UnitRegistry() override;


    void registerPrototype(IUnit* unit) override;
    IUnit* createByName(const std::string& name) const override;

private:
    std::vector<IUnit*> prototypes;
    void clear();
};

#endif // UNIT_REGISTRY_H
