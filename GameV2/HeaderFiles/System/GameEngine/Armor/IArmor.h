#pragma once
#ifndef IARMOR_H
#define IARMOR_H

#include <string>

class IArmor {
public:
    virtual ~IArmor() = default;
    virtual IArmor* clone() const = 0;

    virtual const std::string& getName() const = 0;
    virtual unsigned getDefense() const = 0;
    virtual unsigned getDurability() const = 0;

    virtual void setDurability(unsigned dur) = 0;

    virtual void use() = 0;
    virtual unsigned calculateMitigatedDamage(unsigned rawDamage) const = 0;
};

#endif // IARMOR_H