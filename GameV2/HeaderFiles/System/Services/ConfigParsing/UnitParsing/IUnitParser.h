#pragma once
#ifndef I_UNIT_PARSER_H
#define I_UNIT_PARSER_H

#include <string>
class IUnit;

class IUnitParser {
public:
    virtual ~IUnitParser() = default;
    //gives ownership
    virtual IUnit* parse(const std::string& raw) const = 0;
};

#endif // I_UNIT_PARSER_H