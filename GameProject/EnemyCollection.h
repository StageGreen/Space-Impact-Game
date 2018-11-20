#ifndef ENEMYCOLLECTION_H_INCLUDED
#define ENEMYCOLLECTION_H_INCLUDED

#include "Enemy.h"

#include "Dropship.h"
#include "TieFighter.h"

class EnemyCollection
{
public:
	EnemyCollection();
	~EnemyCollection();

	Enemy * operator[](short index) const;

	void addEnemy(Enemy * newEnemy);
	void removeEnemy(short index);
	size_t getSize() const;

	void save(std::ostream& out);
	void load(std::istream& in);

private:
	EnemyCollection(const EnemyCollection& other) = delete;
	EnemyCollection& operator=(const EnemyCollection& other) = delete;

	void resize();
	void clean();

	size_t size;
	size_t capacity;
	Enemy ** enemyArray;
};

#endif