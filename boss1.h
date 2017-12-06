#pragma once
#ifndef _BOSS1_H                 // Prevent multiple definitions if this 
#define _BOSS1_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"
#include "boss.h"


class Boss1 : public Boss
{
private:
	float HP = 900;
	int form = 1;
	bool ShieldOn;
	int shield_radius = 20;
	int shieldX;
	int shieldY;
	float rotation_rate = 1.0;
	float angle;
	Image boss_form1;
	Image shield;
public:
	// constructor
	Boss1();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);



};


#endif