#ifndef NUKE_H_INCLUDED
#define NUKE_H_INCLUDED

#include "PowerUp.h"

const size_t nukeWidth = 7;
const size_t nukeHeight = 1;
const char nukeImage[nukeHeight][nukeWidth] = {
	{ '(', 'N', 'U', 'K', 'E', ')', 'X' }
};

class Nuke : public PowerUp
{
public:
	Nuke(short X, short Y);
	Nuke(const Nuke& other);
	Nuke& operator=(const Nuke& other);
	virtual ~Nuke();

	virtual size_t getType() const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

private:

};

#endif
