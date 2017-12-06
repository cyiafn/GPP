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
	velocity.x = 0;
	velocity.y = 0;
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
	angle += 1;
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
	// VECTOR2 newPosition = VECTOR2 position + VECTOR2 direction * frameTime;
}

int BossCannon::getdamage()
{
	return damage;
}
void BossCannon::setVelocityX(float newX)
{
	velocity.x = newX;
}

void BossCannon::setVelocityY(float newY)
{
	velocity.y = newY;
}

bool BossCannon::getReset()
{
	return resetBool;
}

void BossCannon::setReset(bool reset)
{
	resetBool = reset;
}

void BossCannon::resetPosition(bool boolean)
{
	if (resetBool = boolean)
	{
		spriteData.x = Cannon::X;              // location on screen
		spriteData.y = Cannon::Y;
	}
}
