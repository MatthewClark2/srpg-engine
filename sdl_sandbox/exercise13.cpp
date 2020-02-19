#include <array>
#include "sdl.h"
#include "exercises.h"
#include "setup.h"

int animations_and_vsync() {
  GraphicalContext ctx(SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  Texture texture(ctx, "images/emerald-walk-sprites.png");
  SpriteSheet anim(std::move(texture), 16, 22);

  // This is a hack since the cut run cycle includes the walk cycle interspersed.
  std::array<int, 4> positions = {1, 0, 5, 0};

  // Increase sprite size.
  int scale = 3;

  bool done = false;
  SDL_Event e;

  size_t i = 0;

  while (!done) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        done = true;
      }
    }

    // Clear the screen.
    SDL_SetRenderDrawColor(ctx.renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(ctx.renderer);

    // Draw the current frame of animation and mark the next one.
    anim.draw(ctx, (WIDTH - anim.sprite_width_ * scale) / 2, (HEIGHT - anim.sprite_height_ * scale) / 2,
              scale, positions[i]);
    i = (i + 1) % positions.size();

    // Display and wait.
    SDL_RenderPresent(ctx.renderer);

    SDL_Delay(200);
  }

  return 0;
}