#include "Elevator.h"

Elevator::Elevator(string tileName, int theX, int theY, Map* aMap)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
		sprite.setTexture(texture);

	up = true;
	speed = 2.0f;
	width = 96;
	height = 32;
	x = theX * 32;
	y = theY * height;
	yPos = y;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
	limitY = 32 * 2;
	theMap = aMap;
	thePlayer = nullptr;
}


Elevator::~Elevator()
{

}

void Elevator::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	window.draw(sprite);
}

void Elevator::Update(Input * input, Time time)
{
	if (up)
	{
		y -= 1;
		if (y <= limitY)
		{
			y = limitY;
			up = false;
		}
		if (thePlayer)
		{
			thePlayer->SetY(y - height);
		}
	}
	else
	{
		y += 1;
		if (y >= yPos)
		{
			y = yPos;
			up = true;
		}
		if (thePlayer)
		{
			thePlayer->SetY(y - height);
		}
	}
}

void Elevator::SetPlayer(Player * thePl)
{
	thePlayer = thePl;
}

Player* Elevator::GetPlayer()
{
	return thePlayer;
}
