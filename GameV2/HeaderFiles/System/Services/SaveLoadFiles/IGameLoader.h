#pragma once
#ifndef I_GAME_STATE_LOADER_H
#define I_GAME_STATE_LOADER_H

#include <string>

class IGameState;

class IGameLoader {
public:
    virtual ~IGameLoader() = default;
    virtual void loadFromFile(const std::string& filepath, IGameState& state) = 0;
};

#endif // I_GAME_STATE_LOADER_H

