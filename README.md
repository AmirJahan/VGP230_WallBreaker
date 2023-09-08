# VGP230 Wall Breaker

A classic Arkanoid/brick breaker game built with C++ and Raylib for the VGP230 game development course.

## Overview

Control a paddle to bounce a ball and break all the colored bricks. Don't let the ball fall off the screen!

## Features

### Gameplay
- Classic brick breaker mechanics
- 5 rows × 8 columns = 40 bricks
- 5 lives system
- Pause functionality
- Game over and win states

### Visual Elements
- Color-coded brick rows (Red, Purple, Orange, Blue, Green)
- Paddle at bottom of screen
- Ball physics with angle variation
- Lives display

## Tech Stack

- **Language**: C++ (C++17)
- **Framework**: Raylib
- **IDE**: Visual Studio 2022
- **Target FPS**: 180

## Controls

| Key | Action |
|-----|--------|
| Left/Right Arrow | Move paddle |
| Space | Launch ball |
| P | Pause/Resume |
| Enter | Restart (after game over) |
| ESC | Exit |

## Project Structure

```
VGP230_WallBreaker/
├── WallBreakerGame.sln        # VS Solution
└── WallBreakerGame/
    ├── main.cpp               # Entry point
    ├── WallBreaker.h          # Class definition
    └── WallBreaker.cpp        # Game implementation
```

## Game Components

### Player (Paddle)
- Width: 1/10th of screen
- Height: 20 pixels
- Controlled with arrow keys

### Ball
- Radius: 8 pixels
- Bounces off walls, bricks, and paddle
- Speed adjusts based on paddle hit position

### Bricks
- 40 total bricks in 5×8 grid
- Height: 24 pixels each
- 8-pixel gaps between bricks

## Building

1. Open `WallBreakerGame.sln` in Visual Studio 2022
2. Ensure Raylib is linked
3. Build (Debug or Release)
4. Run from x64 folder

## Game Rules

1. Launch ball with Space
2. Move paddle to bounce ball
3. Break all bricks to win
4. Ball falling = lose 1 life
5. 0 lives = Game Over
