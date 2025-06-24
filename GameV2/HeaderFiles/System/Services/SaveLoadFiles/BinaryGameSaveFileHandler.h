#pragma once
#ifndef BINARY_GAME_SAVE_FILE_HANDLER_H
#define BINARY_GAME_SAVE_FILE_HANDLER_H

#include "../../HeaderFiles/System/Services/SaveLoadFiles/IGameSaveFileHandler.h"

#include <string>

struct EngineConfig;
class IAbilityRegistry;
class IUnitRegistry;
class IArmorRegistry;
class IBaseState;
enum class Faction;

class BinaryGameSaveFileHandler : public IGameSaveFileHandler {
public:
    BinaryGameSaveFileHandler(IUnitRegistry& units, IArmorRegistry& armors, IAbilityRegistry& abilities, EngineConfig const& config);
    ~BinaryGameSaveFileHandler() override = default;

    void saveToFile(const std::string& path, const IGameState* state) override;
    IGameState* loadFromFile(const std::string& path) override;
    IGameState* restartFile(const std::string& path) override;

private:
    IBaseState* createBaseFromScratch(Faction faction) const;

    IUnitRegistry& units;
    IArmorRegistry& armors;
    IAbilityRegistry& abilities;
    EngineConfig const& config;
};

#endif // BINARY_GAME_SAVE_FILE_HANDLER_H
