#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "Entity.h"
#include "Player.h"

class Elevator : public Entity
{

public:

	Elevator(string tileName, int theX, int theY, Map* aMap);
	~Elevator();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;

	void SetPlayer(Player* thePl);
	Player* GetPlayer();

private:

	int xSprite;
	int ySprite;
	bool up;
	float speed;
	int limitY;
	int yPos;
	Map* theMap;

	Player* thePlayer;
};

#endif