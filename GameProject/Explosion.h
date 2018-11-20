#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Object.h"

static const size_t ExplosionWidth = 7;
static const size_t ExplosionHeight = 5;
static const char ExplosionImage1[ExplosionHeight][ExplosionWidth] = {
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ' },
	{ ' ', ' ', '@', '@', '@', ' ', ' ' },
	{ '@', '@', '@', '@', '@', '@', '@' },
	{ ' ', ' ', '@', '@', '@', ' ', ' ' },
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ' },
};
static const char ExplosionImage2[ExplosionHeight][ExplosionWidth] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ' },
	{ ' ', '@', '@', '@', '@', '@', ' ' },
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
};

static const char ExplosionImage3[ExplosionHeight][ExplosionWidth] = {
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', '@', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
};


class Explosion : public Object
{
public:
	Explosion(short X, short Y);
	Explosion(const Explosion& other);
	Explosion& operator=(const Explosion& other);
	virtual ~Explosion();

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);
	//void load(std::istream& in);

	void update(size_t gameSpeed);
	size_t getStage() const;

private:
	size_t stage;
	size_t gameTicks;
};




#endif