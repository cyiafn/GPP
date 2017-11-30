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
	radius = bossNS::COLLISION_RADIUS;
	collisionType = entityNS::CIRCLE;
	this->status = 0;
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
	Image::draw();              // draw boss
	if (this->shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

void Boss::update(float frameTime)
{
	Entity::update(frameTime);
	//////////////////////////////
	//rotating shield :cmonBruh://
	//////////////////////////////
	if (shieldOn)
	{
		//angle += frameTime*rotation_rate;
		//shieldX = bossNS::X + cos(angle)*radius;
		//shieldY = bossNS::Y + sin(angle)*radius;
	}
	///////////////////////////
	// CHEAT CODE :PogChamp: //
	///////////////////////////
	if (input->isKeyDown(BOSS_STAGE1)) //cheat code stage 1
	{
		form = 1;
		HP = bossNS::MAXHP;
		shieldOn = true;
		BARON_Spawn = true;
		BARON_Dead = false;
		NORAB_Spawn = false;
		NORAB_Dead = false;
		
	}
	else if (input->isKeyDown(BOSS_STAGE2)) //cheat code stage 2
	{
		form = 2;
		shieldOn = false;
		NORAB_Spawn = true;
		HP = 1000;
		BARON_Dead = true;
		NORAB_Dead = false;
		BARON_Spawn = false;
	}
	else if (input->isKeyDown(BOSS_CLEAR)) //clear boss = win game
	{
		BARON_Dead = true;
		NORAB_Dead = true;
		BARON_Spawn = false;
		NORAB_Spawn = false;
	}
	//////////////////////////////////
	// Boss Health Tracking :kappa: //
	//////////////////////////////////
	if (form = 1) // BARON SPAWN, and more than half health
	{
		BARON_Spawn == true;
		BARON_Dead = false; //boss 1 is defeated
		NORAB_Spawn = false; //ensure NORAB doesn't spawn
		NORAB_Dead = false; //ensure NORAB isnt dead
	}
	else if (form = 2) //<=33% HP
	{
		shieldOn = false;
		BARON_Spawn = false; //de-spawn BARON
		BARON_Dead = true; //state BARON has died
		NORAB_Spawn = true; //NORAB SPAWN, less than half health
		NORAB_Dead = false; //ensure NORAB isn't dead
	}


	if (HP <= 0) //dieded && ensure NORAB is the one that died
	{
		NORAB_Dead = true;
		NORAB_Spawn = false;
		BARON_Dead = true;
		BARON_Spawn = false;
	}
	/////////////////////////////
	// WIN CONDITION :kreyGASM://
	/////////////////////////////
	if (BARON_Dead == true && NORAB_Dead == true) //if 2 forms are dead
	{
		//WIN
		MessageBox(nullptr, TEXT("YOU WIN!!"), TEXT(""), MB_OK);
	}
	
	
	//this->HP -= 10;
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

void Boss::setForm(int newform)
{
	form = newform;
}

void Boss::takesDamage(int dmgValue)
{
	this->HP -= dmgValue;
}

int Boss::getStatus()
{
	return this->status;
}

void Boss::changeStatus()
{
	if (this->status == 0)
	{
		this->status = 1;
	}
	else if (this->status == 1)
	{
		this->status = 0;
	}
}