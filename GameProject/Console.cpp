#include <iostream>
#include <windows.h>
#include <chrono>
#include <fstream>


#include "helperFunctions.h"
#include "Console.h"

using std::cout;
using std::endl;
using std::ios;

const char * fileName = "Save.dat";

Console::Console() //load game constructor
	:width(CONSOLE_WIDTH)
	,height(CONSOLE_HEIGHT)
{
	std::ifstream in(fileName, ios::binary);
	if (!in)
		throw std::runtime_error("Save.dat not found!");
	
	in.read((char *)&gameSpeed, sizeof(gameSpeed));
	in.read((char *)&playerScore, sizeof(playerScore));
	in.read((char *)&currentEnemyLevel, sizeof(currentEnemyLevel));
	player.load(in);
	enemies.load(in);
	bullets.load(in);
	powerups.load(in);
	explosions.load(in);
	if (!in)
		throw ("Something went wrong with the stream!");
	
	in.close();
	//loading data from file is done
	
	try {
		Matrix = new char[height*width];
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!";
		throw;
	}
}

Console::Console(size_t gameSpeed) //new game constructor
	:width(CONSOLE_WIDTH)
	, height(CONSOLE_HEIGHT)
	, player(10, CONSOLE_HEIGHT / 2) //player starting position
	, playerScore(0)
	, currentEnemyLevel(1)
{
	try {
		Matrix = new char[height*width];	
	}
	catch (const std::bad_alloc&)
	{
		std::cerr << "Couldn't allocate memory!";
		throw;
	}
	this->gameSpeed = gameSpeed;
}

Console::~Console()
{
	delete[] Matrix;
	Matrix = nullptr;
}



bool Console::GameOver() const
{
	if (player.getLives() == 0 && explosions.getSize() == 0)
		return true;
	return false;
}

size_t Console::getPlayerScore() const
{
	return playerScore;
}

size_t Console::getGameSpeed() const
{
	return gameSpeed;
}

void Console::updateLives()
{
	gotoxy(strlen("Lives: "), 0);
	cout << player.getLives() << endl;
}

void Console::updateScore()
{
	gotoxy((width / 3) * 2 + strlen("Score: "), 0);
	cout << playerScore << endl;
}

void Console::saveGame()
{
	std::ofstream out(fileName, ios::binary | ios::trunc);
	if (!out)
		throw "Couldn't open file!";
	out.write((const char *)&gameSpeed, sizeof(gameSpeed));
	out.write((const char *)&playerScore, sizeof(playerScore));
	out.write((const char *)&currentEnemyLevel, sizeof(currentEnemyLevel));
	player.save(out);
	enemies.save(out);
	bullets.save(out);
	powerups.save(out);
	explosions.save(out);
	if (!out)
		throw ("Something went wrong with the stream!");
	out.close();

	gotoxy(1, 2);
	cout << "GAME SAVED" << endl;
	Sleep(250);
	gotoxy(1, 2);
	cout << "          " << endl;
}

void Console::init()
{
	hideCursor();
	gotoxy(0, 0);
	cout << "                             "; //deleting the "select difficulty" text
	gotoxy(0, 0);
	cout << "Lives: " << player.getLives() << endl; 
	gotoxy((width / 3) * 2, 0);
	cout << "Score: " << playerScore << endl;
	for (short i = 1; i < height; i++) 
	{
		for (short j = 0; j < width; j++)
		{
			gotoxy(j, i);
			if (i == 1 || j == 0 || i == height - 1 || j == width - 1) 
			{
				Matrix[i*width + j] = char(219); //wall 
				cout << Matrix[i*width + j] << endl;
			}
			else
			{
				Matrix[i*width + j] = ' '; //empty space
				cout << Matrix[i*width + j] << endl;
			}
		}
	}
	player.draw(Matrix, width, height);
	gotoxy(0, 0); //else the user has to scroll up
}

void Console::gameLoop()
{
	while (!GameOver())
	{
		auto start_s = std::chrono::steady_clock::now();
		updateExplosions(); //explosions need to be in the background, since they are only decoration
		readInput();
		updatePlayer();
		enemiesFire();
		CollisionDetection();
		moveBullets();
		moveEnemies();
		movePowerUps();
		spawnEnemies();
		spawnPowerUps();
		//handle lag
		auto stop_s = std::chrono::steady_clock::now();
		auto calcTime = std::chrono::duration <double, std::milli>(stop_s - start_s).count();
		Sleep(max(3500.0/gameSpeed - calcTime, 0));
	}
	clearScreen();
	gameOver();
}

