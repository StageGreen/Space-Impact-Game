#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Object.h"

//////////Player Settings////////////
const size_t initialLives = 3;
const size_t playerHorizontalSpeed = 2;
const size_t playerVerticalSpeed = 1;
const size_t playerWidth = 3;
const size_t playerHeight = 3;
const char playerImage[playerHeight][playerWidth] = {
	{ '\\', '-',' ' },
	{ '=', 'X', '>' },
	{ '/', '-', ' ' }
};
const size_t playerBlinkingTime = 35;
/////////////////////////////////////

class Player : public Object
{
public:
	Player(); //for loading game
	Player(short X, short Y); //for new game
    virtual ~Player();
	
	//selectors
	size_t getLives() const;
	size_t getLevel() const;
	bool isBlinking() const;
	bool isHighlighted() const; //is green or yellow (for playerUpdate() )

	//mutators
	void takeDamage();
	void increaseLives();
	void setLives(size_t lives); //for loading game
	void resetLevel();
	void increaseLevel();
	void setLevel(size_t level); //for loading game
	void move(const char * direction);
	void colorGreen();
	void colorYellow();

	//base functions
	virtual void draw(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void erase(char * Matrix, size_t matrixWidth, size_t matrixHeight);
	virtual void save(std::ostream& out);
	void load(std::istream& in);

private:
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = delete;

	const size_t horizontalSpeed;
	const size_t verticalSpeed;
	size_t lives;
	size_t level;
	size_t blinking;
	size_t greenHighlight;
	size_t yellowHighlight;
};


#endif
