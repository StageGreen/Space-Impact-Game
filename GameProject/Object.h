#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "helperFunctions.h"

class Object
{
public:
	Object(size_t width, size_t height, char * image); //used by player, when loading game
	Object(short X, short Y); //used when creating enemy, since the width, heigth and image can be different   
	Object(short X, short Y, size_t width, size_t height, char * image); //used by player, bullet
	Object(const Object& other);
	Object& operator=(const Object& other);
	virtual ~Object();

	short getX() const;
	short getY() const;
	size_t getWidth() const;
	size_t getHeight() const;

	void setX(short X);
	void setY(short Y);

	char operator[](short index) const;

	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight) = 0;
	virtual void save(std::ostream& out) = 0;

protected:
	void copy(const Object& other);
	void copyImage(const char * newImage);
	void clean();

	short X;
	short Y;
	size_t width;
	size_t height;
	char * image;
};

#endif
