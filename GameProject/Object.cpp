#include <iostream>
#include <cstring>
#include "Object.h"

Object::Object(size_t width, size_t height, char * image)
	:X(0)
	,Y(0)
{
	this->width = width;
	this->height = height;
	copyImage(image);
}

Object::Object(short X, short Y)
	:width(0)
	,height(0)
	,image(nullptr)
{
	if (X < 0 || Y < 0)
		throw std::invalid_argument("negative coordinates!");
	this->X = X;
	this->Y = Y;
}

Object::Object(short X, short Y, size_t width, size_t height, char * image)
{
	if (X < 0 || Y < 0)
		throw std::invalid_argument("negative coordinates!");
	this->X = X;
	this->Y = Y;
	this->width = width;
	this->height = height;
	copyImage(image);
}

Object::Object(const Object& other)
{
	copy(other);
}

Object& Object::operator=(const Object& other)
{
	if (this != &other)
	{
		clean();
		copy(other);
	}
	return *this;
}

Object::~Object()
{
	clean();
}

short Object::getX() const
{
	return X;
}

short Object::getY() const
{
	return Y;
}

size_t Object::getWidth() const
{
	return width;
}

size_t Object::getHeight() const
{
	return height;
}

void Object::setX(short X)
{
	if (X < 0)
		throw std::invalid_argument("negative X coordinate!");
	this->X = X;
}

void Object::setY(short Y)
{
	if (Y < 0)
		throw std::invalid_argument("negative Y coordinate!");
	this->Y = Y;
}

char Object::operator[](short index) const
{
	if (index < 0 || index > strlen(image))
		throw std::invalid_argument("invalid index!");
	return image[index];
}

void Object::copyImage(const char * newImage)
{
	if (newImage != nullptr)
	{
		try {
			this->image = new char[height*width];
			
			for (size_t i = 0; i < height; i++)
			{
				for (size_t j = 0; j < width; j++)
				{
					this->image[i*width+ j] = newImage[i*width + j];
				}
			}
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!" << std::endl;
			throw;
		}
	}
	else
	{
		this->image = nullptr;
	}
}

void Object::copy(const Object& other)
{
	this->X = other.X;
	this->Y = other.Y;
	this->width = other.width;
	this->height = other.height;
	copyImage(other.image);
}

void Object::clean()
{
	delete[] image;
	image = nullptr;
}


