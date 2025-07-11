#pragma once
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "IGameEngine.h"

class IGameState;
class IUnitRegistry;
struct EngineConfig;
class IGameSaveFileHandler;

enum class InitMode { NewGame, LoadGame };

class GameEngine : public IGameEngine {
public:
    //takes ownership of state
    GameEngine(IUnitRegistry& unitFactory, IGameSaveFileHandler* fileHandler, const std::string& savePath, InitMode mode);
    GameEngine(const GameEngine& other) = delete;
    GameEngine& operator=(const GameEngine& other) = delete;
    ~GameEngine() override;

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

    virtual bool restartWipeTheGame() override;
    virtual bool saveTheGameToFile(const std::string& path) override;
    virtual bool loadTheGameFromFile(const std::string& path) override;

private:
    void goNextTurnOrStageFighting();
    void cleanUpAfterCompletion();

    IUnitRegistry& unitRegister;
    IGameState* gameState;
    IGameSaveFileHandler* fileHandler;
    std::string pathToSaveFile;
};

#endif // GAME_ENGINE_H
