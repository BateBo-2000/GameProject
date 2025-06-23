#include "../../HeaderFiles/System/Services/Registries/Unit/UnitRegistry.h"
#include "../../HeaderFiles/System/GameEngine/Units/IUnit.h"

#include <stdexcept>

UnitRegistry::UnitRegistry() = default;

UnitRegistry::UnitRegistry(const UnitRegistry& other) {
    for (size_t i = 0; i < other.prototypes.size(); ++i) {
        prototypes.push_back(other.prototypes[i]->clone());
    }
}

UnitRegistry& UnitRegistry::operator=(const UnitRegistry& other) {
    if (this != &other) {
        std::vector<IUnit*> temp;

        for (size_t i = 0; i < other.prototypes.size(); i++)
        {
            temp.push_back(other.prototypes[i]->clone());
        }

        clear();
        this->prototypes = std::move(temp);
    }
    return *this;
}

UnitRegistry::~UnitRegistry() {
    clear();
}

void UnitRegistry::registerPrototype(IUnit* unit) {
    if (!unit)
        return;

    const std::string& type = unit->getType();
    // check for duplicates
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (prototypes[i]->getType() == type) {
            delete unit;
            throw std::invalid_argument("UnitRegistry: duplicate unit type '" + type + "'");
        }
    }
    prototypes.push_back(unit);
}

IUnit* UnitRegistry::createByName(const std::string& name) const {
    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (prototypes[i]->getType() == name) {
            return prototypes[i]->clone();
        }
    }
    return nullptr;
}

void UnitRegistry::clear() {
    for (size_t i = 0; i < prototypes.size(); ++i) {
        delete prototypes[i];
    }
    prototypes.clear();
}
