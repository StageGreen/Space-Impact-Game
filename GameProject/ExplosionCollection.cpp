#include <iostream>
#include "ExplosionCollection.h"

const size_t initialCapacity = 4;

ExplosionCollection::ExplosionCollection()
	:capacity(initialCapacity)
	, size(0)
	, explosionArray(nullptr)
{
	try {
		explosionArray = new Explosion *[capacity];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

ExplosionCollection::~ExplosionCollection()
{
	clean();
}

Explosion * ExplosionCollection::operator[](short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	return explosionArray[index];
}

void ExplosionCollection::addExplosion(Explosion * newExplosion)
{
	if (size >= capacity)
		resize();
	explosionArray[size] = newExplosion;
	size++;

}

void ExplosionCollection::removeExplosion(short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	if (capacity / 3 > size)
		resize();
	explosionArray[index] = explosionArray[size - 1];
	size--;
}

void ExplosionCollection::resize()
{
	if (size >= capacity)
		capacity *= 2;
	else
		capacity /= 2;
	try {
		Explosion ** newArray = new Explosion *[capacity];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = this->explosionArray[i];
		}
		delete[] this->explosionArray;
		this->explosionArray = newArray;
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

size_t ExplosionCollection::getSize() const
{
	return size;
}

void ExplosionCollection::save(std::ostream& out)
{
	out.write((const char *)&size, sizeof(size)); //enemyCollection
	for (size_t i = 0; i < size; i++)
	{
		if (!out)
			throw ("Something went wrong with the stream!");
		explosionArray[i]->save(out);
	}
}

void ExplosionCollection::load(std::istream& in)
{
	size_t loadedSize;
	short X;
	short Y;
	in.read((char *)&loadedSize, sizeof(loadedSize));
	for (size_t i = 0; i < loadedSize; i++)
	{
		if (!in)
			throw ("Something went wrong with the stream!");
		in.read((char *)&X, sizeof(X));
		in.read((char *)&Y, sizeof(Y));
		try {
			addExplosion(new Explosion(X, Y));
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!" << std::endl;
			throw;
		}
	}
}

void ExplosionCollection::clean()
{
	for (int i = 0; i < size; i++)
		delete[] explosionArray[i];
	delete[] explosionArray;
	size = 0;
}