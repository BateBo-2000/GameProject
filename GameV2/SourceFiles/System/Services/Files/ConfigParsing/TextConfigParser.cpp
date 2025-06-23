#include "../../HeaderFiles/System/Services/ConfigParsing/TextConfigParser.h"

#include "../../HeaderFiles/ConfigDataStruct.h"
#include "../../HeaderFiles/Util/Split.h"

void ConfigParser::parse(const std::string& fileContents, ConfigData& data) {
    std::vector<std::string>  lines = split(fileContents, '\n');

	for (size_t i = 0; i < lines.size(); i++)
	{
		if (lines[i].starts_with("SETTINGS:")) {
			data.settings.push_back(lines[i]);
		}
		else if (lines[i].starts_with("ARMOR:")) {
			data.armors.push_back(lines[i]);
		}
		else if (lines[i].starts_with("ABILITY:")) {
			data.abilities.push_back(lines[i]);
		}
		else if (lines[i].starts_with("UNIT:")) {
			data.units.push_back(lines[i]);
		}
		else if (lines[i].starts_with("COMMANDER:")) {
			data.units.push_back(lines[i]);
		}
		else {
			data.unknown.push_back(lines[i]);
		}
	}
	
}

