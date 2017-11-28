#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES
#include <cmath>

#include "entity.h"
#include "constants.h"
#include <string>



namespace bossNS
{
	const float HP = 900;
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	//const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   BOSS_START_FRAME = 0;      // boss starts at frame 0
	const int   BOSS_END_FRAME = 2;        // boss animation frames 0,1,2 //frame 3 is used for attack
	const float BOSS_ANIMATION_DELAY = 0.5f;    // time between frames
	const int form = 0;
	const float damage = 0;
	const int BOSS_ATTACK_DURATION = 0;
	const int RELOAD_TIME = 0;
	const int COLLISION_RADIUS = 0;

}

class Boss : public Entity
{ 
protected:

public:
	// constructor
	Boss();
	
	//// inherited member functions
	//virtual void draw();
	//virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	//void update(float frameTime);
};


#endif