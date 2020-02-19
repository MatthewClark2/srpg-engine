#include <iostream>
#include "sdl.h"
#include "setup.h"
#include "exercises.h"

int color_modulation() {
  GraphicalContext ctx;
  Texture texture(ctx, "images/colormod.png");

  Texture foreground(ctx, "images/man.jpeg");

  // Required to be able to modify alpha channel.
  foreground.set_blend_mode(SDL_BLENDMODE_BLEND);

  // Used to scale the foreground texture.
  SDL_Rect scale = {(WIDTH - 240) / 2, (HEIGHT - 240) / 2, 240, 240};

  // You can set the color modulation of a texture freely, which is kind of nice.
  // You can also set alpha values, which will be done on the foreground.

  int r = 0, b = 0, g = 0, a = 255;

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
          case SDLK_z:
            a += 32;
            break;
          case SDLK_x:
            a -= 32;
            break;
          case SDLK_r:
            r = b = g = 0;
            a = 255;
            break;
        }
      }

      SDL_SetRenderDrawColor(ctx.renderer, 0xff, 0xff, 0xff, 0xff);
      SDL_RenderClear(ctx.renderer);

      texture.color(r, g, b);
      foreground.alpha(a);

      texture.draw(ctx, 0, 0);
      foreground.draw(ctx, scale);

      SDL_RenderPresent(ctx.renderer);

      SDL_Delay(1);
    }
  }
  return 0;
}