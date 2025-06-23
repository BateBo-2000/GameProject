#include "../../HeaderFiles/System/Services/ConfigParsing/SettingsParsing/SettingParser.h"

#include "../../HeaderFiles/Util/Split.h"
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/EngineConfig.h"

#include <stdexcept>

const EngineConfig* SettingsParser::parse(const std::vector<std::string>& lines) const {
    EngineConfig* cfg = new EngineConfig;  //really uncomfortable but trying to be consistent with the other parsers.

	try
	{
        for (size_t i = 0; i < lines.size(); ++i) {
            std::vector<std::string> lineArgs = split(lines[i], ' ');

            if (lineArgs.size() != 3) throw std::invalid_argument("All game settigns have exactly 3 fields.");
            if (lineArgs[0] != "SETTINGS:") continue;

            if (lineArgs[1] == "starting_gold_living") {
                cfg->startingGoldLiving = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "starting_gold_undead") {
                cfg->startingGoldUndead = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "health_regen_per_round") {
                cfg->healthRegenPerRound = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "mana_regen_per_round") {
                cfg->manaRegenPerRound = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "unit_limit") {
                cfg->maxAliveUnits = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "max_commander") {
                cfg->maxCommanders = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "gold_per_win") {
                cfg->goldPerWin = std::stoul(lineArgs[2]);
            }
            else if (lineArgs[1] == "duelsToWin") {
                cfg->duelsToWin = std::stoul(lineArgs[2]);
            }
            else continue;
        }

        return cfg;
	}
	catch (const std::exception&)
	{
        delete cfg;
        return nullptr;
	}
}
