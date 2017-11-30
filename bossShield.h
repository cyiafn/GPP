#pragma once
#ifndef _BOSSSHIELD_H                 // Prevent multiple definitions if this 
#define _BOSSSHIELD_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "boss.h"

namespace ShieldNS
{
	const int   WIDTH = 64;                // image width
	const int   HEIGHT = 64;               // image height
	const int   COLLISION_RADIUS = 60 / 2;   // for circular collision
	const int   X = GAME_WIDTH / 2 - WIDTH / 2 +150;
	const int   Y = GAME_HEIGHT / 2 - HEIGHT / 2 + 150;
	const int   TEXTURE_COLS = 2;       // texture has 2 columns
	const int   START_FRAME = 1;        // starts at frame 1
	const int   END_FRAME = 1;          // no animation
	const int   SHIELD_RADIUS = 40;
	const int   SHIELD_START_FRAME = 1;        // starts at frame 1
	const int   SHIELD_END_FRAME = 1;          // no animation
	const float SHIELD_ANIMATION_DELAY = 0.5f;    // time between frames
}

class BossShield : public Entity            // inherits from Entity class
{
public:
	// constructor
	BossShield();
};
#endif