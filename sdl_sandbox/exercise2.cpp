#include <iostream>
#include "exercises.h"
#include "setup.h"

int render_image_to_screen() {
  SDL_Window* window = init();
  SDL_Surface* window_surface = SDL_GetWindowSurface(window);

  SDL_Surface* image_surface = load_media("./images/nice-thighs.png");

  SDL_BlitSurface(image_surface, nullptr, window_surface, nullptr);
  SDL_UpdateWindowSurface(window);

  SDL_Delay(2'000);

  close(window, 1, &image_surface);

  return 0;
}
