#include "../../HeaderFiles/App.h"

//Comunications
#include "../../HeaderFiles/Communication/UI/ConsoleUserInterface.h"
#include "../../HeaderFiles/Communication/Loggers/ConsoleLogger.h"

//Controller
#include "../../HeaderFiles/System/Control/Controller.h"
#include "../../HeaderFiles/System/Control/Commands/ICommand.h"

#include <stdexcept>


App::App()
{
	this->ui = new(std::nothrow) ConsoleUI();
	this->logger = new(std::nothrow) ConsoleLogger();

	if (!ui || !logger) {
		delete ui;
		delete logger;
		throw std::runtime_error("Failed to initialized logger or user interface.");
	}
}

App::~App()
{
	ui->inform("Goodbye cruel world! T_T");
	delete ui;
	delete logger;
}

void App::run()
{
	//Config and run the game engine
}

std::string App::getConfigLocation()
{
	return ui->askQuestion("Enter config file location:");
}

#include "../../HeaderFiles/System/Services/Files/FileReading/BasicFileReader.h"

void App::ReadConfigFile(const std::string& path, std::string& dest)
{
	TextFileReader file(path);
	
	if (!file.readFileContents(dest)) {
		throw std::runtime_error("Something went wrong while reading the configuration file.");
	}
}

#include "../../HeaderFiles/ConfigDataStruct.h"
#include "../../HeaderFiles/System/Services/ConfigParsing/TextConfigParser.h"

void App::ParseConfigFile(const std::string& file, ConfigData& data)
{
	ConfigParser parser;
	parser(file, data);
}

#include "../HeaderFiles/System/Services/ConfigParsing/ArmorParsing/ArmorParser.h"
void App::parseArmors(std::vector<IArmor*>& dest, const std::vector<std::string>& armors)
{
	ArmorParser p;

	IArmor* armor;
	for (size_t i = 0; i < armors.size(); i++)
	{
		armor = p.parse(armors[i]);
		if (!armor) {
			logger->error("Failed to parse armor: " + armors[i]);
			continue;
		}
		else {
			dest.push_back(armor);
		}
	}
}

void App::parseAbilities(std::vector<IAbility*>& dest, const std::vector<std::string>& abilities)
{
	//TODO
}

void App::parseUnits(std::vector<IUnit*>& dest, std::vector<std::string>& units, const IArmorRegistry* armorReg, const IAbilityRegistry* abilityReg)
{
	//TODO
}


#include "../../HeaderFiles/System/Services/Registries/Armor/ArmorRegistry.h"

IArmorRegistry* App::RegisterArmor(const std::vector<std::string>& armorsData)
{
	std::vector<IArmor*> armors;
	parseArmors(armors, armorsData);


	ArmorRegistry reg;

	for (size_t i = 0; i < armors.size(); i++)
	{
		reg.registerPrototype(armors[i]);
	}
	return &reg;
}

IAbilityRegistry* App::RegisterAbilities(const std::vector<std::string>& abilities)
{
	return nullptr;
}

IUnitRegistry* App::RegisterUnits(std::vector<std::string>& units, const IArmorRegistry* armorReg, const IAbilityRegistry* abilityReg)
{
	return nullptr;
}

IGameEngine* App::initGameEngine(IUnitRegistry* unitReg, std::vector<std::string> systemSettings)
{
	return nullptr;
}
