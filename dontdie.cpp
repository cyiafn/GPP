
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
	this->zombieStageThreeSpawn = 0;
	this->TankStageThreeSpawn = 0;
	this->SpitterStageThreeSpawn = 10;
	this->currentSpawn = 0;
	this->stageSpawnComplete = false;
	this->stageBufferTime = 180;
	this->clearCooldown = 180;

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
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initalizing Spitter bullet texture"));
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
	///////////////
	//BOSS HP BAR//
	///////////////
	if (!bossMAXHPTexture.initialize(graphics, BOSS_MAX_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP texture"));
	if (!bossMAXHP.initialize(graphics, 1000, 0, 0, &bossMAXHPTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP BAR"));
	bossMAXHP.setX(140); //centerize the HP bar
	bossMAXHP.setY(GAME_HEIGHT - 32); //show the HP bar at the bottom
	// BOSS
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
	if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
	// CANNON
	if (!cannonTexture.initialize(graphics, BOSSCANNON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannon texture"));
	for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
	{
		if (!CannonArray[cannonNo].initialize(this, Cannon::WIDTH, Cannon::HEIGHT, Cannon::TEXTURE_COLS, &cannonTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cannon textures"));
		}
		CannonArray[cannonNo].setInitialised(false);
		CannonArray[cannonNo].setX(Cannon::X);
		CannonArray[cannonNo].setY(Cannon::Y);
	}

	// SHIELD
	if (!shieldTexture.initialize(graphics, BOSS_SHIELD))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shield texture"));
	if (!shield.initialize(this, ShieldNS::WIDTH, ShieldNS::HEIGHT, ShieldNS::TEXTURE_COLS, &shieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield"));
	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setX(shield.getprevX());
	shield.setY(shield.getprevY());
	//zombieArray[0].setInitialised(true);
	//zombieArray[0].setX(500);
	//zombieArray[0].setY(500);
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

	boss.setSpawn(false);



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
	if (fpscounter % 60 == 0)
	{
		seconds++;
	}
	player1.setPrev(player1.getX(), player1.getY());
	
	if (player1.getHp() <= 0)
	{
		player1.setX(GAME_WIDTH / 2);
		//player1.setY(GAME_HEIGHT / 2);
	}
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
	if (clearCooldown != 180)
	{
		clearCooldown += 1;
	}
	if (input->isKeyDown(KILL_ALL))
	{
		if (clearCooldown == 180)
		{
			clearAllMobs();
			clearCooldown = 0;
		}
			
	}

	if (checkStageClear() == true)
	{
		stage += 1;
		stageSpawnComplete = false;
		spawnbuffer = 30;
		currentSpawn = 0;
	}
	if (stage == 1)
	{
		if (spawnbuffer == 30)
		{
			if (stageSpawnComplete == false)
			{
				if (zombieStageOneSpawn != 0)
				{

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
					zombieStageOneSpawn -= 1;
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
	if (stage == 2)
	{
		if (spawnbuffer == 30)
		{
			if (stageSpawnComplete == false)
			{
				if (zombieStageTwoSpawn != 0)
				{
					zombieArray[zombieStageTwoSpawn - 1].setInitialised(true);
					zombieArray[zombieStageTwoSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						zombieArray[zombieStageTwoSpawn - 1].setX(0 + zombieArray[zombieStageTwoSpawn - 1].getWidth());
						zombieArray[zombieStageTwoSpawn - 1].setY(0 + zombieArray[zombieStageTwoSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						zombieArray[zombieStageTwoSpawn - 1].setX(0 + zombieArray[zombieStageTwoSpawn - 1].getWidth());
						zombieArray[zombieStageTwoSpawn - 1].setY(720 - zombieArray[zombieStageTwoSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						zombieArray[zombieStageTwoSpawn - 1].setX(1280 - zombieArray[zombieStageTwoSpawn - 1].getWidth());
						zombieArray[zombieStageTwoSpawn - 1].setY(720 - zombieArray[zombieStageTwoSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						zombieArray[zombieStageTwoSpawn - 1].setX(1280 - zombieArray[zombieStageTwoSpawn - 1].getWidth());
						zombieArray[zombieStageTwoSpawn - 1].setY(0 + zombieArray[zombieStageTwoSpawn - 1].getHeight());
						currentSpawn = 0;
					}
					zombieStageTwoSpawn -= 1;

				}
				else if (TankStageTwoSpawn != 0)
				{

					tankArray[TankStageTwoSpawn - 1].setInitialised(true);
					tankArray[TankStageTwoSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						tankArray[TankStageTwoSpawn - 1].setX(0 + tankArray[TankStageTwoSpawn - 1].getWidth());
						tankArray[TankStageTwoSpawn - 1].setY(0 + tankArray[TankStageTwoSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						tankArray[TankStageTwoSpawn - 1].setX(0 + tankArray[TankStageTwoSpawn - 1].getWidth());
						tankArray[TankStageTwoSpawn - 1].setY(720 - tankArray[TankStageTwoSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						tankArray[TankStageTwoSpawn - 1].setX(1280 - tankArray[TankStageTwoSpawn - 1].getWidth());
						tankArray[TankStageTwoSpawn - 1].setY(720 - tankArray[TankStageTwoSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						tankArray[TankStageTwoSpawn - 1].setX(1280 - tankArray[TankStageTwoSpawn - 1].getWidth());
						tankArray[TankStageTwoSpawn - 1].setY(0 + tankArray[TankStageTwoSpawn - 1].getHeight());
						currentSpawn = 0;
					}
					TankStageTwoSpawn -= 1;
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
	else if (stage == 3)
	{
		if (spawnbuffer == 30)
		{
			if (stageSpawnComplete == false)
			{
				if (zombieStageThreeSpawn != 0)
				{

					zombieArray[zombieStageThreeSpawn - 1].setInitialised(true);
					zombieArray[zombieStageThreeSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						zombieArray[zombieStageThreeSpawn - 1].setX(0 + zombieArray[zombieStageThreeSpawn - 1].getWidth());
						zombieArray[zombieStageThreeSpawn - 1].setY(0 + zombieArray[zombieStageThreeSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						zombieArray[zombieStageThreeSpawn - 1].setX(0 + zombieArray[zombieStageThreeSpawn - 1].getWidth());
						zombieArray[zombieStageThreeSpawn - 1].setY(720 - zombieArray[zombieStageThreeSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						zombieArray[zombieStageThreeSpawn - 1].setX(1280 - zombieArray[zombieStageThreeSpawn - 1].getWidth());
						zombieArray[zombieStageThreeSpawn - 1].setY(720 - zombieArray[zombieStageThreeSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						zombieArray[zombieStageThreeSpawn - 1].setX(1280 - zombieArray[zombieStageThreeSpawn - 1].getWidth());
						zombieArray[zombieStageThreeSpawn - 1].setY(0 + zombieArray[zombieStageThreeSpawn - 1].getHeight());
						currentSpawn = 0;
					}
					zombieStageThreeSpawn -= 1;
				}
				else if (TankStageThreeSpawn != 0)
				{

					tankArray[TankStageThreeSpawn - 1].setInitialised(true);
					tankArray[TankStageThreeSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						tankArray[TankStageThreeSpawn - 1].setX(0 + tankArray[TankStageThreeSpawn - 1].getWidth());
						tankArray[TankStageThreeSpawn - 1].setY(0 + tankArray[TankStageThreeSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						tankArray[TankStageThreeSpawn - 1].setX(0 + tankArray[TankStageThreeSpawn - 1].getWidth());
						tankArray[TankStageThreeSpawn - 1].setY(720 - tankArray[TankStageThreeSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						tankArray[TankStageThreeSpawn - 1].setX(1280 - tankArray[TankStageThreeSpawn - 1].getWidth());
						tankArray[TankStageThreeSpawn - 1].setY(720 - tankArray[TankStageThreeSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						tankArray[TankStageThreeSpawn - 1].setX(1280 - tankArray[TankStageThreeSpawn - 1].getWidth());
						tankArray[TankStageThreeSpawn - 1].setY(0 + tankArray[TankStageThreeSpawn - 1].getHeight());
						currentSpawn = 0;
					}
					TankStageThreeSpawn -= 1;
				}
				else if (SpitterStageThreeSpawn != 0)
				{

					spitterArray[SpitterStageThreeSpawn - 1].setInitialised(true);
					spitterArray[SpitterStageThreeSpawn - 1].setEndFrame(0);
					spawnbuffer = 0;
					if (currentSpawn == 0)
					{
						spitterArray[SpitterStageThreeSpawn - 1].setX(0 + spitterArray[SpitterStageThreeSpawn - 1].getWidth());
						spitterArray[SpitterStageThreeSpawn - 1].setY(0 + spitterArray[SpitterStageThreeSpawn - 1].getHeight());
						currentSpawn = 1;
					}
					else if (currentSpawn == 1)
					{
						spitterArray[SpitterStageThreeSpawn - 1].setX(0 + spitterArray[SpitterStageThreeSpawn - 1].getWidth());
						spitterArray[SpitterStageThreeSpawn - 1].setY(720 - spitterArray[SpitterStageThreeSpawn - 1].getHeight());
						currentSpawn = 2;
					}
					else if (currentSpawn == 2)
					{
						spitterArray[SpitterStageThreeSpawn - 1].setX(1280 - spitterArray[SpitterStageThreeSpawn - 1].getWidth());
						spitterArray[SpitterStageThreeSpawn - 1].setY(720 - spitterArray[SpitterStageThreeSpawn - 1].getHeight());
						currentSpawn = 3;
					}
					else if (currentSpawn == 3)
					{
						spitterArray[SpitterStageThreeSpawn - 1].setX(1280 - spitterArray[SpitterStageThreeSpawn - 1].getWidth());
						spitterArray[SpitterStageThreeSpawn - 1].setY(0 + spitterArray[SpitterStageThreeSpawn - 1].getHeight());
						currentSpawn = 0;
					}
					SpitterStageThreeSpawn -= 1;
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
	else if (stage == 4)
	{
		if (!boss.isSpawn())
		{
			boss.setSpawn(true);
		}
		//////////////////////////////////boss HP bar////////////////////////////////////
		int bossHP = boss.getHP() / 2; //1000 pixel, 1 pixel = 2 HP
		if (!bossCURHPTexture.initialize(graphics, BOSS_CUR_HP))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss CURRENT HP texture"));
		if (!bossCURHP.initialize(graphics, bossHP, 32, 1, &bossCURHPTexture))
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss CURRENT HP BAR"));
		bossCURHP.setX(140); //centerize the HP bar
		bossCURHP.setY(GAME_HEIGHT - 32); //show the HP bar at the bottom
										  /////////////////////////////////////////////////////////////////////////////////
										  //////BOSS MOTIONS RELOADING -> CHANNELING -> ATTACKING -> RELOADING -> etc//////
										  /////////////////////////////////////////////////////////////////////////////////
		if (boss.getForm() == 1) //boss form 1 :: BARON
		{
			if (boss.isReloading())
			{
				for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
				{
					CannonArray[cannonNo].setInitialised(false);
				}
				boss.setFrames(bossNS::BARON_START_FRAME, bossNS::BARON_END_FRAME);
				boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
				boss.setLoop(true);
				if (fpscounter % 60 == 0) //for every second
				{
					BARON_RELOADING_TIMER--;
				}
				if (BARON_RELOADING_TIMER == 0) //if reload time is up
				{
					boss.changeMotion(boss.isReloading());
					boss.setCurrentFrame(bossNS::BARON_CHANNEL_START_FRAME);
					BARON_CHANNELING_TIMER = bossNS::BARON_CHANNELING_TIMER;
				}
			}
			else if (boss.isChanneling())
			{
				boss.setFrames(bossNS::BARON_CHANNEL_START_FRAME, bossNS::BARON_CHANNEL_END_FRAME);
				boss.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
				boss.setLoop(true);
				if (fpscounter % 60 == 0)
				{
					BARON_CHANNELING_TIMER--;
				}
				if (BARON_CHANNELING_TIMER == 0) //if channel time is up
				{
					boss.changeMotion(boss.isChanneling());
					boss.setCurrentFrame(bossNS::BARON_ATTACK_FRAME);
					BARON_ATTACKING_TIMER = bossNS::BARON_ATTACKING_TIMER;
					for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
					{
						CannonArray[cannonNo].setX(Cannon::X); //set bullet positions
						CannonArray[cannonNo].setY(Cannon::Y);
					}
				}
			}
			else if (boss.isAttacking())
			{
				for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
				{
					CannonArray[cannonNo].setInitialised(true);
				}
				for (int i = 0; i <= 4; i++)
				{
					CannonArray[i].setVelocityX(400.0f);
				}
				for (int i = 4; i <= 12; i++)
				{
					CannonArray[i].setVelocityY(400.0f);
				}
				for (int i = 12; i <= 20; i++)
				{
					CannonArray[i].setVelocityX(-400.0f);
				}
				for (int i = 20; i <= 28; i++)
				{
					CannonArray[i].setVelocityY(-400.0f);
				}
				for (int i = 28; i < 32; i++)
				{
					CannonArray[i].setVelocityX(400.0f);
				}
				float Sy = 0.0f;
				for (int i = 0; i < 4; i++)
				{
					CannonArray[i].setVelocityY(Sy);
					Sy += 100.0f;
				}
				float Sx = 400.0f;
				for (int i = 4; i < 12; i++)
				{
					CannonArray[i].setVelocityX(Sx);
					Sx -= 100.0f;
				}
				float Wy = 400.0f;
				for (int i = 13; i < 20; i++)
				{
					CannonArray[i].setVelocityY(Wy);
					Wy -= 100.0f;
				}
				float Nx = -400.0f;
				for (int i = 21; i < 28; i++)
				{
					CannonArray[i].setVelocityX(Nx);
					Nx += 100.0f;
				}
				float Ey = -400.0f;
				for (int i = 29; i < 32; i++)
				{
					CannonArray[i].setVelocityY(Ey);
					Ey += 100.0f;
				}
				for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
				{
					CannonArray[cannonNo].update(frameTime);
				}
				boss.setFrames(bossNS::BARON_ATTACK_FRAME, bossNS::BARON_ATTACK_FRAME);	//no animation
				if (fpscounter % 60 == 0)
				{
					BARON_ATTACKING_TIMER--;
				}
				if (BARON_ATTACKING_TIMER == 0) //if attack time is up
				{
					boss.changeMotion(boss.isAttacking());
					boss.setCurrentFrame(bossNS::BARON_START_FRAME);
					BARON_RELOADING_TIMER = bossNS::BARON_RELOADING_TIMER;
					
				}
			}
		}
		else if (boss.getForm() == 2) //boss form 2 :: NORAB
		{
			if (boss.isReloading())
			{
				boss.setFrames(bossNS::NORAB_START_FRAME, bossNS::NORAB_END_FRAME);
				boss.setFrameDelay(bossNS::NORAB_ANIMATION_DELAY);
				boss.setLoop(true);
				if (fpscounter % 60 == 0)
				{
					NORAB_RELOADING_TIMER--;
				}
				if (NORAB_RELOADING_TIMER == 0) //if reload time is up
				{
					boss.changeMotion(boss.isReloading());
					boss.setCurrentFrame(bossNS::NORAB_CHANNEL_START_FRAME);
					NORAB_CHANNELING_TIMER = bossNS::NORAB_CHANNELING_TIMER;
				}
			}
			else if (boss.isChanneling())
			{
				boss.setFrames(bossNS::NORAB_CHANNEL_START_FRAME, bossNS::NORAB_CHANNEL_END_FRAME);
				boss.setFrameDelay(bossNS::NORAB_ANIMATION_DELAY);
				boss.setLoop(true);
				if (fpscounter % 60 == 0)
				{
					NORAB_CHANNELING_TIMER--;
				}
				if (NORAB_CHANNELING_TIMER == 0) //if channel time is up
				{
					boss.changeMotion(boss.isChanneling());
					boss.setCurrentFrame(bossNS::NORAB_ATTACK_FRAME);
					NORAB_ATTACKING_TIMER = bossNS::NORAB_ATTACKING_TIMER;
				}
			}
			else if (boss.isAttacking())
			{
				VECTOR2 direction;
				direction.x = player1.getX() - boss.getX();
				direction.y = player1.getY() - boss.getY();
				float hypotenuse = sqrt(direction.x * direction.x + direction.y * direction.y);
				direction.x /= hypotenuse;
				direction.y /= hypotenuse;
				direction.x *= bossNS::CHARRRGE_SPEED;
				direction.y *= bossNS::CHARRRGE_SPEED;
				boss.setVelocity(direction);
				boss.CHARRRGE(frameTime);
				float angle = atan2(player1.getY() - boss.getY(), player1.getX() - boss.getX()) * (180 / PI) + 90;
				boss.setDegrees(angle);

				boss.setFrames(bossNS::NORAB_ATTACK_FRAME, bossNS::NORAB_ATTACK_FRAME);	//no animation
				if (fpscounter % 60 == 0)
				{
					NORAB_ATTACKING_TIMER--;
				}
				if (NORAB_ATTACKING_TIMER == 0) //if attack time is up
				{
					boss.changeMotion(boss.isAttacking());
					boss.setCurrentFrame(bossNS::NORAB_START_FRAME);
					angle = 0.0f;
					boss.setDegrees(angle);
					NORAB_RELOADING_TIMER = bossNS::NORAB_RELOADING_TIMER;
				}
			}
		}
		if (boss.hasShield() == true)
		{
			shield.update(frameTime);
			shield.setX(shield.getprevX());
			shield.setY(shield.getprevY());
		}
	}
	
	map.update(frameTime);
	boss.update(frameTime);
	
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


	if (boss.isSpawn()) //if boss spawns
	{
		bossMAXHP.draw(); //draw MAXHP bar
		if (boss.getHP() > 0) 
		{
			bossCURHP.draw(); //draw boss current HP bar
		}
		boss.draw(); //draw my boss
		if (boss.hasShield()) //draw my shield
			shield.draw();
		if (boss.isAttacking() && boss.getForm() == 1)
		{
			for (int cannonNo = 0; cannonNo < (sizeof(CannonArray) / sizeof(*CannonArray)); cannonNo++)
			{
				if (CannonArray[cannonNo].isInitialised() == true)
				{
					CannonArray[cannonNo].draw();
				}
					
			}
		}
	}
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
	bossTexture.onLostDevice();
	bossMAXHPTexture.onLostDevice();
	bossCURHPTexture.onLostDevice();
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
	bossTexture.onResetDevice();
	bossMAXHPTexture.onResetDevice();
	bossCURHPTexture.onResetDevice();
	tankTexture.onResetDevice();
	spitterTexture.onLostDevice();
	spitterbulletTexture.onLostDevice();
	Game::resetAll();
	return;
}


void dontdie::collisions()
{
	VECTOR2 tempVector;
	for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
	{
		if (spitterbulletArray[bullet].isInitialised() == true)
		{
			if (spitterbulletArray[bullet].collidesWith(player1, tempVector))
			{
				spitterbulletArray[bullet].setInitialised(false);
				player1.damageMe(2);
			}

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
	/*if (bullet.collidesWith(boss, tempVector)) //waiting for player bullet
	{
		boss.takesDamage(bullet.getDamage());
												pop bullet
	}
	if (bullet.collidesWith(shield, tempVector)) //waiting for player bullet
	{
												pop bullet
	}*/
	for (int cannon = 0; cannon < (sizeof(CannonArray) / sizeof(*CannonArray)); cannon++)
	{
		if (CannonArray[cannon].isInitialised() == true)
		{
			if (CannonArray[cannon].collidesWith(player1, tempVector))
			{
				player1.damageMe(1);
			}
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (CannonArray[cannon].collidesWith(wallArray[i], tempVector))
				{
					CannonArray[cannon].setInitialised(false);
				}
			}
		}
			
	}

	//i will treat you lunch nxt time ;P
	for (int i = 0; i < (sizeof(wallArray)/sizeof(*wallArray)); i++)
	{
		if (player1.collidesWith(wallArray[i], tempVector))
		{
			player1.revertLocation();
		}
		for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
		{
			if (spitterbulletArray[bullet].isInitialised() == true)
			{
				if (spitterbulletArray[bullet].collidesWith(wallArray[i], tempVector))
				{
					spitterbulletArray[bullet].setInitialised(false);
				}
				if (spitterbulletArray[bullet].getX() < 0 || spitterbulletArray[bullet].getX() > GAME_WIDTH || spitterbulletArray[bullet].getY() < 0 || spitterbulletArray[bullet].getY() > GAME_HEIGHT)
				{
					spitterbulletArray[bullet].setInitialised(false);
				}
				
			}
		}
	}
	//when palyerbullet touches the zombie
	//for loop to track which bullet
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			//damage the tank
			if (tankArray[tank].getDamageAnimationBuffer() == 30.0f)
			{
				tankArray[tank].setDamageAnimationBuffer(0.0f);
			}
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
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 0 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 1 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 2 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					zombieArray[zomb].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(zombieArray[zomb], tempVec) == 3 && zombieArray[zomb].collidesWith(wallArray[i], tempVec))
				{
					zombieArray[zomb].revertLocation();
					zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
					zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					zombieArray[zomb].setVelocity(dir);
				}
				else
				{
					if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
					{
						zombieArray[zomb].revertLocation();
						zombieArray[zomb].setX(zombieArray[zomb].getX() + 1);
						if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "right";
							// zombieArray[zombie].revertLocation();
						}
						zombieArray[zomb].revertLocation();
						if (failDirection == "")
						{
							zombieArray[zomb].setX(zombieArray[zomb].getX() - 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "left";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "")
						{
							zombieArray[zomb].setY(zombieArray[zomb].getY() - 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "up";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "")
						{
							zombieArray[zomb].setY(zombieArray[zomb].getY() + 1);
							if (zombieArray[zomb].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "down";
								// zombieArray[zombie].revertLocation();
							}
							zombieArray[zomb].revertLocation();
						}
						if (failDirection == "right")
						{

							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= zombieArray[zomb].getY())
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
							if (up < down)
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
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= zombieArray[zomb].getY())
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
							if (up < down)
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
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= zombieArray[zomb].getX())
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
							float xValue = player1.getX() - zombieArray[zomb].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - zombieArray[zomb].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= zombieArray[zomb].getX())
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
								wallVec.x = -1 * zombieNS::ZOMBIE_SPEED;
								wallVec.y = 0 * zombieNS::ZOMBIE_SPEED;
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
				
			}
			VECTOR2 tempVector;
			if (player1.collidesWith( zombieArray[zomb], tempVector))
			{
				player1.revertLocation();
				 zombieArray[zomb].revertLocation();
				player1.damageMe( zombieArray[zomb].getDamage());
			}
			 zombieArray[zomb].setPrev( zombieArray[zomb].getX(),  zombieArray[zomb].getY());
		}
	}
	


	//Tank AI
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		if (tankArray[tank].isInitialised() == true)
		{
			dir.x = player1.getX() - tankArray[tank].getX();
			dir.y = player1.getY() - tankArray[tank].getY();
			float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
			dir.x /= hyp;
			dir.y /= hyp;
			dir.x *= zombieNS::ZOMBIE_SPEED;
			dir.y *= zombieNS::ZOMBIE_SPEED;
			tankArray[tank].setVelocity(dir);
			float angle = atan2(player1.getY() - tankArray[tank].getY(), player1.getX() - tankArray[tank].getX()) * (180 / PI) + 90;
			tankArray[tank].setDegrees(angle);
			for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
			{
				if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 0 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() - 1);
					tankArray[tank].setY(tankArray[tank].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 1 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() + 1);
					tankArray[tank].setY(tankArray[tank].getY() - 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * -1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 2 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() + 1);
					tankArray[tank].setY(tankArray[tank].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * 1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					tankArray[tank].setVelocity(dir);
				}
				else if (wallArray[i].checkVoronoiRegion(tankArray[tank], tempVec) == 3 && tankArray[tank].collidesWith(wallArray[i], tempVec))
				{
					tankArray[tank].revertLocation();
					tankArray[tank].setX(tankArray[tank].getX() - 1);
					tankArray[tank].setY(tankArray[tank].getY() + 1);
					//dir.x = zombieNS::ZOMBIE_SPEED * -1;
					//dir.y = zombieNS::ZOMBIE_SPEED * 1;
					tankArray[tank].setVelocity(dir);
				}
				else
				{
					if (tankArray[tank].collidesWith(wallArray[i], tempVec))
					{
						tankArray[tank].revertLocation();
						tankArray[tank].setX(tankArray[tank].getX() + 1);
						if (tankArray[tank].collidesWith(wallArray[i], tempVec))
						{
							failDirection = "right";
							// zombieArray[zombie].revertLocation();
						}
						tankArray[tank].revertLocation();
						if (failDirection == "")
						{
							tankArray[tank].setX(tankArray[tank].getX() - 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "left";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "")
						{
							tankArray[tank].setY(tankArray[tank].getY() - 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "up";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "")
						{
							tankArray[tank].setY(tankArray[tank].getY() + 1);
							if (tankArray[tank].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "down";
								// zombieArray[zombie].revertLocation();
							}
							tankArray[tank].revertLocation();
						}
						if (failDirection == "right")
						{

							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= tankArray[tank].getY())
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
							if (up < down)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
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
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getY() >= tankArray[tank].getY())
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
							if (up < down)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = -1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down < up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (down == up)
							{
								wallVec.x = 0 * tankNS::TANK_SPEED;
								wallVec.y = 1 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
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
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= tankArray[tank].getX())
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
								wallVec.x = -1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right < left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
						}
						else if (failDirection == "down")
						{
							float xValue = player1.getX() - tankArray[tank].getX();
							if (xValue < 0)
							{
								xValue *= -1;
							}
							float yValue = player1.getY() - tankArray[tank].getY();
							if (yValue < 0)
							{
								yValue *= -1;
							}
							if (player1.getX() >= tankArray[tank].getX())
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
								wallVec.x = -1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							//else if (up <= left && up <= right)
							//{
							//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
							//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
							//	 zombieArray[zombie].setVelocity(wallVec);
							//}
							else if (right < left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}
							else if (right == left)
							{
								wallVec.x = 1 * tankNS::TANK_SPEED;
								wallVec.y = 0 * tankNS::TANK_SPEED;
								tankArray[tank].setVelocity(wallVec);
							}

						}

					}
				}

			}
			VECTOR2 tempVector;
			if (player1.collidesWith(tankArray[tank], tempVector))
			{
				player1.revertLocation();
				tankArray[tank].revertLocation();
				player1.damageMe(tankArray[tank].getDamage());
			}
			tankArray[tank].setPrev(tankArray[tank].getX(), tankArray[tank].getY());
		}
	}

	//Spitter AI
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		if (spitterArray[spitter].isInitialised() == true)
		{
			float xValue = player1.getX() - spitterArray[spitter].getX();
			if (xValue < 0)
			{
				xValue *= -1;
			}
			float yValue = player1.getY() - spitterArray[spitter].getY();
			if (yValue < 0)
			{
				yValue *= -1;
			}
			float distanceToPlayer = sqrt((xValue) * (xValue) + (yValue) * (yValue));
			if (distanceToPlayer > 200)
			{
				spitterArray[spitter].setEndFrame(0);
				dir.x = player1.getX() - spitterArray[spitter].getX();
				dir.y = player1.getY() - spitterArray[spitter].getY();
				float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
				dir.x /= hyp;
				dir.y /= hyp;
				dir.x *= zombieNS::ZOMBIE_SPEED;
				dir.y *= zombieNS::ZOMBIE_SPEED;
				spitterArray[spitter].setVelocity(dir);
				float angle = atan2(player1.getY() - spitterArray[spitter].getY(), player1.getX() - spitterArray[spitter].getX()) * (180 / PI) + 90;
				spitterArray[spitter].setDegrees(angle);
				for (int i = 0; i < (sizeof(wallArray) / sizeof(*wallArray)); i++)
				{
					if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 0 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * -1;
						//dir.y = zombieNS::ZOMBIE_SPEED * -1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 1 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * 1;
						//dir.y = zombieNS::ZOMBIE_SPEED * -1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 2 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * 1;
						//dir.y = zombieNS::ZOMBIE_SPEED * 1;
						spitterArray[spitter].setVelocity(dir);
					}
					else if (wallArray[i].checkVoronoiRegion(spitterArray[spitter], tempVec) == 3 && spitterArray[spitter].collidesWith(wallArray[i], tempVec))
					{
						spitterArray[spitter].revertLocation();
						spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
						spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
						//dir.x = zombieNS::ZOMBIE_SPEED * -1;
						//dir.y = zombieNS::ZOMBIE_SPEED * 1;
						spitterArray[spitter].setVelocity(dir);
					}
					else
					{
						if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
						{
							spitterArray[spitter].revertLocation();
							spitterArray[spitter].setX(spitterArray[spitter].getX() + 1);
							if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
							{
								failDirection = "right";
								// zombieArray[zombie].revertLocation();
							}
							spitterArray[spitter].revertLocation();
							if (failDirection == "")
							{
								spitterArray[spitter].setX(spitterArray[spitter].getX() - 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "left";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "")
							{
								spitterArray[spitter].setY(spitterArray[spitter].getY() - 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "up";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "")
							{
								spitterArray[spitter].setY(spitterArray[spitter].getY() + 1);
								if (spitterArray[spitter].collidesWith(wallArray[i], tempVec))
								{
									failDirection = "down";
									// zombieArray[zombie].revertLocation();
								}
								spitterArray[spitter].revertLocation();
							}
							if (failDirection == "right")
							{

								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getY() >= spitterArray[spitter].getY())
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
								if (up < down)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down < up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down == up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
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
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getY() >= spitterArray[spitter].getY())
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
								if (up < down)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = -1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down < up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (down == up)
								{
									wallVec.x = 0 * spitterNS::SPITTER_SPEED;
									wallVec.y = 1 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
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
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getX() >= spitterArray[spitter].getX())
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
									wallVec.x = -1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right < left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right == left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
							}
							else if (failDirection == "down")
							{
								float xValue = player1.getX() - spitterArray[spitter].getX();
								if (xValue < 0)
								{
									xValue *= -1;
								}
								float yValue = player1.getY() - spitterArray[spitter].getY();
								if (yValue < 0)
								{
									yValue *= -1;
								}
								if (player1.getX() >= spitterArray[spitter].getX())
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
									wallVec.x = -1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								//else if (up <= left && up <= right)
								//{
								//	wallVec.x = 0 * zombieNS::ZOMBIE_SPEED;;
								//	wallVec.y = -1 * zombieNS::ZOMBIE_SPEED;;
								//	 zombieArray[zombie].setVelocity(wallVec);
								//}
								else if (right < left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}
								else if (right == left)
								{
									wallVec.x = 1 * spitterNS::SPITTER_SPEED;
									wallVec.y = 0 * spitterNS::SPITTER_SPEED;
									spitterArray[spitter].setVelocity(wallVec);
								}

							}

						}
					}

				}
			}
			else
			{
				float angle = atan2(player1.getY() - spitterArray[spitter].getY(), player1.getX() - spitterArray[spitter].getX()) * (180 / PI) + 90;
				spitterArray[spitter].setDegrees(angle);
				dir.x = 0;
				dir.y = 0;
				spitterArray[spitter].setVelocity(dir);
				if (spitterArray[spitter].getAttackBuffer() == 20.0f)
				{
					spitterArray[spitter].setAttackBuffer(0);
					for (int bullet = 0; bullet < (sizeof(spitterbulletArray) / sizeof(*spitterbulletArray)); bullet++)
					{
						if (spitterbulletArray[bullet].isInitialised() == false)
						{
							spitterbulletArray[bullet].setInitialised(true);
							dir.x = player1.getX() - spitterArray[spitter].getX();
							dir.y = player1.getY() - spitterArray[spitter].getY();
							float hyp = sqrt(dir.x * dir.x + dir.y * dir.y);
							dir.x /= hyp;
							dir.y /= hyp;
							dir.x *= spitterbulletNS::SPITTERBULLET_SPEED;
							dir.y *= spitterbulletNS::SPITTERBULLET_SPEED;
							spitterbulletArray[bullet].setX(spitterArray[spitter].getX());
							spitterbulletArray[bullet].setY(spitterArray[spitter].getY());
							spitterbulletArray[bullet].setVelocity(dir);
							break;
						}
					}
				}
			}
			
			VECTOR2 tempVector;
			if (player1.collidesWith(spitterArray[spitter], tempVector))
			{
				player1.revertLocation();
			}
			spitterArray[spitter].setPrev(spitterArray[spitter].getX(), spitterArray[spitter].getY());
		}
	}

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
		if (spitterArray[spitter].isInitialised() == true)
		{
			zombieCount += 1;
		}
	}
	if (zombieCount == 0 && tankCount == 0 && spitterCount == 0 && boss.isSpawn() == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void dontdie::clearAllMobs()
{
	for (int zomb = 0; zomb < (sizeof(zombieArray) / sizeof(*zombieArray)); zomb++)
	{
		zombieArray[zomb].setInitialised(false);
	}
	for (int tank = 0; tank < (sizeof(tankArray) / sizeof(*tankArray)); tank++)
	{
		tankArray[tank].setInitialised(false);
	}
	for (int spitter = 0; spitter < (sizeof(spitterArray) / sizeof(*spitterArray)); spitter++)
	{
		spitterArray[spitter].setInitialised(false);
	}
}