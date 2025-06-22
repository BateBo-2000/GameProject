#pragma once
#ifndef ARMOR_PARSER_H
#define ARMOR_PARSER_H

#include "IArmorParser.h"
#include <string>
class IArmor;

class ArmorParser : public IArmorParser {
public:
    IArmor* parseLine(const std::string& line) override;
};

#endif // ARMOR_PARSER_H
