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
    git clone [https://github.com/your-username/your-repo.git](https://github.com/your-username/your-repo.git)
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

*   **Control Structures:** The power-up system uses conditional checks to determine when to spawn power-ups, detect collisions, and manage their durations.
    *   Files: `game.cpp`
    *   Line Numbers: (Provide specific line numbers)
*   **Functions:** New functions have been created to handle power-up spawning, collision detection, effect activation, and duration management.
    *   Files: `game.cpp`, `renderer.cpp`
    *   Line Numbers: (Provide specific line numbers)
*   **Data Structures:** The `activePowerUps` vector stores the active power-ups.
    *   Files: `game.h`, `game.cpp`
    *   Line Numbers: (Provide specific line numbers)
*   **Immutable Variables:** Constant variables define the power-up spawn interval, duration, and other parameters.
    *   Files: `game.h`
    *   Line Numbers: (Provide specific line numbers)

### Object-Oriented Programming

*   **Classes:** The `PowerUp` class represents the different types of power-ups.
    *   Files: `powerup.h`, `powerup.cpp`
*   **Access Specifiers:** The `PowerUp` class uses appropriate access specifiers.
    *   Files: `powerup.h`
*   **Constructors & Initialization Lists:** The `PowerUp` constructor uses initialization lists.
    *   Files: `powerup.h`

### Memory Management

*   **Smart Pointers:** `std::unique_ptr` is used to manage the memory of dynamically created `PowerUp` objects.
    *   Files: `game.h`, `game.cpp`
    *   Line Numbers: (Provide specific line numbers)
*   **Move Semantics:** The `Game` class implements move semantics (move constructor and move assignment operator) to efficiently transfer resources.
    *   Files: `game.h`
    *   Line Numbers: (Provide specific line numbers)

**Note:** Replace `your-username` and `your-repo` with your actual GitHub username and repository name. Also, remember to fill in the specific line numbers for the rubric points addressed in the code.
