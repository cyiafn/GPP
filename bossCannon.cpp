//#include "bossCannon.h"
//
//BossCannon::bossCannon() : Entity()
//{
//	spriteData.width = Cannon::WIDTH;           // size of boss
//	spriteData.height = Cannon::HEIGHT;
//	spriteData.x = Cannon::X;                   // location on screen
//	spriteData.y = Cannon::Y;
//	startFrame = Cannon::BOSSCANNON_START_FRAME;     // first frame of boss animation
//	endFrame = Cannon::BOSSCANNON_END_FRAME;     // last frame of boss animation
//	currentFrame = startFrame;
//	radius = Cannon::WIDTH / 2.0;
//	collisionType = entityNS::CIRCLE;
//}

//bool BossCannon::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
//{
//	bossCannon.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
//	bossCannon.setFrames(bossCannon::BOSSCANNON_START_FRAME, bossCannon::BOSSCANNON_END_FRAME);
//	bossCannon.setCurrentFrame(bossCannon::BOSSCANNON_START_FRAME);
//	bossCannon.setLoop(true);                  // do not loop animation
//	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
//}
//
//void BossCannon::draw()
//{
//	Image::draw();              // draw boss
//}
//
//void BossCannon::update(float frameTime)
//{
//	Entity::update(frameTime);
//}