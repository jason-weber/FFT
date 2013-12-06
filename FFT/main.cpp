#include "Wave.h"
#include "SignalGraph.h"
#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[]){
	std::cout << "How many input values are there (remember it must be a power of 2): ";
	int size;
	std::cin >> size;
	std::cout << "\nWhat is the sampling length in seconds? ";
	float interval;
	std::cin >> interval;

	Wave::VectorCf* values = new Wave::VectorCf();
	for(int i = 0; i < size; i++){
		std::cout << "Enter the real part of the amplitude: ";
		float real;
		std::cin >> real;

		std::cout << "Enter the imaginary part of the amplitude: ";
		float imaginary;
		std::cin >> imaginary;

		values->push_back(std::complex<float>(real, imaginary));
	}
	
	Wave* wave = new Wave(values, interval); 
	std::cout << "\n" << wave->toString() << std::endl;

	SignalGraph* graph = new SignalGraph(wave, 800, 600);
	if(graph->init()){
		graph->drawSignal();
		bool quit = false;
		SDL_Event e;
		SDL_RenderPresent(graph->renderer);
		while(!quit){
			while(SDL_PollEvent(&e) != 0){
				if(e.type == SDL_QUIT){
					quit = true;
				}
			}
		}
	}

	graph->close();
	return 1;
}

