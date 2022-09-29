#pragma once
#include <random>
#include <stdlib.h>
#include <chrono>
#include <thread>

inline void sleep(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

#define CANVAS_WIDTH 28.5f
#define CANVAS_HEIGHT 16.5f

#define ASSET_PATH ".\\assets\\"

#define PLAYER_SIZE 1.5f
#define PLAYER_MOTION_RANGE 5.0f
#define PLAYER_ATTACK_RANGE 5.0f
//#define RAND_MAX 1.0f
#define SETCOLOR(c,r,g,b){c[0] = r; c[1] = g; c[2] = b;}
#define RAND0TO1() (rand()/(float)RAND_MAX)

inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

