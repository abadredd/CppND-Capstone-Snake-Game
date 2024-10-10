# Ali's C++ Snake Game with Power-Ups

This project is an enhanced version of the classic Snake game, implemented in C++ using SDL. It introduces three exciting power-ups to make the gameplay more challenging and engaging.

## New Features

The following power-ups have been added to the game:

1.  **Speed Boost:** Increases the snake's speed for a short duration.
2.  **Slow Down:** Decreases the snake's speed for a short duration.
3.  **Tunnel:** Allows the snake to pass through itself for a short duration.

## Expected Behavior

*   **Power-up Spawning:** Power-ups spawn randomly on the game board at a fixed time interval.
*   **Power-up Collection:** When the snake's head collides with a power-up, the corresponding effect is activated.
*   **Power-up Duration:** Each power-up has a fixed duration, after which its effect is deactivated.
*   **Visual Feedback:** The snake's head changes color when the tunnel effect is active.

## Building and Running

### Prerequisites

*   **SDL2:** You need to have SDL2 installed on your system. Here's how you can install it on different platforms:

    *   **Linux:**
        ```bash
        sudo apt-get install libsdl2-dev  # Debian/Ubuntu
        sudo yum install SDL2-devel       # Fedora/CentOS/RHEL
        ```
    *   **macOS:**
        ```bash
        brew install sdl2
        ```
    *   **Windows:**
        *   Download the SDL2 development libraries from the official website: [https://www.libsdl.org/download-2.0.php](https://www.libsdl.org/download-2.0.php)
        *   Extract the archive and follow the instructions to set up the include and library paths in your IDE or build system.

### Build Instructions

1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/abadredd/CppND-Capstone-Snake-Game.git]([https://github.com/your-username/your-repo.git](https://github.com/abadredd/CppND-Capstone-Snake-Game.git))
    ```
2.  **Navigate to the project directory:**
    ```bash
    cd your-repo
    ```
3.  **Create a build directory:**
    ```bash
    mkdir build
    cd build
    ```
4.  **Generate build files using CMake:**
    ```bash
    cmake ..
    ```
5.  **Compile the code:**
    ```bash
    make
    ```
6.  **Run the game:**
    ```bash
    ./SnakeGame
    ```

## Rubric Points Addressed

This project addresses the following rubric points from the C++ Capstone Project:

### Loops, Functions, I/O

*   **Control Structures:** The power-up system uses conditional checks (`if`, `else if`, `switch`) to determine when to spawn power-ups (lines 92-95 in `game.cpp`), detect collisions (lines 104-108 in `game.cpp`), and manage their durations (lines 110-123 in `game.cpp`). It also uses loops (`for`) to iterate through the `activePowerUps` vector (lines 120-139 in `game.cpp`).
    *   Files: `game.cpp`
*   **Functions:** New functions have been created to handle power-up spawning (`SpawnPowerUp`, lines 128-144 in `game.cpp`), collision detection (within `Update`, lines 104-108 in `game.cpp`), effect activation (`ActivatePowerUp`, lines 146-162 in `game.cpp`), and duration management (within `Update`, lines 110-124 in `game.cpp`). The `Renderer` class provides functions for rendering game elements (`Render`, lines 59-97 in `renderer.cpp`) and updating the window title (`UpdateWindowTitle`, lines 99-102 in `renderer.cpp`).
    *   Files: `game.cpp`, `renderer.cpp`
*   **Data Structures:** The `activePowerUps` vector (line 48 in `game.h`) stores the active power-ups.
    *   Files: `game.h`, `game.cpp`
*   **Immutable Variables:** Constant variables define the power-up spawn interval (`POWERUP_SPAWN_INTERVAL`, line 33 in `game.h`) and duration (`POWERUP_DURATION`, line 34 in `game.h`).
    *   Files: `game.h`

### Object-Oriented Programming

*   **Classes:** The `PowerUp` class represents the different types of power-ups. The `Game` class manages the game logic and interacts with other classes like `Snake`, `Controller`, and `Renderer`. The `Renderer` class encapsulates the rendering logic using SDL.
    *   Files: `powerup.h`, `powerup.cpp`, `game.h`, `game.cpp`, `renderer.h`, `renderer.cpp`
*   **Access Specifiers:** The `PowerUp` and `Game` classes use appropriate access specifiers (`public`, `private`) to control member visibility (e.g., lines 18-38 in `powerup.h`). The `Renderer` class uses appropriate access specifiers (`public`, `private`) to control member visibility.
    *   Files: `powerup.h`, `game.h`, `renderer.h`
*   **Constructors & Initialization Lists:** The `PowerUp` constructor uses initialization lists. 
    *   Files: `powerup.h`
*   **Getter/Setter:** Added getter in  `Game.cpp` to GetActivePowerUps line 193. 
    *   Files: `game.cpp`
*   **Destructor:** The `Renderer` class has a destructor to clean up SDL resources (in `renderer.cpp`).
    *   Files: `renderer.cpp`

### Memory Management

*   **Smart Pointers:** `std::unique_ptr` is used to manage the memory of dynamically created `PowerUp` objects (line 17 in `game.h`, line 107, 118, 143, 193 in `game.cpp`).
    *   Files: `game.h`, `game.cpp`
*   **Rule of 5:** The `Game` class implements the Rule of 5 by defining a destructor, copy constructor, copy assignment operator, move constructor, and move assignment operator. This ensures proper resource management, especially when transferring ownership of the `activePowerUps` vector, which contains `std::unique_ptr` elements.
    *   Files: `game.h`
*   **References:** The project uses references in function declarations to avoid unnecessary copying of objects. For example, the `Controller::HandleInput` function takes the `Snake` object by reference (`Snake&`) instead of by value. The `Renderer` constructor and `Render` function take the `Game` object by reference (`Game&`) to access the `activePowerUps` vector.
    *   Files: `controller.h`, `renderer.h`, `game.h`, `renderer.cpp` 
*   **Move Semantics:** The `Game` class implements move semantics (move constructor and move assignment operator) to efficiently transfer resources, especially the `activePowerUps` vector. This avoids unnecessary copying of `std::unique_ptr` elements when a `Game` object is moved.
    *   Files: `game.h`

