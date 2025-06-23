#pragma once
#ifndef I_ARMOR_REGISTRY_H
#define I_ARMOR_REGISTRY_H

#include <string>

class IArmor;

class IArmorRegistry {
public:
    virtual ~IArmorRegistry() = default;
    //takes ownership
    virtual void registerPrototype(IArmor* armor) = 0;
    //gives ownership
    virtual IArmor* createByName(const std::string& name, unsigned durability) const = 0;
};

#endif // I_ARMOR_REGISTRY_H
