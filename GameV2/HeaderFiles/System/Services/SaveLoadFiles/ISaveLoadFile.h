#pragma once
#ifndef I_GAMESTATE_PERSISTENCE_H
#define I_GAMESTATE_PERSISTENCE_H

#include "IGameLoader.h"
#include "IGameSaverFile.h"

class IGamePersistence : public IGameSaver, public IGameLoader {
public:
    virtual ~IGamePersistence() = default;
};

#endif // I_GAMESTATE_PERSISTENCE_H