void Console::gameOver()
{
	setColor(12);
	cout << "  _____                       ____" << endl;
	cout << " / ____|                     / __ \\" << endl;
	cout << "| |  __  __ _ _ __ ___   ___| |  | |_   _____ _ __" << endl;
	cout << "| | |_ |/ _` | '_ ` _ \\ / _ \\ |  | \\ \\ / / _ \\ '__|" << endl;
	cout << "| |__| | (_| | | | | | |  __/ |__| |\\ V /  __/ |" << endl;
	cout << " \\_____|\\__,_|_| |_| |_|\\___|\\____/  \\_/ \\___|_|" << endl;
	cout << endl;
	setColor(15);
	cout << "                   Your score: " << playerScore << endl;
}


/*
void Console::drawObject(const Object& obj)
{
	size_t objHeight = obj.getHeight();
	size_t objWidth = obj.getWidth();
	for (short i = 0; i < objHeight; i++)     //Draw a rectangle with upper left corner
	{										  //(obj.X, obj.Y) and sidelenghts obj.height and obj.width
		for (short j = 0; j < objWidth; j++)
		{
			gotoxy(obj.getX() + j, obj.getY() + i);
			Matrix[(i + obj.getY())*width + obj.getX() + j] = obj[i * obj.getWidth() + j];
			cout << Matrix[(i + obj.getY())*width + obj.getX() + j];
		}
	}
}

void Console::eraseObject(const Object& obj)
{
	size_t objHeight = obj.getHeight();
	size_t objWidth = obj.getWidth();
	for (size_t i = 0; i < objHeight; i++)     //Draw a rectangle of empty intervals with upper left corner
	{										   //(obj.X, obj.Y) and sidelenghts obj.height and obj.width
		for (size_t j = 0; j < objWidth; j++)
		{
			gotoxy(obj.getX() + j, obj.getY() + i);
			Matrix[(i + obj.getY())*width + obj.getX() + j] = ' ';
			cout << Matrix[(i + obj.getY())*width + obj.getX() + j];
		}
	}
}
*/
void Console::clearScreen()
{
	gotoxy(0, 0);
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			gotoxy(j, i);
			cout << ' ' << endl;
		}
	}
	gotoxy(0, 0);
}

