#include <iostream>
#include "EnemyCollection.h"

const size_t initialCapacity = 4;

EnemyCollection::EnemyCollection()
	:capacity(initialCapacity)
	,size(0)
	,enemyArray(nullptr)
{
	try {
		enemyArray = new Enemy *[capacity];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

EnemyCollection::~EnemyCollection()
{
	clean();
}

Enemy * EnemyCollection::operator[](short index) const
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	return enemyArray[index];
}

void EnemyCollection::addEnemy(Enemy * newEnemy)
{
	if (size >= capacity)
		resize();
	enemyArray[size] = newEnemy;
	size++;
}

void EnemyCollection::removeEnemy(short index)
{
	if (index < 0)
		throw std::invalid_argument("negative index!");
	if (index > size - 1)
		throw std::invalid_argument("index is too large!");
	
	if (capacity / 3 > size)
		resize();
	enemyArray[index] = enemyArray[size - 1];
	size--;
}

void EnemyCollection::resize()
{
	if (size >= capacity)
		capacity *= 2;
	else
		capacity /= 2;
	try {
		Enemy ** newArray = new Enemy *[capacity];
		for (int i = 0; i < size; i++)
		{
			newArray[i] = this->enemyArray[i];
		}
		delete[] this->enemyArray;
		this->enemyArray = newArray;
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!" << std::endl;
		throw;
	}
}

size_t EnemyCollection::getSize() const
{
	return size;
}

void EnemyCollection::save(std::ostream& out)
{
	out.write((const char *)&size, sizeof(size)); //enemyCollection
	for (size_t i = 0; i < size; i++)
	{
		if (!out)
			throw ("Something went wrong with the stream!");
		enemyArray[i]->save(out);
	}
}

void EnemyCollection::load(std::istream& in)
{
	size_t loadedSize;
	size_t enemyType;
	short X;
	short Y;
	size_t level;
	size_t health;
	in.read((char *)&loadedSize, sizeof(loadedSize));
	for (size_t i = 0; i < loadedSize; i++)
	{
		if (!in)
			throw ("Something went wrong with the stream!");
		in.read((char *)&enemyType, sizeof(enemyType));
		in.read((char *)&X, sizeof(X));
		in.read((char *)&Y, sizeof(Y));
		in.read((char *)&level, sizeof(level));
		in.read((char *)&health, sizeof(health));
		try {
			if(enemyType == 1)
				addEnemy(new Dropship(X, Y, level));
			else if(enemyType == 2)
				addEnemy(new TieFighter(X, Y, level));
			enemyArray[size-1]->setHealth(health);
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!" << std::endl;
			throw;
		}
	}
}

void EnemyCollection::clean()
{
	for (int i = 0; i < size; i++)
		delete[] enemyArray[i];
	delete[] enemyArray;
	size = 0;
}
