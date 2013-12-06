#ifndef SIGNALGRAPH_H
#define SIGNALGRAPH_H

#include "Wave.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include "Plot.h"

#define TIMEDOMAINGRAPH_X 100
#define TIMEDOMAINGRAPH_Y 50
#define FFTGRAPH_X 100
#define FFTGRAPH_Y 300
#define GRAPH_HEIGHT 200
#define GRAPH_WIDTH 500

class SignalGraph{
public: 
	SignalGraph(Wave* wave, int width, int height);
	SDL_Window* window;
	SDL_Surface* screenSurface;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int width;
	int height;

	Wave* wave;
	Plot* timePlot;
	Plot* frequencyPlot;

	TTF_Font* font;
	
	bool init();
	void drawSignal();
	void close();
private:

};
#endif