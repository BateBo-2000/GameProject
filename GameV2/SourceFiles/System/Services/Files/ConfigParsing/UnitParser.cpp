#include "../../HeaderFiles/System/Services/ConfigParsing/UnitParsing/UnitParser.h"

#include "../../HeaderFiles/Util/Split.h"

#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
#include "../../HeaderFiles/System/GameEngine/Units/Unit.h"

#include "../../HeaderFiles/System/Services/Registries/Armor/IArmorRegistry.h"
#include "../../HeaderFiles/System/Services/Registries/Ability/IAbilityRegistry.h"

#include <stdexcept>

UnitParser::UnitParser(IArmorRegistry& armorReg, IAbilityRegistry& abilityReg)
    : armorRegistry(armorReg)
    , abilityRegistry(abilityReg)
{
}




IUnit* UnitParser::parse(const std::string& raw) const {
    // split by space
    std::vector<std::string> args = split(raw, ' ');

    // Format: prefix, type, faction, health, attack, gold, armorType, armorDur, [mana] , [Ability]

    if (args.size() < 8)  return nullptr;
        
    const std::string& prefix = args[0];
    bool isCommander = prefix == "COMMANDER:";

    const std::string& type = args[1];
    const std::string& faction = args[2];
    const std::string& armorName = args[4];

    unsigned health, attack, goldCost, armorDurability, mana = 0;

    bool hasAbilities;

    try {
        health = std::stoul(args[3]);
        attack = std::stoul(args[6]);
        goldCost = std::stoul(args[7]);
        armorDurability = std::stoul(args[5]);
        if (args.size() > 8) {
            mana = std::stoul(args[8]);
        }
    }
    catch (...) {
        return nullptr;
    }

    /*
        args with index 9 and so on are ability names
    */
    hasAbilities = (mana != 0 && args.size() > 9);
    std::vector<IAbility*> abilities;

    IArmor* armor = nullptr;

    try {
        //armor
        armor = armorRegistry.createByName(armorName, armorDurability);
        if (!armor)
            throw std::invalid_argument("Unknown armor: " + armorName);

        // abilities
        if (hasAbilities) {
            for (size_t i = 9; i < args.size(); ++i) {
                IAbility* ab = abilityRegistry.createByName(args[i]);
                if (!ab)
                    throw std::invalid_argument("Unknown ability: " + args[i]);
                abilities.push_back(ab);
            }
        }

        // construct unit
        IUnit* unit = new Unit(type,
            (faction == "Undead" ? Faction::Undead : Faction::Living),
            health,
            attack,
            goldCost,
            armor,
            abilities,
            mana,
            isCommander);
        return unit;
    }
    catch (...) {
        // cleanup on any failure
        delete armor;

        for (size_t i = 0; i < abilities.size(); ++i) {
                delete abilities[i];
        }

        return nullptr;
    }
}
