#pragma once
#ifndef UNIT_PARSER_H
#define UNIT_PARSER_H

#include "IUnitParser.h"
#include <string>
#include <vector>

class IArmorRegistry;
class IAbilityRegistry;
class IUnit;

/*
    uses armor and ability registries assuming already initialized and working to create armors and abilities for the unit
*/
class UnitParser : public IUnitParser {
public:
    UnitParser(IArmorRegistry& armorReg, IAbilityRegistry& abilityReg);
    IUnit* parse(const std::string& raw) const override;

private:
    IArmorRegistry& armorRegistry;
    IAbilityRegistry& abilityRegistry;

};

#endif // UNIT_PARSER_H
