// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 8 threeCsDX.cpp v1.0

#include "dontdie.h"

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
	if (!zombieTexture.initialize(graphics, ZOMBIE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing game textures"));
    // initialize DirectX fonts
    // 15 pixel high Arial
	if (!zombie1.initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship1"));
	zombie1.setFrames(zombieNS::ZOMBIE_START_FRAME, zombieNS::ZOMBIE_END_FRAME);
	zombie1.setCurrentFrame(zombieNS::ZOMBIE_START_FRAME);
	zombie1.setX(GAME_WIDTH / 4);
	zombie1.setY(GAME_HEIGHT / 4);
	zombie1.setVelocity(VECTOR2(zombieNS::SPEED, -zombieNS::SPEED)); // VECTOR2(X, Y)

    

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
	zombie1.update(frameTime);
}

//=============================================================================
// render game items
//=============================================================================
void dontdie::render()
{

    graphics->spriteBegin();

	zombie1.draw();
	 
    graphics->spriteEnd();


}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void dontdie::releaseAll()
{
	zombieTexture.onResetDevice();
    Game::releaseAll();
    return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces and reset all entities.
//=============================================================================
void dontdie::resetAll()
{
	zombieTexture.onResetDevice();
    Game::resetAll();
    return;
}
