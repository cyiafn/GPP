#pragma once
#ifndef _BOSSCANNON_H                 // Prevent multiple definitions if this 
#define _BOSSCANNON_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "boss.h"

namespace Cannon
{
	const int   WIDTH = 64;                // image width
	const int   HEIGHT = 64;               // image height
	const int   COLLISION_RADIUS = 60 / 2;   // for circular collision
	const int   X = bossNS::X;
	const int   Y = bossNS::Y;
	const int   TEXTURE_COLS = 2;       // texture has 2 columns
	const int   START_FRAME = 1;        // starts at frame 1
	const int   END_FRAME = 1;          // no animation
}

class BossCannon : public Entity            // inherits from Entity class
{
private:
	int damage = 1;
	Image CannonBall;
	int speed = 20;
public:
	// constructor
	BossCannon();

	int getdamage();
};
#endif