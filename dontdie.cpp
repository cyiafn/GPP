
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
	if (!wall1.initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
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
	
	
	if (input->isKeyDown(PLAYER_RIGHT_KEY) || input->isKeyDown(PLAYER_LEFT_KEY) || input->isKeyDown(PLAYER_UP_KEY) || input->isKeyDown(PLAYER_DOWN_KEY))
	{
		if (input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
		{
			player1.setX(player1.getX() + frameTime * PLAYER_SPEED);
			if (player1.getX() > GAME_WIDTH)               // if off screen right
				player1.setX((float)-player1.getWidth());  // position off screen left
			player1.setDegrees(90.0f);
		}
		if (input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
		{
			player1.setX(player1.getX() - frameTime * PLAYER_SPEED);
			if (player1.getX() < -player1.getWidth())         // if off screen left
				player1.setX((float)GAME_WIDTH);      // position off screen right
			player1.setDegrees(270.0f);
		}
		if (input->isKeyDown(PLAYER_UP_KEY))               // if move up
		{
			player1.setY(player1.getY() - frameTime * PLAYER_SPEED);
			if (player1.getY() < -player1.getHeight())        // if off screen top
				player1.setY((float)GAME_HEIGHT);     // position off screen bottom
			if(input->isKeyDown(PLAYER_RIGHT_KEY))
			{
				player1.setDegrees(45.0f);
			}
			else if(input->isKeyDown(PLAYER_LEFT_KEY))
			{
				player1.setDegrees(315.0f);
			}
			else
				player1.setDegrees(0.0f);
		}

		if (input->isKeyDown(PLAYER_DOWN_KEY))             // if move down
		{
			player1.setY(player1.getY() + frameTime * PLAYER_SPEED);
			if (player1.getY() > GAME_HEIGHT)              // if off screen bottom
				player1.setY((float)-player1.getHeight());    // position off screen top
			if (input->isKeyDown(PLAYER_RIGHT_KEY))
			{
				player1.setDegrees(135.0f);
			}
			else if (input->isKeyDown(PLAYER_LEFT_KEY))
			{
				player1.setDegrees(225.0f);
			}
			else
			player1.setDegrees(180.0f);
		}
		player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_END_FRAME);
	}

	else
		player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);

	player1.setDegrees((atan2(player1.getY() - input->getMouseY(), player1.getX() - input->getMouseX()) * 180) / PI);     //angle of player
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
	wall1.draw();		//adds the wall to the scene
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
}