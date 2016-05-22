#include "Tuto.h"

Tuto::Tuto(string tileName, int theX, int theY)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		sprite.setTexture(texture);
	}

	width = 256;
	height = 128;
	x = theX * 32;
	y = theY * 32;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}


Tuto::~Tuto()
{
}

void Tuto::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Tuto::Update(Input* input, Time time)
{

}

void Tuto::ResetEntity()
{

}