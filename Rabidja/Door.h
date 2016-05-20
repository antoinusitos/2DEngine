#pragma once
#include "Entity.h"
class Door : public Entity
{
public:
	Door(string tileName, int theX, int theY);
	~Door();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input = nullptr, Time time = Time::Zero) override;

	void ResetEntity() override;

private:
	int xSprite;
	int ySprite;
};

