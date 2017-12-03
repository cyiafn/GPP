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

namespace dontdieNS
{
	const int TEXTURE_SIZE = 64;
	const int TEXTURE_COLS = 1;
	const int MAP_HEIGHT = 8;
	const int MAP_WIDTH = 16;
	const float SCROLL_RATE = 10;
	const int __ = -1;                  // empty tile

	const int tileMap[MAP_HEIGHT][MAP_WIDTH] = {
		__, 0,__,__, 1,__,__,__,12,13,__,__,__,__, 0,__,
		__,__,__,__,__,__,__,11,__,__,__,__,__,__,__,__,
		__,__,__, 2,__,__,__,15,__, 3,__,__,__,__, 3, 2,
		5, 4, 5, 6, 4, 4, 5,15, 4, 7, 5,__,14, 5, 7, 6
	};
}

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

	Image   map;                 // map image
	Image   player;                 // player image
	Image zombie;
	Image	wall;				 // wall image	

	Player player1;
	Zombie zombie1;
	Wall wall1;
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
