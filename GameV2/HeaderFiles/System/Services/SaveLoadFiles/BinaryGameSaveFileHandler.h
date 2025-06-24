#pragma once
#ifndef BINARY_GAME_SAVE_FILE_HANDLER_H
#define BINARY_GAME_SAVE_FILE_HANDLER_H

#include "../../HeaderFiles/System/Services/SaveLoadFiles/IGameSaveFileHandler.h"
#include <string>
#include <fstream>

class BinaryGameSaveFileHandler : public IGameSaveFileHandler {
public:
    ~BinaryGameSaveFileHandler() override = default;

    void saveToFile(const std::string& path, const IGameState& state) override;

    void loadFromFile(const std::string& path, IGameState& state) override;
};

#endif // BINARY_GAME_SAVE_FILE_HANDLER_H
