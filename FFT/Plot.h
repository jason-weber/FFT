#ifndef PLOT_H
#define PLOT_H
#include "SDL.h"
#include <vector>
#include <complex>
#include <algorithm>
#include "SDL_ttf.h"

class Plot{
public:
	Plot(int x, int y, float deltaX, int width, int height, std::vector<std::complex<float>>* nums, std::string xAxis, std::string yAxis, int xtext_width, int xtext_height, int ytext_width, int ytext_height);
	Plot(int x, int y, float deltaX, int width, int height, std::vector<float>* nums, std::string xAxis, std::string yAxis, int xtext_width, int xtext_height, int ytext_width, int ytext_height);

	int x;
	int y;
	int width;
	int height;
	float deltaX;
	float maxX;
	float maxY;
	std::vector<float>* yValues;
	TTF_Font* font;

	int xtext_width;
	int xtext_height;
	int ytext_width;
	int ytext_height;

	std::string xAxis;
	std::string yAxis;

	void drawPlot(SDL_Texture* text, SDL_Renderer* renderer, TTF_Font* font);
};

#endif