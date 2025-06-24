#include "../../HeaderFiles/System/Control/Commands/Other/StatusCmd.h"

#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/EngineConfig.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/BaseState/IBaseSate.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/GameState/IGameState.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/IAbility.h"
#include "../../HeaderFiles/System/GameEngine/Armor/IArmor.h"



const std::string StatusCmd::NAME = "status";
const std::string StatusCmd::DESCRIPTION = "Display detailed information about the game state.";

StatusCmd::StatusCmd(IGameEngine& engine)
    : engine(engine)
{
}

ICommand* StatusCmd::clone() const {
    return new StatusCmd(*this);
}

bool StatusCmd::isThisMe(const std::vector<std::string>& args) const {
    return args.size() == 1 && args[0] == NAME;
}

static std::string stageToString(DuelStage stage) {
    switch (stage) {
    case DuelStage::LivingSetup: return "Living Setup (Pick Team)";
    case DuelStage::UndeadSetup:return "Undead Setup (Pick Team)";
    case DuelStage::UndeadAttack:return "Undead Attacks First";
    case DuelStage::LivingAttack:return "Living Counter-Attack";
    case DuelStage::Completed:return "Duel Completed";
    case DuelStage::GameFinished:return "Game Finished";
    default:return "Unknown Stage";
    }
}

static void printUnits(const std::string& title, const std::vector<IUnit*>& units, IUserInterface& ui) {
    ui.inform("\n--- " + title + " ---");
    for (size_t i = 0; i < units.size(); ++i) {
        const IUnit* u = units[i];
        std::string line = u->getType() + " | HP: " + std::to_string(u->getHealth()) +
            " | ATK: " + std::to_string(u->getAttack()) +
            " | MANA: " + std::to_string(u->getMana());

        const IArmor& armor = u->getArmor();
        line += " | ARMOR: " + armor.getName() +
            " (" + std::to_string(armor.getDefense()) + " def / " +
            std::to_string(armor.getDurability()) + " dur)";

        const std::vector<IAbility*>& abilities = u->getAbilities();
        if (!abilities.empty()) {
            line += " | ABILITIES: ";
            for (size_t j = 0; j < abilities.size(); ++j) {
                const IAbility* ab = abilities[j];
                line += ab->getName() + "(" + std::to_string(ab->getManaCost()) + "mp)";
                if (j + 1 < abilities.size()) line += ", ";
            }
        }

        ui.inform(line);
    }
}

static void printCurrentTurnUnit(const IGameState& state, IUserInterface& ui) {
    DuelStage stage = state.getStage();
    const IUnit* currentUnit = nullptr;

    if (stage == DuelStage::LivingAttack) {
        const std::vector<IUnit*>& team = state.getLivingTeam();
        size_t index = state.getLivingTurnIndex();
        if (index < team.size()) {
            currentUnit = team[index];
        }
    }
    else if (stage == DuelStage::UndeadAttack) {
        const std::vector<IUnit*>& team = state.getUndeadTeam();
        size_t index = state.getUndeadTurnIndex();
        if (index < team.size()) {
            currentUnit = team[index];
        }
    }

    ui.inform("\n--- Current Turn ---");
    if (!currentUnit) {
        ui.inform("No unit currently has the turn.");
        return;
    }

    std::string line = currentUnit->getType() + " | HP: " + std::to_string(currentUnit->getHealth()) +
        " | ATK: " + std::to_string(currentUnit->getAttack()) +
        " | MANA: " + std::to_string(currentUnit->getMana());

    const IArmor& armor = currentUnit->getArmor();
    line += " | ARMOR: " + armor.getName() +
        " (" + std::to_string(armor.getDefense()) + " def / " +
        std::to_string(armor.getDurability()) + " dur)";

    const std::vector<IAbility*>& abilities = currentUnit->getAbilities();
    if (!abilities.empty()) {
        line += " | ABILITIES: ";
        for (size_t j = 0; j < abilities.size(); ++j) {
            const IAbility* ab = abilities[j];
            line += ab->getName() + "(" + std::to_string(ab->getManaCost()) + "mp)";
            if (j + 1 < abilities.size()) line += ", ";
        }
    }

    ui.inform(line);
}



bool StatusCmd::execute(const std::vector<std::string>& args, IUserInterface& ui) const
{
    if (args.size() != 1) {
        ui.error("Usage: status");
        return false;
    }

    const IGameState& state = engine.getGameState();
    const EngineConfig& config = state.getConfig();
    
    // duel stage
    DuelStage stage = state.getStage();
    
    ui.inform("========== GAME STATUS ==========");
    ui.inform("Duel Stage: " + std::string(stageToString(stage)));

    // gold and Wins
    const IBaseState& living = state.getLivingBase();
    const IBaseState& undead = state.getUndeadBase();
    ui.inform("Gold (Living): " + std::to_string(living.getGoldReserve()));
    ui.inform("Gold (Undead): " + std::to_string(undead.getGoldReserve()));
    ui.inform("Wins (Living): " + std::to_string(living.getWins()));
    ui.inform("Wins (Undead): " + std::to_string(undead.getWins()));
    
    printUnits("Living Team", state.getLivingTeam(), ui);
    printUnits("Undead Team", state.getUndeadTeam(), ui);

    ui.inform("=================================");

    printCurrentTurnUnit(state, ui);

    ui.inform("=================================");
    return true;



}

const std::string& StatusCmd::getName() const {
    return NAME;
}

const std::string& StatusCmd::getDescription() const {
    return DESCRIPTION;
}

