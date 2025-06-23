#pragma once

#include <string>
#include <vector>

class IUnit;
class IUnitFactory;
enum class Faction;


/*
    this is the actual game and everything else is here to support it or use it
 */
class IGameEngine {
public:
    virtual ~IGameEngine() = default;

    // --- for the invoker ---
    virtual Faction getWhoseTurnItIsNow() = 0;

    // --- system controls ---
    virtual bool Save(const std::string& filepath) = 0;
    virtual bool Load(const std::string& filepath) = 0;
    virtual void Restart() = 0;
    virtual void Exit() = 0;

    // --- fighting controls ---
    virtual void SkipTurn() = 0;
    virtual bool Target(const std::string& unitName) = 0;
    virtual bool UseAbility(const std::string& abilityName) = 0;

    // --- gameplay controls ---
    virtual bool Create(const std::string& unitName) = 0;
    virtual bool Select(const std::string& unitName) = 0;
    virtual bool SelectBoss(const std::string& bossName) = 0;
    virtual void Start() = 0;
    virtual void Status() const = 0;


};
