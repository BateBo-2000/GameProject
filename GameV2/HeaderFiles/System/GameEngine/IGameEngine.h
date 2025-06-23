#pragma once
#ifndef I_GAME_ENGINE_H
#define I_GAME_ENGINE_H

#include <string>
#include <vector>

enum class Faction;
class IGameState;

/*
    this is the actual game and everything else is here to support it or use it
 */
class IGameEngine {
public:
    virtual ~IGameEngine() = default;

    // duel preparation
    virtual void create(const std::string& unitType) = 0;
    virtual void selectBoss(const std::string& bossType) = 0;
    virtual void selectUnits(const std::string& unitType, unsigned count) = 0;
    virtual void startDuel() = 0;

    // duel combat
    virtual void skipTurn() = 0;
    virtual void attackTarget(const std::string& targetName) = 0;
    virtual void useAbility(const std::vector<std::string>& targetNames, size_t abilityIndex = 0) = 0;

    // information
    virtual const IGameState& getGameState() const =0;
    virtual IGameState& getGameState() = 0;


    // turns
    virtual Faction getWhoseTurnItIsNow() const = 0;
    virtual bool isGameWon() const = 0;
};


#endif // I_GAME_ENGINE_H