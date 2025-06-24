#include "../../HeaderFiles/System/GameEngine/GameEngine.h"

#include "../../HeaderFiles/System/Services/Registries/Unit/IUnitRegistry.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/EngineConfig.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/IBaseSate.h"

#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/IAbility.h"
#include "../../HeaderFiles/System/GameEngine/Armor/IArmor.h"

#include "../../HeaderFiles/System/Services/Registries/Unit/UnitRegistry.h"
#include "../../HeaderFiles/System/Services/SaveLoadFiles/IGameSaveFileHandler.h"

#include <stdexcept>

GameEngine::GameEngine(IUnitRegistry& unitRegistry, IGameSaveFileHandler* fileHandler, const std::string& savePath, InitMode mode)
    : unitRegister(unitRegistry), gameState(nullptr), fileHandler(fileHandler), pathToSaveFile(savePath)
{
    if (mode == InitMode::NewGame) {
        if (!restartWipeTheGame()) throw std::runtime_error("GameEngine: failed to create default game state from");
    }
    else {
        if (!loadTheGameFromFile(pathToSaveFile)) {
            throw std::runtime_error("GameEngine: failed to load game from " + pathToSaveFile);
        }
    }
}

GameEngine::~GameEngine()
{
    delete gameState;
    delete fileHandler;
}

void GameEngine::create(const std::string& unitType) {
    DuelStage stage = gameState->getStage();

    if (stage != DuelStage::LivingSetup && stage != DuelStage::UndeadSetup) {
        throw std::runtime_error("Cannot create unit in current stage");
    }
    IUnit* unit = unitRegister.createByName(unitType);

    if (!unit) throw std::runtime_error("Unknown unit type: " + unitType);

    if (stage == DuelStage::LivingSetup && unit->getFaction() != Faction::Living) {
        delete unit;
        throw std::invalid_argument("Living faction can only create living units.");
    }

    if (stage == DuelStage::UndeadSetup && unit->getFaction() != Faction::Undead) {
        delete unit;
        throw std::invalid_argument("Undead faction can only create undead units.");
    }

    if (stage == DuelStage::LivingSetup) {
        if (unit->isCommander()) {
            gameState->getLivingBase().addCommander(unit);
        }
        else {
            gameState->getLivingBase().addUnit(unit);
        }
    }
    else {
        if (unit->isCommander()) {
            gameState->getUndeadBase().addCommander(unit);
        }
        else {
            gameState->getUndeadBase().addUnit(unit);
        }
        
    }
}

void GameEngine::selectBoss(const std::string& bossType)
{
    DuelStage stage = gameState->getStage();
    if (stage != DuelStage::LivingSetup && stage != DuelStage::UndeadSetup) {
        throw std::runtime_error("Cannot select boss in current stage");
    }

    IBaseState& base = (stage == DuelStage::LivingSetup) ? gameState->getLivingBase() : gameState->getUndeadBase();
    std::vector<IUnit*>& team = (stage == DuelStage::LivingSetup) ? gameState->getLivingTeam(): gameState->getUndeadTeam();

    //searching for it
    IUnit* chosen = nullptr;
    for (size_t i = 0; i < base.getCommanders().size(); ++i) {
        IUnit* cmd = base.getCommanders()[i];
        if (cmd->getType() == bossType) {
            chosen = cmd;
            break;
        }
    }

    if (!chosen) {
        throw std::invalid_argument("No commander of type '" + bossType + "' available");
    }
    

    base.removeCommander(chosen);   //remove from the base put in the team
    team.push_back(chosen);
}

void GameEngine::selectUnits(const std::string& unitType, unsigned count)
{
    DuelStage stage = gameState->getStage();
    if (stage != DuelStage::LivingSetup && stage != DuelStage::UndeadSetup) {
        throw std::runtime_error("Cannot select units in current stage");
    }

    IBaseState& base = (stage == DuelStage::LivingSetup) ? gameState->getLivingBase() : gameState->getUndeadBase();
    std::vector<IUnit*>& team = (stage == DuelStage::LivingSetup) ? gameState->getLivingTeam() : gameState->getUndeadTeam();

    std::vector<IUnit*> matches;
    const std::vector<IUnit*>& available = base.getUnits();
    for (size_t i = 0; i < available.size() && matches.size() < count; ++i) {
        if (available[i]->getType() == unitType) {
            matches.push_back(available[i]);
        }
    }

    if (matches.size() < count) {
        throw std::runtime_error("Not enough units of type: " + unitType);
    }
    
    //remove from base and add to team
    for (size_t i = 0; i < matches.size(); ++i) {
        base.removeUnit(matches[i]);
        team.push_back(matches[i]);
    }
}

