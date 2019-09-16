#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "./Characters/Player.h"
#include "./Characters/Enemy.h"
#include "./Objects/Bullet.h"
#include "Systems/BoundingTree.h"
#include "Systems/IBoundingBox.h"

int main() {
	// ============
	//	  SET UP
	// ============
	HWND window = GetConsoleWindow();
	HDC hdc = GetDC(window);
	
	//Instantiate Collision tree
	BoundingTree *tree = new BoundingTree(11);
	//Instantiate Player
	Player* playerCharacter = new Player(hdc, tree);
	//Instantiate Enemies
	std::vector<Enemy*> enemies;
	int startingX = 96;
	int startingY = 128;
	for (int i = 1; i < 10; i++) {
		int offsetX = startingX + (i * 32 * 2);
		int offsetY = startingY + (i * 32 * 2);
		IBoundingBox *box;
		Enemy* enemyTmp = new Enemy(new RECT{ offsetX, startingY, offsetY, startingX }, hdc, tree);
		box = &*enemyTmp;
		tree->insertObject(box);
		enemies.push_back(enemyTmp);
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