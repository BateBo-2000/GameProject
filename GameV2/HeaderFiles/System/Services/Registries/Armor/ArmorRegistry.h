#pragma once
#ifndef ARMOR_REGISTRY_H
#define ARMOR_REGISTRY_H

#include "IArmorRegistry.h"

#include <vector>
#include <string>

class IArmor;

class ArmorRegistry : public IArmorRegistry {
public:
    ArmorRegistry();
    ArmorRegistry(const ArmorRegistry& other);
    ArmorRegistry& operator=(const ArmorRegistry& other);
    ~ArmorRegistry() override;

    void registerPrototype(IArmor* armor) override;
    IArmor* createByName(const std::string& name, unsigned durability) const override;

private:
    std::vector<IArmor*> prototypes;

    void clear();
};

#endif // ARMOR_REGISTRY_H
