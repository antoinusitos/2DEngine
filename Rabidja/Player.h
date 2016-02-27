#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void Initialize();

	// setter

	void SetLife(int theLife);
	void SetSpeed(float theSpeed);

	// getter

	int GetLife();
	float GetSpeed();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;
	void mapCollision(Map* map);

private:
	float dirX;
	float dirY;

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

	bool hasJump;
	bool canJump;

	int jumpState;
};

#endif