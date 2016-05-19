#include "Power.h"
#include <time.h>

#include "Entity.h"
#include "Tile.h"
#include "Map.h"
#include "Blocker.h"
#include "EndingPlateform.h"

Power::Power(type aType, float aTimeToRespawn, int aPosX, int aPosY, Map* theMap, int theTypeExecution)
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

	if (!bufferPut.loadFromFile("sound/put.wav"))
	{
		// Error
		cout << "Error while loading the sound put of the power." << endl;
	}
	else
	{
		soundPut.setBuffer(bufferPut);
	}

	if (!bufferReturn.loadFromFile("sound/return.wav"))
	{
		// Error
		cout << "Error while loading the return put of the power." << endl;
	}
	else
	{
		soundReturn.setBuffer(bufferReturn);
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
	map = theMap;
	pickUpTime = 0.0f;
	typeExecution = theTypeExecution;
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
		Debug::Instance()->AddDebug("time:" + to_string(pickUpTime/1000.0f), false, 15, Color::Blue);
		Debug::Instance()->AddDebug("timeToRespawn:" + to_string(timeToRespawn), false, 15, Color::Blue);
	}
}

void Power::Update(Input * input, sf::Time time)
{
	if (!isAttached)
	{
		pickUpTime += time.asMilliseconds();
		if (pickUpTime / 1000 >= timeToRespawn)
		{
			Reset();
			map->ResetRunningPower();
		}
	}
}

void Power::Take()
{
	if (isAttached)
	{
		pickUpTime = 0.0f;
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

void Power::SetIsAttached(bool newState)
{
	isAttached = newState;
}

bool Power::GetCanBePicked()
{
	return canbePicked;
}

void Power::Reset()
{
	x = posX;
	y = posY;
	isAttached = true;
	pickUpTime = 0.0f;
	Desactivate();
	soundReturn.play();
}

void Power::Activate()
{
	PlayPut();

	if (typeExecution == 0)
	{
		map->GetEnding()->SetMove(true);
	}
	else if (typeExecution == 1)
	{
		map->GetBlockers().at(0)->Rotate(true);
		map->SetCanFinish(true);
	}
	else if (typeExecution == 2)
	{
		map->GetTile(45)->Hide();
		map->GetTile(55)->Hide();
		map->GetTile(65)->Hide();
	}


	/*if (currentType == type::green)
	{
		map->GetEnding()->SetMove(true);
	}
	else if (currentType == type::red)
	{
		map->GetBlockers().at(0)->Rotate(true);
		map->SetCanFinish(true);
	}
	else if (currentType == type::yellow)
	{
		map->GetTile(45)->Hide();
		map->GetTile(55)->Hide();
		map->GetTile(65)->Hide();
	}*/
}

void Power::Desactivate()
{
	if (currentType == type::green)
	{
		map->GetEnding()->SetMove(false);
		map->GetEnding()->SetRetour(true);
	}
	else if (currentType == type::red)
	{
		//map->GetBlockers().at(0)->Rotate(false);
		//map->SetCanFinish(false);
	}
	else if (currentType == type::yellow)
	{
		map->GetTile(45)->Show();
		map->GetTile(55)->Show();
		map->GetTile(65)->Show();
	}
}

void Power::PlayPut()
{
	soundPut.play();
}
