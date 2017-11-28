#include "boss1.h"
#include <cmath>

Boss1::Boss1() : Boss()
{
	spriteData.width = bossNS::WIDTH;           // size of boss
	spriteData.height = bossNS::HEIGHT;
	spriteData.x = bossNS::X;                   // location on screen
	spriteData.y = bossNS::Y;
	spriteData.rect.bottom = bossNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bossNS::WIDTH;
	frameDelay = bossNS::BOSS_ANIMATION_DELAY;
	startFrame = bossNS::BOSS_START_FRAME;     // first frame of boss animation
	endFrame = bossNS::BOSS_END_FRAME;     // last frame of boss animation
	currentFrame = startFrame;
	radius = bossNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
	ShieldOn = true;
}

bool Boss1::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{

	boss_form1.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	boss_form1.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
	boss_form1.setCurrentFrame(bossNS::BOSS_START_FRAME);
	boss_form1.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
	boss_form1.setLoop(true);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss1::draw()
{
	Image::draw();              // draw boss
	if (ShieldOn)
	{
		shield.draw(spriteData);
	}
}

void Boss1::update(float frameTime)
{
		angle += frameTime*rotation_rate;
		shieldX = bossNS::X + cos(angle)*radius;
		shieldY = bossNS::Y + sin(angle)*radius;
		Entity::update(frameTime);

}

