#ifndef BULLETCOLLECTION_H_INCLUDED
#define BULLETCOLLECTION_H_INCLUDED

#include "Bullet.h"

#include "BasicBullet.h"
#include "AdvancedBullet.h"

class BulletCollection
{
public:
	BulletCollection();
	~BulletCollection();

	Bullet * operator[](short index);

	void addBullet(Bullet * newBullet);
	void removeBullet(short index);
	size_t getSize() const;

	void save(std::ostream& out);
	void load(std::istream& in);

private:
	BulletCollection(const BulletCollection& other) = delete;
	BulletCollection& operator=(const BulletCollection& other) = delete;

	void resize();
	void clean();

	size_t size;
	size_t capacity;
	Bullet ** bulletArray;
};

#endif
