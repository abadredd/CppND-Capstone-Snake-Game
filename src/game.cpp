#include "game.h"
#include "powerup.h"
#include <iostream>
#include "SDL.h"
#include "game.h"
#include "renderer.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
    
    /*
    // Apply score multiplier if active
    if (scoreMultiplierActive) {
      score += scoreMultiplierValue - 1; // Add the bonus points
    }
    */
  }

  // Check for collision with power-ups
  for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
      if (it->get()->position.x == new_x && it->get()->position.y == new_y) {
          ActivatePowerUp(*it->get()); 
          it = activePowerUps.erase(it); 
      } else {
          ++it;
      }
  }

  // Update power-up durations and remove expired ones
  for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
      it->get()->duration--;
      if (it->get()->duration <= 0) {
          DeactivatePowerUp(*it->get()); // If needed for certain power-ups
          it = activePowerUps.erase(it);
      } else {
          ++it;
      }
  }

  /*
  // Handle score multiplier duration
  if (scoreMultiplierActive) {
      scoreMultiplierDuration--;
      if (scoreMultiplierDuration <= 0) {
          scoreMultiplierActive = false;
      }
  }
  */

  // Try to spawn a new power-up randomly
  if (rand() % 100 < POWERUP_SPAWN_CHANCE) {
    SpawnPowerUp();
  }
  
}

void Game::SpawnPowerUp() {
    PowerUpType type = static_cast<PowerUpType>(rand() % 6); // Random type
    int x, y;
    do {
        x = random_w(engine);
        y = random_h(engine);
    } while (snake.SnakeCell(x, y) || 
                (x == food.x && y == food.y) ||
                PowerUpExistsAt(x, y));

    int duration = rand() % 60 + 30; // Random duration between 30 and 90 frames

    activePowerUps.push_back(std::make_unique<PowerUp>(type, x, y, duration));
}

void Game::ActivatePowerUp(const PowerUp& powerUp) {
    switch (powerUp.type) {
        case PowerUpType::SPEED_BOOST:
            snake.speed *= 1.5; // Increase speed temporarily
            break;
        case PowerUpType::INVINCIBILITY:
            // Implement invincibility logic (e.g., set a flag)
            break;
        case PowerUpType::CONFUSION:
            // Implement confusion logic (e.g., reverse controls)
            break;
        case PowerUpType::SHRINK:
            // Implement shrink logic (e.g., remove tail segments)
            break;
        case PowerUpType::TELEPORT:
            // Implement teleport logic
            break;
    }
}

void Game::DeactivatePowerUp(const PowerUp& powerUp) {
    switch (powerUp.type) {
        case PowerUpType::SPEED_BOOST:
            snake.speed /= 1.5; // Reset speed
            break;
        // Add deactivation logic for other power-ups if needed
    }
}

bool Game::PowerUpExistsAt(int x, int y) {
    for (const auto& powerUp : activePowerUps) {
        if (powerUp->position.x == x && powerUp->position.y == y) {
            return true;
        }
    }
    return false;
}


int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
const std::vector<std::unique_ptr<PowerUp>>& Game::GetActivePowerUps() const { return activePowerUps; }