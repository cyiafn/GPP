#include "bullet.h"

//=============================================================================
// default constructor
//=============================================================================
Bullet::Bullet() : Entity()
{
	spriteData.width = bulletNS::WIDTH;
	spriteData.height = bulletNS::HEIGHT;
	spriteData.x = bulletNS::X;                   // location on screen
	spriteData.y = bulletNS::Y;
	spriteData.rect.bottom = bulletNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bulletNS::WIDTH;
	velocity.x = 0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	startFrame = bulletNS::PISTOLBULLET_START_FRAME;     // first frame of ship animation
	endFrame = bulletNS::PISTOLBULLET_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = bulletNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}

bool Bullet::initialize(Game *gamePtr, int width, int height, int ncols,
	TextureManager *textureM)
{
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Bullet::draw()
{
	Image::draw();              // draw bullet
}

void Bullet::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;
	spriteData.y += frameTime * velocity.y;
}

void Bullet::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void Bullet::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}
//int bullet::getDamage()
//{
//	return bulletNS::DAMAGE;
//}
