#ifndef EXPLOSIONCOLLECTION_H_INCLUDED
#define EXPLOSIONCOLLECTION_H_INCLUDED

#include "Explosion.h"

class ExplosionCollection
{
public:
	ExplosionCollection();
	~ExplosionCollection();

	Explosion * operator[](short index);

	void addExplosion(Explosion * newExplosion);
	void removeExplosion(short index);
	size_t getSize() const;

	void save(std::ostream& out);
	void load(std::istream& in);

private:
	ExplosionCollection(const ExplosionCollection& other) = delete;
	ExplosionCollection& operator=(const ExplosionCollection& other) = delete;

	void resize();
	void clean();

	size_t size;
	size_t capacity;
	Explosion ** explosionArray;
};

#endif
