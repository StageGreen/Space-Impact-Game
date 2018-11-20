#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Object.h"

//////////////////Bullet Settings///////////////////
const size_t bulletSpeed = 3;
const size_t verticalBulletSpeed = 1;
const size_t bulletWidth = 1;
const size_t bulletHeight = 1;
const char bulletImage[bulletHeight][bulletWidth] = {
	{ '-' }
};

////////////////////////////////////////////////////

class Bullet : public Object
{
public:
	Bullet(short X, short Y, const char * owner);
	Bullet(short X, short Y, bool isPlayerBullet); //less pretty constructor for game loading
	Bullet(const Bullet& other);
	Bullet& operator=(const Bullet& other);
	virtual ~Bullet();

	size_t getDamage() const;
	size_t getSpeed() const;
	bool getIsPlayerBullet() const;
	virtual size_t getType() const = 0;

	virtual void move() = 0;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void save(std::ostream& out) = 0;

protected:
	void copy(const Bullet& other);

	bool isPlayerBullet;
    size_t damage;
	size_t speed;
	short direction; //0 forward; -1 up; 1 down
};

#endif
