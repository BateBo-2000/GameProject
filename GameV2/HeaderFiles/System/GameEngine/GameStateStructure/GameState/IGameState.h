#pragma once
#ifndef I_GAME_STATE_H
#define I_GAME_STATE_H

#include "../EngineConfig.h"

class IBaseState;

class IGameState {
public:
    virtual ~IGameState() = default;

    //access bases
    virtual IBaseState& getLivingBase() = 0;
    virtual IBaseState& getUndeadBase() = 0;

    //game settings
    virtual const EngineConfig& getConfig() const = 0;

    // all units in the game
    virtual size_t countAllUnits() const = 0;
};

#endif // I_GAME_STATE_H
