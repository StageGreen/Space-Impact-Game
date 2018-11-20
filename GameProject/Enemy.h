#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "Object.h"

//////////////////Enemy Settings///////////////////



////////////////////////////////////////////////////

class Enemy : public Object
{
public:
	Enemy(short X, short Y, size_t level);
	Enemy(const Enemy& other);
	Enemy& operator=(const Enemy& other);
	virtual ~Enemy();

	virtual size_t getType() const = 0;
	size_t getHealth() const;
	size_t getLevel() const;

	void setHealth(size_t health);
	void takeDamage(size_t damage);
	void move();

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void save(std::ostream& out) = 0;

protected:
	void copy(const Enemy& other);

	size_t speed;
	size_t health;
	size_t level;
};

#endif