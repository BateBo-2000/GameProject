#pragma once
#ifndef ENGINE_CONFIG_H
#define ENGINE_CONFIG_H

struct EngineConfig {
    unsigned startingGoldLiving;
    unsigned startingGoldUndead;
    unsigned healthRegenPerRound;
    unsigned manaRegenPerRound;

    unsigned maxAliveUnits;
    unsigned maxCommanders;
    unsigned goldPerWin;
    unsigned duelsToWin;
};

#endif // ENGINE_CONFIG_H
