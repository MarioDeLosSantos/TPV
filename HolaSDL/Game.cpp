#include "Game.h"
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include "GameMap.h"
#include <fstream>
#include "Pacman.h"
#include"Ghost.h"
#include "Texture.h"
using namespace std;

const int renderTime = 5;

Game::Game()
{
	winX = winY = SDL_WINDOWPOS_CENTERED;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("First test with SDL", winX, winY,
		winWidth, winHeight, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		cout << "Error inicializando SDL";
	else
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 

	for (int i = 0; i < 7; i++)
		{
			texturas[i] = new Texture();
		}

	Mapa = new GameMap(this);
	
	texturas[0]->load(renderer, "..\\images\\wall2.png");
	texturas[1]->load(renderer, "..\\images\\food2.png");
	texturas[2]->load(renderer, "..\\images\\burguer1.png");
	texturas[3]->load(renderer, "..\\images\\characters1.png", 4, 14);	
	texturas[4]->load(renderer, "..\\images\\vidas.png",3,1);
	texturas[5]->load(renderer, "..\\images\\menu.jpg");
	texturas[6]->load(renderer, "..\\images\\flecha.png");
}

Game::~Game()
{
	for (int i = 0; i < 4; i++)
	{
		delete Fantasmas[i];
	}
	delete pacman;
	delete Mapa;
	for (int j = 0; j < 7; j++)
	{
		delete texturas[j];
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

void Game::run()
{
	bool nivelactual = true;
	int startime, frametime, FRAMERATE = 150;
	bool opcion = Menu();
	while (!exit && pasoNiveles<=5)
	{
		creaMapa(opcion);
		nivelactual = true;
		if (!opcion)
		{
			vidas = 3;
			energia = 0;
		}
		while (nivelactual && !exit)
		{
			startime = SDL_GetTicks();
			handleEvents();
			update();
			render();
			if (vidas == 0)
			{
				exit = true;
				nivelactual = false;
			}

			else if (comidarestante == 0)
			{
				nivelactual = false;
				pasoNiveles++;
			}

			frametime = SDL_GetTicks() - startime;
			if (frametime < FRAMERATE) SDL_Delay(FRAMERATE - frametime);
		}

		opcion = false;
	}
	GuardaMapa();
	SDL_Quit();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	Mapa->Render(renderer,texturas);
	pacman->render(renderer,texturas[3]);
	for (int i = 0; i < 4; i++)
		Fantasmas[i]->render(renderer,texturas[3]);
	pintaVidas();
	SDL_RenderPresent(renderer);
	SDL_Delay(renderTime);
}

int Game::GetposXfan(int x)
{
	return Fantasmas[x]->GetPosX();
}

int Game::GetposYfan(int x)
{
	return Fantasmas[x]->GetPosY();
}

void Game::update()
{
	pacman->update();
	for (int i = 0; i < 4; i++)
	{
		Fantasmas[i]->update();
	}
}

void Game::handleEvents()
{
	
	SDL_Event event;
	
	//Control de eventos
	while (SDL_PollEvent(&event) && !exit) {
	
			if (event.type == SDL_QUIT)
				exit= true;
			else if (event.type == SDL_KEYDOWN)
			{
				pacman->Ndir(event);
				exit=false;
			}
	}
}




//PACMAN
void Game::creaMapa(bool indice)
{
	
	int elemento;
	ifstream archivoMapa;
	if (!indice)
	archivoMapa.open("..\\Levels\\level0"+to_string(pasoNiveles)+".dat");
	else archivoMapa.open("..\\Levels\\NivelGuardado.dat");
	archivoMapa >> fils >> cols;
	Mapa->ReservaMemoriaMapa(fils, cols);

	for (int i = 0; i < fils; i++){
		for (int j = 0; j < cols; j++)
		{
			archivoMapa >> elemento;
			if (elemento == 2 || elemento == 3)
				comidarestante++;
			else if (elemento == 9) 
			{
				pacman = new Pacman(i,j, Mapa, this,fils,cols);
				pacman->PosicionInicial(i, j);
			}
			else if(elemento>=5)
			{
				Fantasmas[elemento - 5] = new Ghost(i, j, this, Mapa, elemento-5);
			}
			Mapa->SetPos(i, j, elemento);
		}
	}

	if (indice)
	{
		archivoMapa >> vidas >> pasoNiveles;
	}
	archivoMapa.close();
}

void Game::GuardaMapa()
{
	ofstream archivoMapa("..\\Levels\\NivelGuardado.dat");
	int elemento;
	archivoMapa << fils << " " << cols<<endl;

	for (int i = 0; i < fils; i++) {
		for (int j = 0; j < cols; j++)
		{
			
				if (i == Fantasmas[0]->GetPosIniX() && j == Fantasmas[0]->GetPosIniY())

					archivoMapa << 5 <<" ";

				else if (i == Fantasmas[1]->GetPosIniX() && j == Fantasmas[1]->GetPosIniY())
					archivoMapa << 6 <<" ";

				else if (i == Fantasmas[2]->GetPosIniX() && j == Fantasmas[2]->GetPosIniY())
					archivoMapa << 7 <<" ";

				else if (i == Fantasmas[3]->GetPosIniX() && j == Fantasmas[3]->GetPosIniY())
					archivoMapa << 8 <<" ";

				else if (i == pacman->GetPosX() && j == pacman->GetPosY())
					archivoMapa << 9 << " ";
			
				else
				archivoMapa << Mapa->Getelemento(i, j) << " ";
			
			
		}
		archivoMapa << endl;
	}

	archivoMapa << vidas << " " << pasoNiveles<<endl;

	archivoMapa.close();
}


void Game::ComeComida(int x, int y)
{
	Mapa->cambiacasiila(x, y);
}
void Game::restauraPosciones(Pacman* pacman,int i)
{
	if (energia <= 0)
	{
		for (int i = 0; i < 4; i++)
			Fantasmas[i]->setposIni();
		pacman->setPos(pacman->GetposiniX(), pacman->GetposiniY());
		restavidas();
		pacman->setDir(0, 1);
	}

	else 
		Fantasmas[i]->setposIni();
	
}

bool Game::HayFantasma(int x, int y)
{
	bool hayfantasma = false;
	for (int i = 0; i < 4; i++)
	{
		if (x == Fantasmas[i]->GetPosX() && y == Fantasmas[i]->GetPosY())
			hayfantasma = true;
	}

	return hayfantasma;
}

void Game::pintaVidas()
{
	SDL_Rect recDest;
	recDest.w = 200;
	recDest.h = 75;
	recDest.x = winWidth/2-recDest.w/2;
	recDest.y = (winHeight-100);
	if (vidas == 3) 
	texturas[4]->renderFrame(renderer, recDest,0,0);
	else if (vidas == 2) 
	texturas[4]->renderFrame(renderer, recDest, 1, 0);
	else if (vidas == 1)
	texturas[4]->renderFrame(renderer, recDest, 2, 0);
}

bool Game::Menu()
{
	bool contador=false;
	SDL_Event eventt;
	SDL_Rect Rec_destFondo;
	SDL_Rect Rec_destFlecha;
	Rec_destFlecha.w = winWidth/10;
	Rec_destFlecha.h = winHeight / 10;
	Rec_destFondo.w = winWidth;
	Rec_destFondo.h = winHeight;
	Rec_destFondo.x = 0;
	Rec_destFondo.y = 0;

	bool exitMenu = false;
	while (SDL_PollEvent(&eventt) || !exitMenu)
	{
		SDL_RenderClear(renderer);

		if (eventt.type == SDL_KEYDOWN)
		{
			
			if (eventt.key.keysym.sym == SDLK_DOWN && !contador)
			{
				contador = true;
			}

		    else  if (eventt.key.keysym.sym == SDLK_UP && contador)
			{
				contador = false;
			}
			
			else if (eventt.key.keysym.sym == SDLK_SPACE)
				exitMenu = true;
		}

		texturas[5]->render(renderer, Rec_destFondo);

		if (contador == 0)
		{
			Rec_destFlecha.x = 280;
			Rec_destFlecha.y = 430;
			texturas[6]->render(renderer, Rec_destFlecha);
		}

		else
		{
			Rec_destFlecha.x = 280;
			Rec_destFlecha.y = 540;
			texturas[6]->render(renderer, Rec_destFlecha);
		}

		SDL_RenderPresent(renderer);
	}
	return contador;
}