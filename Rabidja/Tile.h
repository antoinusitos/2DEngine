#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(string tileName, int theX, int theY, int theType);
	~Tile();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input) override;

	int GetType();

private:
	int type;
};

#endif