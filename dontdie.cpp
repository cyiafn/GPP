
#include "dontdie.h"
#include "input.h"
#include <string>

//=============================================================================
// Constructor
//=============================================================================
dontdie::dontdie()
{

}

//=============================================================================
// Destructor
//=============================================================================
dontdie::~dontdie()
{
	releaseAll();               // call deviceLost() for every graphics item
}

//=============================================================================
// initializes the game
// Throws GameError on error
//=============================================================================
void dontdie::initialize(HWND hwnd)
{
	Game::initialize(hwnd);
	graphics->setBackColor(graphicsNS::WHITE);


	// Map texture
	//if (!mapTexture.initialize(graphics, MAP_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Map texture"));
	// Player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player texture"));

	// Zombie Texture
	if (!zombieTexture.initialize(graphics, ZOMBIE_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Zombie texture"));
	}

	// Map 
	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	// Player
	if (!player1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	player1.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player1.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//player1.setDegrees((atan2(ship.getY - getMouseY() , ship.getX - getMouseX()) * 180) / M_PI);     //angle of player

	if (!zombie1.initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));
	}
	zombie1.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_START_FRAME);
	zombie1.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	zombie1.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);

	// boss form 1 texture
	// if hp >66%
	if (!bossTexture.initialize(graphics, BOSS_IMAGE1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
	if (!shieldTexture.initialize(graphics, BOSS1_SHIELD))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shield texture"));
	}
	// boss form 1 image
	if (!boss1.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture, 1))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
	
	boss1.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
	boss1.setCurrentFrame(bossNS::BOSS_START_FRAME);
	if (!shield.initialize(this, ShieldNS::WIDTH, ShieldNS::HEIGHT, 2, &shieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield"));
	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setX(ShieldNS::SHIELDX);
	shield.setY(ShieldNS::SHIELDY);
	////boss 2? if hp > 33% < 66%
	//if (!bossTexture.initialize(graphics, BOSS_IMAGE2))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 2 texture"));
	//if (!boss2.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));

	//boss2.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
	//boss2.setCurrentFrame(bossNS::BOSS_START_FRAME);

	//// if hp <33%
	//if (!bossTexture.initialize(graphics, BOSS_IMAGE3))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 3 texture"));

	reset();            // reset all game variables
	return;
}


//=============================================================================
// Reset the game to begin play and after a score
//=============================================================================
void dontdie::reset()
{
	return;
}

//=============================================================================
// move all game items
// frameTime is used to regulate the speed of movement
//=============================================================================
void dontdie::update()
{
	player1.setPrev(player1.getX(), player1.getY());
	zombie1.setPrev(zombie1.getX(), zombie1.getY());
	player1.update(frameTime);
	zombie1.update(frameTime);
	boss1.update(frameTime);
	
	map.update(frameTime);
}

//=============================================================================
// render game items
//=============================================================================
void dontdie::render()
{
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];

	graphics->spriteBegin();

	zombie1.draw();
	map.draw();         //adds the map to the scene
	player1.draw();      //adds the player into the scene
	boss1.draw();


	graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void dontdie::releaseAll()
{
	zombieTexture.onLostDevice();
	mapTexture.onLostDevice();
	playerTexture.onLostDevice();
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void dontdie::resetAll()
{
	zombieTexture.onLostDevice();
	mapTexture.onResetDevice();
	playerTexture.onResetDevice();
	Game::resetAll();
	return;
}


void dontdie::collisions()
{
	VECTOR2 tempVector;
	if (player1.collidesWith(zombie1, tempVector))
	{
		player1.revertLocation();
		zombie1.revertLocation();
		player1.damageMe(zombie1.getDamage());
		if (player1.getHp() == 0)
		{
			//player1.setX(GAME_WIDTH / 2);
			
			player1.setY(GAME_HEIGHT / 2);
		}
	}
}