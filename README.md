# SeaBattle

## Overview

SeaBattle is a strategic game where players command fleets of ships and engage in naval battles. The game involves
placing ships on a grid and taking turns to attack the opponent's ships. The objective is to sink all of the opponent's
ships before they sink yours.

## Features

- **Single Player Mode**: Play against a computer-controlled opponent.
- **Abilities**: Use special abilities like bombardment, double damage, and scanning to gain an advantage.
- **Customizable Game Settings**: Adjust game settings such as grid and ship sizes.
- **Save and Load**: Save your game at any stage and load it later to continue from where you left off.
- **Configurable Key Bindings**: Customize key bindings through a configuration file (`key_bindings.json`).

## Gameplay

- The game currently supports a mode where a human player competes against bots.
- If the player wins, a new bot is created, and the player's field and abilities are carried over to the next round.
- If the bot wins, a new game starts with a fresh setup.

## Installation

To build the project locally, follow these steps:

1. **Clone the repository**:
   ```bash
   git clone https://github.com/eggunof/SeaBattle.git
   cd SeaBattle
2. **Install the nlohmann::json library**:
   
   You can install the library using your package manager or by including it directly in your project. For example,
   using apt on Ubuntu:
   ```bash
   sudo apt-get install nlohmann-json3-dev
3. **Build the project using CMake**:
    ```bash
    mkdir build
    cd build
    cmake ..

## Usage

After building the project, you can run the game using the following command:

```bash
./SeaBattle
