#include "Bomb.h"

Bomb::Bomb(string tileName, int theX, int theY)
{
	if (!texture.loadFromFile("graphics/" + tileName + ".png"))
	{
		// Error
		cout << "Error while loading the texture of the bomb." << endl;
	}
	else
	{
		ySprite = 0;
		xSprite = 5;
		sprite.setTexture(texture);
	}

	if (!bufferExplosion.loadFromFile("sound/explosion.wav"))
	{
		// Error
		cout << "Error while loading the sound explosion of the bomb." << endl;
	}
	else
	{
		soundExplosion.setBuffer(bufferExplosion);
	}

	if (!bufferBip.loadFromFile("sound/bip.wav"))
	{
		// Error
		cout << "Error while loading the sound bip of the bomb." << endl;
	}
	else
	{
		soundBip.setBuffer(bufferBip);
	}

	width = 32;
	height = 32;
	x = theX * width;
	y = theY * height;
	sprite.setPosition(Vector2f((float)x, (float)y));
	sprite.setTextureRect(sf::IntRect(xSprite * width, ySprite * height, width, height));
	currentTime = 0;
	timeToExplode = 70.0f;
	activated = false;
	exploded = false;
	timeToBip = 1.0f;
	currentTimeToBip = 0.0f;
}

Bomb::~Bomb()
{
}

void Bomb::Draw(sf::RenderWindow & window)
{
	sprite.setPosition(Vector2f((float)x, (float)y));
	window.draw(sprite);
}

void Bomb::Update(Input * input, Time time)
{
	currentTimeToBip += time.asMilliseconds();
	if (currentTimeToBip / 1000 >= timeToBip)
	{
		currentTimeToBip = 0.0f;
		soundBip.play();
	}

	if (currentTime / 1000 >= timeToExplode * 0.9f)
	{
		timeToBip = 0.1f;
	}
	else if (currentTime / 1000 >= timeToExplode * 0.7f)
	{
		timeToBip = 0.3f;
	}
	else if (currentTime / 1000 >= timeToExplode * 0.5f)
	{
		timeToBip = 0.5f;
	}
	else if (currentTime / 1000 >= timeToExplode * 0.3f)
	{
		timeToBip = 0.75f;
	}

	if (debug)
	{
		Debug::Instance()->AddDebug("Bomb : " + to_string(currentTime / 1000), false, 15, Color::Red);
	}
	if(activated)
		currentTime += time.asMilliseconds();
	if (currentTime / 1000 >= timeToExplode && exploded == false)
	{
		PlayExplosion();
		exploded = true;
	}
}

void Bomb::UpdateY(int value)
{
	y = value;
}

void Bomb::PlayExplosion()
{
	soundExplosion.play();
}

void Bomb::Activate()
{
	activated = true;
	Time time;
	debutTime = time.asMilliseconds();
}

bool Bomb::GetExploded()
{
	return exploded;
}
