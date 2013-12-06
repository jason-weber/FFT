#include "SignalGraph.h"

SignalGraph::SignalGraph(Wave* wave, int width, int height){
	this->wave = wave;
	this->width = width;
	this->height = height;

	this->timePlot = new Plot(TIMEDOMAINGRAPH_X, TIMEDOMAINGRAPH_Y, wave->samplingInterval, GRAPH_WIDTH, GRAPH_HEIGHT, wave->timeDomain, "Seconds", "Amplitude", 70, 20, 75, 20);

	std::vector<float>* nums = new std::vector<float>();
	for(unsigned int i = 0; i < wave->magnitudes->size(); i++){
		if(wave->magnitudes->at(i) < 1){
			nums->push_back(0);
		}
		else{
			nums->push_back(20 * log(wave->magnitudes->at(i)));
		}
	}
	this->frequencyPlot = new Plot(FFTGRAPH_X, FFTGRAPH_Y, wave->samplingRate / wave->frequencyDomain->size(), GRAPH_WIDTH, GRAPH_HEIGHT, nums, "Hz", "Decibels", 20, 20, 75, 20);
}

bool SignalGraph::init(){
	bool success = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printf("Could not initialize SDL. SDL_ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else{
		this->window = SDL_CreateWindow("Fast Fourier Transform", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if(window == NULL){
			printf("Could not create window. SDL_ERROR: %s\n", SDL_GetError());
			success = false;
		}
		else {
			this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(renderer == NULL){
				printf("Could not create renderer. SDL_ERROR: %s\n", SDL_GetError()); 
				success = false;
			}
			else{
				screenSurface = SDL_GetWindowSurface(window);
				texture = SDL_CreateTexture(renderer, screenSurface->format->format, SDL_TEXTUREACCESS_STATIC, width, height);
				
			}
		}
		if(TTF_Init() < 0){
			printf("Could not initialize SDL_TTF for text drawing. TTF_Error:  %s\n", TTF_GetError());
			success = false;
		}
		else{
			font = TTF_OpenFont("arial.ttf", 14);
		}
	}
	return success;
}

void SignalGraph::drawSignal(){
	SDL_SetRenderTarget(renderer, texture);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	timePlot->drawPlot(texture, renderer, font);
	frequencyPlot->drawPlot(texture, renderer, font);
}

void SignalGraph::close(){
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_DestroyTexture(texture);
	texture = NULL;
	TTF_CloseFont(font);
	font = NULL;
	SDL_Quit();
}