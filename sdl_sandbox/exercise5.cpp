#include <iostream>
#include "sdl.h"
#include "exercises.h"
#include "setup.h"

int optimized_images() {
  SDL_Window* window = init();
  SDL_Surface* window_surface = SDL_GetWindowSurface(window);
  SDL_Surface* img_surface = optimize(window_surface, load_media("images/nice-thighs.png"));

  SDL_Rect stretch_rect;
  stretch_rect.x = 0;
  stretch_rect.y = 0;
  stretch_rect.h = HEIGHT;
  stretch_rect.w = WIDTH;

  bool done = false;
  SDL_Event e;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, 0xff, 0xff, 0xff));
    SDL_BlitScaled(img_surface, nullptr, window_surface, &stretch_rect);
    SDL_UpdateWindowSurface(window);
  }

  close(window, 1, &img_surface);
  return 0;
}