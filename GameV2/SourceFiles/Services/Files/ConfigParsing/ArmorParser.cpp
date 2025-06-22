#include "../../HeaderFiles/System/Services/ConfigParsing/ArmorParsing/ArmorParser.h"

#include "../../HeaderFiles/System/GameEngine/Armor/Armor.h"

#include "../../HeaderFiles/Util/Split.h"
#include <vector>
#include <string>
#include <cstdlib>
//Armor format in config: # Armor - Format: <ArmorName (text)> <MitigationPercentage (positive number 0-100)>


IArmor* ArmorParser::parseLine(const std::string& raw) {
	std::vector<std::string> args = split(raw, ' ');

	if (args.size() != 3) return nullptr;

	const std::string& name = args[1];
	if (name.empty()) return nullptr;

	unsigned short mit;
	try {
		mit = std::stoul(args[2]);
	}
	catch (...) {
		return nullptr;
	}

	return new(std::nothrow) Armor(name, mit);
}