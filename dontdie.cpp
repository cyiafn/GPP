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
	if (!player1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player texture"));
	player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	player1.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player1.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//player1.setDegrees((atan2(ship.getY - getMouseY() , ship.getX - getMouseX()) * 180) / M_PI);     //angle of player

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
	player1.update(frameTime);
	if (input->isKeyDown(PLAYER_RIGHT_KEY) || input->isKeyDown(PLAYER_LEFT_KEY) || input->isKeyDown(PLAYER_UP_KEY) || input->isKeyDown(PLAYER_DOWN_KEY))
	{
		if (input->isKeyDown(PLAYER_RIGHT_KEY))            // if move right
		{
			player1.setX(player1.getX() + frameTime * PLAYER_SPEED);
			if (player1.getX() > GAME_WIDTH)               // if off screen right
				player1.setX((float)-player1.getWidth());  // position off screen left
		}
		if (input->isKeyDown(PLAYER_LEFT_KEY))             // if move left
		{
			player1.setX(player1.getX() - frameTime * PLAYER_SPEED);
			if (player1.getX() < -player1.getWidth())         // if off screen left
				player1.setX((float)GAME_WIDTH);      // position off screen right
		}
		if (input->isKeyDown(PLAYER_UP_KEY))               // if move up
		{
			player1.setY(player1.getY() - frameTime * PLAYER_SPEED);
			if (player1.getY() < -player1.getHeight())        // if off screen top
				player1.setY((float)GAME_HEIGHT);     // position off screen bottom
		}

		if (input->isKeyDown(PLAYER_DOWN_KEY))             // if move down
		{
			player1.setY(player1.getY() + frameTime * PLAYER_SPEED);
			if (player1.getY() > GAME_HEIGHT)              // if off screen bottom
				player1.setY((float)-player1.getHeight());    // position off screen top
		}
		player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_END_FRAME);
	}

	else
		player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
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
	player1.draw();      //adds the player into the scene

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
