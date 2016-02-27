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

	const int TILE_SIZE = 32;

	/* Constant for the player */
	const float GRAVITY_SPEED = 0.6f;
	const float MAX_FALL_SPEED = 15.0f;
	const float JUMP_HEIGHT = 10.0f;

	/* Constant for the animation */
	const int TIME_BETWEEN_2_FRAMES = 20;

	/* size of the window */
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 480;

	/* size of the map : 400 x 150 tiles */
	const int MAX_MAP_X = 400;
	const int MAX_MAP_Y = 150;

	/* Size of the player */
	const int PLAYER_WIDTH = 40;
	const int PLAYER_HEIGTH = 50;
	const int TIME_BETWEEN_2_FRAMES_PLAYER = 5;

	/* State of the player */
	const int IDLE = 0;
	const int WALK = 1;
	const int JUMP1 = 2;
	const int JUMP2 = 3;
	const int DEAD = 4;

	const int RIGHT = 1;
	const int LEFT = 2;

private:

	Data();
	~Data();

	static Data* m_instance;
};


#endif