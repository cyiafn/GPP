//#include "boss2.h"
//
//Boss2::Boss2() : Boss()
//{
//	spriteData.width = bossNS::WIDTH;           // size of boss
//	spriteData.height = bossNS::HEIGHT;
//	spriteData.x = bossNS::X;                   // location on screen
//	spriteData.y = bossNS::Y;
//	spriteData.rect.bottom = bossNS::HEIGHT;    // rectangle to select parts of an image
//	spriteData.rect.right = bossNS::WIDTH;
//	frameDelay = bossNS::BOSS_ANIMATION_DELAY;
//	startFrame = bossNS::BOSS_START_FRAME;     // first frame of boss animation
//	endFrame = bossNS::BOSS_END_FRAME;     // last frame of boss animation
//	currentFrame = startFrame;
//	radius = bossNS::WIDTH / 2.0;
//	collisionType = entityNS::CIRCLE;
//}
//
//bool Boss2::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
//{
//	if (Boss::form2Spawn == true)
//	{
//		boss_form2.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//		boss_form2.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
//		boss_form2.setCurrentFrame(bossNS::BOSS_START_FRAME);
//		boss_form2.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
//		boss_form2.setLoop(true);                  // do not loop animation
//		return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//	}
//}
//
//void Boss2::draw()
//{
//	Image::draw();              // draw boss
//}
//
//void Boss2::update(float frameTime)
//{
//	Entity::update(frameTime);
//}