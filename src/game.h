#ifndef GAME_H
#define GAME_H

class Renderer; // Forward declaration of the Renderer class

#include <random>
#include "powerup.h"
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

#include <vector>
#include <memory> // For smart pointers

#include <mutex>   // For std::mutex
#include <condition_variable> // For std::condition_variable
#include <thread>  // For std::thread

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  Game(Game&& other) noexcept; // Move constructor
  Game& operator=(Game&& other) noexcept; // Move assignment operator
  ~Game(); // Declare the destructor explicitly

  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
  const std::vector<std::unique_ptr<PowerUp>>& GetActivePowerUps() const; // Getter function

 private:
  Snake snake;
  SDL_Point food;    
  
  // Ali Added
  std::vector<std::unique_ptr<PowerUp>> activePowerUps;
  const int POWERUP_SPAWN_CHANCE = 0.7; // 5% chance per frame
  const int POWERUP_SPAWN_INTERVAL = 8000; // 5 seconds in milliseconds
  const int POWERUP_DURATION = 6000;      // 3 seconds in milliseconds
  Uint32 lastPowerUpSpawnTime = 0;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  
  void SpawnPowerUp();
  void ActivatePowerUp(const PowerUp& powerUp);  // Pass PowerUp by reference
  void DeactivatePowerUp(const PowerUp& powerUp); // Pass PowerUp by reference

  bool PowerUpExistsAt(int x, int y);
  //   void ActivateConfusion();
  Snake::Direction ReverseDirection(Snake::Direction dir);
  
  // Multithreading members
  std::mutex powerUpMutex;
  std::condition_variable powerUpCV;
  std::thread powerUpThread;
  bool powerUpThreadRunning;

  void PowerUpSpawnerThread();


};

#endif