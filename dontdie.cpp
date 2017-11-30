
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
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
	// boss form 1 image
	if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
	if (!shieldTexture.initialize(graphics, BOSS1_SHIELD))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shield texture"));
	}
	if (!shield.initialize(this, ShieldNS::WIDTH, ShieldNS::HEIGHT, 2, &shieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield"));

	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setX(ShieldNS::X);
	shield.setY(ShieldNS::Y);

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
	fpscounter++;
	player1.setPrev(player1.getX(), player1.getY());
	zombie1.setPrev(zombie1.getX(), zombie1.getY());
	player1.update(frameTime);
	zombie1.update(frameTime);
	map.update(frameTime);
	boss.update(frameTime);
	if (boss.getHP() < bossNS::MAXHP/2)
	{
		boss.setForm(2);
		if (!bossTexture.initialize(graphics, BOSS_IMAGE))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
		// boss form 2 image
		if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
		boss.setFrames(bossNS::NORAB_START_FRAME, bossNS::NORAB_END_FRAME);
		boss.setCurrentFrame(bossNS::NORAB_START_FRAME);
	}
	if (fpscounter % 60 == 0)
	{
		seconds++;
		if (seconds % 5 == 0 && boss.getStatus() == 1) //after 5 secs, transitiion ATTACK to RELOAD
		{
			seconds = 0;
			boss.changeStatus();
			boss.setFrames(bossNS::BARON_START_FRAME, bossNS::BARON_END_FRAME);
			boss.setCurrentFrame(bossNS::BARON_START_FRAME);
			boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
			boss.setLoop(true);
		}
		else if (seconds % 5 == 0 && boss.getStatus() == 0) //after 5 secs, transition RELOAD to ATTACK
		{
			seconds = 0;
			boss.changeStatus();
			boss.setFrames(bossNS::BARON_CHANNEL_FRAME, bossNS::BARON_ATTACK_FRAME);
			boss.setCurrentFrame(bossNS::BARON_CHANNEL_FRAME);
			boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
			boss.setLoop(true);
		}
	}
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
	boss.draw();


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
	bossTexture.onLostDevice();
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
	bossTexture.onResetDevice();
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
	if (player1.collidesWith(boss, tempVector))
	{
		player1.revertLocation();
		player1.damageMe(boss.getDamage());
		if (player1.getHp() == 0)
		{
			player1.setX(GAME_WIDTH / 2);

			player1.setY(GAME_HEIGHT / 4);
		}
	}
}