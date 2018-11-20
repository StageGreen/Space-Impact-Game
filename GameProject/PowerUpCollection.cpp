#include <iostream>
#include "PowerUpCollection.h"

const size_t initialCapacity = 4;

PowerUpCollection::PowerUpCollection()
	:capacity(initialCapacity)
	, size(0)
	, powerUpArray(nullptr)
{
	try {
		powerUpArray = new PowerUp *[capacity];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

PowerUpCollection::~PowerUpCollection()
{
	clean();
}

PowerUp * PowerUpCollection::operator[](short index) const
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	return powerUpArray[index];
}

void PowerUpCollection::addPowerUp(PowerUp * newPowerUp)
{
	if (size >= capacity)
		resize();
	powerUpArray[size] = newPowerUp;
	size++;
}

void PowerUpCollection::removePowerUp(short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");

	if (capacity / 3 > size)
		resize();
	powerUpArray[index] = powerUpArray[size - 1];
	size--;
}

void PowerUpCollection::resize()
{
	if (size >= capacity)
		capacity *= 2;
	else
		capacity /= 2;
	try {
		PowerUp ** newArray = new PowerUp *[capacity];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = this->powerUpArray[i];
		}
		delete[] this->powerUpArray;
		this->powerUpArray = newArray;
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

size_t PowerUpCollection::getSize() const
{
	return size;
}

void PowerUpCollection::save(std::ostream& out)
{
	out.write((const char *)&size, sizeof(size)); //PowerUpCollection
	for (size_t i = 0; i < size; i++)
	{
		if (!out)
			throw ("Something went wrong with the stream!");
		powerUpArray[i]->save(out);
	}
}

void PowerUpCollection::load(std::istream& in)
{
	size_t loadedSize;
	size_t PowerUpType;
	short X;
	short Y;
	in.read((char *)&loadedSize, sizeof(loadedSize));
	for (size_t i = 0; i < loadedSize; i++)
	{
		if (!in)
			throw ("Something went wrong with the stream!");
		in.read((char *)&PowerUpType, sizeof(PowerUpType));
		in.read((char *)&X, sizeof(X));
		in.read((char *)&Y, sizeof(Y));
		try {
			if (PowerUpType == 1)
				addPowerUp(new ExtraLife(X, Y));
			else if (PowerUpType == 2)
				addPowerUp(new GunUpgrade(X, Y));

		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!" << std::endl;
			throw;
		}
	}
}

void PowerUpCollection::clean()
{
	for (int i = 0; i < size; i++)
		delete[] powerUpArray[i];
	delete[] powerUpArray;
	size = 0;
}
