#include <iostream>
#include "BulletCollection.h"

const size_t initialCapacity = 4;

BulletCollection::BulletCollection()
	:capacity(initialCapacity)
	,size(0)
	,bulletArray(nullptr)
{
	try {
		bulletArray = new Bullet *[capacity];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

BulletCollection::~BulletCollection()
{
	clean();
}

Bullet * BulletCollection::operator[](short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	return bulletArray[index];
}

void BulletCollection::addBullet(Bullet * newBullet)
{
	if(size >= capacity)
		resize();
	bulletArray[size] = newBullet;
	size++;

}

void BulletCollection::removeBullet(short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	if (capacity / 3 > size)
		resize();
	bulletArray[index] = bulletArray[size-1];
	size--;
}

void BulletCollection::resize()
{
	if (size >= capacity)
		capacity *= 2;
	else
		capacity /= 2;
	try {
		Bullet ** newArray = new Bullet *[capacity];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = this->bulletArray[i];
		}
		delete[] this->bulletArray;
		this->bulletArray = newArray;
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

size_t BulletCollection::getSize() const
{
	return size;
}

void BulletCollection::save(std::ostream& out)
{
	out.write((const char *)&size, sizeof(size)); //enemyCollection
	for (size_t i = 0; i < size; i++)
	{
		if (!out)
			throw ("Something went wrong with the stream!");
		bulletArray[i]->save(out);
	}
}

void BulletCollection::load(std::istream& in)
{
	size_t loadedSize;
	size_t type;
	short X;
	short Y;
	bool playerBullet;
	size_t direction;
	in.read((char *)&loadedSize, sizeof(loadedSize));
	for (size_t i = 0; i < loadedSize; i++)
	{
		if (!in)
			throw ("Something went wrong with the stream!");
		in.read((char *)&type, sizeof(type));
		in.read((char *)&X, sizeof(X));
		in.read((char *)&Y, sizeof(Y));
		in.read((char *)&playerBullet, sizeof(playerBullet));
		in.read((char *)&direction, sizeof(direction));
		try {
			if(type == 1)
				addBullet(new BasicBullet(X, Y, playerBullet, direction));
			else if(type == 2)
				addBullet(new AdvancedBullet(X, Y, playerBullet, direction));
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!" << std::endl;
			throw;
		}
	}
}

void BulletCollection::clean()
{
	for (int i = 0; i < size; i++)
		delete[] bulletArray[i];
	delete[] bulletArray;
	size = 0;
}