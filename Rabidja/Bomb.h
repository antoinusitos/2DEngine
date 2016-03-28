#ifndef BOMB_H
#define BOMB_H

#include "Entity.h"

class Bomb : public Entity
{
public:
	Bomb(string tileName, int theX, int theY);
	~Bomb();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;

	void UpdateY(int value);

private:
	int xSprite;
	int ySprite;
};

#endif