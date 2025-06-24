#include "../../HeaderFiles/System/Services/Registries/Armor/ArmorRegistry.h"
#include "../../HeaderFiles/System/GameEngine/Armor/Armor.h"
#include <stdexcept>

ArmorRegistry::ArmorRegistry() = default;

ArmorRegistry::ArmorRegistry(const ArmorRegistry& other) {
    for (size_t i = 0; i < other.prototypes.size(); i++)
    {
        this->prototypes.push_back(other.prototypes[i]);
    }
}

ArmorRegistry& ArmorRegistry::operator=(const ArmorRegistry& other) {
    if (this != &other) {
        std::vector<IArmor*> temp;
        
        for (size_t i = 0; i < other.prototypes.size(); i++)
        {
            temp.push_back(other.prototypes[i]->clone());
        }

        clear();
        this->prototypes = std::move(temp);
    }
    return *this;
}

ArmorRegistry::~ArmorRegistry() {
    clear();
}

void ArmorRegistry::registerPrototype(IArmor* armor) {
    if (!armor)
        return;

    const std::string& name = armor->getName();

    for (size_t i = 0; i < prototypes.size(); ++i) {
        if (prototypes[i]->getName() == name) {
            throw std::invalid_argument("ArmorRegistry: duplicate armor name '" + name + "'");
        }
    }

    prototypes.push_back(armor);
}

IArmor* ArmorRegistry::createByName(const std::string& name, unsigned durability) const {
    for (size_t i = 0; i < prototypes.size(); i++)
    {
        if (prototypes[i]->getName() == name) {
            IArmor* result = prototypes[i]->clone();
            result->setDurability(durability);
            return result;
        }
    }
    return nullptr;
}

void ArmorRegistry::clear() {
    for (size_t  i = 0; i < prototypes.size(); i++)
    {
        delete prototypes[i];
    }
    prototypes.clear();
}
