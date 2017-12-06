
#include "dontdie.h"
#include "zombie.h"
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
	this->pistolBuffer = 0;
	this->smgBuffer = 0;
	this->shotgunBuffer = 0;
	this->rifleBuffer = 0;
	this->pBullets = 10000;
	this->smgBullets = 100000;
	this->rifleBullets = 10000;

	// Map texture
	if (!mapTexture.initialize(graphics, MAP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Map texture"));
	//Wall texture
	if (!wallTexture.initialize(graphics, WALL_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Wall texture"));
	// Player texture
	if (!playerTexture.initialize(graphics, PLAYER_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player texture"));

	if (!playerHealthTexture.initialize(graphics, HEALTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Player Health texture"));

	// Zombie Texture
	if (!zombieTexture.initialize(graphics, ZOMBIE_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Zombie texture"));
	}

	//Bullet Texture
	if (!PbulletTexture.initialize(graphics, BULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bullet texture"));
	}

	/*if (!SMGbulletTexture.initialize(graphics, SMGBULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SMG Bullet texture"));
	}

	if (!ShotgunbulletTexture.initialize(graphics, SHOTGUNBULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shotgun Bullet texture"));
	}

	if (!RiflebulletTexture.initialize(graphics, RIFLEBULLET_IMAGE))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Rifle Bullet texture"));
	}*/

	// Map 
	if (!map.initialize(graphics, 0, 0, 0, &mapTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing map"));
	map.setFrames(0, 0);
	map.setCurrentFrame(0);
	// Wall 
	//for (int i = 0; i < 10; i++)
	//{
	//	int x = 2;
	//	int y = 2;
	//	if (!wallArray[i].initialize(this, 0, 0, 0, &wallTexture))
	//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	//	wallArray[i].setX(GAME_WIDTH / 10 * x);
	//	wallArray[i].setY(GAME_HEIGHT / y);
	//	x += 2;
	//	y += 2;
	//}

	// Wall 
	if (!wallArray[0].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[0].setX(GAME_WIDTH / 2);
	wallArray[0].setY(GAME_HEIGHT / 4);

	if (!wallArray[1].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[1].setX(wallArray[0].getX() + 128);
	wallArray[1].setY(GAME_HEIGHT / 4);
	wallArray[1].setDegrees(90.0f);

	if (!wallArray[2].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[2].setX(wallArray[0].getX() - 128);
	wallArray[2].setY(GAME_HEIGHT / 4);
	wallArray[2].setDegrees(90.0f);

	if (!wallArray[3].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[3].setX(wallArray[2].getX() - 128);
	wallArray[3].setY(GAME_HEIGHT / 4);


	if (!wallArray[4].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[4].setX(wallArray[1].getX() + 128);
	wallArray[4].setY(GAME_HEIGHT / 4);

	if (!wallArray[5].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[5].setX(GAME_WIDTH / 2);
	wallArray[5].setY(GAME_HEIGHT / 2 + 64);

	if (!wallArray[6].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[6].setX(wallArray[0].getX() + 128);
	wallArray[6].setY(GAME_HEIGHT / 2 + 64);
	wallArray[6].setDegrees(90.0f);

	if (!wallArray[7].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[7].setX(wallArray[0].getX() - 128);
	wallArray[7].setY(GAME_HEIGHT / 2 + 64);
	wallArray[7].setDegrees(90.0f);

	if (!wallArray[8].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[8].setX(wallArray[2].getX() - 128);
	wallArray[8].setY(GAME_HEIGHT / 2 + 64);

	if (!wallArray[9].initialize(this, 0, 0, 0, &wallTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing wall"));
	wallArray[9].setX(wallArray[1].getX() + 128);
	wallArray[9].setY(GAME_HEIGHT / 2 + 64);

	// Player
	if (!player1.initialize(this, playerNS::WIDTH, playerNS::HEIGHT, playerNS::TEXTURE_COLS, &playerTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));

	player1.setFrames(playerNS::PLAYER_START_FRAME, playerNS::PLAYER_START_FRAME);
	player1.setCurrentFrame(playerNS::PLAYER_START_FRAME);
	player1.setFrameDelay(playerNS::PLAYER_ANIMATION_DELAY);
	//player1.setDegrees((atan2(player1.getY - input->getMouseY() , player1.getX - input->getMouseX()) * 180) / PI);     //angle of player

	// Player Health
	if (!player1health.initialize(this, playerHealthNS::WIDTH, playerHealthNS::HEIGHT, playerHealthNS::TEXTURE_COLS, &playerHealthTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing player"));


	//Bullets
	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (!pistolBulletArray[pistolb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Pistol Buller"));
		}
		pistolBulletArray[pistolb].setFrames(bulletNS::PISTOLBULLET_START_FRAME, bulletNS::PISTOLBULLET_END_FRAME);
		pistolBulletArray[pistolb].setCurrentFrame(bulletNS::PISTOLBULLET_START_FRAME);
		pistolBulletArray[pistolb].setInitialized(false);
	}

	for (int smgb = 0; smgb < (sizeof(smgBulletArray) / sizeof(*smgBulletArray)); smgb++)
	{
		if (!smgBulletArray[smgb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing SMG Bullet"));
		}
		smgBulletArray[smgb].setFrames(bulletNS::SMGBULLET_START_FRAME, bulletNS::SMGBULLET_END_FRAME);
		smgBulletArray[smgb].setCurrentFrame(bulletNS::SMGBULLET_START_FRAME);
		smgBulletArray[smgb].setInitialized(false);
	}
	
	if (!ShotgunBullet.initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &ShotgunbulletTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shotgun Bullet"));


	for (int rifleb = 0; rifleb < (sizeof(rifleBulletArray) / sizeof(*rifleBulletArray)); rifleb++)
	{
		if (!rifleBulletArray[rifleb].initialize(this, bulletNS::WIDTH, bulletNS::HEIGHT, bulletNS::TEXTURE_COLS, &PbulletTexture))
		{
			throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Pistol Buller"));
		}
		rifleBulletArray[rifleb].setFrames(bulletNS::RIFLEBULLET_START_FRAME, bulletNS::RIFLEBULLET_END_FRAME);
		rifleBulletArray[rifleb].setCurrentFrame(bulletNS::RIFLEBULLET_START_FRAME);
		rifleBulletArray[rifleb].setInitialized(false);
	}


// Zombies
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
	VECTOR2 dir;
	player1.setPrev(player1.getX(), player1.getY());
	zombie1.setPrev(zombie1.getX(), zombie1.getY());
	player1.update(frameTime);
	zombie1.update(frameTime);
	player1health.update(frameTime);
	if (player1.getHealth() != 20)
	{
		for (int health = 19; health > 0; health--)
		{
			int frame = 1;
			if (player1.getHealth() == health)
			{
				player1health.setFrames(frame, frame);
			}
			frame++;
		}
	}
	player1health.setX(player1.getX());
	player1health.setY(player1.getY() + 32);


	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (pistolBulletArray[pistolb].isInitialized() == true)
		{
			pistolBulletArray[pistolb].update(frameTime);
		}
	}

	if (input->getMouseLButton() == true)
	{
		float clickY = input->getMouseY();
		float clickX = input->getMouseX();

		if (pistolBuffer == pistolBulletArray[pBullets - 1].getPistolBuffer())
		{
			if (pBullets != 0)
			{
				pBullets -= 1;
				pistolBulletArray[pBullets - 1].setInitialized(true);
				pistolBuffer = 0;
				pistolBulletArray[pBullets - 1].setX(player1.getX());
				pistolBulletArray[pBullets - 1].setY(player1.getY());
			}
		}
		else
		{
			pistolBuffer += 1;
		}

		dir.x = clickX - player1.getX();
		dir.y = clickY - player1.getY();
		float hyp = sqrt(dir.x*dir.x + dir.y*dir.y);
		dir.x /= hyp;
		dir.y /= hyp;
		dir.x *= bulletNS::SPEED;
		dir.y *= bulletNS::SPEED;
		pistolBulletArray[pBullets - 1].setVelocity(dir);
		float angle = atan2(clickX - player1.getX(), clickY - player1.getY())* (180 / PI) + 90;
		pistolBulletArray[pBullets - 1].setDegrees(angle);
		
	}
	//map.update(frameTime);
}

//=============================================================================
// render game items
//=============================================================================
void dontdie::render()
{
	const int BUF_SIZE = 20;
	static char buffer[BUF_SIZE];
	VECTOR2 dir;

	graphics->spriteBegin();
	for (int row = 0; row < MAP_HEIGHT; row++)       // for each row of map
	{
		map.setY((float)(row*TEXTURE_SIZE)); // set tile Y
		for (int col = 0; col < MAP_WIDTH; col++)    // for each column of map
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


	for (int i = 0; i < 10; i++)
	{
		wallArray[i].draw();
	}

	zombie1.draw();
	player1.draw();     //adds the player into the scene
	player1health.draw();

	for (int pistolb = 0; pistolb < (sizeof(pistolBulletArray) / sizeof(*pistolBulletArray)); pistolb++)
	{
		if (pistolBulletArray[pistolb].isInitialized() == true)
		{
			pistolBulletArray[pistolb].draw();
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
	playerHealthTexture.onLostDevice();
	PbulletTexture.onLostDevice();
	//SMGbulletTexture.onLostDevice();
	//ShotgunbulletTexture.onLostDevice();
	//RiflebulletTexture.onLostDevice();
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
	playerHealthTexture.onResetDevice();
	PbulletTexture.onResetDevice();
	//SMGbulletTexture.onResetDevice();
	//ShotgunbulletTexture.onResetDevice();
	//RiflebulletTexture.onResetDevice();
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
		}
	}
}
