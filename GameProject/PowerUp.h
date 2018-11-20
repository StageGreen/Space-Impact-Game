#ifndef POWERUP_H_INCLUDED
#define POWERUP_H_INCLUDED

#include "Object.h"

const size_t powerUpSpeed = 2;

class PowerUp : public Object
{
public:
	PowerUp(short X, short Y);
	PowerUp(const PowerUp& other);
	PowerUp& operator=(const PowerUp& other);
	virtual ~PowerUp();

	virtual size_t getType() const = 0;

	virtual void move();

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void save(std::ostream& out) = 0;

protected:
	bool blinking;

};

#endif
