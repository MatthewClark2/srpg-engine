#include "sdl.h"
#include "exercises.h"
#include "setup.h"

int clipped_texture() {
  GraphicalContext ctx;

  SDL_Surface* surface = load_media("images/circles.png");
  SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xff, 0xff));

  Texture sheet(ctx, surface);

  SDL_Rect clips[4] = {{0,   0,   100, 100},
                       {100, 0,   100, 100},
                       {0,   100, 100, 100},
                       {100, 100, 100, 100}};

  bool done = false;
  SDL_Event e;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    SDL_SetRenderDrawColor(ctx.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(ctx.renderer);

    sheet.draw_clip(ctx, 0, 0, clips[0]);
    sheet.draw_clip(ctx, WIDTH - clips[1].w, 0, clips[1]);
    sheet.draw_clip(ctx, 0, HEIGHT - clips[2].h, clips[2]);
    sheet.draw_clip(ctx, WIDTH - clips[3].w, HEIGHT - clips[3].h, clips[3]);

    SDL_RenderPresent(ctx.renderer);
  }

  return 0;
}