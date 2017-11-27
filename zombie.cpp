#include "zombie.h"

//=============================================================================
// default constructor
//=============================================================================
Zombie::Zombie() : Entity()
{
	spriteData.width = zombieNS::WIDTH;
	spriteData.height = zombieNS::HEIGHT;
	spriteData.x = zombieNS::X;                   // location on screen
	spriteData.y = zombieNS::Y;
	spriteData.rect.bottom = zombieNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = zombieNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = zombieNS::ZOMBIE_ANIMATION_DELAY;
	startFrame = zombieNS::ZOMBIE_START_FRAME;     // first frame of ship animation
	endFrame = zombieNS::ZOMBIE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = zombieNS::WIDTH / 2.0;
	health = zombieNS::HEALTH;
	collisionType = entityNS::CIRCLE;
}

bool Zombie::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	//zomb.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	//zomb.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zomb.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zomb.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);
	//zomb.setLoop(false);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Zombie::draw()
{
	Image::draw();              // draw ship
}

void Zombie::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
}