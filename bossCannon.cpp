#include "bossCannon.h"

//=============================================================================
// default constructor
//=============================================================================
BossCannon::BossCannon() : Entity()
{
	spriteData.x = Cannon::X;              // location on screen
	spriteData.y = Cannon::Y;
	radius = Cannon::COLLISION_RADIUS;
	startFrame = Cannon::START_FRAME;    // first frame of ship animation
	endFrame = Cannon::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
}

int BossCannon::getdamage()
{
	return damage;
}