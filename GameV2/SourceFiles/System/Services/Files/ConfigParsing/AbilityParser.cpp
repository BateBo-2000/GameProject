#include "../../HeaderFiles/System/Services/ConfigParsing/AbilityParsing/AbilityParser.h"

#include"../../HeaderFiles/System/GameEngine/Abilities/DamageAbility.h"
#include"../../HeaderFiles/System/GameEngine/Abilities/HealAbility.h"
#include"../../HeaderFiles/System/GameEngine/Abilities/SummonAbility.h"
#include"../../HeaderFiles/System/GameEngine/Abilities/ResurrectAbilit.h"

#include "../../HeaderFiles/Util/Split.h"


#include <vector>
#include <stdexcept>

IAbility* AbilityParser::parse(const std::string& raw) const {
    std::vector<std::string> args = split(raw, ' ');
    
    /*
        Format: ABILITY: <Abilityargs[1](Damage, Heal, Ressurect, Summon)> <AbilityName(text)> <ManaCost(positive number)>[<Parameter1(positive number)>][<Parameter2>] ...
    */
    
    if (args.size() < 5) return nullptr; 

    if(args[0] != "ABILITY:") return nullptr;

    const std::string& type = args[1];
    const std::string& abilityName = args[2];

    try
    {
        if (type == "Damage" && args.size() >= 5) {
            const std::string& manaStr = args[3];
            const std::string& damageStr = args[4];
            unsigned mana = std::stoul(manaStr);
            unsigned damage = std::stoul(damageStr);
            return new DamageAbility(abilityName, mana, damage);
        }

        if (type == "Heal" && args.size() >= 5) {
            const std::string& manaStr = args[3];
            const std::string& healStr = args[4];
            unsigned mana = std::stoul(manaStr);
            unsigned heal = std::stoul(healStr);
            return new HealAbility(abilityName, mana, heal);
        }

        if (type == "Resurrect" && args.size() >= 6) {
            const std::string& manaStr = args[3];
            const std::string& targetType = args[4];
            const std::string& resultType = args[5];
            unsigned mana = std::stoul(manaStr);
            return new ResurrectAbility(abilityName, mana, targetType, resultType);
        }

        if (type == "Summon" && args.size() >= 6) {
            const std::string& manaStr = args[3];
            const std::string& unitType = args[4];
            const std::string& countStr = args[5];
            unsigned mana = std::stoul(manaStr);
            unsigned count = std::stoul(countStr);
            return new SummonAbility(abilityName, mana, unitType, count);
        }
    }
    catch (const std::exception&)
    {
        return nullptr;
    }

    return nullptr;
}

