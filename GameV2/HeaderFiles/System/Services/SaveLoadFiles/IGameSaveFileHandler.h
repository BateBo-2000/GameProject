#pragma once
#ifndef I_GAME_SAVE_FILE_HANDLER_H
#define I_GAME_SAVE_FILE_HANDLER_H

#include <string>

class IGameState;

class IGameSaveFileHandler {
public:
    virtual ~IGameSaveFileHandler() = default;

    virtual void saveToFile(const std::string& path, const IGameState* state) = 0;
    virtual IGameState* loadFromFile(const std::string& path) = 0;
    virtual IGameState* restartFile(const std::string& path) = 0;
};

#endif // I_GAME_SAVE_FILE_HANDLER_H
