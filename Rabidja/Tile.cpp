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
		xSprite = theTileType % setLength;
		sprite.setTexture(texture);
	}

	x = theX;
	y = theY;
	tileType = theTileType;

	// number of tile which has no collision
	const int length = 30;

	// tiles with no collision
	int transparent[length] = { 15, 0, 1, 12, 13, 66, 67, 68, 69, 76, 77, 78, 79, 86, 87, 88, 89, 19 };

	//find the tile in the array
	int *foo = std::find(std::begin(transparent), std::end(transparent), theTileType);

	//tile found
	if (foo != transparent + length) 
	{
		collisionType = Data::Instance()->BLANK_TILE;
	}
	else if (tileType == 50 || tileType == 40 || tileType == 30 || tileType == 20 || tileType == 10 || tileType == 32 || tileType == 42 || tileType == 52 || tileType == 62 || tileType == 72 || tileType == 82)
	{
		collisionType = Data::Instance()->TILE_LADDER;
	}
	else 
	{
		collisionType = Data::Instance()->TILE_DUR;
	}

	originalCollisionType = collisionType;

	mustBeRendered = true;
}


Tile::~Tile()
{
}

void Tile::Draw(RenderWindow &window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
	if(mustBeRendered)
		window.draw(sprite);
}

void Tile::Update(Input * input)
{
}

int Tile::GetType()
{
	return collisionType;
}

int Tile::GetTileType()
{
	return tileType;
}

void Tile::Hide()
{
	mustBeRendered = false;
	collisionType = Data::Instance()->BLANK_TILE;
}

void Tile::Show()
{
	mustBeRendered = true;
	collisionType = originalCollisionType;
}

