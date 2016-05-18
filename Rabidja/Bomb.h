#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"

class Bomb : public Entity
{
public:
	Bomb(string tileName, int theX, int theY);
	~Bomb();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, Time time) override;

	void UpdateY(int value);

	void PlayExplosion();

private:
	int xSprite;
	int ySprite;

	sf::SoundBuffer bufferExplosion;
	sf::Sound soundExplosion;

	float timeToExplode;
	float currentTime;
};

#endif