#ifndef BLOCKER_H
#define BLOCKER_H

#include "Entity.h"

class Blocker :	public Entity
{
public:
	Blocker(string tileName, int theX, int theY);
	~Blocker();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, Time time) override;

	void Rotate(bool right);

private:
	int xSprite;
	int ySprite;
};

#endif