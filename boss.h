#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES
#include <cmath>

#include "entity.h"
#include "constants.h"
#include <string>



namespace bossNS
{
	const int MAXHP = 2700;
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	//const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   BOSS_START_FRAME = 0;      // boss starts at frame 0
	const int   BOSS_END_FRAME = 2;        // boss animation frames 0,1,2 //frame 3 is used for attack
	const float BOSS_ANIMATION_DELAY = 0.5f;    // time between frames
	const int form = 1;
	const int damage = 1;
	const int BOSS_ATTACK_DURATION = 0;
	const int RELOAD_TIME = 0;
	const int COLLISION_RADIUS = 0;
	const int CHANNEL_TIME = 2;
	const float ATTACK_DURATION = 3.0f;
	//1
	
	//2

	//3
	const int MOVEMENT_SPEED = 40;
}

class Boss : public Entity
{ 
protected:
	int HP = 2700;
	int form = 1;
	int damage = 1;
	bool form1Spawn = false;
	bool form1Dead = false;
	bool form2Spawn = false;
	bool form2Dead = false;
	bool form3Spawn = false;
	bool form3Dead = false;
	Image boss_form1;
	Image shield;
	Image boss_form2;
	Image boss_form3;
	bool shieldOn = false;
public:
	// constructor
	Boss();
	
	//common functions
	int getDamage();
	void setDamage(int dmg);
	int getHP();
	int getForm();
	void setForm(int form);

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int form);
	void update(float frameTime);

	
	//1

	//2
	//3
};


#endif