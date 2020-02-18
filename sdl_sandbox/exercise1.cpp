//
// Created by matthew on 2/17/20.
//

#include "exercises.h"
#include <iostream>

#include "sdl.h"

int white_screen_2_secs() {
  SDL_Window* window = nullptr;

  // The surface contained in the window.
  SDL_Surface* surface = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL. Exiting." << std::endl;
    return -1;
  }

  window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Could not open SDL window. Exiting." << std::endl;
    return -2;
  }

  surface = SDL_GetWindowSurface(window);

  // Fill it white.
  SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));

  // Update the surface.
  SDL_UpdateWindowSurface(window);

  // Wait 2 seconds.
  SDL_Delay(2'000);

  // Destroy the window. This probably also invalidates its surface.
  SDL_DestroyWindow(window);

  // Quit out.
  SDL_Quit();

  return 0;
}

