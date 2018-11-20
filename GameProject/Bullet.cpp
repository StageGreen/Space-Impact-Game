#include <iostream>
#include <cstring>
#include "Bullet.h"

Bullet::Bullet(short X, short Y, const char * owner)
	:Object(X, Y)
	,speed(bulletSpeed)
{
	if (strcmp(owner, "player") == 0)
		this->isPlayerBullet = true;
	else if (strcmp(owner, "enemy") == 0)
		this->isPlayerBullet = false;
	else
		throw std::invalid_argument("invalid bullet owner!");
}

Bullet::Bullet(short X, short Y, bool isPlayerBullet)
	:Object(X, Y)
	,speed(bulletSpeed)
{
	this->isPlayerBullet = isPlayerBullet;
	/*
	if (type == 1)
		this->damage = 1;
	else if (type == 2)
		this->damage = 3;
	this->type = type;
	*/
}

Bullet::Bullet(const Bullet& other)
	:Object(other)
	,speed(bulletSpeed)
{
	copy(other);
}

Bullet& Bullet::operator=(const Bullet& other)
{
	if (this != &other)
	{
		Object::operator=(other);
		copy(other);
	}
	return *this;
}
Bullet::~Bullet()
{}

size_t Bullet::getDamage() const
{
	return damage;
}

size_t Bullet::getSpeed() const
{
	return speed;
}

bool Bullet::getIsPlayerBullet() const
{
	return isPlayerBullet;
}

void Bullet::copy(const Bullet& other)
{
	this->isPlayerBullet = other.isPlayerBullet;
	this->damage = other.damage;
	this->direction = other.direction;
}

void Bullet::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	for (short i = 0; i < height; i++)     //Draw a rectangle with upper left corner
	{										  //(X, Y) and sidelenghts height and width
		for (short j = 0; j < width; j++)
		{
			gotoxy(X + j, Y + i);
			Matrix[(i + Y)*matrixWidth + X + j] = image[i * width + j];
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
	setColor(15);
}

void Bullet::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	for (size_t i = 0; i < height; i++)     //Draw a rectangle of empty intervals with upper left corner
	{										   //(X, Y) and sidelenghts height and width
		for (size_t j = 0; j < width; j++)
		{
			gotoxy(X + j, Y + i); 
			Matrix[(i + Y)*matrixWidth + X + j] = ' ';
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
}

void Bullet::save(std::ostream& out)
{
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
	out.write((const char *)&isPlayerBullet, sizeof(isPlayerBullet));
}