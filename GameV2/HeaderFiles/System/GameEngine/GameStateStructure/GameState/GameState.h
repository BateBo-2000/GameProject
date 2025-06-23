#pragma once
#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "IGameState.h"
#include <vector>

class IUnit;
class IBaseState;

class GameState : public IGameState {
public:
    GameState(const EngineConfig& cfg, IBaseState& livingBase, IBaseState& undeadBase);
    ~GameState() override;
    IBaseState& getLivingBase()  override;
    IBaseState& getUndeadBase()  override;

    const EngineConfig& getConfig()   const override;

    size_t countAllUnits() const override;
    
    DuelStage getStage() const override;
    void setStage(DuelStage stage) override;

    //duel units chosen for duel
    const std::vector<IUnit*>& getLivingTeam() const override;
    std::vector<IUnit*>& getLivingTeam() override;
    const std::vector<IUnit*>& getUndeadTeam() const override;
    std::vector<IUnit*>& getUndeadTeam() override;

    //who from living team has to act next
    size_t getLivingTurnIndex() const override;
    void LivingTurnIndexIncrement() override;
    void resetLivingTurnIndex() override;

    //who from undead team has to act next
    size_t getUndeadTurnIndex() const override;
    void UndeadTurnIndexIncrement() override;
    void resetUndeadTurnIndex() override;

private:
    IBaseState& livingBase;
    IBaseState& undeadBase;
    const EngineConfig& config;
    DuelStage currentStage;

    //owning them
    std::vector<IUnit*> livingTeam;
    std::vector<IUnit*> undeadTeam;
    //tracking how many of the team have passed this turn
    size_t livingTurnIndex = 0;
    size_t undeadTurnIndex = 0;
};

#endif // GAME_STATE_H