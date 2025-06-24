#pragma once
#ifndef I_BASE_STATE_H
#define I_BASE_STATE_H

#include <vector>
#include <iostream>

class IUnit;

class IBaseState {
public:
    virtual ~IBaseState() = default;

    virtual unsigned getGoldReserve() const = 0;
    virtual void setGoldReserve(unsigned gold) = 0;

    virtual unsigned getWins() const = 0;
    virtual void win() = 0;

    // regular unit
    virtual const std::vector<IUnit*>& getUnits() const = 0;
    virtual std::vector<IUnit*>& getUnits() = 0;
    //takes ownership
    virtual void addUnit(IUnit* u) = 0;
    //untakes ownership
    virtual void removeUnit(IUnit* u) = 0;
    virtual IUnit* getUnit(size_t index) = 0;
    virtual size_t getUnitCount() const = 0;

    //commanders
    virtual const std::vector<IUnit*>& getCommanders() const = 0;
    virtual std::vector<IUnit*>& getCommanders() = 0;
    //takes ownership
    virtual void addCommander(IUnit* c) = 0;
    //untakes ownership
    virtual void removeCommander(IUnit* c) = 0;
    virtual IUnit* getCommander(size_t index) = 0;
    virtual size_t getCommanderCount() const = 0;

    virtual void serialize(std::ostream& out) const = 0;
};

#endif // I_BASE_STATE_H