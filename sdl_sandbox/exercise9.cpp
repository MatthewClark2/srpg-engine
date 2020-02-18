#include "sdl.h"
#include "exercises.h"
#include "setup.h"

int viewports() {
  GraphicalContext g_ctx;

  // Now we need a texture.
  SDL_Texture* texture = load_media("images/nice-thighs.png", g_ctx.renderer);

  SDL_Rect top_left_viewport = {0, 0, WIDTH / 2, HEIGHT / 2};
  SDL_Rect top_right_viewport = {WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2};
  SDL_Rect bottom_viewport = {0, HEIGHT / 2, WIDTH, HEIGHT / 2};

  // To render to a viewport, we first set the viewport, then render as normal.
  SDL_RenderSetViewport(g_ctx.renderer, &top_left_viewport);
  SDL_RenderCopy(g_ctx.renderer, texture, nullptr, nullptr);

  SDL_RenderSetViewport(g_ctx.renderer, &top_right_viewport);
  SDL_RenderCopy(g_ctx.renderer, texture, nullptr, nullptr);

  SDL_RenderSetViewport(g_ctx.renderer, &bottom_viewport);
  SDL_RenderCopy(g_ctx.renderer, texture, nullptr, nullptr);

  SDL_RenderPresent(g_ctx.renderer);

  SDL_Delay(5'000);

  SDL_DestroyTexture(texture);

  return 0;
}