void GameEngine::startDuel()
{
    DuelStage stage = gameState->getStage();
    if (stage == DuelStage::LivingSetup) {
        gameState->setStage(DuelStage::UndeadSetup);
        gameState->resetLivingTurnIndex();   //to set it up to 0
    }
    else if (stage == DuelStage::UndeadSetup) {
        gameState->setStage(DuelStage::UndeadAttack);
        gameState->resetUndeadTurnIndex();
    }
    else {
        throw std::runtime_error("Cannot start duel in current stage");
    }
}



void GameEngine::skipTurn() {
    goNextTurnOrStageFighting();
}

void GameEngine::attackTarget(const std::string& targetName)
{
    DuelStage stage = gameState->getStage();
    
    std::vector<IUnit*>* targetTeam = nullptr;;
    IUnit* attacker = nullptr;;

    if (stage == DuelStage::LivingAttack) {

        targetTeam = &gameState->getUndeadTeam();
        attacker = gameState->getLivingTeam()[gameState->getLivingTurnIndex()];

    }else if (stage == DuelStage::UndeadAttack) {
        
        targetTeam = &gameState->getLivingTeam();
        attacker = gameState->getUndeadTeam()[gameState->getUndeadTurnIndex()];
    }
    else {
        throw std::invalid_argument("Cannot attack targets in this stage.");
    }



    for (size_t i = 0; i < targetTeam->size(); i++)
    {
        if ((*targetTeam)[i]->getType() == targetName && (*targetTeam)[i]->isAlive()) {
            attacker->attack((*(*targetTeam)[i])); //not pretty TODO fix
            goNextTurnOrStageFighting();
            return;
        }
    }

    throw std::invalid_argument("Couldn't find any target with name " + targetName + "that is alive");
}


#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

void GameEngine::useAbility(const std::vector<std::string>& targetNames, size_t abilityIndex)
{
    DuelStage stage = gameState->getStage();
    if (stage != DuelStage::UndeadAttack && stage != DuelStage::LivingAttack)
        throw std::invalid_argument("Cannot use ability in this stage.");

    IUnit* caster;
    (stage == DuelStage::UndeadAttack) ? caster =
        gameState->getUndeadTeam()[gameState->getUndeadTurnIndex()]
        : caster = gameState->getLivingTeam()[gameState->getLivingTurnIndex()];

    std::vector<IUnit*> targets;

    //searching in both teams. Abilities know who they should attack or heal.

    for (size_t i = 0; i < targetNames.size(); i++)
    {
        for (size_t j = 0; j < gameState->getLivingTeam().size(); j++)
        {
            if (gameState->getLivingTeam()[i]->getType() == targetNames[i]) {
                targets.push_back(gameState->getLivingTeam()[i]);
            }
        }
        for (size_t j = 0; j < gameState->getUndeadTeam().size(); j++)
        {
            if (gameState->getUndeadTeam()[i]->getType() == targetNames[i]) {
                targets.push_back(gameState->getUndeadTeam()[i]);
            }
        }
    }

    BattleContext cxt(unitRegister);

    caster->useAbility(targets, cxt, abilityIndex); //can throw

    //if the ability wants to summon unit/s it is creating them and the cxt is carrying the ptrs for them
    //here jsut taking ownership
    for (size_t i = 0; i < cxt.spawnedUnitsToBeAdded.size(); i++)   
    {
        try
        {
            if (!cxt.spawnedUnitsToBeAdded[i]) continue;

            if (cxt.spawnedUnitsToBeAdded[i]->getFaction() == Faction::Living) {
                gameState->getLivingTeam().push_back(cxt.spawnedUnitsToBeAdded[i]);
            }
            else {
                gameState->getUndeadTeam().push_back(cxt.spawnedUnitsToBeAdded[i]);
            }
        }
        catch (...)
        {
            //puts in the team whatever gets in leaving it like that so i can add team size limiting logic later 
            delete cxt.spawnedUnitsToBeAdded[i];
            continue;
        }
    }

    goNextTurnOrStageFighting();

    return;
       
}

