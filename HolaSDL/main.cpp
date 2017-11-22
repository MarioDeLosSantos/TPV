
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char* argv[]){

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game* juego = new Game;
	juego->run();
	system("pause");
	delete juego;
	
	return 0;
}