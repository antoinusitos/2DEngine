#include "Tile.h"

Tile::Tile(string tileName, int theX, int theY, int theType)
{
	if (!texture.loadFromFile("graphics/"+tileName+".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
		sprite.setTexture(texture);

	x = theX;
	y = theY;
	width = Data::Instance()->TILE_SIZE;
	height = Data::Instance()->TILE_SIZE;
	type = theType;
}


Tile::~Tile()
{
}

void Tile::Draw(RenderWindow &window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
	window.draw(sprite);
}

void Tile::Update(Input * input)
{
}

int Tile::GetType()
{
	return type;
}
