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
	velocity.x =  0;                             // velocity X
	velocity.y = 0;                             // velocity Y
	frameDelay = zombieNS::ZOMBIE_ANIMATION_DELAY;
	startFrame = zombieNS::ZOMBIE_START_FRAME;     // first frame of ship animation
	endFrame = zombieNS::ZOMBIE_END_FRAME;     // last frame of ship animation
	currentFrame = startFrame;
	radius = zombieNS::WIDTH / 2.0;
	health = zombieNS::HEALTH;
	collisionType = entityNS::CIRCLE;
	attack = false;
	wallCheck = false;
	wallVector.x = 0;
	wallVector.y = 0;
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
	Image::draw();              // draw zombie
}

void Zombie::update(float frameTime)
{
	Entity::update(frameTime);
	spriteData.x += frameTime * velocity.x;         // move ship along X 
	spriteData.y += frameTime * velocity.y;         // move ship along Y
}
void Zombie::ai(float frameTime, Zombie &ent)
{
	//spriteData.x = spriteData.x + frameTime * zombieNS::ZOMBIE_SPEED;
}
void Zombie::setPrev(float x, float y)
{
	this->prevX = x;
	this->prevY = y;
}
void Zombie::revertLocation()
{
	this->spriteData.x = prevX;
	this->spriteData.y = prevY;
}
int Zombie::getDamage()
{
	return zombieNS::DAMAGE;
}
int Zombie::checkVoronoiRegion(Entity &ent, VECTOR2 &collisionVector)
{
	float min01, min03, max01, max03, center01, center03;

	computeRotatedBox();                    // prepare rotated box

											// project circle center onto edge01
	center01 = graphics->Vector2Dot(&edge01, ent.getCenter());
	min01 = center01 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max01 = center01 + ent.getRadius()*ent.getScale();
	if (min01 > edge01Max || max01 < edge01Min) // if projections do not overlap
		return false;                       // no collision is possible

											// project circle center onto edge03
	center03 = graphics->Vector2Dot(&edge03, ent.getCenter());
	min03 = center03 - ent.getRadius()*ent.getScale(); // min and max are Radius from center
	max03 = center03 + ent.getRadius()*ent.getScale();
	if (min03 > edge03Max || max03 < edge03Min) // if projections do not overlap
		return false;                       // no collision is possible

											// circle projection overlaps box projection
											// check to see if circle is in voronoi region of collision box
	if (center01 < edge01Min && center03 < edge03Min)    // if circle in Voronoi0
		return 0;
	if (center01 > edge01Max && center03 < edge03Min)    // if circle in Voronoi1
		return 1;
	if (center01 > edge01Max && center03 > edge03Max)    // if circle in Voronoi2
		return 2;
	if (center01 < edge01Min && center03 > edge03Max)    // if circle in Voronoi3
		return 3;

}


int Zombie::getWallVectorX()
{
	return this->wallVector.x;
}
int Zombie::getWallVectorY()
{
	return this->wallVector.y;
}
void Zombie::setWallVector(VECTOR2 vector)
{
	this->wallVector = vector;
}
