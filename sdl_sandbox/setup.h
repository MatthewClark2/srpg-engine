#ifndef SRPG_ENGINE_SETUP_H
#define SRPG_ENGINE_SETUP_H

#include "sdl.h"
#include <string>

SDL_Surface* optimize(SDL_Surface* window_surface, SDL_Surface* in);

SDL_Window* init();

SDL_Surface* load_media(const std::string& file);
SDL_Texture* load_media(const std::string& file, SDL_Renderer* renderer);

void close(SDL_Window* window, size_t n_surfaces, SDL_Surface** surfaces);

#endif //SRPG_ENGINE_SETUP_H
