#ifndef DROPSHIP_H_INCLUDED
#define DROPSHIP_H_INCLUDED

#include "Enemy.h"

const size_t dropshipSpeed = 1;
const size_t dropshipWidth = 4;
const size_t dropshipHeight = 3;
const char dropshipImage[dropshipHeight][dropshipWidth] = {
	{ '=', '=', '=', '}' },
	{ ' ', ' ', ' ', '+' },
	{ '=', '=', '=', '}' }
};

class Dropship : public Enemy
{
public:
	Dropship(short X, short Y, size_t level);
	virtual ~Dropship();


	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

	virtual size_t getType() const;

private:
};

#endif
