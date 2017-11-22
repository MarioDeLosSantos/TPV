#include "GameMap.h"
#include "Game.h"
#include "Texture.h"


GameMap::GameMap(Game* juego)
{
	game = juego;
}


GameMap::~GameMap()
{
	//Borramos los punteros de las columnas
	for (int i = 0; i < DimX; i++) {
		delete matrizMapa[i];
	}
	delete matrizMapa; //Borramos la matriz de putteros a filas
}

//enum MapCell { empty, Wall, Food, Vitaminas }; Para acordarme
void GameMap::SetPos(int posicionX, int posicionY, int elemento)
{
	//SITUAMOS ELEMENTOS ESTATICOS
	if (elemento == 0) { matrizMapa[posicionX][posicionY] = empty; }
	else if (elemento == 1) { matrizMapa[posicionX][posicionY] = Wall; }
	else if (elemento == 2) { matrizMapa[posicionX][posicionY] = Food; }
	else if (elemento == 3) { matrizMapa[posicionX][posicionY] = Vitaminas; }
	//PONEMOS VACIA LA CASILLA DE LOS PERSONAJES
	else if (elemento >= 4) { matrizMapa[posicionX][posicionY] = empty; }

}
//DEVUELVE SI HAY MURO O NO EN LAS COORDENADAS X E Y
bool GameMap::hayMuro(int x, int y)
{
	//Toroide
	toroide(x, y);

	if (matrizMapa[x][y]== Wall) { return true; }
	else { return false; }
}

void GameMap::toroide(int& x, int& y)
{
	if (x < 0) { x = game->getFilas() - 1; }
	else if (x > game->getFilas() - 1) { x = 0; }
	else if (y > game->getCols() - 1) { y = 0; }
	else if (y < 0) { y = game->getCols() - 1; }
}


void GameMap::ReservaMemoriaMapa(int fils, int cols)
{
	DimX = fils;
	DimY = cols;

	matrizMapa = new MapCell*[DimX];

	for (int i = 0; i < fils; i++){
		matrizMapa[i] = new MapCell[DimY];
	}
}


void GameMap::DepuraMapa()
{
	cout << "filas: " << DimX << " Columnas: " << DimY << "\n\n";
	for (int i = 0; i < DimX; i++){
		for (int j = 0; j < DimY; j++){
			if (matrizMapa[i][j] == empty)
				cout << "  ";
			else if (matrizMapa[i][j] == Wall)
				cout << "W ";
			else if (matrizMapa[i][j] == Vitaminas)
				cout << "V ";
			else if (matrizMapa[i][j] == Food)
				cout << "F ";
		}
		cout << "\n";
	}
}


void GameMap::cambiacasiila(int posX, int posY)
{
	if(matrizMapa[posX][posY] == Vitaminas || matrizMapa[posX][posY]==Food)
	{
		if (matrizMapa[posX][posY] == Vitaminas)
			game->setEnergia(30);

		game->bajacomida();
		matrizMapa[posX][posY] = empty;	
	}
	
}

void GameMap::Render(SDL_Renderer* render,Texture*  maptexture [4])
{
	SDL_Rect recDest; 
	recDest.w = game->getWinWidth() / DimY;
	recDest.h = (game->getWinHeight()-100)/ DimX;

	for(int i=0;i<DimX;i++)
		for (int j = 0; j < DimY; j++)
		{
			recDest.x = recDest.w*j;
			recDest.y = recDest.h*i;
			if (matrizMapa[i][j] == Wall)
				maptexture[0]->renderFrame(game->getRenderer(), recDest, 0, 0);
			if (matrizMapa[i][j] == Food)
				maptexture[1]->renderFrame(game->getRenderer(), recDest, 0, 0);
			if (matrizMapa[i][j] == Vitaminas)
				maptexture[2]->renderFrame(game->getRenderer(), recDest, 0, 0);
		}
}

int GameMap::Getelemento(int x, int y)
{
	if (matrizMapa[x][y] == empty)
		return 0;
	else if (matrizMapa[x][y] == Wall)
		return 1;
	else if (matrizMapa[x][y] == Food)
		return 2;
	else if (matrizMapa[x][y] == Vitaminas)
		return 3;
}				

