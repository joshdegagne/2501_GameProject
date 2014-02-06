#include "Entity.h"

Entity::Entity(float x, float y)
{
	setPos(x,y);
}

float Entity::getX() { return pos.x; }
float Entity::getY() { return pos.y; }
void Entity::setX(float x) { pos.x = x; }
void Entity::setY(float y) { pos.y = y; }

void Entity::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}