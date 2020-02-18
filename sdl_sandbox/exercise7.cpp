#include <iostream>
#include "sdl.h"
#include "exercises.h"
#include "setup.h"

int texturing() {
  SDL_Window* window = init();
  SDL_Renderer* window_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Texture* texture = load_media("images/nice-thighs.png", window_renderer);

  if (window_renderer == nullptr) {
    std::cerr << "Skidaddle, skidoodle, renderers are not noodles." << std::endl;
    std::exit(-8);
  }

  SDL_SetRenderDrawColor(window_renderer, 0xff, 0xff, 0xff, 0xff);

  bool done = false;
  SDL_Event e;

  while (!done) {
    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
      //User requests quit
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    // Clear the screen.
    SDL_RenderClear(window_renderer);

    // Render the texture to the screen.
    SDL_RenderCopy(window_renderer, texture, nullptr, nullptr);

    // Update the screen.
    SDL_RenderPresent(window_renderer);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(window_renderer);
  SDL_DestroyWindow(window);
  // close(window, 0, nullptr);

  return 0;
}