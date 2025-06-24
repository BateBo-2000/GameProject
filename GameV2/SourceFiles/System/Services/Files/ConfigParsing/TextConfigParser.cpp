#include "../../HeaderFiles/System/Services/ConfigParsing/TextConfigParser.h"

#include "../../HeaderFiles/ConfigDataStruct.h"
#include "../../HeaderFiles/Util/Split.h"

void ConfigParser::parse(const std::string& fileContents, ConfigData& data) {
    std::vector<std::string>  lines = split(fileContents, '\n');

	for (size_t i = 0; i < lines.size(); i++)
	{

		const std::string& raw = lines[i];
		size_t pos = raw.find_first_not_of(' ');
		if (pos == std::string::npos)
			continue;

		std::string line = raw.substr(pos);

		if (line.starts_with("#")) {
			continue; //comments
		}
		if (line.starts_with("SETTINGS:")) {
			data.settings.push_back(line);
		}
		else if (line.starts_with("ARMOR:")) {
			data.armors.push_back(line);
		}
		else if (line.starts_with("ABILITY:")) {
			data.abilities.push_back(line);
		}
		else if (line.starts_with("UNIT:")) {
			data.units.push_back(line);
		}
		else if (line.starts_with("COMMANDER:")) {
			data.units.push_back(line);
		}
		else {
			data.unknown.push_back(line);
		}
	}
	
}

