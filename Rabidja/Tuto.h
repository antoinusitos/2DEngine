#pragma once
#include "Entity.h"
class Tuto : public Entity
{
public:
	Tuto(string tileName, int theX, int theY);
	~Tuto();

	void Draw(sf::RenderWindow &window) override;
	void Update(Input* input = nullptr, Time time = Time::Zero) override;

	void ResetEntity() override;

};

