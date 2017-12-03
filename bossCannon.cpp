#include "bossCannon.h"

//=============================================================================
// default constructor
//=============================================================================
BossCannon::BossCannon() : Entity()
{
	spriteData.width = Cannon::WIDTH;
	spriteData.height = Cannon::HEIGHT;
	spriteData.x = Cannon::X;              // location on screen
	spriteData.y = Cannon::Y;
	radius = Cannon::COLLISION_RADIUS;
	startFrame = Cannon::CANNON_START_FRAME;    // first frame of ship animation
	endFrame = Cannon::CANNON_END_FRAME;      // last frame of ship animation
	setCurrentFrame(startFrame);
	collisionType = entityNS::CIRCLE;
}

void BossCannon::draw()
{
	Image::draw();
}
bool BossCannon::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	CannonBall.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	CannonBall.setFrames(Cannon::CANNON_START_FRAME, Cannon::CANNON_END_FRAME);
	CannonBall.setCurrentFrame(Cannon::CANNON_START_FRAME);
	CannonBall.setLoop(true);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void BossCannon::update(float frameTime)
{
	Entity::update(frameTime);
}

int BossCannon::getdamage()
{
	return damage;
}

int BossCannon::getprevX()
{
	return prevX;
}

void BossCannon::setprevX()
{

}

int BossCannon::getprevY()
{
	return prevY;
}

void BossCannon::setprevY()
{

}