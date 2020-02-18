#include "exercises.h"
#include "sdl.h"
#include "setup.h"

int stay_open() {
  SDL_Window* window = init();
  SDL_Surface* window_surface = SDL_GetWindowSurface(window);
  SDL_Surface* image_surface = load_media("images/nice-thighs.png");

  SDL_Event e;
  bool should_quit = false;

  while (!should_quit) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        should_quit = true;
      }
    }

    SDL_BlitSurface(image_surface, nullptr, window_surface, nullptr);
    SDL_UpdateWindowSurface(window);
  }

  close(window, 1, image_surface);

  return 0;
}

