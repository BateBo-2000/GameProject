#pragma once
#ifndef CONFIG_DATA_STUCT_H
#define CONFIG_DATA_STUCT_H

#include <vector>
#include <string>

struct ConfigData {
	std::vector<std::string> armors;
	std::vector<std::string> abilities;
	std::vector<std::string> units;
	std::vector<std::string> settings;
    std::vector<std::string> unknown;
};

#endif // !CONFIG_DATA_STUCT_H
