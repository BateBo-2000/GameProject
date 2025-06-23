#pragma once
#ifndef BASE_STATE_H
#define BASE_STATE_H

#include <vector>
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/IBaseSate.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"

class BaseState : public IBaseState {
public:
    BaseState(unsigned maxCommandersPerType);
    BaseState(const BaseState& other) = delete;
    BaseState& operator=(const BaseState& other) = delete ;
    ~BaseState() override;

    unsigned getGoldReserve() const override;
    void setGoldReserve(unsigned gold) override;

    unsigned getWins() const override;
    void win() override;

    const std::vector<IUnit*>& getUnits() const override;
    std::vector<IUnit*>& getUnits() override;
    void addUnit(IUnit* u) override;
    //removes its pointer
    void removeUnit(IUnit* u) override;
    IUnit* getUnit(size_t index) override;
    size_t getUnitCount() const override;

    const std::vector<IUnit*>& getCommanders() const override;
    std::vector<IUnit*>& getCommanders() override;
    void addCommander(IUnit* c) override;
    //removes its pointer
    void removeCommander(IUnit* c) override;
    IUnit* getCommander(size_t index) override;
    size_t getCommanderCount() const override;

private:
    const size_t MAX_COMMANDERS_FROM_THE_SAME_TYPE;

    /*
        TODO MAKE A PROXY FOR THE NON CONST RETURNING - in the future
    */
    

    unsigned goldReserve = 0;
    unsigned wins = 0;
    std::vector<IUnit*> units;
    std::vector<IUnit*> commanders;
};

#endif // BASE_STATE_H