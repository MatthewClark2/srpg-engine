#include "exercises.h"
#include "setup.h"
#include "sdl.h"

int color_keying_and_layered_textures() {
  GraphicalContext ctx;

  Texture background_texture(ctx, "images/nature.jpeg");

  // Since the guy has a white background, we want to remove it by color keying.
  SDL_Surface* man = load_media("images/man.jpeg");

  // Color key the image. SDL_TRUE makes it so that the color is keyed out. The color is the color to be keyed.
  // The result is imperfect, but good enough for our purposes right now.
  SDL_SetColorKey(man, SDL_TRUE, SDL_MapRGB(man->format, 0xff, 0xff, 0xff));

  Texture foreground_texture(ctx, man);

  bool done = false;
  SDL_Event e;

  int min_left = 0;
  int max_left = WIDTH - 240;

  int current_pos = min_left;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    SDL_Rect quad = {current_pos, HEIGHT / 2, 160, 80};
    background_texture.draw(ctx, 0, 0);
    foreground_texture.draw_scaled(ctx, quad);

    SDL_RenderPresent(ctx.renderer);

    current_pos = (current_pos + 1) % max_left;

    // Try to slow down the monster that we've made.
    SDL_Delay(5);
  }

  return 0;
}