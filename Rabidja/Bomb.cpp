#include "Bomb.h"

Bomb::Bomb(string tileName, int theX, int theY)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		ySprite = 0;
		xSprite = 5;
		sprite.setTexture(texture);
	}
	width = 32;
	height = 32;
	x = theX * width;
	y = theY * height;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
}

Bomb::~Bomb()
{
}

void Bomb::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	window.draw(sprite);
}

void Bomb::Update(Input * input)
{
}

void Bomb::UpdateY(int value)
{
	y = value;
}
