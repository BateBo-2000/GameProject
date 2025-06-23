#pragma once
#ifndef ABILITY_PARSER_H
#define ABILITY_PARSER_H

#include "IAbilityParser.h"
class IAbility;

#include <string>


/*
    Simple Paraser that just creates an ability from text line.
*/
class AbilityParser : public IAbilityParser {
public:
    IAbility* parse(const std::string& raw) const override;
};

#endif // ABILITY_PARSER_H