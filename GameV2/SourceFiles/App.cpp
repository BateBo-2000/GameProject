#include "../../HeaderFiles/App.h"

//Comunications
#include "../../HeaderFiles/Communication/UI/IUserInterFace.h"
#include "../../HeaderFiles/Communication/Loggers/ILogger.h"

//Control
#include "../../HeaderFiles/System/Control/IController.h"
#include "../../HeaderFiles/System/Control/Invoker/CommandInvoker.h"

//SaveFile
#include "../../HeaderFiles/System/Services/SaveLoadFiles/BinaryGameSaveFileHandler.h"

//core
#include "../../HeaderFiles/System/GameEngine/GameEngine.h"

#include <stdexcept>

App::App(IUserInterface& player1UI, IUserInterface& player2UI, ILogger& logger, ITextFileReader& textFileReader)
	:player1UI(player1UI)
	, player2UI(player2UI)
	, logger(logger)
	, textFileReader(textFileReader)
	, armorRegistry(nullptr)
	, abilityRegistry(nullptr)
	, unitRegistry(nullptr)
	, settings(nullptr)
	, engine(nullptr)
	, controller(nullptr)
	, invoker(nullptr)
{
}

App::~App()
{
	free();
}

void App::run()
{
	logger.log("App::run()");

	try
	{
		init();
	}
	catch (const std::exception& e)
	{
		logger.error("Initialization failed. Reason:\n" + std::string(e.what()));
	}

}

#include "../HeaderFiles/ConfigDataStruct.h"

void App::init()
{
	BinaryGameSaveFileHandler* saveFileHandler = nullptr;
	try
	{
		//config file
		std::string configPath = getConfigLocation();
		std::string file;
		readConfigFile(configPath, file);
		ConfigData data;
		parseConfigFile(file, data);
		initAllRegistries(data);

		//savefile
		saveFileHandler = new BinaryGameSaveFileHandler(*unitRegistry, *armorRegistry, *abilityRegistry, *settings);

		//engine
		savePath = player1UI.askQuestion("Enter save file path:");
		bool fromSave = player1UI.confirm("Load saved game?");
		initEngine(fromSave, saveFileHandler);

		//commands
		initInvoker();
		initController();

		controller->run();
	}
	catch (const std::exception&e)
	{
		free();
		delete saveFileHandler;
		logger.error("App initialisation failed!\n"+std::string(e.what()));
		throw;
	}
}

void App::free()
{
	cleanupRegistriesAndSettings();

	delete controller;
	controller = nullptr;
	delete invoker;
	invoker = nullptr;
	delete engine;
	engine = nullptr;
}

std::string App::getConfigLocation()
{
	return player1UI.askQuestion("Enter config file location:");
}

#include "../../HeaderFiles/System/Services/Files/FileReading/IFileReader.h"

void App::readConfigFile(const std::string& path, std::string& dest)
{

	if (!this->textFileReader.readFileContents(path, dest)) 
		throw std::runtime_error("Failed to read configuration from file:" + path);

}

#include "../../HeaderFiles/ConfigDataStruct.h"
#include "../../HeaderFiles/System/Services/ConfigParsing/TextConfigParser.h"

void App::parseConfigFile(const std::string& raw, ConfigData& data)
{
	ConfigParser cp;
	cp.parse(raw, data);
}

#include "../HeaderFiles/System/Services/ConfigParsing/ArmorParsing/ArmorParser.h"
#include "../HeaderFiles/System/Services/Registries/Armor/ArmorRegistry.h"

#include "../HeaderFiles/System/Services/ConfigParsing/AbilityParsing/AbilityParser.h"
#include "../HeaderFiles/System/Services/Registries/Ability/AbilityRegistry.h"

#include "../HeaderFiles/System/Services/ConfigParsing/UnitParsing/UnitParser.h"
#include "../HeaderFiles/System/Services/Registries/Unit/UnitRegistry.h"

#include "../HeaderFiles/System/Services/ConfigParsing/SettingsParsing/SettingParser.h"
#include "../HeaderFiles/System/GameEngine/GameStateStructure/EngineConfig.h"

void App::initAllRegistries(const ConfigData& cfg)
{
	try
	{
		armorRegistry = new ArmorRegistry();
		abilityRegistry = new AbilityRegistry();
		unitRegistry = new UnitRegistry();

		ArmorParser arp;
		AbilityParser abp;
		UnitParser up(*armorRegistry, *abilityRegistry);
		SettingsParser sp;

		initArmorRegistry(cfg.armors, arp);
		initAbilityRegistry(cfg.abilities, abp);
		initUnitRegistry(cfg.units, up);
		initSettings(cfg.settings, sp);

		if (!cfg.unknown.empty()) {
			for (size_t i = 0; i < cfg.unknown.size(); i++)
			{
				logger.warn("Unknown configuration: " + cfg.unknown[i]);
			}
		}
	}
	catch (const std::exception& e)
	{
		cleanupRegistriesAndSettings();
		throw std::runtime_error("Failed to parse or register configurations. Registers are deleted. Reason:\n" + std::string(e.what()));
	}
}

void App::initInvoker()
{
	if(!engine) throw std::logic_error("App::initInvoker: engine is null");
	if (invoker) return; 

	this->invoker = new CommandInvoker(*engine);

	registerCommands();
}

#include "../../HeaderFiles/System/Control/Controller.h"

