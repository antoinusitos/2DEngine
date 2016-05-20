#include "Blocker.h"

Blocker::Blocker(string tileName, int theX, int theY)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		ySprite = 5;
		xSprite = 6;
		sprite.setTexture(texture);
		sprite.setOrigin(4 * 32, 32);
	}
	width = 32;
	height = 32;
	x = theX * width + width ;
	y = theY * height + (height);
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width * 4, height));
}

Blocker::~Blocker()
{
}

void Blocker::Draw(sf::RenderWindow & window)
{
	window.draw(sprite);
}

void Blocker::Update(Input * input, Time time)
{
}

void Blocker::Rotate(bool right)
{
	if (right)
	{
		sprite.setRotation(-90);
	}
	else
	{
		sprite.setRotation(0);
	}
}

void Blocker::ResetEntity()
{
	ResetPos();
	sprite.setRotation(0);
}
