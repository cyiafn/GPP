#include "boss.h"

Boss::Boss() : Entity()
{
	spriteData.width = boss::WIDTH;           // size of boss
	spriteData.height = boss::HEIGHT;
	spriteData.x = boss::X;                   // location on screen
	spriteData.y = boss::Y;
	spriteData.rect.bottom = boss::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = boss::WIDTH;
	frameDelay = boss::BOSS_ANIMATION_DELAY;
	startFrame = boss::BOSS_START_FRAME;     // first frame of boss animation
	endFrame = boss::BOSS_END_FRAME;     // last frame of boss animation
	currentFrame = startFrame;
	radius = boss::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}

bool Boss::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
{
	boss.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	boss.setFrames(boss::BOSS_START_FRAME, boss::BOSS_END_FRAME);
	boss.setCurrentFrame(boss::BOSS_START_FRAME);
	boss.setFrameDelay(boss::BOSS_ANIMATION_DELAY);
	boss.setLoop(true);                  // do not loop animation
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss::draw()
{
	Image::draw();              // draw boss
}

void Boss::update(float frameTime)
{
	Entity::update(frameTime);
}