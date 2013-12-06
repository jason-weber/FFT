#include "Plot.h"

Plot::Plot(int x, int y, float deltaX, int width, int height, std::vector<std::complex<float>>* nums, std::string xAxis, std::string yAxis, int xtext_width, int xtext_height, int ytext_width, int ytext_height){
	std::vector<float>* yValues = new std::vector<float>();
	for(unsigned int i = 0; i < nums->size(); i++){
		yValues->push_back(std::sqrtf(nums->at(i).real() * nums->at(i).real() + nums->at(i).imag() * nums->at(i).imag()));
	}

	this->yValues = yValues;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->deltaX = deltaX;
	this->maxX = (nums->size() - 1) * deltaX;
	this->maxY = *std::max_element(yValues->begin(), yValues->end());
	this->xAxis = xAxis;
	this->yAxis =yAxis;
	this->xtext_width = xtext_width;
	this->xtext_height = xtext_height;
	this->ytext_width = ytext_width;
	this->ytext_height = ytext_height;
}

Plot::Plot(int x, int y, float deltaX, int width, int height, std::vector<float>* nums, std::string xAxis, std::string yAxis, int xtext_width, int xtext_height, int ytext_width, int ytext_height){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->deltaX = deltaX;
	this->maxX = (nums->size() - 1) * deltaX;
	this->maxY = *std::max_element(nums->begin(), nums->end());
	this->yValues = nums;
	this->xAxis = xAxis;
	this->yAxis = yAxis;
	this->xtext_width = xtext_width;
	this->xtext_height = xtext_height;
	this->ytext_width = ytext_width;
	this->ytext_height = ytext_height;
}

void Plot::drawPlot(SDL_Texture* text, SDL_Renderer* renderer, TTF_Font* font){
	this->drawAxes(renderer);
	this->drawMaxValues(renderer, font);
	this->drawGraph(renderer);
	this->drawAxesLabels(renderer, font);	
}

void Plot::drawAxes(SDL_Renderer* renderer){
	SDL_RenderDrawLine(renderer, x, y, x, y + height);
	SDL_RenderDrawLine(renderer, x, y + height, x + width, y + height);
}

void Plot::drawMaxValues(SDL_Renderer* renderer, TTF_Font* font){
	//Draw max values on axes
	//Draw Y
	SDL_Color color = {0, 0, 0, SDL_ALPHA_OPAQUE};
	std::ostringstream str;
	str << std::setprecision(2) << this->maxY;
	std::string temp = str.str();
	SDL_Surface* surf = TTF_RenderText_Blended(font, temp.c_str(), color);
	SDL_Rect pos = {x - 50, y, 30, 15};
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf); 
	SDL_RenderCopy(renderer, texture, NULL, &pos);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);

	//Draw X
	str.clear();
	str.str("");
	str << std::setprecision(2) << this->maxX;
	temp = str.str();
	surf = TTF_RenderText_Blended(font, temp.c_str(), color);
	pos.x = x + width + 5;
	pos.y = y + height + 5;
	texture = SDL_CreateTextureFromSurface(renderer, surf); 
	SDL_RenderCopy(renderer, texture, NULL, &pos);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

void Plot::drawGraph(SDL_Renderer* renderer){
	SDL_RenderDrawLine(renderer, x - 5, y, x + 5, y);
	SDL_RenderDrawLine(renderer, x - 5, y + (float)(height / 5), x + 5, y + (float)(height / 5));
	SDL_RenderDrawLine(renderer, x - 5, y + (float)(height / 5) * 2, x + 5, y + (float)(height / 5) * 2);
	SDL_RenderDrawLine(renderer, x - 5, y + (float)(height / 5) * 3, x + 5, y + (float)(height / 5) * 3);
	SDL_RenderDrawLine(renderer, x - 5, y + (float)(height / 5) * 4, x + 5, y + (float)(height / 5) * 4);
	for(unsigned int i = 0; i < yValues->size() - 1; i++){
		//Draw next plot line
		int x1 = (int)((i * deltaX / this->maxX) * this->width + x);
		int y1 = (int)((y + this->height) - (yValues->at(i) / this->maxY) * this->height);
		int x2 = (int)(((i + 1) * deltaX / this->maxX) * this->width + x);
		int y2 = (int)((y + this->height) - (yValues->at(i + 1) / this->maxY) * this->height);
		SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

		//Draw tick marks on x axis
		SDL_RenderDrawLine(renderer, x2, y + height - 5, x2, y + height + 5);
	}

}

void Plot::drawAxesLabels(SDL_Renderer* renderer, TTF_Font* font){
	//Draw axes labels
	SDL_Color color = {0, 0, 0, SDL_ALPHA_OPAQUE};
	SDL_Surface* surf = TTF_RenderText_Solid(font, xAxis.c_str(), color);
	SDL_Rect pos;
	pos.x = x + width / 4;
	pos.y = y + height + 20;
	pos.w = xtext_width;
	pos.h = xtext_height;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf); 
	SDL_RenderCopy(renderer, texture, NULL, &pos);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
	surf = TTF_RenderText_Solid(font, yAxis.c_str(), color);
	pos.x = 0;
	pos.y = y + height / 2;
	pos.h = ytext_height;
	pos.w = ytext_width;
	texture = SDL_CreateTextureFromSurface(renderer, surf); 
	SDL_RenderCopy(renderer, texture, NULL, &pos);
	SDL_FreeSurface(surf);
}