#ifndef BASICBULLET_H_INCLUDED
#define BASICBULLET_H_INCLUDED

#include "Bullet.h"

//////////////Basic Bullet Settings/////////////////
const size_t basicBulletDamage = 1;
const size_t basicBulletWidth = 1;
const size_t basicBulletHeight = 1;
const char basicBulletImage[basicBulletHeight][basicBulletWidth] = {
	{ '-' }
};
///////////////////////////////////////////////////

class BasicBullet : public Bullet
{
public:
	BasicBullet(short X, short Y, const char * owner, short direction = 0);
	BasicBullet(short X, short Y, bool isPlayerBullet, short direction = 0);
	virtual ~BasicBullet();

	virtual void move();
	virtual size_t getType() const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

private:



};

#endif
