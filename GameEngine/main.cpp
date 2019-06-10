#include <iostream>
#include <Windows.h>
#include <conio.h>

#include "Player.h"
#include "Enemy.h"

int main() {
	// ============
	//	  SET UP
	// ============
	HWND window = GetConsoleWindow();
	HDC hdc = GetDC(window);

	//Get the player 'level'
	//int level;
	//std::cout << "Please input level of difficulty (1-3):" << std::endl;
	//std::cin >> level;

	//Instantiate Player
	Player* playerCharacter = new Player(hdc);
/*
	//Instantiate Enemies
	Enemy** enemies;
	for (int i = 0; i < level * 5; i++) {
		enemies[i] = new Enemy(level, i, i);
	}
	*/
	// ===========
	//  Game Loop
	// ===========
	while (true) {
		
		playerCharacter->processInput();
		// add exit condition
	} 
	
	// ===========
	//  CLEAN UP
	// ===========

	delete(playerCharacter);
	ReleaseDC(window, hdc);
	return 0;
}