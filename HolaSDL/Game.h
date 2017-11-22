#pragma once

#include "SDL.h"
#include <string.h>
#include <vector>
#include <iostream>
#include<sstream>

using namespace std;

//Dependencias
class GameMap;
class Texture;
class GameObject;
class Pacman;
class Ghost;
class Game
{
private:
	//Generales
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	const int winWidth=1300;
	const int winHeight = 800;
	int fils, cols;
	int winX, winY;
	int energia;
	int vidas=3;
	bool exit = false;
	int comidarestante=0;
	int pasoNiveles=0;	
	//Para el laberinto
	Texture* texturas[7];
	Pacman* pacman;
	Ghost* Fantasmas[4];
	//PACMAN
	GameMap* Mapa=nullptr;
	

public:

	Game();
	~Game();

	//Ejecuta el juego
	void run();

	//Actualizan
	void update();
	void render();
	void handleEvents();
	void pintaVidas();
	void GuardaMapa();
	bool Menu();
	int GetposXfan(int x);
	int GetposYfan(int x);

	//Getters
	int getWinWidth() { return winWidth; };
	int getWinHeight() { return winHeight; };
	int getFilas() { return fils; };
	int getCols() { return cols; };
	int getEnergia() { return energia; };
	void ComeComida(int x, int y);
	void restavidas() { vidas--; };
	void restaEnergia()
	{
		if (energia > 0)
			energia--;
	}
	void setEnergia(int x) { energia = x; };
	void restauraPosciones(Pacman* pacman,int i);
	void bajacomida() { comidarestante -= 1; };
	bool HayFantasma(int x, int y);
	SDL_Renderer* getRenderer() { return renderer; };

	//PACMAN
	void creaMapa(bool indice);
};


