#ifndef DATA_H
#define DATA_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Data
{

public:
	static Data* Instance();

	const enum
	{
		up,
		down,
		right,
		left,
		action,
		jump,
		start
	};

	//Structures
	struct Button
	{
		bool left;
		bool right;
		bool up;
		bool down;
		bool jump;
		bool action;
		bool start;
	};

	/* tile size = 32 */
	const int TILE_SIZE = 32;

	/* Number of tile in X */
	const int TILE_X = 20;

	/* Number of tile in Y */
	const int TILE_Y = 10;

	// Constant of gravity = 0.6f
	const float GRAVITY_SPEED = 0.6f;
	// Constant of fall speed = 20.0f
	const float MAX_FALL_SPEED = 20.0f;
	// Constant of jump height = 15.0f
	const float JUMP_HEIGHT = 15.0f;
	// Constant of climb height = 2.0f
	const float CLIMB_HEIGHT = 2.0f;

	/* Constant for the animation = 20*/
	const int TIME_BETWEEN_2_FRAMES = 20;

	/* size of the window 800 * 480 */
	const int SCREEN_WIDTH = 800;
	/* size of the window 800 * 480 */
	const int SCREEN_HEIGHT = 480;

	/* size of the map : 600 x 400 tiles */
	const int MAX_MAP_X = TILE_X * TILE_SIZE;
	/* size of the map : 600 x 400 tiles */
	const int MAX_MAP_Y = TILE_Y * TILE_SIZE;

	/* Width of the player = 40 */
	const int PLAYER_WIDTH = 40;
	/* height of the player = 50 */
	const int PLAYER_HEIGTH = 50;
	/* time = 5 */
	const int TIME_BETWEEN_2_FRAMES_PLAYER = 5;

	/* State of the player */
	const int IDLE = 0;
	const int WALK = 1;
	const int JUMP1 = 2;
	const int LADDER = 3;
	const int DEAD = 4;

	const int RIGHT = 1;
	const int LEFT = 2;

	// 6 tiles per line
	const int TILE_PER_LINE = 6;

	const int TILE_LADDER = -1;
	const int BLANK_TILE = 0;
	const int TILE_TRAVERSABLE = 1;
	const int TILE_DUR = 2;

private:

	Data();
	~Data();

	static Data* m_instance;
};


#endif