#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

//from the outside
class ITextFileReader; //for config
class IGameSaveFileHandler; //for saves
class IUserInterface;
class ILogger;

//config data
struct ConfigData;
struct EngineConfig;

//regiters
class IArmorRegistry;
class IAbilityRegistry;
class IUnitRegistry;


//parsers
class IArmorParser;
class IAbilityParser;
class IUnitParser;
class ISettingsParser;

//core parts
class IArmor;
class IAbility;
class IUnit;
class IController;
class IInvoker;
class IGameEngine;

#include <vector>
#include <string>
#include <istream>

/*
    player1UI will be prompted for things like file locations and stuff related to the game setup
*/

class App {
public:
	App(IUserInterface& player1UI, IUserInterface& player2UI ,ILogger& logger, ITextFileReader& textFileReader);
	~App();
	App(const App& other) = delete;	
	App& operator=(const App& other) = delete;
	
	// 0 to hero run the game
	void run();

private:
	//dependecies
	IUserInterface& player1UI;
	IUserInterface& player2UI;
	ILogger& logger;
	ITextFileReader& textFileReader;


	//inside members
	IArmorRegistry* armorRegistry;
	IAbilityRegistry* abilityRegistry;
	IUnitRegistry* unitRegistry;
	EngineConfig* settings;
	
	//THE engine
	IGameEngine* engine;
	
	//commands
	IInvoker* invoker;
	IController* controller;

	std::string savePath;


private:

	void init();
	void free();

    std::string getConfigLocation();
    void readConfigFile(const std::string& path, std::string& out);
    void parseConfigFile(const std::string& raw, ConfigData& data);
	void initAllRegistries(const ConfigData& cfg);
	void initInvoker();
	void initController();
	void initEngine(bool fromSave, IGameSaveFileHandler* saveFile);

private: //helpers
	
	//registers
	void cleanupRegistriesAndSettings();
    void initArmorRegistry(const std::vector<std::string>& entries, IArmorParser& p);
    void initAbilityRegistry(const std::vector<std::string>& entries, IAbilityParser& p);
	void initUnitRegistry(const std::vector<std::string>& entries, IUnitParser& p);
	void initSettings(const std::vector<std::string>& entries, ISettingsParser& p);

	//commands
	void registerCommands();
};

#endif 