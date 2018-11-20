#include <iostream>

#include "GunUpgrade.h"

GunUpgrade::GunUpgrade(short X, short Y)
	:PowerUp(X, Y)
{
	this->height = gunUpgradeHeight;
	this->width = gunUpgradeWidth;
	copyImage((char *)gunUpgradeImage);

}
GunUpgrade::GunUpgrade(const GunUpgrade& other)
	:PowerUp(other)
{}

GunUpgrade& GunUpgrade::operator=(const GunUpgrade& other)
{
	if (this != &other)
	{
		PowerUp::operator=(other);
	}
	return *this;
}
GunUpgrade::~GunUpgrade()
{}


size_t GunUpgrade::getType() const
{
	return 2;
}

void GunUpgrade::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	/*
	if (blinking)
	{
		setColor(14);
		blinking = false;
	}
	else
	{
		setColor(6);
		blinking = true;
	}*/
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

void GunUpgrade::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
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

void GunUpgrade::save(std::ostream& out)
{
	size_t type = 2;
	out.write((const char *)&type, sizeof(type));
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
}