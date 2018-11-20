#include <iostream>

#include "PowerUp.h"

PowerUp::PowerUp(short X, short Y)
	:Object(X, Y)
	,blinking(true)
{}

PowerUp::PowerUp(const PowerUp& other)
	:Object(other)
{
	this->blinking = other.blinking;
}

PowerUp& PowerUp::operator=(const PowerUp& other)
{
	if (this != &other)
	{
		Object::operator=(other);
		this->blinking = other.blinking;
	}
	return *this;
}
PowerUp::~PowerUp()
{}

void PowerUp::move()
{
	X -= powerUpSpeed; //powerUps need speed variable?
}
