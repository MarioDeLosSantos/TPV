#include "Texture.h"
#include"SDL.h"
#include"SDL_Image.h"
#include<iostream>

using namespace std;


Texture::Texture()
{
}


Texture::~Texture()
{
}

bool Texture::load(SDL_Renderer* renderer, string filename,	int rows, int cols)
{
	NumRows = rows;
	NumCols = cols;

	//Creamos la textura a partir de la surface

	SDL_Surface* surface = IMG_Load(filename.c_str());

	if (surface != nullptr)
	{
		//Creamos la textura
		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == nullptr)
			cout << "textura no cargada";

		//Obtenemos las dimensiones

		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
		fw = w / NumCols;
		fh = h / NumRows;

		SDL_FreeSurface(surface);
		return true;
	}
	else
	{
		return false;
	}
}

void Texture::render(SDL_Renderer* renderer, const SDL_Rect& rect, SDL_RendererFlip flip)
{
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Texture::renderFrame(SDL_Renderer* renderer, const SDL_Rect& destRect, int row, int col, SDL_RendererFlip flip)
{
	//Escoge el frame de origen
	SDL_Rect srcRect;
	srcRect.x = fw*col;
	srcRect.y = fh*row;
	srcRect.w = fw;
	srcRect.h = fh;

	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}
