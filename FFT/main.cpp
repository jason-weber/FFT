#include "Wave.h"
#include "SignalGraph.h"
#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[]){
	//Get initial input to build graphs
	std::cout << "How many input values are there (remember it must be a power of 2): ";
	int size;
	std::cin >> size;
	std::cout << "\nWhat is the sampling length in seconds? ";
	float interval;
	std::cin >> interval;

	//Enter amplitude values for number of samples 
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
	//Show general wave info
	std::cout << "\n" << wave->toString() << std::endl;

	//Initialize graph and draw it
	SignalGraph* graph = new SignalGraph(wave, 800, 600);
	if(graph->init()){
		graph->drawSignal();
		bool quit = false;
		SDL_Event e;
		SDL_RenderPresent(graph->renderer);

		//Keep window open until user exits out
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

