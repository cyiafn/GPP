// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.h v1.0

#ifndef _THREECS_H              // Prevent multiple definitions if this 
#define _THREECS_H              // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "textureManager.h"
#include "image.h"

#include "textDX.h"
#include "player.h"
#include "wall.h"
#include "constants.h"
#include "zombie.h"
#include "boss.h"
#include "playerHealth.h"
#include "bullet.h"

namespace dontdieNS
{

	//const char FONT[] = "Arial Bold";  // font
	const int TEXTURE_SIZE = 64;
	const int TEXTURE_COLS = 1;
	const int MAP_HEIGHT = 9;
	const int MAP_WIDTH = 12;
	const float SCROLL_RATE = 10;
	const int __ = -1;                  // empty tile

	const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0,
		 0,0,0,0,0,0,0,0,0,0,0,0
	};
}

class dontdie : public Game
{
private:
    // game items
	float mapX;
	float mapY;

	TextureManager bossTexture;
	Boss boss1;
	Boss boss2;
	Boss boss3;

	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager playerHealthTexture; 
	TextureManager wallTexture; //wall texture
	TextureManager zombieTexture;
	TextureManager PbulletTexture;
	TextureManager SMGbulletTexture;
	TextureManager ShotgunbulletTexture;
	TextureManager RiflebulletTexture;
	
	Image map;                 // map image
	Image player;                 // player image
	Image playerhealth;
	Image zombie;
	Image wall;				 // wall image	
	Image pistolBullet;          // pistol bullet image
	Image smgBullet;
	Image shotgunBullet;
	Image rifleBullet;

	Player player1;
    PlayerHealth player1health;
	Zombie zombie1;
	Wall wallArray[10];
	Bullet pistolBulletArray[10000], smgBulletArray[100000], shotgunBulletArray[10000], rifleBulletArray[10000];

	float pistolBuffer,smgBuffer,shotgunBuffer,rifleBuffer;
	int stage;
	int pBullets,smgBullets,rifleBullets;

	//tempHP
	TextDX  *dxFontSmall;       // DirectX fonts
public:
	//Constructor
	dontdie();

	//Deconstructor
    virtual ~dontdie();

	//Initialize the game
    void initialize(HWND hwnd);
    void reset();
    void update();
	void ai() {};
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};

#endif
