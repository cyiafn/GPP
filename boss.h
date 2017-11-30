#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES

#include "entity.h"
#include "constants.h"
#include <string>
#include "abilityRange.h"



namespace bossNS
{
	const int MAXHP = 2000;
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	//const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	const int   BARON_START_FRAME = 0;      // boss starts at frame 0
	const int   BARON_END_FRAME = 2;        // boss animation frames 0,1,2 
	const int	BARON_CHANNEL_FRAME = 3;	//frame 3,4 is used for attack
	const int	BARON_ATTACK_FRAME = 4;
	const float BARON_ANIMATION_DELAY = 0.5f;    // time between frames
	const int   NORAB_START_FRAME = 5;      // boss starts at frame 5
	const int   NORAB_END_FRAME = 7;        // boss animation frames 5,6,7 //frame 8,9 is used for attack
	const int	NORAB_CHANNEL_FRAME = 8;	//frame 3,4 is used for attack
	const int	NORAB_ATTACK_FRAME = 9;
	const float NORAB_ANIMATION_DELAY = 0.5f;    // time between frames
	const int form = 1;
	const int damage = 1;
	const int RELOAD_TIME = 5; //5 sec for player to attack Boss
	const int BOSS_ATTACK_DURATION = 5; //5 sec for Boss to attack player
	const int CHANNEL_TIME = 2; //2 sec for Boss to alert player he is about to attack
	const int COLLISION_RADIUS = WIDTH*2/3;
	//1
	
	//2

	//3
	const int MOVEMENT_SPEED = 40;
}

class Boss : public Entity
{ 
protected:
	int HP = 2000;
	int form = 1;
	int damage = 1;
	//enum class STATUS {RELOAD_STATE, ATTACK_STATE}
	int status = 0; //status 0 = RELOAD_STATE, status 1 = ATTACK_STATE
					//in other words, HARDCODED!!!
	bool BARON_Spawn = true;
	bool BARON_Dead = false;
	bool NORAB_Spawn = false;
	bool NORAB_Dead = false;
	Image boss_form;
	Entity shield;
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
	void takesDamage(int dmgValue);
	int getStatus();
	void changeStatus();

	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM);
	void update(float frameTime);
	
	
	//1
	void shootBullet();
	
	//3
	void CHARRRGE();
};


#endif