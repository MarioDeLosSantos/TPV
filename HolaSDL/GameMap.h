#include <iostream>
#include <string>
#include <vector>
#include"SDL.h"
#include"SDL_Image.h"


using namespace std;

#pragma once
class Texture;
class Game;
class GameMap
{

private:

	Game* game = nullptr;

	//Dimensiones del mapa
	int DimX;
	int DimY;
	
	enum MapCell{empty, Wall, Food, Vitaminas}; //Tipos de muro que puede tener el mapa
	MapCell **matrizMapa;


public:
	GameMap(Game* juego);
	~GameMap();
		
	void ReservaMemoriaMapa(int fils, int cols);
	void SetPos(int posicionX, int posicionY, int elemetnto);
	void Render(SDL_Renderer* render,Texture* maptexture[4]);
	void DepuraMapa();
	void cambiacasiila(int posX, int posY);
	void toroide(int& x, int& y);
	int Getelemento(int x, int y);

	//Metodos Get
	bool hayMuro(int x, int y);
	int getDimX() { return DimX; };
	int getDimY() { return DimY; };
};

