#ifndef TIEFIGHTER_H_INCLUDED
#define TIEFIGHTER_H_INCLUDED

#include "Enemy.h"

const size_t tieFighterSpeed = 1;
const size_t tieFighterWidth = 5;
const size_t tieFighterHeight = 3;
const char tieFighterImage[tieFighterHeight][tieFighterWidth] = {
	{ '/', ' ', ' ', ' ', '\\' },
	{ '|', '=', 'X', '=', '|'  },
	{ '\\', ' ', ' ', ' ', '/' }
};

class TieFighter : public Enemy
{
public:
	TieFighter(short X, short Y, size_t level);
	virtual ~TieFighter();


	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);

	virtual size_t getType() const;

private:


};

#endif

