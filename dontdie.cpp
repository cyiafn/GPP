
#include "dontdie.h"
#include "input.h"
#include <string>
using namespace dontdieNS;
using namespace wallNS;

//=============================================================================
// Constructor
//=============================================================================
dontdie::dontdie()
{
	mapX = 0;
	mapY = 0;
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
	map.setFrames(0, 0);
	map.setCurrentFrame(0);
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
	float playerY;

	player1.setPrev(player1.getX(), player1.getY());
	zombie1.setPrev(zombie1.getX(), zombie1.getY());
	player1.update(frameTime);
	zombie1.update(frameTime);
	map.update(frameTime);

	playerY = player1.getY();
	if (playerY < 0)                  // if butterfly off screen left
	{
		mapY -= player1.getVelocity().y * frameTime;  // scroll map right
		player1.setY(0);              // put butterfly at left edge
	}
	// if butterfly off screen right
	else if (playerY > GAME_HEIGHT - player1.getHeight())
	{
		mapY-= player1.getVelocity().y * frameTime;  // scroll map left
														// put butterfly at right edge
		player1.setY((float)(GAME_HEIGHT - player1.getHeight()));
	}

	if (mapY > 0)    // if map past left edge
	{
		mapY = 0;   // stop at left edge of map
		//player1.setVelocityX(0);  // stop butterfly
	}
	// if map past right edge
	else if (mapY < (-MAP_HEIGHT * TEXTURE_SIZE) + GAME_HEIGHT)
	{
		// stop at right edge of map
		mapY = (-MAP_HEIGHT * TEXTURE_SIZE) + GAME_HEIGHT;
		//player1.setVelocityX(0);  // stop butterfly
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
	for (int row = 0; row<MAP_HEIGHT; row++)       // for each row of map
	{
		map.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col<MAP_WIDTH; col++)    // for each column of map
		{
			if (tileMap[row][col] >= 0)          // if tile present
			{
				map.setCurrentFrame(tileMap[row][col]);    // set tile texture
				map.setX((float)(col*TEXTURE_SIZE) + mapX);   // set tile X
															   // if tile on screen
				if (map.getX() > -TEXTURE_SIZE && map.getX() < GAME_WIDTH)
				{
					map.draw();                // draw tile
				}
			}
		}
	}

	for (int row = 0; row<WALL_HEIGHT; row++)       // for each row of map
	{
		wall1.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col<WALL_WIDTH; col++)    // for each column of map
		{
			if (wallSpace[row][col] >= 0)          // if tile present
			{
				wall1.setCurrentFrame(wallSpace[row][col]);    // set tile texture
				wall1.setX((float)(col*TEXTURE_SIZE) + mapX);   // set tile X
															  // if tile on screen
				if (wall1.getX() > -TEXTURE_SIZE && wall.getX() < GAME_WIDTH)
				{
					wall1.draw();                // draw tile
				}
			}
		}
	}
	zombie1.draw();
	//map.draw();         //adds the map to the scene
	//wall1.draw();		//adds the wall to the scene
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