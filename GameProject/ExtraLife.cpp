#include <iostream>

#include "ExtraLife.h"

ExtraLife::ExtraLife(short X, short Y)
	:PowerUp(X, Y)
{
	this->height = extraLifeHeight;
	this->width = extraLifeWidth;
	copyImage((char *)extraLifeImage);

}
ExtraLife::ExtraLife(const ExtraLife& other)
	:PowerUp(other)
{}

ExtraLife& ExtraLife::operator=(const ExtraLife& other)
{
	if (this != &other)
	{
		PowerUp::operator=(other);
	}
	return *this;
}
ExtraLife::~ExtraLife()
{}


size_t ExtraLife::getType() const
{
	return 1;
}

void ExtraLife::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	if (blinking)
	{
		setColor(10);
		blinking = false;
	}
	else
	{
		setColor(2);
		blinking = true;
	}
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

void ExtraLife::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
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

void ExtraLife::save(std::ostream& out)
{
	size_t type = 1;
	out.write((const char *)&type, sizeof(type));
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
}