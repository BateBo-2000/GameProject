#include "../../HeaderFiles/System/Services/SaveLoadFiles/BinaryGameSaveFileHandler.h"

#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"

#include <fstream>

void BinaryGameSaveFileHandler::saveToFile(const std::string& path, const IGameState& state) {
    throw std::runtime_error("Still not implemented.");
}

void BinaryGameSaveFileHandler::loadFromFile(const std::string& path, IGameState& state) {
    throw std::runtime_error("Still not implemented.");
}