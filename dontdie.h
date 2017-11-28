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

class dontdie : public Game
{
private:
    // game items	
	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager wallTexture; //wall texture

	Image   map;                 // map image
	Image   player;              // player image
	Image	wall;				 // wall image	

	Player player1;
	Wall wall1;
    // game variables

public:
	dontdie();
    virtual ~dontdie();
    void initialize(HWND hwnd);
    void reset();
    void update();
    void ai() {};
    void collisions() ;
    void render();
    void releaseAll();
    void resetAll();
};

#endif
