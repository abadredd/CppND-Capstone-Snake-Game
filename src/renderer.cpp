#include "renderer.h"
#include <iostream>
#include <string>

void Renderer::RenderPowerUp(const PowerUp& powerUp) {
  // 1. Set the color for the power-up (e.g., yellow for speed boost)
  switch (powerUp.type) {
    case PowerUpType::SPEED_BOOST:
      SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 0, 255); // Green
      break;
    case PowerUpType::SLOW_DOWN:
      SDL_SetRenderDrawColor(sdl_renderer, 255, 0, 0, 255); // Red
      break;
    case PowerUpType::TUNNEL:
      SDL_SetRenderDrawColor(sdl_renderer, 128, 0, 128, 255); // Purple
      break;
  }
  // 2. Create a rectangle representing the power-up's position and size
  SDL_Rect block;
  block.x = powerUp.position.x * screen_width / grid_width;
  block.y = powerUp.position.y * screen_height / grid_height;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // 3. Render the power-up (you can use a filled rectangle or a more elaborate sprite)
  SDL_RenderFillRect(sdl_renderer, &block);
}

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height, Game& game)
      : game(game),  // Initialize the reference
      screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    if (snake.isTunneling) {
      SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xA5, 0x00, 0xFF); // Orange (or your preferred color)
    } else {
      SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF); // Original head color
    }
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  for (const auto& powerUp : game.GetActivePowerUps()) {
    RenderPowerUp(*powerUp);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
