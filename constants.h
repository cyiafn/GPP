// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Three Cs DX constants.h v1.0

#ifndef _CONSTANTS_H            // Prevent multiple definitions if this 
#define _CONSTANTS_H            // file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

//-----------------------------------------------
// Useful macros
//-----------------------------------------------
// Safely delete pointer referenced item
#define SAFE_DELETE(ptr)       { if (ptr) { delete (ptr); (ptr)=NULL; } }
// Safely release pointer referenced item
#define SAFE_RELEASE(ptr)      { if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
// Safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); (ptr)=NULL; } }
// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

// Safely call onLostDevice
#define SAFE_ON_LOST_DEVICE(ptr)    { if(ptr) { ptr->onLostDevice(); } }
// Safely call onResetDevice
#define SAFE_ON_RESET_DEVICE(ptr)   { if(ptr) { ptr->onResetDevice(); } }
#define TRANSCOLOR  SETCOLOR_ARGB(0,255,0,255)  // transparent color (magenta)

//-----------------------------------------------
//                  Constants
//-----------------------------------------------
// window
const char CLASS_NAME[] = "dontdie";
const char GAME_TITLE[] = "Don't Die";
const bool FULLSCREEN = false;          // windowed or fullscreen
const UINT GAME_WIDTH = 1280;			// width of game in pixels
const UINT GAME_HEIGHT = 720;			// height of game in pixels

// game
const double PI = 3.14159265;
const float FRAME_RATE = 60.0f;                // the target frame rate (frames/sec)
const float MIN_FRAME_RATE = 10.0f;             // the minimum frame rate
const float MIN_FRAME_TIME = 1.0f/FRAME_RATE;   // minimum desired time for 1 frame
const float MAX_FRAME_TIME = 1.0f/MIN_FRAME_RATE; // maximum time used in calculations

//graphics images
const char BOSS_IMAGE1[] = "pictures\\Boss form 1.png";
const char BOSS_IMAGE2[] = "pictures\\Boss form 2.png";
const char BOSS_IMAGE3[] = "pictures\\Boss form 3.png";
const char BOSSCANNON_IMAGE[] = "pictures\\Boss form 1 Cannon Ball.png";
const char BOSS1_SHIELD[] = "pictures\\Boss form 1 Shield.png";
// graphic images
//const char MAP_IMAGE[] = "pictures\\MapforGame.png";  // Picture of background
const char PLAYER_IMAGE[] = "pictures\\player.png"; // picture of Player
const char ZOMBIE_IMAGE[] = "pictures\\zombie.png";  // game textures

// player movement
const float ROTATION_RATE = 180.0f;             // degrees per second
const float SCALE_RATE = 0.2f;                  // % change per second
const float PLAYER_SPEED = 100.0f;                // pixels per second
const float PLAYER_SCALE = 1.5f;                  // starting player scale


// audio files
const char WAVE_BANK[] = "";
const char SOUND_BANK[] = "";

// audio cues

// key mappings
// In this game simple constants are used for key mappings. If variables were used
// it would be possible to save and restore key mappings from a data file.
const UCHAR CONSOLE_KEY  = VK_OEM_3;    // `~ key for U.S.
const UCHAR ESC_KEY      = VK_ESCAPE;   // escape key
const UCHAR ALT_KEY      = VK_MENU;     // Alt key
const UCHAR ENTER_KEY    = VK_RETURN;   // Enter key
const UCHAR PLAYER_RIGHT_KEY = 0x44; //Right arrow key
const UCHAR PLAYER_LEFT_KEY = 0x41; //Left Arrow key
const UCHAR PLAYER_UP_KEY = 0x57; //Up Arrow key
const UCHAR PLAYER_DOWN_KEY = 0x53; //Down Arrow key
const UCHAR BOSS_STAGE1 = VK_SNAPSHOT; //skip to boss stage 1 cheat
const UCHAR BOSS_STAGE2 = VK_INSERT; //skip to boss stage 2 cheat
const UCHAR BOSS_STAGE3 = VK_DELETE; //skip to boss stage 3 cheat
const UCHAR BOSS_CLEAR = VK_BACK; //skip to win cheat
#endif

