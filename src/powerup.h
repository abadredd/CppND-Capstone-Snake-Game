#ifndef POWERUP_H
#define POWERUP_H

#include "SDL.h"

// Ali Added
// PowerUp class to encapsulate power-up data and behavior

// Enum to represent different power-up types
enum class PowerUpType {
    SPEED_BOOST,
    INVINCIBILITY,
    SCORE_MULTIPLIER,
    CONFUSION,
    SHRINK,
    TELEPORT
};

class PowerUp {
public:
    PowerUpType type;
    SDL_Point position;
    int duration; // in frames

    PowerUp(PowerUpType type, int x, int y, int duration) 
        : type(type), position({x, y}), duration(duration) {}

    // Add functions to activate the power-up's effect later
};

#endif