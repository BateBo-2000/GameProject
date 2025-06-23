#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/BaseState.h"

#include <stdexcept>

BaseState::BaseState(unsigned maxCommandersPerType):MAX_COMMANDERS_FROM_THE_SAME_TYPE(maxCommandersPerType)
{
}

BaseState::~BaseState() {
    for (size_t i = 0; i < units.size(); ++i) {
        delete units[i];
    }
    for (size_t i = 0; i < commanders.size(); ++i) {
        delete commanders[i];
    }
}

unsigned BaseState::getGoldReserve() const {
    return goldReserve;
}

void BaseState::setGoldReserve(unsigned gold) {
    goldReserve = gold;
}

unsigned BaseState::getWins() const {
    return wins;
}

void BaseState::win() {
    wins ++;
}

const std::vector<IUnit*>& BaseState::getUnits() const {
    return units; 
}

std::vector<IUnit*>& BaseState::getUnits() {
    return units; //TODO proxy
}

void BaseState::addUnit(IUnit* u) {
    units.push_back(u);
}

void BaseState::removeUnit(IUnit* u) {
    for (size_t i = 0; i < units.size(); ++i) {
        if (units[i] == u) { //compares teh ptrs
            units.erase(units.begin() + i);
            return;
        }
    }
}

IUnit* BaseState::getUnit(size_t index) {
    if (index >= units.size()) throw std::out_of_range("Unit index out of range");
    return units[index]; //TODO proxy
}

size_t BaseState::getUnitCount() const {
    return units.size();
}

const std::vector<IUnit*>& BaseState::getCommanders() const {
    return commanders; 
}

std::vector<IUnit*>& BaseState::getCommanders() {
    return commanders; //TODO proxy
}

void BaseState::addCommander(IUnit* c) {
    commanders.push_back(c);
}

void BaseState::removeCommander(IUnit* c) {
    for (size_t i = 0; i < commanders.size(); ++i) {
        if (commanders[i] == c) {   //compares the pointers
            commanders.erase(commanders.begin() + i);
            return;
        }
    }
}

IUnit* BaseState::getCommander(size_t index) {
    if (index >= commanders.size()) throw std::out_of_range("Commander index out of range");
    return commanders[index]; //TODO proxy
}

size_t BaseState::getCommanderCount() const {
    return commanders.size();
}
