#include "../../HeaderFiles/System/Services/Registries/Ability/AbilityRegistry.h"

#include "../../HeaderFiles/System/GameEngine/Abilities/IAbility.h"

#include <stdexcept>

AbilityRegistry::AbilityRegistry() = default;

AbilityRegistry::AbilityRegistry(const AbilityRegistry& other) {
    for (size_t i = 0; i < other.prototypes.size(); ++i) {
        prototypes.push_back(other.prototypes[i]->clone());
    }
}

AbilityRegistry& AbilityRegistry::operator=(const AbilityRegistry& other) {
    if (this != &other) {
        std::vector<IAbility*> temp;
        for (size_t i = 0; i < other.prototypes.size(); ++i) {
            temp.push_back(other.prototypes[i]->clone());
        }

        clear();
        
        this->prototypes = std::move(temp);
    }
    return *this;
}

AbilityRegistry::~AbilityRegistry() {
    clear();
}

void AbilityRegistry::registerPrototype(IAbility* ability) {
    if (!ability) return;

    // check for name collision
    const std::string& name = ability->getName();

    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (prototypes[i]->getName() == name) {
            delete ability;  // avoid leaking
            throw std::invalid_argument("AbilityRegistry: duplicate ability name '" + name + "'");
        }
    }

    prototypes.push_back(ability);
}

IAbility* AbilityRegistry::createByName(const std::string& name) const {
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (prototypes[i]->getName() == name) {
            return prototypes[i]->clone();
        }
    }
    return nullptr;
}

void AbilityRegistry::clear() {
    for (size_t i = 0; i < prototypes.size(); ++i) {
        delete prototypes[i];
    }
    prototypes.clear();
}