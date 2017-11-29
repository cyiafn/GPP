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
#include "constants.h"
#include "zombie.h"
#include "boss.h"
#include "bossShield.h"

class dontdie : public Game
{
private:
    // game items
	
	Boss boss1, boss2, boss3;
	BossShield shield;
    // game items	
	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager zombieTexture;
	TextureManager bossTexture;
	TextureManager shieldTexture;

	Image   map;                 // map image
	Image   player;                 // player image
	Image zombie;

	Player player1;
	Zombie zombie1;
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
    void ai() {};
    void collisions();
    void render();
    void releaseAll();
    void resetAll();
};

#endif
