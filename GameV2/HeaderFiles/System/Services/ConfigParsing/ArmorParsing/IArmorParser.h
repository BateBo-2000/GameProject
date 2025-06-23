#pragma once
#ifndef I_ARMOR_PARSER_H
#define I_ARMOR_PARSER_H

#include <string>

class IArmor;

class IArmorParser {
public:
    virtual ~IArmorParser() = default;
    //if anything happens returns nullptr;
    virtual IArmor* parse(const std::string& line) = 0;
};

#endif // I_ARMOR_PARSER_H