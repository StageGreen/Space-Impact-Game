#include <iostream>

#include "Dropship.h"

Dropship::Dropship(short X, short Y, size_t level)
	:Enemy(X, Y, level)
{
	this->width = dropshipWidth;
	this->height = dropshipHeight;
	copyImage((char *)dropshipImage);
	this->speed = dropshipSpeed;
}

Dropship::~Dropship()
{}


void Dropship::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	unsigned short defaultColor = 8; //doesn't change
	unsigned short levelColor; //changes with level
	switch (level)
	{
	case 1:
		levelColor = 15; //default game color
		defaultColor = 15;
		break;
	case 2:
		levelColor = 14; //yellow
		defaultColor = 8;
		break;
	case 3:
		levelColor = 12; //red
		defaultColor = 8;
		break;
	case 4:
		levelColor = 11; //cyan
		defaultColor = 8;
		break;
	}
	for (unsigned short i = 0; i < height; i++)     //Draw a rectangle with upper left corner
	{										  //(X, Y) and sidelenghts height and width
		for (unsigned short j = 0; j < width; j++)
		{
			if (X + j < 1 || Y + i < 2 || X + j > matrixWidth - 2 || Y + i > matrixHeight - 2)
				continue;

			gotoxy(X + j, Y + i);
			Matrix[(i + Y)*matrixWidth + X + j] = image[i * width + j];
			//determine color
			if (j == 3)
				setColor(defaultColor);
			else
				setColor(levelColor);
			//draw to screen
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
	setColor(15);
}

void Dropship::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	for (unsigned short i = 0; i < height; i++)     //Draw a rectangle of empty intervals with upper left corner
	{												//(X, Y) and sidelenghts height and width
		for (unsigned short j = 0; j < width; j++)
		{
			if (X + j < 1 || Y + i < 2 || X + j > matrixWidth - 2 || Y + i > matrixHeight - 2)
				continue;

			gotoxy(X + j, Y + i);
			Matrix[(i + Y)*matrixWidth + X + j] = ' ';
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
}

void Dropship::save(std::ostream& out)
{
	size_t type = 1;
	out.write((const char *)&type, sizeof(type));
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
	out.write((const char *)&level, sizeof(level));
	out.write((const char *)&health, sizeof(health));
}

size_t Dropship::getType() const
{
	return 1;
}
