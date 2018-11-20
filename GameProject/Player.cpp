#include <iostream>
#include <cstring>

#include "Player.h"

Player::Player()
	:Object(playerWidth, playerHeight, (char *)playerImage)
	,lives(initialLives)
	,level(1)
	,horizontalSpeed(playerHorizontalSpeed)
	,verticalSpeed(playerVerticalSpeed)
	,blinking(0)
	,greenHighlight(0)
	,yellowHighlight(0)
{}

Player::Player(short X, short Y)
	:Object(X, Y, playerWidth, playerHeight, (char *)playerImage)
	,lives(initialLives)
	,level(1)
	,horizontalSpeed(playerHorizontalSpeed)
	,verticalSpeed(playerVerticalSpeed)
	,blinking(0)
	,greenHighlight(0)
	,yellowHighlight(0)
{}

Player::~Player()
{}

size_t Player::getLives() const
{
	return lives;
}

size_t Player::getLevel() const
{
	return level;
}

bool Player::isBlinking() const
{
	return blinking;
}

bool Player::isHighlighted() const
{
	return greenHighlight || yellowHighlight;
}

void Player::takeDamage()
{
	if (lives > 0)
		if (!blinking)
		{
			lives--;
			blinking = playerBlinkingTime;
		}
}

void Player::increaseLives()
{
	lives++;
}

void Player::setLives(size_t lives)
{
	if (lives > 100)
		throw std::invalid_argument("too many lives!");
	this->lives = lives;
}

void Player::resetLevel()
{
	level = 1;
}

void Player::increaseLevel()
{
	if(level < 4)
		level++;
}

void Player::setLevel(size_t level)
{
	if(level > 4)
		throw std::invalid_argument("level too high!");
	this->level = level;
}

void Player::move(const char * direction)
{
	if (strcmp(direction, "up") == 0)
	{
		Y -= verticalSpeed;
		if (Y < 0)
			Y = 0;
	}
	else if (strcmp(direction, "down") == 0)
		Y += verticalSpeed;
	else if (strcmp(direction, "left") == 0)
	{
		X -= horizontalSpeed;
		if (X < 0)
			X = 0;
	}
	else if (strcmp(direction, "right") == 0)
		X += horizontalSpeed;
}

void Player::colorGreen()
{
	greenHighlight = 10;
}

void Player::colorYellow()
{
	yellowHighlight = 10;
}


void Player::draw(char * Matrix, size_t matrixWidth, size_t matrixHeight)
{
	if(blinking)
	{
		if (blinking > 0)
			blinking--;
		if (blinking % 3 != 0)
			return;
	}
	if (greenHighlight) 
	{
		setColor(10);
		greenHighlight--;
	}
	else if (yellowHighlight)
	{
		setColor(14);
		yellowHighlight--;
	}
	for (unsigned short i = 0; i < height; i++)     //Draw a rectangle with upper left corner
	{												//(X, Y) and sidelenghts height and width
		for (unsigned short j = 0; j < width; j++)
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

void Player::erase(char * Matrix, size_t matrixWidth, size_t matrixHeight)
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

void Player::save(std::ostream& out)
{
	if (!out)
		throw ("Something went wrong with the stream!");
	out.write((const char *)&lives, sizeof(lives));
	out.write((const char *)&level, sizeof(level));
	out.write((const char *)&X, sizeof(X));
	out.write((const char *)&Y, sizeof(Y));
}

void Player::load(std::istream& in)
{
	if (!in)
		throw ("Something went wrong with the stream!");
	in.read((char *)&lives, sizeof(lives));
	in.read((char *)&level, sizeof(level));
	in.read((char *)&X, sizeof(X));
	in.read((char *)&Y, sizeof(Y));
}