void App::initController()
{
	if (!invoker) throw std::logic_error("App::initController: invoker is null");	//assert
	if (controller) return;

	this->controller = new Controller(logger, player1UI, player2UI, *invoker);
}



void App::initEngine(bool fromSave, IGameSaveFileHandler* saveFile)
{
	//just in case
	delete engine;
	engine = nullptr;

	if (!unitRegistry || !armorRegistry || !abilityRegistry || !settings)
		throw std::logic_error("App::initEngine: registries not initialized");

	InitMode mode = fromSave ? InitMode::LoadGame : InitMode::NewGame;

	try {
		engine = new GameEngine(*unitRegistry, saveFile, savePath, mode);
	}
	catch (const std::exception& e) {
		throw std::runtime_error(
			std::string("App::initEngine: Failed to initialize GameEngine:\n")
			+ e.what()
		);
	}
}

void App::cleanupRegistriesAndSettings()
{
	delete armorRegistry;
	armorRegistry = nullptr;

	delete abilityRegistry;
	abilityRegistry = nullptr;

	delete unitRegistry;
	unitRegistry = nullptr;

	delete settings;
	settings = nullptr;
}

#include "../../HeaderFiles/System/GameEngine/Armor/IArmor.h"
void App::initArmorRegistry(const std::vector<std::string>& entries, IArmorParser& p)
{

	for (size_t i = 0; i < entries.size(); i++)
	{
		IArmor* armor = p.parse(entries[i]);

		if (!armor) {
			logger.warn(entries[i] + " failed to parse.");
			continue;
		}

		try
		{
			armorRegistry->registerPrototype(armor); //takes ownership
		}
		catch (std::invalid_argument& ex) {
			logger.warn("Armor '" + armor->getName() + "' has already been registered!" + std::string(ex.what()));
			delete armor;
		}
		catch (...)
		{
			delete armor;
			throw;
		}
	}

}

#include "../../HeaderFiles/System/GameEngine/Abilities/IAbility.h"
void App::initAbilityRegistry(const std::vector<std::string>& entries, IAbilityParser& p)
{
	for (size_t i = 0; i < entries.size(); ++i) {

		IAbility* ability = p.parse(entries[i]);

		if (!ability) {
			logger.warn(entries[i] + " failed to parse.");
			continue;
		}

		try {
			abilityRegistry->registerPrototype(ability);
		}
		catch (const std::invalid_argument& ex) {
			logger.warn("Ability '" + ability->getName() + "' has already been registered!"+ std::string(ex.what()));
			delete ability;
		}
		catch (...) {
			delete ability;
			throw;
		}
	}
}

#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"
void App::initUnitRegistry(const std::vector<std::string>& entries, IUnitParser& p)
{
	for (size_t i = 0; i < entries.size(); ++i) {
		IUnit* unit = p.parse(entries[i]);
		if (!unit) {
			logger.warn(entries[i] + " failed to parse.");
			continue;
		}
		try {
			unitRegistry->registerPrototype(unit);
		}
		catch (const std::invalid_argument& ex) {
			logger.warn("Unit '" + unit->getType() + "' has already been registered!" + std::string(ex.what()));
			delete unit;
		}
		catch (...) {
			delete unit;
			throw;
		}
	}
}
  
#include "../../HeaderFiles/System/GameEngine/GameStateStructure/EngineConfig.h"
void App::initSettings(const std::vector<std::string>& entries, ISettingsParser& p)
{
	EngineConfig* temp = p.parse(entries);
	
	if (settings) delete settings;
	settings = temp;
}

#include "../../HeaderFiles/System/Control/Commands/Combat/AttackTargetCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Combat/SkipTurnCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Combat/UseAbilityCmd.h"

#include "../../HeaderFiles/System/Control/Commands/Other/CreateCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Other/SelectBossCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Other/SelectCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Other/StartCmd.h"
#include "../../HeaderFiles/System/Control/Commands/Other/StatusCmd.h"

#include "../../HeaderFiles/System/Control/Commands/System/ExitCmd.h"
#include "../../HeaderFiles/System/Control/Commands/System/HelpCmd.h"
#include "../../HeaderFiles/System/Control/Commands/System/LoadCmd.h"
#include "../../HeaderFiles/System/Control/Commands/System/RestartCmd.h"
#include "../../HeaderFiles/System/Control/Commands/System/SaveCmd.h"

void App::registerCommands()
{
	if (!invoker) throw std::runtime_error("App::registerCommands: Invoker is NULL");
	if (!engine) throw std::runtime_error("App::registerCommands: Engine is NULL");

	try
	{
		invoker->registerCommand(new AttackTargetCmd(*engine));
		invoker->registerCommand(new SkipTurnCmd(*engine));
		invoker->registerCommand(new UseAbilityCmd(*engine));

		invoker->registerCommand(new CreateUnitCmd(*engine));
		invoker->registerCommand(new SelectBossCmd(*engine));
		invoker->registerCommand(new SelectUnitsCmd(*engine));
		invoker->registerCommand(new StartDuelCmd(*engine));
		invoker->registerCommand(new StatusCmd(*engine));

		invoker->registerCommand(new ExitCommand(*invoker, player1UI));
		invoker->registerCommand(new HelpCmd(*invoker));
		invoker->registerCommand(new LoadCommand(*engine, player1UI));
		invoker->registerCommand(new RestartCommand(*engine, player1UI));
		invoker->registerCommand(new SaveCommand(*engine, player1UI));
	}
	catch (const std::invalid_argument& e)
	{
		logger.warn(e.what());
	}
}