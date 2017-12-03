#ifndef _PISTOLBULLET_H                 // Prevent multiple definitions if this 
#define _PISTOLBULLET_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace bulletNS
{
	const int WIDTH = 32;                   // image width
	const int HEIGHT = 32;                  // image height
	//const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	//const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const int X = 0;
	const int Y = 0;
	const float SPEED = 0;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   PISTOLBULLET_START_FRAME = 0;     //No animation  
	const int   PISTOLBULLET_END_FRAME = 0;         
	const int	PISTOL_DAMAGE = 4;
}

// inherits from Entity class
class Bullet : public Entity
{
private:
	float prevX;
	float prevY;
	int hp;
public:
	// constructor
	Bullet();
	// inherited member functions
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	void update(float frameTime);
	void setPrev(float x, float y);
	void revertLocation();
	void damageMe(int damageValue) {};
};

#endif