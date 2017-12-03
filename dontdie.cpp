
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
	///////////////
	//BOSS HP BAR//
	///////////////
	if (!bossMAXHPTexture.initialize(graphics, BOSS_MAX_HP))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP texture"));
	if (!bossMAXHP.initialize(graphics, 1000, 0, 0, &bossMAXHPTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss MAX HP BAR"));
	bossMAXHP.setX(140); //centerize the HP bar
	bossMAXHP.setY(GAME_HEIGHT - 32); //show the HP bar at the bottom
	// boss form 1 texture
	// if hp >66%
	if (!bossTexture.initialize(graphics, BOSS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Boss form 1 texture"));
	// boss form 1 image
	if (!boss.initialize(this, bossNS::WIDTH, bossNS::HEIGHT, bossNS::TEXTURE_COLS, &bossTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your boss"));
	if (!cannonTexture.initialize(graphics, BOSSCANNON_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Cannon texture"));
	if (!shieldTexture.initialize(graphics, BOSS_SHIELD))
	{
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Shield texture"));
	}
	if (!shield.initialize(this, ShieldNS::WIDTH, ShieldNS::HEIGHT, ShieldNS::TEXTURE_COLS, &shieldTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shield"));
	shield.setFrames(ShieldNS::SHIELD_START_FRAME, ShieldNS::SHIELD_END_FRAME);
	shield.setCurrentFrame(ShieldNS::SHIELD_START_FRAME);
	shield.setX(shield.getprevX());
	shield.setY(shield.getprevY());
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
	zombie1.setPrev(zombie1.getX(), zombie1.getY());
	player1.update(frameTime);
	zombie1.update(frameTime);
	map.update(frameTime);
	boss.update(frameTime);
	
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
				BARON_CHANNELING_TIMER = 3;
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
				BARON_ATTACKING_TIMER = 6;
			}
		}
		else if (boss.isAttacking())
		{			
			/*if (!CannonArray[CannonBallNo].initialize(this, Cannon::WIDTH, Cannon::HEIGHT, Cannon::TEXTURE_COLS, &cannonTexture))
				throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing your cannon ballz"));
			CannonArray[CannonBallNo].setFrames(Cannon::CANNON_START_FRAME, Cannon::CANNON_END_FRAME);
			CannonArray[CannonBallNo].setCurrentFrame(Cannon::CANNON_START_FRAME);
			CannonArray[CannonBallNo].setX(CannonArray[CannonBallNo].getprevX());
			CannonArray[CannonBallNo].setY(CannonArray[CannonBallNo].getprevY());*/
			//CannonBallNo will ++ at draw (code goes from top to bottom)

			boss.setFrames(bossNS::BARON_ATTACK_FRAME, bossNS::BARON_ATTACK_FRAME);	//no animation
			if (fpscounter % 60 == 0)
			{
				BARON_ATTACKING_TIMER--;
			}
			if (BARON_ATTACKING_TIMER == 0) //if attack time is up
			{
				boss.changeMotion(boss.isAttacking());
				boss.setCurrentFrame(bossNS::BARON_START_FRAME);
				BARON_RELOADING_TIMER = 6;
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
				NORAB_CHANNELING_TIMER = 2;
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
				NORAB_ATTACKING_TIMER = 4;
			}
		}
		else if (boss.isAttacking())
		{
			boss.setFrames(bossNS::NORAB_ATTACK_FRAME, bossNS::NORAB_ATTACK_FRAME);	//no animation
			if (fpscounter % 60 == 0)
			{
				NORAB_ATTACKING_TIMER--;
			}			
			if (NORAB_ATTACKING_TIMER == 0) //if attack time is up
			{
				boss.changeMotion(boss.isAttacking());
				boss.setCurrentFrame(bossNS::NORAB_START_FRAME);
				NORAB_RELOADING_TIMER = 4;
			}
		}
	}
	CannonArray[CannonBallNo].update(frameTime);
	if (boss.hasShield() == true)
	{
		shield.update(frameTime);
		shield.setX(shield.getprevX());
		shield.setY(shield.getprevY());
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
	}
	//CannonArray[CannonBallNo].draw();
	//CannonBallNo++;
	//if (CannonBallNo == 359) // reset cannonBallNo
	//{
	//	CannonBallNo = 0;
	//}
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
	bossMAXHPTexture.onLostDevice();
	bossCURHPTexture.onLostDevice();
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
	bossMAXHPTexture.onResetDevice();
	bossCURHPTexture.onResetDevice();
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