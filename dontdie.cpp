
#include "dontdie.h"
#include "input.h"
#include "wall.h"
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
	if (!mapTexture.initialize(graphics, MAP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Map texture"));
	//Wall texture

	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wall texture"));
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
	// Wall 
	if (!wallArray[0].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[0].setX(GAME_WIDTH / 10 * 2);
	wallArray[0].setY(GAME_HEIGHT / 4);

	if (!wallArray[1].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[1].setX(GAME_WIDTH / 10 * 4);
	wallArray[1].setY(GAME_HEIGHT / 4);

	if (!wallArray[2].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[2].setX(GAME_WIDTH / 10 * 6);
	wallArray[2].setY(GAME_HEIGHT / 4);

	if (!wallArray[3].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[3].setX(GAME_WIDTH / 10 * 7);
	wallArray[3].setY(GAME_HEIGHT / 4);

	if (!wallArray[4].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[4].setX(GAME_WIDTH / 10 * 10);
	wallArray[4].setY(GAME_HEIGHT / 4);

	if (!wallArray[5].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[5].setX(GAME_WIDTH / 10 * 2);
	wallArray[5].setY(GAME_HEIGHT / 4 * 2);

	if (!wallArray[6].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[6].setX(GAME_WIDTH / 10 * 4);
	wallArray[6].setY(GAME_HEIGHT / 4 * 2);

	if (!wallArray[7].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[6].setX(GAME_WIDTH / 10 * 6);
	wallArray[6].setY(GAME_HEIGHT / 4 * 2);

	if (!wallArray[8].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[8].setX(GAME_WIDTH / 10 * 8);
	wallArray[8].setY(GAME_HEIGHT / 4 * 2);

	if (!wallArray[9].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[9].setX(GAME_WIDTH / 10 * 10);
	wallArray[9].setY(GAME_HEIGHT / 4 * 2);
	// Player
	if (!player1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));
	player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	player1.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player1.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//player1.setDegrees((atan2(player1.getY - input->getMouseY() , player1.getX - input->getMouseX()) * 180) / PI);     //angle of player

	if (!zombie1.initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));
	}
	zombie1.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_START_FRAME);
	zombie1.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	zombie1.setFrameDelay(zombieNS::ZOMBIE_ANIMATION_DELAY);



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
	for (int i = 0; i < 10; i++)
	{
		wallArray[i].update(frameTime);
	}
	
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

	
	map.draw();         //adds the map to the scene
	zombie1.draw();
	for (int i = 0; i < 10; i++)
	{
		wallArray[i].draw();
	}
	player1.draw();     //adds the player into the scene


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
	wallTexture.onLostDevice();
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
	wallTexture.onResetDevice();
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
	for (int i = 0; i < 10; i++)
	{
		if (player1.collidesWith(wallArray[i], tempVector))
		{
			player1.revertLocation();
			zombie1.revertLocation();
		}
	}
}