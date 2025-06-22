#pragma once
#ifndef ICONFIGPARSER_H
#define ICONFIGPARSER_H

struct ConfigData;
#include <string>

class IConfigParser {
public:
    virtual ~IConfigParser() = default;
    virtual void parse(const std::string& fileContents, ConfigData& outData) = 0;
};

#endif // ICONFIGPARSER_H
