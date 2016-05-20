#include "Panneau.h"

Panneau::Panneau(string tileName, int theX, int theY, int number)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		ySprite = 9;
		xSprite = number * 3;
		sprite.setTexture(texture);
	}

	width = 96;
	height = 32;
	x = theX * 32;
	y = theY * height;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * 32, ySprite * 32, width, height));
}


Panneau::~Panneau()
{
}

void Panneau::Draw(sf::RenderWindow &window)
{
	window.draw(sprite);
}

void Panneau::Update(Input* input, Time time)
{

}

void Panneau::ResetEntity()
{

}
