#ifndef PLAYER_H
#define PLAYER_H

#include "Data.h"
#include "Input.h"
#include "Map.h"

class Player
{
public:
	Player();
	~Player();

	void Initialize();

	// setter

	void SetX(int theX);
	void SetY(int theY);

	void SetHeight(int theHeight);
	void SetWidth(int theWidth);

	void SetLife(int theLife);
	void SetSpeed(float theSpeed);

	// getter

	int GetX();
	int GetY();

	int GetHeight();
	int GetWidth();

	int GetLife();
	float GetSpeed();

	void Draw(sf::RenderWindow &window);
	void Update(Input* input);
	void mapCollision(Map* map);

private:
	int x;
	int y;

	float dirX;
	float dirY;

	int width;
	int height;

	int directionX;
	int directionY;
	bool isGrounding;

	int direction;
	int state;

	int frameNumber;
	int frameTimer;
	int frameMax;

	float speed;

	int life;

	sf::Texture texture;
	sf::Sprite sprite;
};

#endif