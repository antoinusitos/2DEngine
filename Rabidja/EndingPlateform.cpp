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

	if (!bufferWin.loadFromFile("sound/StageClear.wav"))
	{
		// Error
		cout << "Error while loading the sound explosion of the bomb." << endl;
	}
	else
	{
		soundWin.setBuffer(bufferWin);
	}

	if (!textureWin.loadFromFile("graphics/Win.png"))
	{
		// Error
		cout << "Error while loading the texture buttonstart of the main." << endl;
	}
	else
		spriteWin.setTexture(textureWin);

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
	theMap = aMap;
	finished = false;
}

void EndingPlateform::ResetEntity()
{
	ResetPos();
	move = false;
	retour = false;
	yPos = y;
}

EndingPlateform::~EndingPlateform()
{
}

void EndingPlateform::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	window.draw(sprite);
	if (finished)
	{
		int midWidth = Data::Instance()->SCREEN_WIDTH / 3;
		int midHeight = Data::Instance()->SCREEN_HEIGHT / 3;
		spriteWin.setPosition(midWidth / 4, midHeight / 2);
		window.draw(spriteWin);
	}
}

void EndingPlateform::Update(Input * input, Time time)
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
		if (y - 32 <= limitY)
		{
			if (!theMap->GetCanFinish())
			{
				theBomb->PlayExplosion();
				cout << endl; // game over
				sleep(Time(milliseconds(1500)));
				theMap->SetGameOver(true, false);
			}
			else
			{
				finished = true;
				soundWin.play();
				cout << endl; // win 
				sleep(Time(milliseconds(3000)));
				theMap->SetGameOver(true, true);
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
	if (theBomb->GetExploded())
	{
		sleep(Time(milliseconds(1500)));
		theMap->SetGameOver(true, false);
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
