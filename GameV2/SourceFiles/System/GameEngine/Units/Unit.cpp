#include "../../HeaderFiles/System/GameEngine/Units/Unit.h"
#include "../../HeaderFiles/System/GameEngine/Abilities/BattleContext.h"

#include <stdexcept>

Unit::Unit(std::string type,
    Faction f,
    unsigned maxHealth,
    unsigned attack,
    unsigned goldCost,
    IArmor* armor,
    const std::vector<IAbility*>& abilities,    //given from the factory
    unsigned maxMana,
    bool commander
    )
    : type(std::move(type)), faction(f), maxHealth(maxHealth), health(maxHealth), attackDmg(attack), goldCost(goldCost)
    ,armor(armor), maxMana(maxMana), mana(maxMana), commander(commander)
{

    //receive the abilities and armor assuming they are given to the unit.
    //left like that so it can work with static abilities/armor
    
    if (!armor) throw std::invalid_argument("Unit must have armor.");

    for (size_t i = 0; i < abilities.size(); i++)
    {
        if (!abilities[i]) throw std::invalid_argument("Unit's ability cannot be null.");
        this->abilities.push_back(abilities[i]);
    }
}

Unit::~Unit() {
    for (size_t i = 0; i < abilities.size(); i++)
    {
        delete abilities[i];
    }
    delete armor;
    abilities.clear();
}

Unit::Unit(const Unit& other)
    : type(other.type)
    , faction(other.faction)
    , maxHealth(other.maxHealth)
    , health(other.health)
    , attackDmg(other.attackDmg)
    , goldCost(other.goldCost)
    , armor(other.armor->clone())           //not taking ownership 
    , abilities()
    , maxMana(other.maxMana)
    , mana(other.mana)
    , commander(other.commander)
{
    for (size_t i = 0; i < other.abilities.size(); ++i) {
        this->abilities.push_back(other.abilities[i]->clone());   //not taking ownership
    }
}

Unit* Unit::clone() const {
    return new Unit(*this);
}

const std::string& Unit::getType() const {
    return type;
}

unsigned Unit::getHealth() const {
    return health;
}

unsigned Unit::getAttack() const {
    return attackDmg;
}

unsigned Unit::getGoldCost() const {
    return goldCost;
}

bool Unit::isCommander() const
{
    return commander;
}

Faction Unit::getFaction() const
{
    return Faction();
}

const IArmor& Unit::getArmor() const {
    return *armor;
}

const std::vector<IAbility*>& Unit::getAbilities() const {
    return abilities;
}

unsigned Unit::getMana() const {
    return mana;
}

void Unit::useMana(unsigned m) {
    if (m <= mana) {
        mana -= m;
    }
    else {
        throw std::invalid_argument("Not enough mana!");
    }
}

void Unit::takeDamage(unsigned rawDamage) {
    unsigned postMitigationDmg = armor->calculateMitigatedDamage(rawDamage);
    if (postMitigationDmg >= health) {
        health = 0;
    }
    else {
        health -= postMitigationDmg;
    }
    armor->use();
}

void Unit::attack(IUnit& target) {
    target.takeDamage(attackDmg);
}

void Unit::useAbility(std::vector<IUnit*> targets, BattleContext& ctx, size_t abilityIndex) {
    if (abilityIndex >= abilities.size()) throw std::out_of_range(std::string("There is no ability with index ") + std::to_string(abilityIndex));
    IAbility* ab = abilities[abilityIndex];

    unsigned cost = ab->getManaCost(); //just a ptr not copy/cloning

    ab->apply(this, targets, ctx);
}

bool Unit::isAlive() const {
    return health > 0;
}

void Unit::regenerateHealth(unsigned amount) {
    health += amount;
    if (health > maxHealth) health = maxHealth;
}

void Unit::regenerateMana(unsigned amount) {
    mana += amount;
    if (mana > maxMana) mana = maxMana;
}

void Unit::serialize(std::ostream& out) const
{
    throw std::exception("Not implemented.");
}