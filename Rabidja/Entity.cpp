#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::SetX(int theX)
{
	x = theX;
}

void Entity::SetY(int theY)
{
	y = theY;
}

void Entity::SetHeight(int theHeight)
{
	height = theHeight;
}

void Entity::SetWidth(int theWidth)
{
	width = theWidth;
}

int Entity::GetX()
{
	return x;
}

int Entity::GetY()
{
	return y;
}

int Entity::GetHeight()
{
	return height;
}

int Entity::GetWidth()
{
	return width;
}

void Entity::ResetPos()
{
	x = xReset;
	y = yReset;
}
