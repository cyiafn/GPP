#ifndef _ZOMBIE_H                 // Prevent multiple definitions if this 
#define _ZOMBIE_H                 // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "entity.h"
#include "constants.h"

namespace zombieNS
{
	const int WIDTH = 64;                   // image width
	const int HEIGHT = 64;                  // image height
	const int X = GAME_WIDTH / 2 - WIDTH / 2;   // location on screen
	const int Y = GAME_HEIGHT / 2 - HEIGHT / 2;
	const float SPEED = 0;                // 100 pixels per second
	const int   TEXTURE_COLS = 1;           // texture has 1 columns
	const int   ZOMBIE_START_FRAME = 0;       // ship starts at frame 0
	const int   ZOMBIE_END_FRAME = 1;         // ship animation frames 0,1,2,3
	const float ZOMBIE_ANIMATION_DELAY = 0.2f; // time between frames
	const int DAMAGE = 1;
	const int HEALTH = 4;
}

// inherits from Entity class
class Zombie : public Entity
{
private:
	bool attack;
	Image zomb;

public:
	// constructor
	Zombie();
	virtual void draw();
	virtual bool initialize(Game *gamePtr, int width, int height, int ncols,
		TextureManager *textureM);
	// inherited member functions
	void update(float frameTime);
	void ai(float frameTime, Zombie &ent);
};
#endif

