#include <iostream>
#include <string>
#include "setup.h"
#include "sdl.h"
#include "exercises.h"

extern "C" {
#include <SDL_image.h>
}

SDL_Surface* optimize(SDL_Surface* window_surface, SDL_Surface* in) {
  SDL_Surface* opt = SDL_ConvertSurface(in, window_surface->format, 0);

  if (opt == nullptr) {
    std::cerr << "Unable to optimize surface." << std::endl;
    std::exit(-5);
  }

  SDL_FreeSurface(in);

  return opt;
}

SDL_Window* init() {
  SDL_Window* window = nullptr;

  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "Could not initialize SDL. Exiting." << std::endl;
    std::exit(-1);
  }

  window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Could not open SDL window. Exiting." << std::endl;
    std::exit(-2);
  }

  return window;
}

// The return value of this function must be manually freed with SDL_FreeSurface().
SDL_Surface* load_media(const std::string& file) {
  SDL_Surface* surface = nullptr;  // SDL_LoadBMP(file.c_str());
  surface = IMG_Load(file.c_str());

  if (surface == nullptr) {
    std::cerr << "Unable to load file: '" << file << "'. " << IMG_GetError() << std::endl;
    std::exit(-3);
  }

  return surface;
}

void close(SDL_Window* window, size_t n_surfaces, SDL_Surface** surfaces) {
  for (size_t i = 0; i < n_surfaces; ++i) {
    SDL_FreeSurface(surfaces[i]);
  }

  // Destroy the window. This probably also invalidates its surface.
  SDL_DestroyWindow(window);

  // Quit out.
  SDL_Quit();
}