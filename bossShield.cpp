#include "bossShield.h"

//=============================================================================
// default constructor
//=============================================================================
BossShield::BossShield() : Entity()
{
	spriteData.x = ShieldNS::X;              // location on screen
	spriteData.y = ShieldNS::Y;
	radius = ShieldNS::COLLISION_RADIUS;
	startFrame = ShieldNS::START_FRAME;    // first frame of ship animation
	endFrame = ShieldNS::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);

}