#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "./Characters/Player.h"
#include "./Characters/Enemy.h"
#include "./Objects/Bullet.h"

int main() {
	// ============
	//	  SET UP
	// ============
	HWND window = GetConsoleWindow();
	HDC hdc = GetDC(window);

	//Instantiate Player
	Player* playerCharacter = new Player(hdc);

	//Instantiate Enemies
	std::vector<Enemy*> enemies;
	int startingX = 80;
	int startingY = 96;
	for (int i = 1; i < 10; i++) {
		int offsetX = startingX + (i * 16 * 2);
		int offsetY = startingY + (i * 16 * 2);
		enemies.push_back(new Enemy(new RECT{ offsetX, startingY, offsetY, startingX}, hdc));
	}
	
	

	// ===========
	//  Game Loop
	// ===========

	time_t oldTime = time(NULL);
	while (true) {

		time_t deltaTime = time(NULL) - oldTime;
		
		playerCharacter->processInput();
		Sleep(50);
		playerCharacter->moveBullets();
		// add exit condition
	} 
	
	// ===========
	//  CLEAN UP
	// ===========

	delete(playerCharacter);
	ReleaseDC(window, hdc);
	return 0;
}