#include "EndingPlateform.h"

EndingPlateform::EndingPlateform(string tileName, int theX, int theY, Bomb* aBomb, Map* aMap)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		ySprite = 8;
		xSprite = 3;
		sprite.setTexture(texture);
	}
	width = 32;
	height = 32;
	x = theX * width;
	y = theY * height;
	yPos = y;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width * 3, height));
	move = false;
	retour = false;
	limitY = 32 * 5;
	theBomb = aBomb;
}

EndingPlateform::~EndingPlateform()
{
}

void EndingPlateform::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	window.draw(sprite);
}

void EndingPlateform::Update(Input * input)
{
	if (move)
	{
		y -= 1;
		theBomb->UpdateY(y - 32);
		if (y <= limitY)
		{
			y = limitY;
			move = false;
		}
		if (y + 32 >= limitY)
		{
			if (theMap->GetCanFinish())
			{
				// victory
			}
			else
			{
				//loose
			}
		}
	}
	if (retour)
	{
		y += 1;
		theBomb->UpdateY(y - 32);
		if (y >= yPos)
		{
			y = yPos;
			retour = false;
		}
	}
}

void EndingPlateform::SetMove(bool state)
{
	move = state;
}

void EndingPlateform::SetRetour(bool state)
{
	retour = state;
}
