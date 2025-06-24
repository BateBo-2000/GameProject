#pragma once
#ifndef I_GAME_STATE_H
#define I_GAME_STATE_H

#include "../EngineConfig.h"

#include <vector>
#include <fstream>

enum class DuelStage {
    LivingSetup,   // Living picks team for duel
    UndeadSetup,   // Undead picks team
    UndeadAttack,  // Undead initial attack
    LivingAttack, // Living counter-attack
    Completed,      // Duel finished
    GameFinished
};

class IBaseState;
class IUnit;

class IGameState {
public:
    virtual ~IGameState() = default;

    //access bases
    virtual IBaseState& getLivingBase() = 0;
    virtual const IBaseState& getLivingBase() const = 0;
    virtual IBaseState& getUndeadBase() = 0;
    virtual const IBaseState& getUndeadBase() const = 0;

    //game settings
    virtual const EngineConfig& getConfig() const = 0;

    // all units in the game
    virtual size_t countAllUnits() const = 0;

    //duel stage
    virtual DuelStage getStage() const = 0;
    virtual void setStage(DuelStage stage) = 0;

    //duel units chosen for duel
    virtual const std::vector<IUnit*>& getLivingTeam() const = 0;
    virtual std::vector<IUnit*>& getLivingTeam() = 0;
    virtual const std::vector<IUnit*>& getUndeadTeam() const =0;
    virtual std::vector<IUnit*>& getUndeadTeam() =0;

    //who from living team has to act next
    virtual size_t getLivingTurnIndex() const = 0;
    virtual void LivingTurnIndexIncrement() = 0;
    virtual void resetLivingTurnIndex() = 0;

    //who from undead team has to act next
    virtual size_t getUndeadTurnIndex() const = 0;
    virtual void UndeadTurnIndexIncrement() = 0;
    virtual void resetUndeadTurnIndex() = 0;
    
    //data
    virtual void serialize(std::ofstream& out) const = 0;
};

#endif // I_GAME_STATE_H
