#pragma once
#ifndef I_GAMESTATE_SAVER_H
#define I_GAMESTATE_SAVER_H

#include <string>

class IGameState;

class IGameSaver {
public:
    virtual ~IGameSaver() = default;
    virtual void saveToFile(const std::string& filepath, const IGameState& state) = 0;
};

#endif // I_GAMESTATE_SAVER_H