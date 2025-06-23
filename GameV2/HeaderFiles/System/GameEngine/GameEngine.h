#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "IGameEngine.h"

class IGameState;
class IUnitRegistry;
struct EngineConfig;
class IStatePersistence;

class GameEngine : public IGameEngine {
public:
    GameEngine(IUnitRegistry& unitFactory, const EngineConfig& settings, IGameState& state);
    GameEngine(const GameEngine& other) = delete;
    GameEngine& operator=(const GameEngine& other) = delete;
    ~GameEngine() override = default;

    void create(const std::string& unitType) override;
    void selectBoss(const std::string& bossType) override;
    void selectUnits(const std::string& unitType, unsigned count) override;
    void startDuel() override;

    void skipTurn() override;
    void attackTarget(const std::string& targetName) override;
    void useAbility(const std::vector<std::string>& targetNames, size_t abilityIndex = 0) override;

    virtual const IGameState& getGameState() const override;
    IGameState& getGameState() override;

    Faction getWhoseTurnItIsNow() const override;
    bool isGameWon() const override;

    void restartTheGame() override;

private:
    void goNextTurnOrStageFighting();
    void cleanUpAfterCompletion();

    const EngineConfig& settings;
    IUnitRegistry& unitRegister;
    IGameState& gameState;
};

#endif // GAME_ENGINE_H
