#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Tile.h"

class Player : public Entity
{
public:
	Player(Map* map);
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
	bool CheckCollision(Map* map);
	bool CheckCollisionBottom(Map* map);
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

	int TileSize;

	bool debug;
	
	Map* theMap;
};

#endif