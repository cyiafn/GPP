#include "boss.h"

Boss::Boss() : Entity()
{
	spriteData.width = bossNS::WIDTH;           // size of boss
	spriteData.height = bossNS::HEIGHT;
	spriteData.x = bossNS::X;                   // location on screen
	spriteData.y = bossNS::Y;
	spriteData.rect.bottom = bossNS::HEIGHT;    // rectangle to select parts of an image
	spriteData.rect.right = bossNS::WIDTH;
	frameDelay = bossNS::BOSS_ANIMATION_DELAY;
	startFrame = bossNS::BOSS_START_FRAME;     // first frame of boss animation
	endFrame = bossNS::BOSS_END_FRAME;     // last frame of boss animation
	currentFrame = startFrame;
	radius = bossNS::WIDTH / 2.0;
	collisionType = entityNS::CIRCLE;
}


bool Boss::initialize(Game *gamePtr, int width, int height, int ncols, TextureManager *textureM, int bossform)
{
	if (bossform == 1)
	{
		boss_form1.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
		boss_form1.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
		boss_form1.setCurrentFrame(bossNS::BOSS_START_FRAME);
		boss_form1.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
		boss_form1.setLoop(true);                  // do not loop animation
		shieldOn = true;

	}
	else if (bossform == 2)
	{
		shieldOn = false;
		boss_form2.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
		boss_form2.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
		boss_form2.setCurrentFrame(bossNS::BOSS_START_FRAME);
		boss_form2.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
		boss_form2.setLoop(true);                  // do not loop animation
	}
	else if (bossform == 3)
	{
		shieldOn = false;
		boss_form3.initialize(gamePtr->getGraphics(), width, height, ncols, textureM);
		boss_form3.setFrames(bossNS::BOSS_START_FRAME, bossNS::BOSS_END_FRAME);
		boss_form3.setCurrentFrame(bossNS::BOSS_START_FRAME);
		boss_form3.setFrameDelay(bossNS::BOSS_ANIMATION_DELAY);
		boss_form3.setLoop(true);
	}
	return(Entity::initialize(gamePtr, width, height, ncols, textureM));
}

void Boss::draw()
{
	Image::draw();              // draw boss
	if (shieldOn)
		// draw shield using colorFilter 50% alpha
		shield.draw(spriteData, graphicsNS::ALPHA50 & colorFilter);
}

void Boss::update(float frameTime)
{
	Entity::update(frameTime);
	///////////////////////////
	// CHEAT CODE :PogChamp: //
	///////////////////////////
	if (input->isKeyDown(BOSS_STAGE1)) //cheat code stage 1
	{
		form = 1;
		shieldOn = true;
		form1Spawn = true;
		HP = bossNS::MAXHP;
		form1Dead = false;
		form2Spawn = false;
		form3Spawn = false;
		
	}
	else if (input->isKeyDown(BOSS_STAGE2)) //cheat code stage 2
	{
		form = 2;
		shieldOn = false;
		form2Spawn = true;
		HP = bossNS::MAXHP;
		form1Dead = true;
		form2Dead = false;
		form1Spawn = false;
		form3Spawn = false;
	}
	else if (input->isKeyDown(BOSS_STAGE3)) //cheat code stage 3
	{
		form = 3;
		shieldOn = false;
		form3Spawn = true;
		HP = bossNS::MAXHP;
		form3Dead = false;
		form1Spawn = false;
		form2Spawn = false;
		
	}
	else if (input->isKeyDown(BOSS_CLEAR)) //clear boss = win game
	{
		form1Spawn = false;
		form2Spawn = false;
		form3Spawn = false;
		form1Dead = true;
		form2Dead = true;
		form3Dead = true;
	}
	//////////////////////////////////
	// Boss Health Tracking :kappa: //
	//////////////////////////////////
	if ((HP <= bossNS::MAXHP*(2/3)) && (HP > (bossNS::MAXHP/3)) && form1Spawn == true) //>33%HP <=66% HP
	{
		form1Dead = true; //boss 1 is defeated
		form1Spawn = false; //no longer spawn boss 1
		form2Spawn = true; //spawn boss 2
	}
	else if (HP <= bossNS::MAXHP && form2Spawn == true) //<=33% HP
	{
		form2Dead = true; //boss 2 is defeated
		form1Dead = true; //assuming: boss 1 is defeated
		form1Spawn = false; //no longer spawn boss 1
		form2Spawn = false; //no longer spawn boss 2
		form3Spawn = true;
	}
	else if (HP = 0 && form3Spawn == true) //dieded
	{
		form3Dead = true;
		form3Spawn = false;
	}
	/////////////////////////////
	// WIN CONDITION :kreyGASM://
	/////////////////////////////
	if (form1Dead == true && form2Dead == true && form3Dead == true) //if 3 forms are dead
	{
		//WIN
		MessageBox(nullptr, TEXT("YOU WIN!!"), TEXT(""), MB_OK);
	}
	//////////////////////////////
	//rotating shield :cmonBruh://
	//////////////////////////////
	if (shieldOn)
	{
		//angle += frameTime*rotation_rate;
		//shieldX = bossNS::X + cos(angle)*radius;
		//shieldY = bossNS::Y + sin(angle)*radius;
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

void Boss::setForm(int newform)
{
	form = newform;
}