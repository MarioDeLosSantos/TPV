#pragma once
#include "GameMap.h"
#include <vector>
using namespace std;

class GameMap;
class Game;
class Texture;
class Pacman;
class Ghost
{
private:

	struct Dirs
	{
		int x;
		int y;
	};
	vector<Dirs> posDirs;
	int posX, posY;
	int posIniX, posIniY;
	int dirX, dirY;
	int numRows, numCols;
	int NumeroFantasma;
	bool pata = false;
	Game* juego = nullptr;
	GameMap* mapa = nullptr;
	
public:
	void render(SDL_Renderer* renderer,Texture* texture);
	void update();
	void PosiblesDirs();
	void RellenaPos(int x, int y);
	void setposIni() {
		posX = posIniX;
		posY = posIniY;
	}
	
	//GETS
	int GetPosIniX() { return posIniX; };
	int GetPosIniY() { return posIniY; };
	int GetPosX() { return posX; };
	int GetPosY() { return posY; };
	int GetDirX() { return dirX; };
	int GetdirY() { return dirY; };
	int GetFantasma() { return NumeroFantasma; };
	Ghost( int x, int y, Game* game, GameMap* mapajuego, int Fantasma);
	~Ghost();
};

	