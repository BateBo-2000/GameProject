#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/GameState.h"

#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/IBaseSate.h"
#include "../../HeaderFiles/System/Services/Registries/Unit/IUnitRegistry.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include <stdexcept>


GameState::GameState(const EngineConfig& cfg, IBaseState* livingBase, IBaseState* undeadBase)
    : livingBase(livingBase)
    , undeadBase(undeadBase)
    , config(cfg)
    , currentStage(DuelStage::Completed)
    , livingTurnIndex(0)
    , undeadTurnIndex(0)

{
    if (!livingBase || !undeadBase) throw std::invalid_argument("BaseStates cannot be null.");
}

GameState::GameState(std::istream& in, IUnitRegistry& units, IBaseState* livingBase, IBaseState* undeadBase, const EngineConfig& cfg): livingBase(livingBase), undeadBase(undeadBase), config(cfg), currentStage(DuelStage::Completed)
{
    throw std::exception("Not implemented.");

}

GameState::~GameState()
{
    for (size_t i = 0; i < livingTeam.size(); i++)
    {
        delete livingTeam[i];
    }
    for (size_t i = 0; i < undeadTeam.size(); i++)
    {
        delete undeadTeam[i];
    }
    delete livingBase;
    delete undeadBase;
}

IBaseState& GameState::getLivingBase() {
    return *livingBase;
}
const IBaseState& GameState::getLivingBase() const {
    return *livingBase;
}


IBaseState& GameState::getUndeadBase() {
    return *undeadBase;
}
const IBaseState& GameState::getUndeadBase() const {
    return *undeadBase;
}

const EngineConfig& GameState::getConfig() const {
    return config;
}

size_t GameState::countAllUnits() const {
    size_t total = 0;
    total += livingBase->getUnitCount();
    total += livingBase->getCommanderCount();
    total += undeadBase->getUnitCount();
    total += undeadBase->getCommanderCount();
    return total;
}

DuelStage GameState::getStage() const
{
    return currentStage;
}

void GameState::setStage(DuelStage stage) {
    currentStage = stage;
}

const std::vector<IUnit*>& GameState::getLivingTeam() const {
    return livingTeam;
}

std::vector<IUnit*>& GameState::getLivingTeam() {
    return livingTeam;  //TODO proxy
}

const std::vector<IUnit*>& GameState::getUndeadTeam() const
{
    return undeadTeam;
}

std::vector<IUnit*>& GameState::getUndeadTeam()
{
    return undeadTeam; //TODO proxy
}

size_t GameState::getLivingTurnIndex() const
{
    return livingTurnIndex;
}

void GameState::LivingTurnIndexIncrement()
{
    if (livingTurnIndex + 1 >= livingTeam.size()) {
        resetLivingTurnIndex();
    }
    else {
        livingTurnIndex++;
    }
}

void GameState::resetLivingTurnIndex()
{
    livingTurnIndex = 0;
}


size_t GameState::getUndeadTurnIndex() const
{
    return undeadTurnIndex;
}

void GameState::UndeadTurnIndexIncrement()
{
    if (undeadTurnIndex + 1 >= undeadTeam.size()) {
        resetUndeadTurnIndex();
    }
    else {
        undeadTurnIndex++;
    }
}

void GameState::resetUndeadTurnIndex()
{
    undeadTurnIndex = 0;
}

void GameState::serialize(std::ofstream& out) const
{
    throw std::exception("Not implemented.");
}

