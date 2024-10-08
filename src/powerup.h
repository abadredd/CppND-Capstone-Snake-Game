#ifndef POWERUP_H
#define POWERUP_H

#include "SDL.h"

// Ali Added
// PowerUp class to encapsulate power-up data and behavior

// Enum to represent different power-up types
enum class PowerUpType {
    SPEED_BOOST,
    SLOW_DOWN, // Renamed from INVINCIBILITY
    TUNNEL
//     REVERSE
//     CONFUSION 
};

class PowerUp {
public:
    PowerUpType type;
    SDL_Point position;
    int duration; // in frames

    PowerUp(PowerUpType type, int x, int y, Uint32 spawnTime)
        : type(type), position({x, y}), spawnTime(spawnTime) {}

    Uint32 GetSpawnTime() const { 
        return spawnTime; 
    }
  
private:
    // ... other members
    Uint32 spawnTime; // Store the time when the power-up was spawned
};

#endif