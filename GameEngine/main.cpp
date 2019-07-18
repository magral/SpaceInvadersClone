#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <ctime>

#include "./Characters/Player.h"
#include "./Characters/Enemy.h"

int main() {
	// ============
	//	  SET UP
	// ============
	HWND window = GetConsoleWindow();
	HDC hdc = GetDC(window);
    // Don't check in commented out dead code. 
    // Makes file messy and code is either required or its not

	//Instantiate Player
	Player* playerCharacter = new Player(hdc);

	// ===========
	//  Game Loop
	// ===========

	time_t oldTime = time(NULL);
    time_t frameTime = 100; 
    // by forcing this frame time you are 
    // making sure that the movement is not frame rate dependant. 
    // otherwise you can move faster on a faster computer which is not fair
	while (true) {

		time_t deltaTime = time(NULL) - oldTime;
		
		playerCharacter->processInput();
		// add exit condition
        time_t waitTime = frameTime - deltaTime;
        if (waitTime > 0)
        {
            Sleep(DWORD(waitTime));
        }
        else
        {
            // warn that the game went over the frame time
        }
	} 
	
	// ===========
	//  CLEAN UP
	// ===========

	delete(playerCharacter);
	ReleaseDC(window, hdc);
	return 0;
}