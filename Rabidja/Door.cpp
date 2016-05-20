#include "Door.h"

Door::Door(string tileName, int theX, int theY)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		ySprite = 6;
		xSprite = 0;
		sprite.setTexture(texture);
	}

	width = 64;
	height = 96;
	x = theX * 32;
	y = theY * 32;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * 32, ySprite * 32, width, height));
}


Door::~Door()
{
}

void Door::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Door::Update(Input* input, Time time)
{

}

void Door::ResetEntity()
{

}
