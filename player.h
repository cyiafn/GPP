// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 ship.h v1.0

#ifndef _PLAYER_H                 // Prevent multiple definitions if this 
#define _PLAYER_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace playerNS
{
    const int WIDTH = 26;                   // image width
    const int HEIGHT = 18;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float SPEED = 100;                // 100 pixels per second
    const float MASS = 250.0f;              // mass
    const int   TEXTURE_COLS = 1;           // texture has 2 columns
    const int   PLAYER_START_FRAME = 0;      // player starts at frame 0
    const int   PLAYER_END_FRAME = 2;        // player animation frames 0,1,2
    const float PLAYER_ANIMATION_DELAY = 0.2f;    // time between frames
}

// inherits from Entity class
class Player : public Entity
{
private:

public:
    // constructor
    Player();

    // inherited member functions
    virtual void draw();
    virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
                            TextureManager *textureM);
    void update(float frameTime);
};
#endif

