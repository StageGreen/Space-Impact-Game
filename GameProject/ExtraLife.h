#ifndef EXTRALIFE_H_INCLUDED
#define EXTRALIFE_H_INCLUDED

#include "PowerUp.h"

const size_t extraLifeWidth = 3;
const size_t extraLifeHeight = 1;
const char extraLifeImage[extraLifeHeight][extraLifeWidth] = {
	{ '{', '+', '}' }
};

class ExtraLife : public PowerUp
{
public:
	ExtraLife(short X, short Y);
	ExtraLife(const ExtraLife& other);
	ExtraLife& operator=(const ExtraLife& other);
	virtual ~ExtraLife();

	virtual size_t getType() const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

private:

};

#endif