#pragma once
#ifndef _BOSS_H                 // Prevent multiple definitions if this 
#define _BOSS_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#define _USE_MATH_DEFINES

#include "entity.h"
#include "constants.h"
#include <string>
#include "bossShield.h"
#include "bossCannon.h"


namespace bossNS
{
	const int MAXHP = 2000;
	const int WIDTH = 128;                   // image width
	const int HEIGHT = 128;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	//const float SPEED = 100;                // 100 pixels per second
	const int   TEXTURE_COLS = 2;           // texture has 2 columns
	////////////BARON :: FORM 1////////////////////////////
	const int   BARON_START_FRAME = 0;      // boss starts at frame 0
	const int   BARON_END_FRAME = 2;        // boss animation frames 0,1,2 
	const int	BARON_CHANNEL_START_FRAME = 3;	//frame 3,4 is used for attack
	const int	BARON_CHANNEL_END_FRAME = 4;	//frame 3,4 is used for attack
	const int	BARON_ATTACK_FRAME = 5;
	const int	BARON_RELOADING_TIMER = 6;
	const int	BARON_CHANNELING_TIMER = 3;
	const int	BARON_ATTACKING_TIMER = 6;
	const float BARON_ANIMATION_DELAY = 0.5f;    // time between frames
	/*int	BARON_RELOADING_TIMER = 6;
	int	BARON_CHANNELING_TIMER = 3;
	int	BARON_ATTACKING_TIMER = 6;*/
	///////////////////////////////////////////////////////
	////////////NORAB :: FORM 2////////////////////////////
	const int   NORAB_START_FRAME = 6;      // boss starts at frame 6
	const int   NORAB_END_FRAME = 8;        // boss animation frames 6,7,8 
	const int	NORAB_CHANNEL_START_FRAME = 9;	//frame 9,10 is used for attack
	const int	NORAB_CHANNEL_END_FRAME = 10;	//frame 9,10 is used for attack
	const int	NORAB_ATTACK_FRAME = 11;
	const int	NORAB_RELOADING_TIMER = 4;
	const int	NORAB_CHANNELING_TIMER = 2;
	const int	NORAB_ATTACKING_TIMER = 4;
	const float NORAB_ANIMATION_DELAY = 0.5f;    // time between frames
	/*int	NORAB_RELOADING_TIMER = 4;
	int	NORAB_CHANNELING_TIMER = 2;
	int	NORAB_ATTACKING_TIMER = 4;*/
	///////////////////////////////////////////////////////
	const int form = 1;
	const int damage = 1;
	const int COLLISION_RADIUS = WIDTH*2/3;
	//1
	
	//2

	//3
	const int MOVEMENT_SPEED = 40;
}

enum BOSS_STATUS {
	NotSpawn = 0,
	Reloading = 1,
	Channeling = 2,
	Attacking = 3,
	Dead = 4,
};

class Boss : public Entity
{ 
protected:
	int HP = 2000;
	int form = 1;
	int damage = 1;
	//enum class STATUS {RELOAD_STATE, ATTACK_STATE}
	bool spawn = true;
	Image boss_form;
	BOSS_STATUS _boss_Status; //how does this work???
	int frameTimer = 0;
	int bossTimer = 0;
	bool reloading = true;
	bool channeling = false;
	bool attacking = false;
	bool shieldOn = false;
	BossShield *shield;
public:
	// constructor
	Boss();
	
	//common functions
	int getDamage();
	void setDamage(int dmg);
	int getHP();
	int getForm();
	bool isSpawn();
	void takesDamage(int dmgValue);
	bool hasShield();
	bool isReloading();
	bool isChanneling();
	bool isAttacking();
	void changeMotion(bool motion);

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