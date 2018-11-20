#include <iostream>
#include <windows.h>

#include "Console.h"

using namespace std;

void getGameSpeed(size_t &gameSpeed)
{
	size_t choice = 1;
	cout << "Please choose difficulty: " << endl;
	cout << "[0] Easy(slow)" << endl;
	cout << "[1] Normal" << endl;
	cout << "[2] Hard(fast)" << endl;
	cout << "_____________________________" << endl;
	cout << "[3] Load game from \"Save.dat\" ";
	cout << endl;
	do {
		cin >> choice;
	} while (choice > 3);
	switch (choice)
	{
		case 0:
			gameSpeed = 40;
			break;
		case 1:
			gameSpeed = 50;
			break;
		case 2: 
			gameSpeed = 60;
			break;
		case 3:
			gameSpeed = 0;
			break;
		default: //not supposed to come here because of do-while
			throw invalid_argument("invalid input!");
	}
}

int main()
{
	srand(time(NULL));
	size_t gameSpeed = 0;
	getGameSpeed(gameSpeed);
	
	if (gameSpeed == 0) //load game
	{
		try {
			Console console;
			console.init();
			console.gameLoop();
		}
		catch (std::runtime_error& ex)
		{
			cout << ex.what() << endl;
			Sleep(100);
			Console console(60);
			console.init();
			console.gameLoop();
		}
	}
	else                //new game
	{
		Console console(gameSpeed);
		console.init();
		console.gameLoop();
	}
 }

