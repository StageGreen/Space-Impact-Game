#include <iostream>

#include "Enemy.h"

Enemy::Enemy(short X, short Y, size_t level)
	:Object(X, Y)
	,speed(1)
{
	/*
	this->type = type;
	if (this->type == 1)
	{
		this->width = enemy1Width;
		this->height = enemy1Height;
		copyImage((char *)enemy1Image);
	}
	else if (this->type == 2)
	{
		this->width = enemy2Width;
		this->height = enemy2Height;
		copyImage((char *)enemy2Image);
	}
	else
		throw("unexisting enemy type!");
	*/
	switch (level)
	{
	case 1:
		this->health = 1;
		break;
	case 2:
		this->health = 3;
		break;
	case 3:
		this->health = 5;
		break;
	case 4:
		this->health = 10;
		break;
	default:
		throw std::invalid_argument("Level too high!");
		break;
	}
	this->level = level;
}

Enemy::Enemy(const Enemy& other)
	:Object(other)
{
	copy(other);
}

Enemy& Enemy::operator=(const Enemy& other)
{
	if (this != &other)
	{
		Object::operator=(other);
		copy(other);
	}
	return *this;
}

Enemy::~Enemy()
{}

size_t Enemy::getHealth() const
{
	return health;
}

size_t Enemy::getLevel() const
{
	return level;
}

void Enemy::takeDamage(size_t damage)
{
	if (health >= damage)
		health -= damage;
	else
		health = 0;
}

void Enemy::setHealth(size_t health)
{
	if (health > 100)
		throw std::invalid_argument("Health too high!");
	this->health = health;
}

void Enemy::move()
{	
	X -= speed;
}

void Enemy::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	switch (level)
	{
	case 1:
		break; //default game color
	case 2:
		setColor(14); //yellow
		break;
	case 3:
		setColor(9); //blue
		break;
	case 4:
		setColor(5); //purple
		break;
	}
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

void Enemy::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
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

void Enemy::save(std::ostream& out)
{
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
	out.write((const char *)&speed, sizeof(speed));
	out.write((const char *)&level, sizeof(level));
	out.write((const char *)&health, sizeof(health));
	//out.write((const char *)&type, sizeof(type));
}

void Enemy::copy(const Enemy& other)
{
	this->speed = other.speed;
	this->level = other.level;
	this->health = other.health;
}
