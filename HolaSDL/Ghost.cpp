#include "Ghost.h"
#include "Texture.h"
#include "Game.h"
#include "GameMap.h"
#include "Pacman.h"
Ghost::Ghost(int x, int y, Game* game ,GameMap* mapajuego, int Fantasma)
{
	posIniX = x;
	posIniY = y;
	posX = x;
	posY = y;
	juego = game;
	mapa = mapajuego;
	NumeroFantasma = Fantasma;
	numCols = NumeroFantasma * 2;
	dirX = 0;
	dirY = 1;
}


Ghost::~Ghost()
{
	//delete textura;
}

void Ghost::RellenaPos(int x, int y)
{
	Dirs aux;
	aux.x = x;
	aux.y = y;
	posDirs.push_back(aux);
}

void Ghost::PosiblesDirs()
{
	posDirs.clear();
	
	RellenaPos(1, 0);
	RellenaPos(-1, 0);
	RellenaPos(0, 1);
	RellenaPos(0, -1);
	int i = 0;

	while (i < posDirs.size()) {
		if ((mapa->hayMuro(posX+posDirs[i].x, posY+posDirs[i].y)) || (posDirs[i].x==-dirX && posDirs[i].y==-dirY) ||
			juego->HayFantasma(posX + posDirs[i].x, posY + posDirs[i].y)) 
		{
			posDirs.erase(posDirs.begin() + i);
		}
		else i++;
	}
	if (posDirs.size() < 1)
	{
		RellenaPos(-dirX, -dirY);
	}
	
	
}


void Ghost::update()
{
	PosiblesDirs();
	int random = rand() % posDirs.size();
	dirX = posDirs[random].x;
	dirY = posDirs[random].y;
	//detectaPacman();
	posX += dirX;
	posY += dirY;
	mapa->toroide(posX, posY);
	//juego->Conpruebamuerte(this);
	
}

void Ghost::render(SDL_Renderer*  renderer,Texture* texture)
{
	SDL_Rect recDest;
	recDest.w = juego->getWinWidth()/ mapa->getDimY();
	recDest.h = (juego->getWinHeight()-100) / mapa->getDimX();
	recDest.x = recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (juego->getEnergia() <= 0) {
		if (!pata)
		{
			texture->renderFrame(juego->getRenderer(), recDest, numRows, numCols);
			pata = true;
		}
		else
		{
			texture->renderFrame(juego->getRenderer(), recDest, numRows, numCols+1);
			pata = false;
		}
	}
	else
	{
		if (!pata)
		{
			texture->renderFrame(juego->getRenderer(), recDest, 0, 12);
			pata = true;
		}
		else
		{
			texture->renderFrame(juego->getRenderer(), recDest, 0, 13);
			pata = false;
		}
	}
} 