void Console::readInput()
{
	if (player.getLives() == 0)
		return;
	if (GetAsyncKeyState(VK_UP))
	{
		player.erase(Matrix, width, height);   //delete current image of player
		player.move("up");	   //reduce Y
		if (player.getY() < 2) //if playerY goes beyond the wall 
			player.setY(2);    //set playerY under the wall
		
		player.draw(Matrix, width, height);      //draw player with the new Y
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		player.erase(Matrix, width, height);   //same logic as above
		player.move("down");	   
		if (player.getY() + player.getHeight() > height-2)  
			player.setY(height - player.getHeight() - 1);    

		player.draw(Matrix, width, height);
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		player.erase(Matrix, width, height);
		player.move("left");
		if (player.getX() < 1)
			player.setX(1);

		player.draw(Matrix, width, height);
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		player.erase(Matrix, width, height);
		player.move("right");
		if (player.getX() + player.getWidth() > width - 2)
			player.setX(width - player.getWidth() - 1);

		player.draw(Matrix, width, height);
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		if(player.getX() + player.getWidth() + bulletWidth < width-2)
		{
			try {
				size_t playerLevel = player.getLevel();
				switch (playerLevel)
				{
				case 2:
					bullets.addBullet(new BasicBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player", 1));
					bullets.addBullet(new BasicBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player", -1));
				case 1:
					bullets.addBullet(new BasicBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player"));
					break;
				case 4:
					bullets.addBullet(new AdvancedBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player", 1));
					bullets.addBullet(new AdvancedBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player", -1));
				case 3:
					bullets.addBullet(new AdvancedBullet(player.getX() + player.getWidth(), player.getY() + (player.getHeight() / 2), "player"));
					break;

				default:
					throw "level too high!";
				}
			} //places a bullet to the right of the player, in the center of the player's height
			catch (const std::bad_alloc&)
			{
				std::cerr << "Couldn't allocate memory!" << std::endl;
				throw;
			}
			bullets[bullets.getSize() - 1]->draw(Matrix, width, height); //draw the last bullet
		}
	}
	if (GetAsyncKeyState(0x53)) //S Key value
	{
		try {
			saveGame();
		}
		catch (const char * exception)
		{
			gotoxy(1, 2);
			cout << exception << endl;
			Sleep(500);
			gotoxy(1, 2);
			size_t exceptionLenght = strlen(exception);
			for (size_t i = 0; i < exceptionLenght; i++) //clean exception
				cout << ' ';
		}
	}
}

void Console::updatePlayer()
{
	if ((!player.isBlinking() && !player.isHighlighted()) 
		|| player.getLives() == 0)
		return;
	else
	{
		player.erase(Matrix, width, height);
		player.draw(Matrix, width, height);
	}
}

void Console::playerDies()
{
	player.erase(Matrix, width, height);
	try { //create and draw explosion right after erasing player
		explosions.addExplosion(new Explosion(player.getX() + player.getWidth() / 2 - ExplosionWidth / 2,
			player.getY() + player.getHeight() / 2 - ExplosionHeight / 2));
		explosions[explosions.getSize() - 1]->draw(Matrix, width, height);
	}
	catch (const std::bad_alloc&)
	{
		throw;
	}
}

void Console::moveBullets()
{
	for (short i = 0; i < bullets.getSize(); i++)
	{
		bullets[i]->erase(Matrix, width, height);     //delete image of bullet
		bullets[i]->move();           //change X coordinate of bullet(increase X if player's bullet and vice versa)
		if (bullets[i]->getX() < 1 || bullets[i]->getX() > width - 2)
			bullets.removeBullet(i);  //remove bullet if it hits a wall 
		else
			bullets[i]->draw(Matrix, width, height);  //else draw bullet with new X
	}
}

void Console::moveEnemies()
{           
	for (short i = 0; i < enemies.getSize(); i++)
	{
		enemies[i]->erase(Matrix, width, height);     //delete image of enemy
		enemies[i]->move();           //reduce enemy X 
		if (enemies[i]->getX() < 2)
			enemies.removeEnemy(i);   //remove enemy if it reaches the left wall 
		else
			enemies[i]->draw(Matrix, width, height);  //else draw enemy with new X
	}
}

void Console::movePowerUps()
{
	for (short i = 0; i < powerups.getSize(); i++)
	{
		powerups[i]->erase(Matrix, width, height);     //delete image of enemy
		powerups[i]->move();           //reduce enemy X 
		if (powerups[i]->getX() < 2)
			powerups.removePowerUp(i);   //remove enemy if it reaches the left wall 
		else
			powerups[i]->draw(Matrix, width, height);  //else draw enemy with new X
	}
}

bool Console::objectsCollide(const Object& obj1,const Object& obj2) const
{
	return obj1.getX() + obj1.getWidth() > obj2.getX()
		&& obj1.getX() < obj2.getX() + obj2.getWidth()
		&& obj1.getY() + obj1.getHeight() > obj2.getY()
		&& obj1.getY() < obj2.getY() + obj2.getHeight();
}  

bool Console::objectBulletCollide(const Object& obj, const Bullet& bullet) const //Since the bullet object skips
{															 //a lot of pixels while moving, we'll need to increase
															 //its hitbox when detecting collision 
	return obj.getX() + obj.getWidth() > bullet.getX() - bullet.getSpeed()/2     
		&& obj.getX() < bullet.getX() + bullet.getWidth() + bullet.getSpeed()/2
		&& obj.getY() + obj.getHeight() > bullet.getY()      //bullet doesn't skip pixels
		&& obj.getY() < bullet.getY() + bullet.getHeight();  //along the Y axis, so this code stays the same
}

void Console::playerBulletCollision()
{
	size_t bulletsSize = bullets.getSize(); //local variables for faster loops

	for (size_t i = 0; i < bulletsSize; i++)
	{
		if (!bullets[i]->getIsPlayerBullet() && objectBulletCollide(player, *bullets[i]))
		{
			if (player.getLives() == 0)
				return;
			bullets[i]->erase(Matrix, width, height); //erase bullet from screen
			bullets.removeBullet(i);
			bulletsSize--;
			player.takeDamage();
			updateLives();
			if (player.getLives() == 0)
				playerDies();
			player.resetLevel();
		}
	}
}

void Console::enemyBulletCollision()
{
	size_t bulletsSize = bullets.getSize(); //local variables for faster loops
	size_t enemiesSize = enemies.getSize();

	for (size_t i = 0; i < enemiesSize; i++)
	{
		for (size_t j = 0; j < bulletsSize; j++)
		{
			if (bullets[j]->getIsPlayerBullet() && objectBulletCollide(*enemies[i], *bullets[j]))
			{
				enemies[i]->takeDamage(bullets[j]->getDamage()); //enemy takes damage equal to the bullet's damage

				bullets[j]->erase(Matrix, width, height); //bullet gets removed
				bullets.removeBullet(j);
				bulletsSize--;

				if (enemies[i]->getHealth() == 0) //if enemy is dead 
				{
					playerScore += 10 * enemies[i]->getLevel(); //player score increases 
					updateScore(); //print new score

					switch (currentEnemyLevel) //increase enemy level if needed
					{
					case 1:
						if (playerScore > 150)
							currentEnemyLevel++;
						break;
					case 2:
						if (playerScore > 350)
							currentEnemyLevel++;
						break;
					case 3:
						if (playerScore > 650)
							currentEnemyLevel++;
						break;
					}

					enemies[i]->erase(Matrix, width, height); //enemy gets erased from screen
					try { //create and draw explosion right after erasing enemy
						explosions.addExplosion(new Explosion(enemies[i]->getX() + enemies[i]->getWidth() / 2 - ExplosionWidth / 2,
							enemies[i]->getY() + enemies[i]->getHeight() / 2 - ExplosionHeight / 2));
						explosions[explosions.getSize() - 1]->draw(Matrix, width, height);
					}
					catch (const std::bad_alloc&)
					{
						throw;
					}
					enemies.removeEnemy(i); //delete enemy
					enemiesSize--;
					break; //enemy is destroyed, no need to check if any other bullets collide with it.
				}          //Onto the next enemy
			}
		}
	}
}

void Console::playerEnemyCollision()
{
	//local variables for faster loops
	size_t enemiesSize = enemies.getSize();
	
	for (size_t i = 0; i < enemiesSize; i++)
	{
		if (player.getLives() == 0)
			return;
		if (objectsCollide(player, *enemies[i])) //if player and enemy number i collide
		{
			enemies[i]->erase(Matrix, width, height); //erase enemy from screen
			try {
				explosions.addExplosion(new Explosion(enemies[i]->getX() + enemies[i]->getWidth() / 2 - ExplosionWidth / 2,
					enemies[i]->getY() + enemies[i]->getHeight() / 2 - ExplosionHeight / 2));
				explosions[explosions.getSize() - 1]->draw(Matrix, width, height);
			}
			catch (const std::bad_alloc&)
			{
				throw;
			}
			enemies.removeEnemy(i); //enemy doesn't survive the crash
			enemiesSize--;
			player.takeDamage();
			updateLives();
			if (player.getLives() == 0)
				playerDies();
			player.resetLevel();
		}
	}
}

void Console::playerPowerupCollision()
{
	//local variables for faster loops
	size_t powerupsSize = powerups.getSize();

	for (size_t i = 0; i < powerupsSize; i++)
	{
		if (player.getLives() == 0)
			return;
		if (objectsCollide(player, *powerups[i])) //if player and powerup number i collide
		{
			powerups[i]->erase(Matrix, width, height); //erase powerup from screen
			size_t type = powerups[i]->getType();
			switch (type)
			{
			case 1:
				player.increaseLives();
				updateLives();
				player.colorGreen();
				break;
			case 2:
				if (player.getLevel() < 4)
					player.increaseLevel();
				player.colorYellow();
				break;
			case 3:
				killAllEnemies();
				break;
			default:
				throw "no such type!";
			}
			powerups.removePowerUp(i); //powerup is consumed
			powerupsSize--;
		}
	}
}

void Console::CollisionDetection()
{
	//collision loops
	playerBulletCollision();
	enemyBulletCollision();
	playerEnemyCollision();
	playerPowerupCollision();
}

void Console::killAllEnemies()
{
	size_t enemiesSize = enemies.getSize();
	for (size_t i = 0; i < enemiesSize; i++)
	{
		enemies[0]->erase(Matrix, width, height); //erase enemy from screen
		try {
			explosions.addExplosion(new Explosion(enemies[0]->getX() + enemies[0]->getWidth() / 2 - ExplosionWidth / 2,
				enemies[0]->getY() + enemies[0]->getHeight() / 2 - ExplosionHeight / 2));
			explosions[explosions.getSize() - 1]->draw(Matrix, width, height);
		}
		catch (const std::bad_alloc&)
		{
			throw;
		}
		enemies.removeEnemy(0); 
	}
}

void Console::spawnEnemies()
{
	size_t spawnChance = rand() % 20;
	size_t type = rand() % 2 + 1; //returns 1 or 2
	size_t spawnHeight = 0; 
	
	if (spawnChance == 0) //spawn enemy
	{
		if (enemies.getSize() == 0) //no enemies to collide with when spawning
		{
			try {
				if (type == 1)
				{
					spawnHeight = (rand() % (27 - dropshipHeight)) + 3;
					enemies.addEnemy(new Dropship(width - 1 - dropshipWidth, spawnHeight, currentEnemyLevel));
				}
				if (type == 2)
				{
					spawnHeight = (rand() % (27 - tieFighterHeight)) + 3;
					enemies.addEnemy(new TieFighter(width - 1 - tieFighterWidth, spawnHeight, currentEnemyLevel));
				}
			}
			catch (const std::bad_alloc&)
			{
				std::cerr << "Couldn't allocate memory!";
				throw;
			}
			return;
		}
		//else if there are enemies, create random height and check for collision
		do {
			if(type == 1)
				spawnHeight = (rand() % (27 - dropshipHeight)) + 3;
			if(type == 2)
				spawnHeight = (rand() % (27 - tieFighterHeight)) + 3;
		}while(objectsCollide(*enemies[enemies.getSize() - 1], TieFighter(width - 2, spawnHeight, 1)));
		//Do the last enemy and the next imaginary enemy(with Y = spawnHeight) collide?
		//if not continue: 
		try {
			if(type == 1)
				enemies.addEnemy(new Dropship(width - 1 - dropshipWidth, spawnHeight, currentEnemyLevel));
			if(type == 2)
				enemies.addEnemy(new TieFighter(width - 1 - tieFighterWidth, spawnHeight, currentEnemyLevel));
		}
		catch (const std::bad_alloc&)
		{
			std::cerr << "Couldn't allocate memory!";
			throw;
		}
		enemies[enemies.getSize() - 1]->draw(Matrix, width, height); //draw last enemy, which was created in this function
	}
}

void Console::enemiesFire()
{
	size_t fireChance = 0;
	for (size_t i = 0; i < enemies.getSize(); i++)
	{
		fireChance = rand() % 40;
		if (fireChance == 0 && enemies[i]->getX() - bulletWidth > 2) //if there is space for a bullet 
		{
			try {
				if (enemies[i]->getType() == 1)
				{
					//this enemy fires 2 shots, because it has 2 guns
					bullets.addBullet(new BasicBullet(enemies[i]->getX(), enemies[i]->getY(),"enemy"));
					bullets.addBullet(new BasicBullet(enemies[i]->getX(), enemies[i]->getY() + 2,"enemy"));
					bullets[bullets.getSize() - 2]->draw(Matrix, width, height);
					bullets[bullets.getSize() - 1]->draw(Matrix, width, height); //draw the last 2 bullets
				}
				else if (enemies[i]->getType() == 2)
				{
					//1 shot at the center of the height
					bullets.addBullet(new BasicBullet(enemies[i]->getX(), enemies[i]->getY() + 1, "enemy"));
					bullets[bullets.getSize() - 1]->draw(Matrix, width, height); //draw the last bullet
				}
				else
					throw("unknown enemy type!");
			} 
			//places bullets to the left of the enemy, Y coordinate depends on the type of enemy
			catch (const std::bad_alloc&)
			{
				std::cerr << "Couldn't allocate memory!" << std::endl;
				throw;
			}
		}
	}
}

void Console::spawnPowerUps()
{
	if (powerups.getSize() == 4)
		return;
	int spawnChance = rand() % 100;
	int type = 0;
	int spawnHeight = 0;
	if (spawnChance < 1)
	{
		type = rand() % 3; 
		switch (type)
		{
		case 0:
			spawnHeight = (rand() % (27 - extraLifeHeight)) + 3;
			powerups.addPowerUp(new ExtraLife(width-3, spawnHeight));
			break;
		case 1:
			if (player.getLevel() == 4)
				return;
			spawnHeight = (rand() % (27 - gunUpgradeHeight)) + 3;
			powerups.addPowerUp(new GunUpgrade(width-5, spawnHeight));
			break;
		case 2:
			spawnHeight = (rand() % (27 - gunUpgradeHeight)) + 3;
			powerups.addPowerUp(new Nuke(width - 5, spawnHeight));
			break;
		}

		powerups[powerups.getSize() - 1]->draw(Matrix, width, height);
	}
}

void Console::updateExplosions()
{
	size_t explosionsSize = explosions.getSize();
	for (size_t i = 0; i < explosionsSize; i++)
	{
		if (explosions[i]->getStage() == 4)
		{
			explosions[i]->erase(Matrix, width, height);
			explosions.removeExplosion(i);
			explosionsSize--;
			continue;
		}
		explosions[i]->update(gameSpeed); //changes image
		explosions[i]->draw(Matrix, width, height); //draws new image
	}
}


