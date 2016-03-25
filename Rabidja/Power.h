#ifndef POWER_H
#define POWER_H

#include "Entity.h"

class Map;

class Power : public Entity
{
public:

	enum type
	{
		yellow,
		red,
		green,
	};

	Power(type aType, float aTimeToRespawn, int aPosX, int aPosY, Map* theMap);
	~Power();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;

	void Take();
	void Release();

	void SetPosition(int X, int Y);

	bool GetIsAttached();
	void SetIsAttached(bool newState);
	bool GetCanBePicked();

	void Reset();

	void Activate();
	void Desactivate();

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

	Map* map;
};

#endif