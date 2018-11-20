#ifndef ADVANCEDBULLET_H_INCLUDED
#define ADVANCEDBULLET_H_INCLUDED
//identical to the basicBullet but different image and damage

#include "Bullet.h"

//////////////Advanced Bullet Settings/////////////////
const size_t advancedBulletDamage = 3;
const size_t advancedBulletWidth = 1;
const size_t advancedBulletHeight = 1;
const char advancedBulletImage[advancedBulletHeight][advancedBulletWidth] = {
	{ 'o' }
};
///////////////////////////////////////////////////

class AdvancedBullet : public Bullet
{
public:
	AdvancedBullet(short X, short Y, const char * owner, short direction = 0);
	AdvancedBullet(short X, short Y, bool isPlayerBullet, short direction = 0);
	virtual ~AdvancedBullet();

	virtual void move();
	virtual size_t getType() const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

private:



};

#endif

