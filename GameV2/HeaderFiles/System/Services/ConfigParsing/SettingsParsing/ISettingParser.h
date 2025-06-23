#pragma once
#ifndef I_SETTINGS_PARSER_H
#define I_SETTINGS_PARSER_H

#include <vector>
#include <string>
struct EngineConfig;

class ISettingsParser {
public:
    virtual ~ISettingsParser() = default;
    virtual const EngineConfig* parse(const std::vector<std::string>& lines) const = 0;
};

#endif // I_SETTINGS_PARSER_H
