#include "sdl.h"
#include "setup.h"
#include "exercises.h"

int rectangles() {
  GraphicalContext gc;

  SDL_Event e;
  bool done = false;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    // Clear the screen.
    SDL_SetRenderDrawColor(gc.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(gc.renderer);

    // Add a base rectangle to serve as the outline.
    SDL_Rect outline_rect = {WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3};
    SDL_SetRenderDrawColor(gc.renderer, 0, 0xff, 0, 0xff);
    SDL_RenderFillRect(gc.renderer, &outline_rect);

    // Draw a rectangle to the screen.
    SDL_Rect fill_rect = {WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2};
    // Set the draw color for the rectangle.
    SDL_SetRenderDrawColor(gc.renderer, 0xff, 0, 0, 0xff);
    SDL_RenderFillRect(gc.renderer, &fill_rect);

    SDL_RenderPresent(gc.renderer);
  }

  return 0;
}