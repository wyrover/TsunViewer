#include "render.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <string>

void render(const std::string& title, int width, int height, const std::string& path)
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* image = nullptr;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Mysterious unhandled SDL init problem!" << std::endl;
		return;
	}
	
	window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	image = IMG_LoadTexture(renderer, path.c_str());
	SDL_Rect texture; 
	texture.x = 0; 
	texture.y = 0; 
	texture.w = width; 
	texture.h = height; 
	
	SDL_Event event;		
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
				
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}
		}
		
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, image, NULL, &texture);
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
