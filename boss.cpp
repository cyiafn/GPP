#include "boss.h"

Boss::Boss() : Entity()
{

	spriteData.width = bossNS::WIDTH;           // size of boss
	spriteData.height = bossNS::HEIGHT;
	spriteData.x = bossNS::X;                   // location on screen
	spriteData.y = bossNS::Y;
	spriteData.rect.bottom = bossNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bossNS::WIDTH;
	frameDelay = bossNS::BARON_ANIMATION_DELAY;
	startFrame = bossNS::BARON_START_FRAME;     // first frame of boss animation
	endFrame = bossNS::BARON_END_FRAME;     // last frame of boss animation
	currentFrame = startFrame;
	edge.left = -64;
	edge.top = -64;
	edge.right = 64;
	edge.bottom = 64;
	collisionType = entityNS::BOX;
}


bool Boss::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM)
{
	boss_form.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
	boss_form.setFrames(bossNS::BARON_START_FRAME, bossNS::BARON_END_FRAME);
	boss_form.setCurrentFrame(bossNS::BARON_START_FRAME);
	boss_form.setFrameDelay(bossNS::BARON_ANIMATION_DELAY);
	boss_form.setLoop(true);                  // do not loop animation
	shieldOn = true;
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss::draw()
{
	Image::draw();
}

void Boss::update(float frameTime)
{
	Entity::update(frameTime);
	
	///////////////////////////
	// CHEAT CODE :PogChamp: //
	///////////////////////////
	if (input->isKeyDown(BOSS_STAGE1)) //cheat code stage 1
	{
		spawn = true;
		form = 1;
		HP = bossNS::MAXHP;
		spriteData.x = bossNS::X; //reset position
		spriteData.y = bossNS::Y;
		shieldOn = true;
	}
	else if (input->isKeyDown(BOSS_STAGE2)) //cheat code stage 2
	{
		spawn = true;
		form = 2;
		shieldOn = false;
		spriteData.x = bossNS::X; //reset position
		spriteData.y = bossNS::Y;
		HP = 1000;
	}
	else if (input->isKeyDown(BOSS_CLEAR)) //clear boss = win game
	{
		HP = 0;
	}
	//////////////////////////////////
	// Boss Health Tracking :kappa: //
	//////////////////////////////////
	if (spawn)
	{
		if (HP > bossNS::MAXHP / 2) // if HP > 50% == form 1
		{
			form = 1;
		}
		else if (HP <= bossNS::MAXHP / 2) // if HP <= 50% == form 2
		{
			form = 2;
			shieldOn = false;
		}

		if (HP <= 0) // if HP <= 0% == DIEDED
		{
			//WIN
			spawn = false;
			MessageBox(nullptr, TEXT("YOU WIN!!"), TEXT(""), MB_OK);			
		}
	}
	
}

int Boss::getDamage()
{
	return damage;
}

void Boss::setDamage(int dmg)
{
	damage = dmg;
}

int Boss::getHP()
{
	return HP;
}

int Boss::getForm()
{
	return form;
}

bool Boss::isSpawn()
{
	return spawn;
}

void Boss::takesDamage(int dmgValue)
{
	this->HP -= dmgValue;
}


bool Boss::hasShield()
{
	return shieldOn;
}

bool Boss::isReloading()
{
	return reloading;
}
bool Boss::isChanneling()
{
	return channeling;
}
bool Boss::isAttacking()
{
	return attacking;
}


void Boss::changeMotion(bool motion)
{
	if (reloading == motion)
	{
		channeling = true; //change to channeling frame
		attacking = false;
		reloading = false;
	}
	else if (channeling == motion)
	{
		attacking = true; //change to attacking frame
		reloading = false;
		channeling = false;
	}
	else if (attacking == motion)
	{
		reloading = true; //change to reloading frame
		channeling = false;
		attacking = false;
	}
}


void Boss::CHARRRGE(float frameTime)
{
	if (form == 2 && attacking)
	{	
		spriteData.x += frameTime * velocity.x;        
		spriteData.y += frameTime * velocity.y;
	}
}