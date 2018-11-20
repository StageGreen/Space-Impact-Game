#include <iostream>

#include "Explosion.h"

Explosion::Explosion(short X, short Y)
	:Object(X, Y)
{
	this->width = ExplosionWidth;
	this->height = ExplosionHeight;
	copyImage((char *)ExplosionImage1);
	this->stage = 1;
	this->gameTicks = 0;
}

Explosion::Explosion(const Explosion& other)
	:Object(other)
{
	this->stage = other.stage;
	this->gameTicks = other.gameTicks;
}

Explosion& Explosion::operator=(const Explosion& other)
{
	if (this != &other)
	{
		Object::operator=(other);
		this->stage = other.stage;
		this->gameTicks = other.gameTicks;
	}
	return *this;
}
Explosion::~Explosion()
{}

void Explosion::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	setColor(12);
	for (size_t i = 0; i < height; i++)     //Draw a rectangle with upper left corner
	{										   //(X, Y) and sidelenghts height and width
		for (size_t j = 0; j < width; j++)
		{
			if (X + j < 1 || Y + i < 2 || X + j > matrixWidth - 2 || Y + i > matrixHeight - 2)
				continue;
			if (stage == 1) //colors for first frame of animation
			{
				if (i == 2 && j == 3) //center of explosion is white
					setColor(15);
				else if ((i - 2)*(i - 2) + (j - 3)*(j - 3) <= 1) //yellow circle around the center
					setColor(14);
				else
					setColor(12);
				
			}
			else if (stage == 2) //colors for second frame
			{
				if(i == 2 && j == 3)
					setColor(14);
				else
					setColor(12);
			}
			gotoxy(X + j, Y + i);
			/*if (image[i * width + j] == '@')
			{
				Matrix[(i + Y)*matrixWidth + X + j] = char(178);
			}
			else*/
				Matrix[(i + Y)*matrixWidth + X + j] = image[i * width + j];
			
			std::cout << Matrix[(i + Y)*matrixWidth + X + j] << std::endl;
		}
	}
	setColor(15);
}

void Explosion::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
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

void Explosion::save(std::ostream& out)
{
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
}

void Explosion::update(size_t gameSpeed)
{
    if (stage < 4)
	{
		gameTicks++;

		if (gameSpeed < 50)
			stage++;
		else if (gameSpeed < 60)
		{
			if (gameTicks % 2 == 0)
				stage++;
		}
		else
		{
			if (gameTicks % 3 == 0)
				stage++;
		}
		
		switch (stage)
		{
		case 1:
			break;
		case 2:
			copyImage((char *)ExplosionImage2);
			break;
		case 3:
			copyImage((char *)ExplosionImage3);
			break;
		case 4:
			break;
		default:
			throw "something went wrong";
		}
	}
}

size_t Explosion::getStage() const
{
	return stage;
}
