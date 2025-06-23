#pragma once
#ifndef SETTINGS_PARSER_H
#define SETTINGS_PARSER_H

#include "ISettingParser.h"

class SettingsParser : public ISettingsParser {
public:
    const EngineConfig* parse(const std::vector<std::string>& lines) const override;
};

#endif // SETTINGS_PARSER_H