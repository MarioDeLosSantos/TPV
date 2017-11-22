#pragma once
#include "GameMap.h"

using namespace std;


class Game;
class Texture;
class Ghost;
class Pacman
{
private:
	Ghost* Fantasma = nullptr;
	Game* game = nullptr;
	GameMap* mapa = nullptr;
	SDL_Event event;
	bool vivo;
	bool abierto = false;
	int posiniX, posiniY;
	int posX, posY;
	int posicionInicialX, posicionInicialY;
	int dirX,dirY;
	int siguientePosX, siguientePosY;
	int posibledirX, posibledirY;
	int NdirX, NdirY;
	bool input=false;

public:

	void render(SDL_Renderer* render,Texture* texture);
	void update();
	void Ndir(SDL_Event event);
	void MuevePacman();
	void Buffer();
	void PosicionInicial(int x, int y) { posicionInicialX = x; posicionInicialY = y; };
	void DetectaFantasma();
	void setPos(int x, int y) { posX = x; posY = y; };
	void setDir(int x, int y) { dirX = x; dirY = y; };
	//Gets
	int GetPosX() { return posX; };
	int GetPosY() { return posY; };
	int GetDirX() { return dirX; };
	int GetdirY() { return dirY; };
	int GetposiniX() { return posicionInicialX; };
	int GetposiniY() { return posicionInicialY; };
	Pacman(int x, int y, GameMap* mapajuego, Game* juego,int filas,int columnas);
	~Pacman();
};

