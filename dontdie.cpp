
#include "dontdie.h"
#include "input.h"
#include "wall.h"
#include <string>
#include "astar.h"
#include "zombie.h"

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
	//ASTAR Algorithm MAP generation
	this->spitterbulletID = 0;
	this->spawnbuffer = 30;
	this->stage = 0;
	this->zombieStageOneSpawn = 50;
	this->zombieStageTwoSpawn = 40;
	this->TankStageTwoSpawn = 10;
	this->zombieStageThreeSpawn = 30;
	this->TankStageThreeSpawn = 10;
	this->SpitterStageThreeSpawn = 10;
	this->currentSpawn = 0;
	this->stageSpawnComplete = false;
	this->stageBufferTime = 180;

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
	if (!tankTexture.initialize(graphics, TANK_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Tank texture"));
	}
	if (!spitterTexture.initialize(graphics, SPITTER_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Spitter texture"));
	}
	if (!spitterbulletTexture.initialize(graphics, SPITTERBULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Tank texture"));
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

	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (!zombieArray[zomb].initialize(this, zombieNS::WIDTH, zombieNS::HEIGHT, zombieNS::TEXTURE_COLS, &zombieTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing zombie texture"));
		}
		zombieArray[zomb].setInitialised(false);
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (!tankArray[tank].initialize(this, tankNS::WIDTH, tankNS::HEIGHT, tankNS::TEXTURE_COLS, &tankTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing tank texture"));
		}
		tankArray[tank].setInitialised(false);
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (!spitterArray[spitter].initialize(this, spitterNS::WIDTH, spitterNS::HEIGHT, spitterNS::TEXTURE_COLS, &spitterTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spitter texture"));
		}
		spitterArray[spitter].setInitialised(false);
	}
	for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
	{
		if (!spitterbulletArray[spitterb].initialize(this, spitterbulletNS::WIDTH, spitterbulletNS::HEIGHT, spitterbulletNS::TEXTURE_COLS, &spitterbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing spitter bullet texture"));
		}
		spitterbulletArray[spitterb].setInitialised(false);
	}

	//zombie1.setPlayerLoc(player1.getX(), player1.getY());



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
	

	player1.update(frameTime);
	//zombie1.setPlayerLoc(player1.getX(), player1.getY());
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			zombieArray[zomb].setPrev(zombieArray[zomb].getX(), zombieArray[zomb].getY());
			zombieArray[zomb].update(frameTime);
		}
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			tankArray[tank].setPrev(tankArray[tank].getX(), tankArray[tank].getY());
			tankArray[tank].update(frameTime);
		}
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			spitterArray[spitter].setPrev(spitterArray[spitter].getX(), spitterArray[spitter].getY());
			spitterArray[spitter].update(frameTime);
		}
	}
	for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
	{
		if (spitterbulletArray[spitterb].isInitialised() == true)
		{
			spitterbulletArray[spitterb].update(frameTime);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		wallArray[i].update(frameTime);
	}

	if (checkStageClear() == true)
	{
		stage += 1;
		stageSpawnComplete = false;
	}
	if (stage == 1)
	{
		if (spawnbuffer == 30)
		{
			if (stageSpawnComplete == false)
			{
				if (zombieStageOneSpawn != 0)
				{
					zombieStageOneSpawn -= 1;
					zombieArray[zombieStageOneSpawn - 1].setInitialised(true);
					zombieArray[zombieStageOneSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						zombieArray[zombieStageOneSpawn - 1].setX(0 + zombieArray[zombieStageOneSpawn - 1].getWidth());
						zombieArray[zombieStageOneSpawn - 1].setY(0 + zombieArray[zombieStageOneSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						zombieArray[zombieStageOneSpawn - 1].setX(0 + zombieArray[zombieStageOneSpawn - 1].getWidth());
						zombieArray[zombieStageOneSpawn - 1].setY(720 - zombieArray[zombieStageOneSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						zombieArray[zombieStageOneSpawn - 1].setX(1280 - zombieArray[zombieStageOneSpawn - 1].getWidth());
						zombieArray[zombieStageOneSpawn - 1].setY(720 - zombieArray[zombieStageOneSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						zombieArray[zombieStageOneSpawn - 1].setX(1280 - zombieArray[zombieStageOneSpawn - 1].getWidth());
						zombieArray[zombieStageOneSpawn - 1].setY(0 + zombieArray[zombieStageOneSpawn - 1].getHeight());
						currentSpawn = 0;
					}
				}
				else
				{
					stageSpawnComplete = true;
				}
			}
		}
		else
		{
			spawnbuffer += 1;
		}
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
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			zombieArray[zomb].draw();
		}
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			tankArray[tank].draw();
		}
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			spitterArray[spitter].draw();
		}
	}
	for (int spitterb = 0; spitterb < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); spitterb++)
	{
		if (spitterbulletArray[spitterb].isInitialised() == true)
		{
			spitterbulletArray[spitterb].draw();
		}
	}
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
	tankTexture.onLostDevice();
	spitterTexture.onLostDevice();
	spitterbulletTexture.onLostDevice();
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
	tankTexture.onResetDevice();
	spitterTexture.onLostDevice();
	spitterbulletTexture.onLostDevice();
	Game::resetAll();
	return;
}


void dontdie::collisions()
{
	VECTOR2 tempVector;
	for (int i = 0; i < 10; i++)
	{
		if (player1.collidesWith(wallArray[i], tempVector))
		{
			player1.revertLocation();
		}
	}
}

void dontdie::ai()
{
	//zombie AI
	VECTOR2 dir, tempVec, wallVec;
	float up, down, left, right, upChange,downChange,leftChange,rightChange;
	string failDirection = "";
	int voronoi;
	bool failCheck = false;
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			dir.x = player1.getX() - zombieArray[zomb].getX();
			dir.y = player1.getY() - zombieArray[zomb].getY();
			float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
			dir.x /= hyp;
			dir.y /= hyp;
			dir.x *= zombieNS::ZOMBIE_SPEED;
			dir.y *= zombieNS::ZOMBIE_SPEED;
			zombieArray[zomb].setVelocity(dir);
			float angle = atan2(player1.getY() - zombieArray[zomb].getY(), player1.getX() - zombieArray[zomb].getX()) * (180 / PI) + 90;
			 zombieArray[zomb].setDegrees(angle);
			for (int i = 0; i < ARRAYSIZE(wallArray); i++)
			{
				if ( zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					 zombieArray[zomb].revertLocation();
					 zombieArray[zomb].setX( zombieArray[zomb].getX() + 1);
					if ( zombieArray[zomb].collidesWith(wallArray[i], tempVec))
					{
						failDirection = "right";
						// zombieArray[zombie].revertLocation();
					}
					 zombieArray[zomb].revertLocation();
					if (failDirection == "")
					{
						 zombieArray[zomb].setX( zombieArray[zomb].getX() - 1);
						if ( zombieArray[zomb].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "left";
							// zombieArray[zombie].revertLocation();
						}
						 zombieArray[zomb].revertLocation();
					}
					if (failDirection == "")
					{
						 zombieArray[zomb].setY( zombieArray[zomb].getY() - 1);
						if ( zombieArray[zomb].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "up";
							// zombieArray[zombie].revertLocation();
						}
						 zombieArray[zomb].revertLocation();
					}
					if (failDirection == "")
					{
						 zombieArray[zomb].setY( zombieArray[zomb].getY() + 1);
						if ( zombieArray[zomb].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "down";
							// zombieArray[zombie].revertLocation();
						}
						 zombieArray[zomb].revertLocation();
					}
					if (failDirection == "right")
					{

						float xValue = player1.getX() -  zombieArray[zomb].getX();
						if (xValue < 0)
						{
							xValue *= -1;
						}
						float yValue = player1.getY() -  zombieArray[zomb].getY();
						if (yValue < 0)
						{
							yValue *= -1;
						}
						if (player1.getY() >=  zombieArray[zomb].getY())
						{
							upChange = 1;
							downChange = -1;
						}
						else
						{
							upChange = -1;
							downChange = 1;

						}
						up = sqrt(xValue * xValue + (yValue + upChange) * (yValue + upChange));
						down = sqrt(xValue * xValue + (yValue + downChange) * (yValue + downChange));
						//left = sqrt((xValue-1) * (xValue-1) + (yValue) * (yValue));
						if ( zombieArray[zomb].checkVoronoiRegion(wallArray[i], tempVec))
						{
							if (up < down)
							{
								wallVec.x = 0;
								wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
								 zombieArray[zomb].setVelocity(wallVec);
							}
							else
							{
								wallVec.x = 0;
								wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
								 zombieArray[zomb].setVelocity(wallVec);
							}
						}
						else if (up < down)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (down < up)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (down == up)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						//else if (left <= up && left <= down)
						//{
						//	wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
						//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
						//	 zombieArray[zombie].setVelocity(wallVec);
						//}
					}
					else if (failDirection == "left")
					{
						float xValue = player1.getX() -  zombieArray[zomb].getX();
						if (xValue < 0)
						{
							xValue *= -1;
						}
						float yValue = player1.getY() -  zombieArray[zomb].getY();
						if (yValue < 0)
						{
							yValue *= -1;
						}
						if (player1.getY() >=  zombieArray[zomb].getY())
						{
							upChange = 1;
							downChange = -1;
						}
						else
						{
							upChange = -1;
							downChange = 1;

						}


						up = sqrt(xValue * xValue + (yValue + upChange)* (yValue + upChange));
						down = sqrt(xValue * xValue + (yValue + downChange)* (yValue + downChange));
						//right = sqrt((xValue + 1) * (xValue + 1) + (yValue) * (yValue));
						if ( zombieArray[zomb].checkVoronoiRegion(wallArray[i], tempVec))
						{
							if (up < down)
							{
								wallVec.x = 0;
								wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
								 zombieArray[zomb].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0;
								wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
								 zombieArray[zomb].setVelocity(wallVec);
							}
						}
						else if (up < down)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (down < up)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (down == up)
						{
							wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 1 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						//else if (right <= up && right <= down)
						//{
						//	wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
						//	wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
						//	 zombieArray[zombie].setVelocity(wallVec);
						//}
					}
					else if (failDirection == "up")
					{
						float xValue = player1.getX() -  zombieArray[zomb].getX();
						if (xValue < 0)
						{
							xValue *= -1;
						}
						float yValue = player1.getY() -  zombieArray[zomb].getY();
						if (yValue < 0)
						{
							yValue *= -1;
						}
						if (player1.getX() >=  zombieArray[zomb].getX())
						{
							leftChange = 1;
							rightChange = -1;
						}
						else
						{
							leftChange = -1;
							rightChange = 1;
						}
						left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
						//down = sqrt(xValue * xValue + (yValue + 1)* (yValue + 1));
						right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
						if (left < right)
						{
							wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (right < left)
						{
							wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (right == left)
						{
							wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}
					}
					else if (failDirection == "down")
					{
						float xValue = player1.getX() -  zombieArray[zomb].getX();
						if (xValue < 0)
						{
							xValue *= -1;
						}
						float yValue = player1.getY() -  zombieArray[zomb].getY();
						if (yValue < 0)
						{
							yValue *= -1;
						}
						if (player1.getX() >=  zombieArray[zomb].getX())
						{
							leftChange = 1;
							rightChange = -1;
						}
						else
						{
							leftChange = -1;
							rightChange = 1;
						}
						left = sqrt((xValue + leftChange) * (xValue + leftChange) + (yValue) * (yValue));
						//up = sqrt(xValue * xValue + (yValue - 1)* (yValue - 1));
						right = sqrt((xValue + rightChange) * (xValue + rightChange) + (yValue) * (yValue));
						if (left < right)
						{
							wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						//else if (up <= left && up <= right)
						//{
						//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
						//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
						//	 zombieArray[zombie].setVelocity(wallVec);
						//}
						else if (right < left)
						{
							wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;;
							 zombieArray[zomb].setVelocity(wallVec);
						}
						else if (right == left)
						{
							wallVec.x = 1 * zombieNS::ZOMBIE_SPEED;
							wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
							 zombieArray[zomb].setVelocity(wallVec);
						}

					}

				}
			}
			VECTOR2 tempVector;
			if (player1.collidesWith( zombieArray[zomb], tempVector))
			{
				player1.revertLocation();
				 zombieArray[zomb].revertLocation();
				player1.damageMe( zombieArray[zomb].getDamage());
				if (player1.getHp() == 0)
				{
					player1.setX(GAME_WIDTH / 2);
					//player1.setY(GAME_HEIGHT / 2);
				}
			}
			 zombieArray[zomb].setPrev( zombieArray[zomb].getX(),  zombieArray[zomb].getY());
		}
	}
	


	//Tank AI


	//Spitter AI
	

}
	

bool dontdie::checkStageClear()
{
	int zombieCount = 0;
	int tankCount = 0;
	int spitterCount = 0;
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		if (zombieArray[zomb].isInitialised() == true)
		{
			zombieCount += 1;
		}
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			tankCount += 1;
		}
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (zombieArray[spitter].isInitialised() == true)
		{
			zombieCount += 1;
		}
	}
	if (zombieCount == 0 && tankCount == 0 && spitterCount == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}