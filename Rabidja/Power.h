#ifndef POWER_H
#define POWER_H

#include "Entity.h"

class Power : public Entity
{
public:

	enum type
	{
		yellow,
		red,
		green,
	};

	Power(type aType, float aTimeToRespawn, int aPosX, int aPosY);
	~Power();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;

	void Take();
	void Release();

	void SetPosition(int X, int Y);

	bool GetIsAttached();
	bool GetCanBePicked();

private:

	float timeToRespawn;
	float currentTime;
	time_t pickUpTime;

	type currentType;
	
	bool isAttached;
	bool canbePicked;

	int posX;
	int posY;

	int collisionType;
	int tileType;

	int xSprite;
	int ySprite;
};

#endif