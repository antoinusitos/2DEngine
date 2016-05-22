#ifndef ENDINGPLATEFORM_H
#define ENDINGPLATEFORM_H

#include "Entity.h"
#include "Bomb.h"

class Map;

class EndingPlateform :	public Entity
{
public:
	EndingPlateform(string tileName, int theX, int theY, Bomb* aBomb, Map* aMap);
	~EndingPlateform();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, Time time) override;

	void SetMove(bool state);
	void SetRetour(bool state);
	void ResetEntity() override;

private:
	int xSprite;
	int ySprite;

	int yPos;

	int limitY;

	bool move;
	bool retour;

	Bomb* theBomb;

	Map* theMap;

	sf::SoundBuffer bufferWin;
	sf::Sound soundWin;

	sf::Texture textureWin;
	sf::Sprite spriteWin;

	bool finished;
};

#endif