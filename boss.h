#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace boss
{
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const int X = GAME_WIDTH / 4 - WIDTH / 4;   // location on screen
	const int Y = GAME_HEIGHT / 4 - HEIGHT / 4;
	const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 4;           // texture has 4 columns
	const int   BOSS_START_FRAME = 0;      // ship1 starts at frame 0
	const int   BOSS_END_FRAME = 3;        // ship1 animation frames 0,1,2,3
	const float BOSS_ANIMATION_DELAY = 0.2f;    // time between frames
}

class Boss : public Entity
{
private:
	Image boss;
public:
	// constructor
	Boss();
	
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
};


#endif