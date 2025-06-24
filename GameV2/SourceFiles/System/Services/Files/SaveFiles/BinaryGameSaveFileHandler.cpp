#include "../../HeaderFiles/System/Services/SaveLoadFiles/BinaryGameSaveFileHandler.h"

#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"

#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/BaseState.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/GameState.h"

#include "../../HeaderFiles/System/Faction.h"

#include <stdexcept>
#include <fstream>

BinaryGameSaveFileHandler::BinaryGameSaveFileHandler(IUnitRegistry& units, IArmorRegistry& armors, IAbilityRegistry& abilities, EngineConfig const& config)
    : units(units), armors(armors), abilities(abilities), config(config)
{
}

void BinaryGameSaveFileHandler::saveToFile(const std::string& path, const IGameState* state) {
    throw std::exception("Not implemented.");
}

IGameState* BinaryGameSaveFileHandler::loadFromFile(const std::string& path) {
    throw std::exception("Not implemented.");
}

IGameState*  BinaryGameSaveFileHandler::restartFile(const std::string& path)
{
    IBaseState* living = nullptr;
    IBaseState* undead = nullptr;
    try {

        living = createBaseFromScratch(Faction::Living);
        undead = createBaseFromScratch(Faction::Undead);

        IGameState* game = new GameState(config, living, undead);

        //DELETE FROM FILE
        return game;
    }
    catch (...) {
        delete living;
        delete undead;
        throw;
    }
}

IBaseState* BinaryGameSaveFileHandler::createBaseFromScratch(Faction faction) const
{
    unsigned maxCommanders = config.maxCommanders;
    unsigned startGold = 0;


    switch (faction) {
    case Faction::Living:
        startGold = config.startingGoldLiving;
        break;
    case Faction::Undead:
        startGold = config.startingGoldUndead;
        break;
    default:
        throw std::invalid_argument("Unknown faction in BaseStateBuilder");
    }

    BaseState* base = new(std::nothrow) BaseState(maxCommanders, startGold);
    base->setGoldReserve(startGold);

    return base;
}