#include "../../HeaderFiles/System/Control/Commands/Combat/UseAbilityCmd.h"

#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/System/GameEngine/IGameEngine.h"

UseAbilityCmd::UseAbilityCmd(IGameEngine& engine, IUserInterface& ui)
    : engine(engine), ui(ui)
{
}

ICommand* UseAbilityCmd::clone() const {
    return new UseAbilityCmd(engine, ui);
}

bool UseAbilityCmd::isThisMe(const std::vector<std::string>& args) const {
    return args.size()>2 && args[0] == "use" && args[0] == "ability";
}

bool UseAbilityCmd::execute(const std::vector<std::string>& args) const {
    if (args.size() < 2) {
        ui.error("Usage: use ability <abilityIndex> [<target1>] [<target2> ...]");
        return false;
    }


    size_t idx;

    try {
        idx = std::stoul(args[2]);
    }
    catch (...) {
        ui.error("Invalid ability index: " + args[2]);
        return false;
    }


    std::vector<std::string> targets;
    for (size_t i = 3; i < args.size(); i++)
    {
        targets.push_back(args[i]);
    }

    try {
        engine.useAbility(targets,idx);
        ui.inform("Used ability on " + std::to_string(targets.size()) + " target(s).");
        return true;
    }
    catch (const std::exception& ex) {
        ui.error("Ability failed: " + std::string(ex.what()));
        return false;
    }
}

const std::string& UseAbilityCmd::getName() const {
    return NAME;
}

const std::string& UseAbilityCmd::getDescription() const {
    return DESCRIPTION;
}

const std::string UseAbilityCmd::NAME = "use ability";
const std::string UseAbilityCmd::DESCRIPTION =
"Use an ability on one or more targets: use ability <abilityIndex> [<target1>] [<target2> ...]";