const IGameState& GameEngine::getGameState() const
{
    return *gameState;
}

IGameState& GameEngine::getGameState()
{
    return *gameState;
}

Faction GameEngine::getWhoseTurnItIsNow() const
{
    DuelStage stage = gameState->getStage();
    if (stage == DuelStage::LivingSetup || stage == DuelStage::LivingAttack)
        return Faction::Living;

    return Faction::Undead;
}

bool GameEngine::isGameWon() const
{
    return gameState->getStage() == DuelStage::GameFinished;
}

bool GameEngine::restartWipeTheGame()
{
    try
    {
        IGameState * temp = fileHandler->restartFile(pathToSaveFile);
        delete gameState;
        gameState = temp;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool GameEngine::saveTheGameToFile(const std::string& path)
{
    if (!path.empty()) {
        pathToSaveFile = path;
    }

    try
    {
        fileHandler->saveToFile(pathToSaveFile, gameState);
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

bool GameEngine::loadTheGameFromFile(const std::string& path)
{
    pathToSaveFile = path; //keeps the last location for other uses

    try
    {
        
        IGameState* temp = fileHandler->loadFromFile(pathToSaveFile);
        delete gameState;
        gameState = temp;
        return true;
    }
    catch (const std::exception&)
    {
        return false;
    }
}

void GameEngine::goNextTurnOrStageFighting()
{
    DuelStage stage = gameState->getStage();

    if (stage == DuelStage::LivingAttack) {
        gameState->LivingTurnIndexIncrement();
        if (gameState->getLivingTurnIndex() == 0)    //it just looped to 0
            if (gameState->getUndeadTeam().size() > 0) {     //if there is enemy to attack its his turn
                gameState->setStage(DuelStage::UndeadAttack);
                return;
            }
            else {          //if no you win
                gameState->setStage(DuelStage::Completed);
                cleanUpAfterCompletion();
                return;
            }
    }

    if (stage == DuelStage::UndeadAttack) {
        gameState->UndeadTurnIndexIncrement();
        if (gameState->getUndeadTurnIndex() == 0)
            if (gameState->getLivingTeam().size() > 0) {
                gameState->setStage(DuelStage::LivingAttack);
                return;
            }
            else {
                gameState->setStage(DuelStage::Completed);
                cleanUpAfterCompletion();
                return;
            }
    }

    if(stage==DuelStage::Completed){
        cleanUpAfterCompletion();
    }

    throw std::invalid_argument("Cannot skip this stage.");
}

void GameEngine::cleanUpAfterCompletion()
{
    if (gameState->getStage() != DuelStage::Completed) return;


    size_t winsNeededForWin = gameState->getConfig().duelsToWin;

    Faction winnerFaction = (gameState->getLivingTeam().size() > gameState->getUndeadTeam().size()) ? Faction::Living : Faction::Undead;
        
    std::vector<IUnit*>& winnerTeam = (winnerFaction == Faction::Living)? gameState->getLivingTeam() : gameState->getUndeadTeam();
    IBaseState& winnerBase = (winnerFaction == Faction::Living) ? gameState->getLivingBase() : gameState->getUndeadBase();
    IBaseState& loserBase = (winnerFaction != Faction::Living) ? gameState->getLivingBase() : gameState->getUndeadBase(); //the reverse
        
    winnerBase.win();

    if (winnerBase.getWins() >= winsNeededForWin) {
        gameState->setStage(DuelStage::GameFinished);
    }
    else {
        gameState->setStage(DuelStage::LivingSetup); //the first stage again
        for (size_t i = 0; i < winnerTeam.size(); i++)
        {
            try
            {
                if (winnerTeam[i]->isAlive())
                    if (winnerTeam[i]->isCommander()) {
                        winnerBase.addCommander(winnerTeam[i]);
                    }
            }
            catch (const std::exception&)
            {
                delete winnerTeam[i];   
                //if it cant add him delete him
            }
        }
        winnerTeam.clear();

        winnerBase.setGoldReserve(winnerBase.getGoldReserve() + gameState->getConfig().goldPerWin);
        loserBase.setGoldReserve(winnerBase.getGoldReserve() + gameState->getConfig().goldPerWin);
    }
}
