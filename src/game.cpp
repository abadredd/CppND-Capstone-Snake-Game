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
  
  Uint32 currentTime = SDL_GetTicks();

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

//   // Check for collision with power-ups
//   for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
//       if (it->get()->position.x == new_x && it->get()->position.y == new_y) {
        
//         std::cout << "Power-up collision detected! Type: " << static_cast<int>(it->get()->type) 
//           << ", Position: (" << it->get()->position.x << ", " << it->get()->position.y << ")" << std::endl;

//           ActivatePowerUp(*it->get()); 
//           it = activePowerUps.erase(it); 
//       } else {
//           ++it;
//       }
//   }

//   // Update power-up durations and remove expired ones
//   for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
//       if (currentTime - it->get()->GetSpawnTime() >= POWERUP_DURATION) { // Use the getter
// //           DeactivatePowerUp(*it->get());
//           std::cout << "Removing expired power-up!" << std::endl;
//           it = activePowerUps.erase(it);
//       } else {
//           ++it;
//       }
//   }

  /*
  // Handle score multiplier duration
  if (scoreMultiplierActive) {
      scoreMultiplierDuration--;
      if (scoreMultiplierDuration <= 0) {
          scoreMultiplierActive = false;
      }
  }
  */
  

  // Check if it's time to spawn a new power-up
  if (currentTime - lastPowerUpSpawnTime >= POWERUP_SPAWN_INTERVAL) {
      SpawnPowerUp();
      lastPowerUpSpawnTime = currentTime; 
  }

  // Update power-up durations, check for collisions, and remove 
    // Update power-up durations, check for collisions, and remove 
    // Update power-up durations, check for collisions, and remove 
    for (auto it = activePowerUps.begin(); it != activePowerUps.end(); ) {
        bool powerUpConsumed = false; 

        // Check for collision
        if (it->get()->position.x == new_x && it->get()->position.y == new_y) {
            ActivatePowerUp(*it->get());
            powerUpConsumed = true; 
            it = activePowerUps.erase(it); // Remove the power-up immediately after collision
        } 
        // Check for expiration (only if not consumed by collision)
        else if (currentTime - it->get()->GetSpawnTime() >= POWERUP_DURATION) {
            // Deactivate ONLY if it's a TUNNEL power-up
            if (it->get()->type == PowerUpType::TUNNEL) { 
                DeactivatePowerUp(*it->get());
                std::cout << "Deactivating and removing expired TUNNEL power-up!" << std::endl;
            } else {
                std::cout << "Removing expired power-up!" << std::endl;
            }
            it = activePowerUps.erase(it);
        } 
        // If not consumed and not expired, move to the next power-up
        else {
            ++it;
        }
    }
  // Try to spawn a new power-up randomly
//   if (rand() % 100 < POWERUP_SPAWN_CHANCE) {
//     SpawnPowerUp();
//   }
  
}

void Game::SpawnPowerUp() {
    PowerUpType type = static_cast<PowerUpType>(rand() % 3); // Random type
    int x, y;
    do {
        x = random_w(engine);
        y = random_h(engine);
    } while (snake.SnakeCell(x, y) || 
                (x == food.x && y == food.y) ||
                PowerUpExistsAt(x, y));

//     int duration = rand() % 60 + 30; // Random duration between 30 and 90 frames
    int duration = 100; // Random duration between 30 and 90 frames

    std::cout << "Power-up spawned! Type: " << static_cast<int>(type) 
      << ", Position: (" << x << ", " << y << ")" << std::endl;
  	
  	activePowerUps.push_back(std::make_unique<PowerUp>(type, x, y, SDL_GetTicks())); // Store spawn time
}

void Game::ActivatePowerUp(const PowerUp& powerUp) {
    switch (powerUp.type) {
        case PowerUpType::SPEED_BOOST:
            snake.speed *= 1.5; // Increase speed temporarily
            std::cout << "Speed Boost activated!" << std::endl;
            break;
        case PowerUpType::SLOW_DOWN:
            snake.speed *= 0.5; // Decrease speed temporarily
            std::cout << "Slow Down activated!" << std::endl;
            break;
       case PowerUpType::TUNNEL:
            snake.isTunneling = true;
            std::cout << "Tunnel activated!" << std::endl;
            break;
//        case PowerUpType::REVERSE:
//             snake.direction = ReverseDirection(snake.direction); // Reverse direction
//             std::cout << "Reverse activated!" << std::endl;
//             break;
//         case PowerUpType::CONFUSION:
//         	ActivateConfusion(); // Call the confusion activation function
//             std::cout << "Confusion activated!" << std::endl;
//             break;
    }
}

void Game::DeactivatePowerUp(const PowerUp& powerUp) {
    switch (powerUp.type) {
        case PowerUpType::SPEED_BOOST:
            snake.speed /= 1.5; // Reset speed
            std::cout << "Speed Boost deactivated!" << std::endl;
            break;
        case PowerUpType::SLOW_DOWN:
            snake.speed /= 0.5; // Reset speed
            std::cout << "Slow Down deactivated!" << std::endl;
            break;
        case PowerUpType::TUNNEL:
            snake.isTunneling = false;
            std::cout << "Tunnel deactivated!" << std::endl;
            break;
    }
}
//         case PowerUpType::REVERSE: {
//             // Store the original head position
//             int originalHeadX = snake.head_x;
//             int originalHeadY = snake.head_y;

//             // Reverse the snake's direction
//             snake.direction = ReverseDirection(snake.direction);

//             // Move the head one step in the new direction to avoid self-collision
//             snake.UpdateHead(); 

//             // Restore the original head position to prevent "teleportation"
//             snake.head_x = originalHeadX;
//             snake.head_y = originalHeadY;

//             std::cout << "Reverse activated!" << std::endl;
//             break;
       
//         case PowerUpType::CONFUSION:
//             snake.isConfused = false; // Activate confusion
//             std::cout << "Confusion deactivated!" << std::endl;
//             break;
   // }

// Snake::Direction Game::ReverseDirection(Snake::Direction dir) {
//     switch (dir) {
//         case Snake::Direction::kUp:
//             return Snake::Direction::kDown;
//         case Snake::Direction::kDown:
//             return Snake::Direction::kUp;
//         case Snake::Direction::kLeft:
//             return Snake::Direction::kRight;
//         case Snake::Direction::kRight:
//             return Snake::Direction::kLeft;
//     }
//     return dir; // Should not happen, but handle it for completeness
// }

// void Game::ActivateConfusion() {
//     snake.isConfused = !snake.isConfused; // Toggle confusion state
//     if (snake.isConfused && snake.size > 1) {
//         // ... (your existing swapping logic for the snake's body)

//         // Swap the head and tail positions using temporary variables
//         int headX = static_cast<int>(snake.head_x);
//         int headY = static_cast<int>(snake.head_y);
//         std::swap(headX, snake.body.back().x);
//         std::swap(headY, snake.body.back().y);
//         snake.head_x = headX; // Update the snake's head_x
//         snake.head_y = headY; // Update the snake's head_y
//     }
// }

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