#pragma once
#include "Entity.h"
class Panneau :	public Entity
{
public:
	Panneau(string tileName, int theX, int theY, int number);
	~Panneau();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input = nullptr, Time time = Time::Zero) override;

	void ResetEntity() override;

private:
	int xSprite;
	int ySprite;
};

