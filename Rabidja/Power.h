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
		blue,
	};

	Power(type aType, float aTimeToRespawn, int aPosX, int aPosY, Map* theMap, int theTypeExecution);
	~Power();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, sf::Time time) override;

	void Take();
	void Release();

	void SetPosition(int X, int Y);

	bool GetIsAttached();
	void SetIsAttached(bool newState);
	bool GetCanBePicked();

	void Reset();

	void Activate();
	void Desactivate();

	void PlayPut();

private:

	float timeToRespawn;
	float currentTime;
	float pickUpTime;

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

	sf::SoundBuffer bufferPut;
	sf::Sound soundPut;

	sf::SoundBuffer bufferReturn;
	sf::Sound soundReturn;

	int typeExecution;
};

#endif