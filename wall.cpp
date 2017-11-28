// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 6 version 1.0

#include "wall.h"

//=============================================================================
// default constructor
//=============================================================================
Wall::Wall() : Entity()
{
	spriteData.x = wallNS::X;              // location on screen
	spriteData.y = wallNS::Y;
	radius = wallNS::COLLISION_RADIUS;
	mass = wallNS::MASS;
	startFrame = wallNS::START_FRAME;    // first frame of ship animation
	endFrame = wallNS::END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
}