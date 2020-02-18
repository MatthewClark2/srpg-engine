#include <iostream>
#include "setup.h"
#include "sdl.h"
#include "exercises.h"

enum KeyImages {
  kDefault,
  kLeft,
  kRight,
  kUp,
  kDown,
  kTotal
};

static SDL_Surface* images[kTotal] = {nullptr, nullptr, nullptr, nullptr, nullptr};
static std::string files[kTotal] = {"images/nice-thighs.png", "images/kleft.png", "images/kright.jpeg",
                                    "images/kup.jpeg", "images/kdown.jpeg"};

void load_media() {
  for (int i = 0; i < kTotal; ++i) {
    images[i] = IMG_Load(files[i].c_str());

    if (images[i] == nullptr) {
      std::cerr << IMG_GetError() << std::endl;
      std::exit(-4);
    }
  }
}

int swap_images() {
  load_media();
  SDL_Window* window = init();
  SDL_Surface* window_surface = SDL_GetWindowSurface(window);
  SDL_Surface* current = images[kDefault];

  bool done = false;
  SDL_Event e;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_UP:
            current = images[kUp];
            break;
          case SDLK_DOWN:
            current = images[kDown];
            break;
          case SDLK_LEFT:
            current = images[kLeft];
            break;
          case SDLK_RIGHT:
            current = images[kRight];
            break;
        }
      }
    }

    SDL_FillRect(window_surface, nullptr, SDL_MapRGB(window_surface->format, 0xff, 0xff, 0xff));
    SDL_BlitSurface(current, nullptr, window_surface, nullptr);
    SDL_UpdateWindowSurface(window);
  }

  close(window, kTotal, images);

  return 0;
}