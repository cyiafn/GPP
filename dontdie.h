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
#include "bossCannon.h"
#include <vector>
#include <list>

class dontdie : public Game
{
private:
    // game items
	
	Boss boss;
	BossShield shield;
    // game items	
	TextureManager mapTexture;   // map texture
	TextureManager playerTexture;     // player texture
	TextureManager zombieTexture;
	TextureManager bossTexture;
	TextureManager shieldTexture;
	TextureManager cannonTexture;
	TextureManager bossMAXHPTexture;
	TextureManager bossCURHPTexture;
	int fpscounter = 0;
	int seconds = 0;
	float CannonAngle = 0.0f;
	int	BARON_RELOADING_TIMER = bossNS::BARON_RELOADING_TIMER;
	int	BARON_CHANNELING_TIMER = bossNS::BARON_CHANNELING_TIMER;
	int	BARON_ATTACKING_TIMER = bossNS::BARON_ATTACKING_TIMER;
	int	NORAB_RELOADING_TIMER = bossNS::NORAB_RELOADING_TIMER;
	int	NORAB_CHANNELING_TIMER = bossNS::NORAB_CHANNELING_TIMER;
	int	NORAB_ATTACKING_TIMER = bossNS::NORAB_ATTACKING_TIMER;

	Image   map;                 // map image
	Image player;                 // player image
	Image zombie;
	Image bossMAXHP;
	Image bossCURHP;
	/*BossCannon cannon1;
	BossCannon cannon2;
	BossCannon cannon3;
	BossCannon cannon4;*/

	Player player1;
	Zombie zombie1;
	BossCannon CannonArray[36];
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
