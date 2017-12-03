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
#include "tank.h"
#include "spitter.h"
#include "spitterbullet.h"
#include <vector>



class dontdie : public Game
{
private:
    // game items
	TextureManager bossTexture;
	Boss boss1;
	Boss boss2;
	Boss boss3;
    // game items	
	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager wallTexture; //wall texture
	TextureManager zombieTexture;
	TextureManager tankTexture;
	TextureManager spitterTexture;
	TextureManager spitterbulletTexture;

	Image   map;                 // map image
	Image   player;                 // player image
	Image zombie;
	Image	wall;				 // wall image
	Image tank;
	Image spitter;
	Image spitterbullet;

	Player player1;
	Zombie zombie1;
	Wall wallArray[10];
	std::vector<Zombie> zombieArray;
	std::vector<Tank> tankArray;
	std::vector<Spitter> spitterArray;
	std::vector<Spitterbullet> spitterbulletArray;
	int spitterbulletID;
	
    // game variables

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
	void ai();
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};

#endif
