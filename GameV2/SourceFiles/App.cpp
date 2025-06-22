#include "../../HeaderFiles/App.h"

//Comunications
#include "../../HeaderFiles/Communication/UI/ConsoleUserInterface.h"
#include "../../HeaderFiles/Communication/Loggers/ConsoleLogger.h"

//Controller
#include "../../HeaderFiles/System/Controller/Controller.h"

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

	this->controller = new(std::nothrow) Controller(*logger, *ui);

	if (!controller) {
		delete ui;
		delete logger;
		throw std::runtime_error("Failed to initialized controller.");
	}
}

App::~App()
{
	delete ui;
	delete logger;
	delete controller;
	std::cout << "Goodbye cruel world";
}

void App::run()
{
	try
	{
		IGameEngine* gameEngine = createGameEngineFromConfig();
	}
	catch (const std::exception&e)
	{
		logger->error(e.what());
	}
}

IGameEngine* App::createGameEngineFromConfig()
{
	std::string path = getConfigLocation();

	std::string fileContents;
	ReadConfigFile(path, fileContents);

	ConfigData fileData;
	ParseConfigFile(fileContents, fileData);

	fileContents.clear(); // to save memory

	if (fileData.unknown.size() > 0) {
		std::string unknowns;
		for (size_t i = 0; i < fileData.unknown.size(); i++)
		{
			unknowns += (fileData.unknown[i] + '\n');
		}
		logger->error("Lines from the configuration that couldnt be parsed:\n" + unknowns);
	}

	if (fileData.units.size() == 0 || fileData.settings.size() < 3) {
		throw std::runtime_error("Cannot create a game without settings or units.");
	}
		
	IArmorRegistry* armReg = nullptr;
	IAbilityRegistry* abiReg = nullptr;
	IUnitRegistry* unitReg = nullptr;
	IGameEngine* game = nullptr;

	try
	{
		armReg = RegisterArmor(fileData.armors);
		abiReg = RegisterAbilities(fileData.abilities);

		unitReg = RegisterUnits(fileData.units, armReg, abiReg);

		delete armReg;
		armReg = nullptr;
		delete abiReg;
		abiReg = nullptr;

		//gameEngine takes the ownership
		game = initGameEngine(unitReg, fileData.settings);
	}
	catch (...)
	{
		delete armReg;
		delete abiReg;
		delete unitReg;

		throw;
	}
	return game;	
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
		armor = p.parseLine(armors[i]);
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
}

void App::parseUnits(std::vector<IUnit*>& dest, std::vector<std::string>& units, const IArmorRegistry* armorReg, const IAbilityRegistry* abilityReg)
{
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
