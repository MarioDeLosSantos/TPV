#include "Pacman.h"
#include "Game.h"
#include "Pacman.h"
#include"Texture.h"
Pacman::Pacman(int x, int y, GameMap* mapajuego, Game* juego,int filas,int columnas)
{
	posX = x;
	posY = y;
	mapa= mapajuego;
	game = juego;
	dirX = 0;
	dirY = 1;
}

Pacman::~Pacman()
{
	
}

void Pacman::DetectaFantasma()
{
	for (int i = 0; i < 4; i++)
	{
		if (posX == game->GetposXfan(i) && posY == game->GetposYfan(i))
		{
			game->restauraPosciones(this,i);
		}
	}
}

void Pacman::render(SDL_Renderer* render,Texture* texture)
{	
	
	SDL_Rect recDest;
	recDest.w = game->getWinWidth()/ mapa->getDimY();
	recDest.h = (game->getWinHeight()-100)/ mapa->getDimX();
	recDest.x =recDest.w * posY;
	recDest.y = recDest.h* posX;
	if (!abierto)
	{
		if (dirX == 0 && dirY == 1)
			texture->renderFrame(game->getRenderer(), recDest, 0, 11);
		else if (dirX == 0 && dirY == -1)
			texture->renderFrame(game->getRenderer(), recDest, 2, 11);
		else if (dirX == 1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 1, 11);
		else if (dirX == -1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 3, 11);

		abierto = true;
	}
	else
	{
		if (dirX == 0 && dirY == 1)
			texture->renderFrame(game->getRenderer(), recDest, 0, 10);
		else if (dirX == 0 && dirY == -1)
			texture->renderFrame(game->getRenderer(), recDest, 2, 10);
		else if (dirX == 1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 1, 10);
		else if (dirX == -1 && dirY == 0)
			texture->renderFrame(game->getRenderer(), recDest, 3, 10);
		abierto = false;
	}

}


void Pacman::update()
{
	Buffer();

	DetectaFantasma();

	MuevePacman();

	DetectaFantasma();

	game->ComeComida(posX, posY);

	game->restaEnergia();

}

void Pacman::Ndir(SDL_Event event)
{
	
		 if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_RIGHT) {
				NdirX = 0;
				NdirY = 1;
				input = true;
			}
			else if (event.key.keysym.sym == SDLK_LEFT) {
				NdirX = 0;
				NdirY =-1;
				input = true;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				NdirX = -1;
				NdirY = 0;
				input = true;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				NdirX = 1;
				NdirY = 0;
				input = true;
			}
			
	}
}

void Pacman::MuevePacman()
{
	siguientePosX = posX + dirX;
	siguientePosY = posY + dirY;
	mapa->toroide(siguientePosX, siguientePosY);

	if (!mapa->hayMuro(siguientePosX, siguientePosY))
	{
		posX = siguientePosX;
		posY = siguientePosY;
	}
}

void Pacman::Buffer()
{
	posibledirX = posX + NdirX;
	posibledirY = posY + NdirY;

	if (!mapa->hayMuro(posibledirX, posibledirY) && input)
	{
		dirX = NdirX;
		dirY = NdirY;
		NdirX = 0;
		NdirY = 0;
		input = false;
	}
}

