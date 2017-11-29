//I WILL DELETE THIS LATER//

//#pragma once
//#ifndef _BOSS1_H                 // Prevent multiple definitions if this 
//#define _BOSS1_H                 // file is included in more than one place
//#define WIN32_LEAN_AND_MEAN
//
//#include "entity.h"
//#include "constants.h"
//#include "boss.h"
//
//namespace boss1NS
//{
//	const int form = 1;
//	const float MASS = 1.0e14f;         // mass
//	const int   TEXTURE_COLS = 2;       // texture has 2 columns
//	const int   SHIELD_START_FRAME = 1;        // starts at frame 1
//	const int   SHIELD_END_FRAME = 1;          // no animation
//	const float SHIELD_ANIMATION_DELAY = 0.5f;    // time between frames
//}
//
//class Boss1 : public Boss
//{
//private:
//	int form = 1;
//	int shield_radius = 20;
//	int shieldX;
//	int shieldY;
//	Image boss_form1;
//	Image shield;
//
//public:
//	// constructor
//	Boss1();
//
//	// inherited member functions
//	virtual void draw();
//	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
//	void update(float frameTime);
//
//};
//
//
//#endif