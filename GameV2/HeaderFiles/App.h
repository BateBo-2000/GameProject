#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

class IUserInterface;
class ILogger;
class IFileReader;
class IConfigParser;
class IGameSaveParser;
class IController;
class IArmorRegistry;
class IAbilityRegistry;
class IUnitRegistry;
class IGameEngine;

struct ConfigData;

class IArmor;
class IUnit;
class IAbility;


#include <vector>
#include <string>

class App {
public:
	App();
	~App();
	App(const App& other) = delete;
	App& operator=(const App& other) = delete;
	
	// 0 to hero run the game
	void run();
private:
	IGameEngine* createGameEngineFromConfig();
	

private:
	//ConfigFile
	std::string getConfigLocation();
	void ReadConfigFile(const std::string& path, std::string& dest);
	void ParseConfigFile(const std::string& file, ConfigData& package);
	
	//parsing
	void parseArmors(std::vector<IArmor*>& dest, const std::vector<std::string>& armors);
	void parseAbilities(std::vector<IAbility*>& dest, const std::vector<std::string>& abilities);
	void parseUnits(std::vector<IUnit*>& dest, std::vector<std::string>& units, const IArmorRegistry* armorReg, const IAbilityRegistry* abilityReg);
	
	//registering
	IArmorRegistry* RegisterArmor(const std::vector<std::string>& armorsData);
	IAbilityRegistry* RegisterAbilities(const std::vector<std::string>& abilities);
	IUnitRegistry* RegisterUnits(std::vector<std::string>& units, const IArmorRegistry* armorReg, const IAbilityRegistry* abilityReg);

	//creating the game
	IGameEngine* initGameEngine(IUnitRegistry* unitReg, const std::vector<std::string> systemSettings);

private:
	IUserInterface* ui;
	ILogger* logger;
};

#endif 
