#include "boss.h"

Boss::Boss() : Entity()
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
}

//bool Boss::initialize(Game *gamePtr, int width, int height, int ncols,TextureManager *textureM)
//{
//	if (Boss::form == 1)
//	{
//		boss.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//		boss.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
//		boss.setCurrentFrame(bossNS::BOSS_START_FRAME);
//		boss.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
//		boss.setLoop(true);                  // do not loop animation
//		return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//	}
//	if (Boss::form == 2)
//	{
//		boss2.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//		boss2.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
//		boss2.setCurrentFrame(bossNS::BOSS_START_FRAME);
//		boss2.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
//		boss2.setLoop(true);                  // do not loop animation
//		return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//	}
//	if (Boss::form == 3)
//	{
//		boss3.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//		boss3.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
//		boss3.setCurrentFrame(bossNS::BOSS_START_FRAME);
//		boss3.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
//		boss3.setLoop(true);                  // do not loop animation
//		return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//	}
//}
//
//void Boss::draw()
//{
//	Image::draw();              // draw boss
//}
//
//void Boss::update(float frameTime)
//{
//	Entity::update(frameTime);
//}


