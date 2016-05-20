#ifndef TILE_H
#define TILE_H

#include "Entity.h"

class Tile : public Entity
{
public:
	Tile(string tileName, int theX, int theY, int theTileType);
	~Tile();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input, sf::Time time) override;

	int GetType();
	int GetTileType();
	void Hide();
	void Show();
	void ResetEntity() override;

private:
	int collisionType;
	int originalCollisionType;
	int tileType;

	int xSprite;
	int ySprite;

	bool mustBeRendered;
};

#endif