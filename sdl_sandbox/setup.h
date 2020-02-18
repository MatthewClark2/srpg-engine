#ifndef SRPG_ENGINE_SETUP_H
#define SRPG_ENGINE_SETUP_H

#include "sdl.h"
#include <string>

SDL_Window* init();

SDL_Surface* load_media(const std::string& file);

void close(SDL_Window* window, size_t n_surfaces, ...);

#endif //SRPG_ENGINE_SETUP_H
