#include"SDL.h"
#include<string>

using namespace std;

class	Texture {
private:
	SDL_Texture*	texture = nullptr;
	int	w = 0;	
	int	h = 0;	
	int fw = 0;	
	int fh = 0;	
	int NumRows;
	int NumCols;
public:
	Texture();
	~Texture();

	bool	load(SDL_Renderer*	renderer, string	filename, int numRows = 1, int numCols = 1);
	void	render(SDL_Renderer*	renderer, const SDL_Rect&	rect, SDL_RendererFlip	flip = SDL_FLIP_NONE);
	void	renderFrame(SDL_Renderer*	renderer, const SDL_Rect&	destRect, int	row, int	col, SDL_RendererFlip	flip = SDL_FLIP_NONE);
	
	int getW() { return w; };
	int getH() { return h; };
	int getFrameW() { return fw; };
	int getFrameH() { return fh; };
	int getCols() { return NumCols; };
};