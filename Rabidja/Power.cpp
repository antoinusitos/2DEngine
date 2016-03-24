#include "Power.h"
#include <time.h>

#include "Entity.h"

Power::Power(type aType, float aTimeToRespawn, int aPosX, int aPosY)
{
	width = Data::Instance()->TILE_SIZE;
	height = Data::Instance()->TILE_SIZE;

	currentType = aType;
	int theTileType = 15;

	if (currentType == type::green)
	{
		theTileType = 11;
	}
	else if (currentType == type::red)
	{
		theTileType = 12;
	}
	else if (currentType == type::yellow)
	{
		theTileType = 13;
	}

	if (!texture.loadFromFile("graphics/level1TileSheet2.png"))
	{
		// Error
		cout << "Error while loading the texture of the player." << endl;
	}
	else
	{
		int setLength = Data::Instance()->TILE_PER_LINE;
		ySprite = floor(theTileType / setLength);
		xSprite = theTileType %  setLength;
		sprite.setTexture(texture);
	}

	timeToRespawn = aTimeToRespawn;
	currentTime = 0.0f;
	posX = aPosX * width;
	posY = aPosY * height;
	x = aPosX * width;
	y = aPosY * height;
	debug = false;
	isAttached = true;
	canbePicked = true;
}

Power::~Power()
{
}

void Power::Draw(RenderWindow &window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
	window.draw(sprite);

	if (debug)
	{
		Debug::Instance()->AddDebug("isAttached:" + to_string(isAttached), false, 15, Color::Blue);
		Debug::Instance()->AddDebug("x:" + to_string(x), false, 15, Color::Blue);
		Debug::Instance()->AddDebug("y:" + to_string(y), false, 15, Color::Blue);
		Debug::Instance()->AddDebug("time:" + to_string(time(0) - pickUpTime), false, 15, Color::Blue);
		Debug::Instance()->AddDebug("timeToRespawn:" + to_string(timeToRespawn), false, 15, Color::Blue);
	}
}

void Power::Update(Input * input)
{
	if (!isAttached)
	{
		if (time(0) - pickUpTime >= timeToRespawn)
		{
			x = posX;
			y = posY;
			isAttached = true;
			pickUpTime = time(0);
		}
	}
}

void Power::Take()
{
	if (isAttached)
	{
		pickUpTime = time(0);
		isAttached = false;
	}
}

void Power::Release()
{
	x = (x / width) * width;
	y = (y / height) * height;
}

void Power::SetPosition(int X, int Y)
{
	x = X;
	y = Y;
}

bool Power::GetIsAttached()
{
	return isAttached;
}

bool Power::GetCanBePicked()
{
	return canbePicked;
}
