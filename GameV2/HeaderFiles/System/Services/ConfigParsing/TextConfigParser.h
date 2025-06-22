#pragma once
#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H


#include "../../HeaderFiles/ConfigDataStruct.h"  
#include "ICongifgParser.h"

#include <string>

class ConfigParser : public IConfigParser {
public:
    void parse(const std::string& fileContents, ConfigData& data);
    void operator()(const std::string& fileContents, ConfigData& data) {
        return parse(fileContents, data);
    }
};

#endif // CONFIG_PARSER_H
