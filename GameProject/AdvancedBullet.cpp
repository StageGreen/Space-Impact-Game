#include <iostream>

#include "AdvancedBullet.h"

AdvancedBullet::AdvancedBullet(short X, short Y, const char * owner, short direction)
	:Bullet(X, Y, owner)
{
	this->width = advancedBulletWidth;
	this->height = advancedBulletHeight;
	copyImage((char *)advancedBulletImage);
	this->damage = advancedBulletDamage;
	this->direction = direction;
}

AdvancedBullet::AdvancedBullet(short X, short Y, bool isPlayerBullet, short direction)
	:Bullet(X, Y, isPlayerBullet)
{
	this->width = advancedBulletWidth;
	this->height = advancedBulletHeight;
	copyImage((char *)advancedBulletImage);
	this->damage = advancedBulletDamage;
	this->direction = direction;
}

AdvancedBullet::~AdvancedBullet()
{}

void AdvancedBullet::move()
{
	if (isPlayerBullet)
	{
		X += speed;
		Y += direction;
	}
	else
		X -= speed;
}

size_t AdvancedBullet::getType() const
{
	return 2;
}

void AdvancedBullet::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	if (!isPlayerBullet)
		setColor(14);
	for (short i = 0; i < height; i++)     //Draw a rectangle with upper left corner
	{										  //(X, Y) and sidelenghts height and width
		for (short j = 0; j < width; j++)
		{
			if (X + j < 1 || Y + i < 2 || X + j > matrixWidth - 2 || Y + i > matrixHeight - 2)
				continue;

			gotoxy(X + j, Y + i);
			Matrix[(i + Y)*matrixWidth + X + j] = image[i * width + j];
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
	setColor(15);
}

void AdvancedBullet::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	for (size_t i = 0; i < height; i++)     //Draw a rectangle of empty intervals with upper left corner
	{										   //(X, Y) and sidelenghts height and width
		for (size_t j = 0; j < width; j++)
		{
			if (X + j < 1 || Y + i < 2 || X + j > matrixWidth - 2 || Y + i > matrixHeight - 2)
				continue;

			gotoxy(X + j, Y + i);
			Matrix[(i + Y)*matrixWidth + X + j] = ' ';
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
}

void AdvancedBullet::save(std::ostream& out)
{
	size_t type = 2;
	out.write((const char *)&type, sizeof(type));
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
	out.write((const char *)&isPlayerBullet, sizeof(isPlayerBullet));
	out.write((const char *)&direction, sizeof(direction));
}