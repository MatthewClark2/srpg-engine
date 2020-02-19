#include "sdl.h"
#include "setup.h"
#include "exercises.h"

int color_modulation() {
  GraphicalContext ctx;
  Texture texture(ctx, "images/colormod.png");

  // You can set the color modulation of a texture freely, which is kind of nice.

  int r = 0, b = 0, g = 0;

  bool done = false;
  SDL_Event e;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      } else if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_q:
            r += 32;
            break;
          case SDLK_w:
            b += 32;
            break;
          case SDLK_e:
            g += 32;
            break;
          case SDLK_a:
            r -= 32;
            break;
          case SDLK_s:
            b -= 32;
            break;
          case SDLK_d:
            g -= 32;
            break;
          case SDLK_r:
            r = b = g = 0;
            break;
        }
      }

      SDL_SetRenderDrawColor(ctx.renderer, 0xff, 0xff, 0xff, 0xff);
      SDL_RenderClear(ctx.renderer);

      texture.color(r, g, b);

      texture.draw(ctx, 0, 0);

      SDL_RenderPresent(ctx.renderer);
    }
  }
  return 0;
}