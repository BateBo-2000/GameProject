#pragma once
#ifndef I_ABILITY_PARSER_H
#define I_ABILITY_PARSER_H

#include <string>
class IAbility;

class IAbilityParser {
public:
    virtual ~IAbilityParser() = default;

    virtual IAbility* parse(const std::string& raw) const = 0;
};

#endif // I_ABILITY_PARSER_H