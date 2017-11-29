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

namespace astarNS
{
	const int n = 1280; //x of the map
	const int m = 720; //y of the map
	static int map[n][m]; //use map cause x and y graph has 2 axis
	static int closed_nodes_map[n][m]; // map of checked nodes
	static int open_nodes_map[n][m]; // map of not tried nodes
	static int dir_map[n][m]; // map of directions
	const int dir = 8; // this is the number of possible directions to go to at any position, can be 4
	static int dx[dir] = { 1, 1, 0, -1, -1, -1, 0, 1 }; // direction x axis
	static int dy[dir] = { 0, 1, 1, 1, 0, -1, -1, -1 }; // direction y axis
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
	Wall wallArray[10];
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
