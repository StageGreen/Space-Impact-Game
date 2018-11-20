#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <random>
#include <time.h>

#include "Explosion.h"
#include "Player.h"
#include "BulletCollection.h"
#include "EnemyCollection.h"
#include "ExplosionCollection.h"
#include "PowerUpCollection.h"

const size_t CONSOLE_WIDTH = 120;
const size_t CONSOLE_HEIGHT = 30;

class Console
{
public:
	Console();//for loading game
	Console(size_t gameSpeed); //for new game
	~Console();
	
	//void drawObject(const Object& obj); //draw a rectangle-shaped image (and save it in the matrix)
	//void eraseObject(const Object& obj); //erase a rectangle-shaped image (and save it in the matrix)
	
	bool GameOver() const; //returns if player is dead
	size_t getPlayerScore() const;
	size_t getGameSpeed() const;

	void init(); //draw walls, empty spaces and player
	void gameLoop(); //loops while !GameOver and goes through all essential functions below(no init)
	void gameOver(); //GameOver screen
	void clearScreen(); //homemade system("cls")
	void readInput(); //read user input and moves player/player shoots
	void updatePlayer(); //draw player if he is blinking
	void playerDies(); //erase player, draw explosion
	void enemiesFire(); //go through enemies and roll the dice if they should fire or not
	void CollisionDetection(); //player-bullet, enemy-bullet, player-enemy
	void moveBullets(); //changes X coordinate of every bullet object
	void moveEnemies(); //decreases X coordinate of every enemy object
	void movePowerUps(); //decreases X coordiante of every powerup object
	void spawnEnemies(); //roll the dice and spawn enemies
	void spawnPowerUps(); //roll the dice and spawn powerups
	void updateExplosions(); //changes animation frames of every explosion

private:
	//functions
	void saveGame();
	bool objectsCollide(const Object& obj1,const Object& obj2) const;
	bool objectBulletCollide(const Object& obj,const Bullet& bullet) const; //same as above, but bullets get an enlarged X-axis-hitbox
	void playerBulletCollision();
	void enemyBulletCollision();
	void playerEnemyCollision();
	void playerPowerupCollision();
	void killAllEnemies(); //deletes all enemies and adds explosions
	void updateLives(); //print new number of lives
	void updateScore(); //print new score
	//variables
	const size_t width;
	const size_t height;
	char * Matrix;
	size_t gameSpeed;
	size_t playerScore;
	//size_t playerLevel;
	size_t currentEnemyLevel;
	//objects
	Player player;
	BulletCollection bullets;
	EnemyCollection enemies;
	PowerUpCollection powerups;
	ExplosionCollection explosions;
};

#endif
