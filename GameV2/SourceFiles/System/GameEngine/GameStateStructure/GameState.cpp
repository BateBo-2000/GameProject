#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/GameState.h"

GameState::GameState(const EngineConfig& cfg, IBaseState& livingBase, IBaseState& undeadBase)
    : livingBase(livingBase)
    , undeadBase(undeadBase)
    , config(cfg)
{
}

IBaseState& GameState::getLivingBase() {
    return livingBase;
}

IBaseState& GameState::getUndeadBase() {
    return undeadBase;
}

const EngineConfig& GameState::getConfig() const {
    return config;
}

size_t GameState::countAllUnits() const {
    size_t total = 0;
    total += livingBase.getUnitCount();
    total += livingBase.getCommanderCount();
    total += undeadBase.getUnitCount();
    total += undeadBase.getCommanderCount();
    return total;
}
