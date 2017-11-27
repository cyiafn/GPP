// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "dontdie.h"
#include "input.h"

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

	//// initialize DirectX fonts
	//// 15 pixel high Arial
	//if (!zombie1.initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));
	//zombie1.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	//zombie1.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	//zombie1.setX(GAME_WIDTH / 4);
	//zombie1.setY(GAME_HEIGHT / 4);
	//zombie1.setVelocity(VECTOR2(zombieNS::SPEED, -zombieNS::SPEED)); // VECTOR2(X, Y)


	// throws GameError
	// Map texture
	if (!mapTexture.initialize(graphics, MAP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Map texture"));
	// Player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player texture"));

	// Map 
	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));

	// Player
	if (!player.initialize(graphics, 0, 0, 0, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player"));
	player.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_END_FRAME);   // animation frames ship.setCurrentFrame(SHIP_START_FRAME);             
	player.setCurrentFrame(playerNS::PLAYER_START_FRAME);																	  // starting frame
	player.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//ship.setDegrees((atan2(ship.getY - getMouseY() , ship.getX - getMouseX()) * 180) / M_PI);                             // angle of ship
	player.setColorFilter(SETCOLOR_ARGB(255, 230, 230, 255));   // light blue, used for shield and torpedo


	reset();            // reset all game variables
	fpsOn = true;       // display frames per second
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
	player.update(frameTime);
	if (input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
	{
		player.setX(player.getX() + frameTime * PLAYER_SPEED);
		if (player.getX() > GAME_WIDTH)               // if off screen right
			player.setX((float)-player.getWidth());  // position off screen left
	}
	if (input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
	{
		player.setX(player.getX() - frameTime * PLAYER_SPEED);
		if (player.getX() < -player.getWidth())         // if off screen left
			player.setX((float)GAME_WIDTH);      // position off screen right
	}
	if (input->isKeyDown(PLAYER_UP_KEY))               // if move up
	{
		player.setY(player.getY() - frameTime * PLAYER_SPEED);
		if (player.getY() < -player.getHeight())        // if off screen top
			player.setY((float)GAME_HEIGHT);     // position off screen bottom
	}

	if (input->isKeyDown(PLAYER_DOWN_KEY))             // if move down
	{
		player.setY(player.getY() + frameTime * PLAYER_SPEED);
		if (player.getY() > GAME_HEIGHT)              // if off screen bottom
			player.setY((float)-player.getHeight());    // position off screen top
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
	player.draw();      //adds the player into the scene

	if (fpsOn)           // if fps display requested
	{
		// convert fps to Cstring
		_snprintf_s(buffer, BUF_SIZE, "fps %d ", (int)fps);
		dxFont.print(buffer, GAME_WIDTH - 200, GAME_HEIGHT - 50);
	}

	graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void dontdie::releaseAll()
{
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
	mapTexture.onResetDevice();
	playerTexture.onResetDevice();
	Game::resetAll();
	return;
}
