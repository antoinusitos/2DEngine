#include "Tile.h"

Tile::Tile(string tileName, int theX, int theY, int theTileType)
{
	width = Data::Instance()->TILE_SIZE;
	height = Data::Instance()->TILE_SIZE;

	if (!texture.loadFromFile("graphics/"+tileName+".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		int setLength = Data::Instance()->TILE_PER_LINE;
		ySprite = floor(theTileType / setLength) ;
		xSprite = theTileType %  setLength;
		sprite.setTexture(texture);
	}

	x = theX;
	y = theY;
	tileType = theTileType;

	// number of tile which has no collision
	const int length = 8;

	// tiles with no collision
	int transparent [length] = { 15, 0, 1, 2, 6, 7, 8, 11 };

	//find the tile in the array
	int *foo = std::find(std::begin(transparent), std::end(transparent), theTileType);

	//tile found
	if (foo != transparent + length) {
		collisionType = Data::Instance()->BLANK_TILE;
	}
	else 
	{
		collisionType = Data::Instance()->TILE_DUR;
	}
}


Tile::~Tile()
{
}

void Tile::Draw(RenderWindow &window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
	window.draw(sprite);
}

void Tile::Update(Input * input)
{
}

int Tile::GetType()
{
	return collisionType;
}
