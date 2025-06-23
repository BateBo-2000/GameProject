#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "IGameState.h"
#include "../BaseState/IBaseSate.h"

class GameState : public IGameState {
public:
    GameState(const EngineConfig& cfg, IBaseState& livingBase, IBaseState& undeadBase);
    IBaseState& getLivingBase()  override;
    IBaseState& getUndeadBase()  override;
    const EngineConfig& getConfig()   const override;

    size_t countAllUnits() const override;

private:
    IBaseState& livingBase;
    IBaseState& undeadBase;
    EngineConfig config;
};

#endif // GAME_STATE_H