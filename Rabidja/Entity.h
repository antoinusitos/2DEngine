#ifndef ENTITY_H
#define ENTITY_H

#include "Data.h"
#include "Input.h"
#include "Map.h"
#include <SFML/Audio.hpp>
#include "Debug.h"

using namespace std;
using namespace sf;

class Entity
{
public:
	Entity();
	~Entity();

	void SetX(int theX);
	void SetY(int theY);

	void SetHeight(int theHeight);
	void SetWidth(int theWidth);

	int GetX();
	int GetY();

	int GetHeight();
	int GetWidth();

	virtual void Draw(sf::RenderWindow &window) = 0;
	virtual void Update(Input* input = nullptr, Time time = Time::Zero) = 0;

	void ResetPos();

	virtual void ResetEntity() = 0;

protected:
	int x;
	int y;

	int xReset;
	int yReset;

	int width;
	int height;

	sf::Texture texture;
	sf::Sprite sprite;

	bool debug;
};

#endif