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
	for (int i = 0; i <  5; i++) {
		enemies.push_back(new Enemy(1, i, i));
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