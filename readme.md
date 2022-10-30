# Proportion Game
Game where the player has to guess the correct representation of a fraction

## Description

- Quick prototype of a game idea given to me by Ralph Leighton
- The player is given a fraction to visualize and then is shown what the fraction looks like after giving their answer

## What I Learned

- Abstracted the run and initialization phases of the app
- Attempted a more reasonable approach to moving numbers around 

## Screenshots

![game screen](/images/proportion_game.png)
![game screen w/ result](/images/proportion_game_results.png)

## Getting Started

### Dependencies
- CMake
- SFML

### Setup
- 
#### simple setup with CMake and GCC

```
mkdir build
cd build
cmake .. -G "Unix Makefiles"
cmake --build . --target main
main
```