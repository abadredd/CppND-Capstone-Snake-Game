#ifndef RENDERER_H
#define RENDERER_H


class Game; // Forward declaration of the Game class

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "powerup.h"
#include "game.h" // Include game.h here

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height, Game& game); // Accept Game reference
  ~Renderer();

  void Render(const Snake& snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  
  void RenderPowerUp(const PowerUp& powerUp);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
  Game& game; // Declare the game reference member variable
};

#endif