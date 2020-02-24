#include <iostream>
#include "graphics.hh"
#include "map.hh"
#include "sdl.hh"
#include "error.hh"

using namespace srpg;

int main() {
//
//  SDL_Init(SDL_INIT_AUDIO);
//  std::cout << SDL_GetError();
//  SDL_Quit();
//
//  return 0;


  try {
    SDLContext ctx(480, 480, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SpriteSheet sprites(ctx, "images/chipset01.jpg", 16, 16);

    Tile pl(Terrain::PLAIN, 0);
    Tile tr(Terrain::LIGHT_DEFENSIVE, 1);
    Tile ft(Terrain::HEAVY_DEFENSIVE, 2);
    Tile wt(Terrain::OCEAN, 3);
    Tile sz(Terrain::THRONE, 4);
    Tile it(Terrain::IMPASSABLE, 5);

    std::vector<Tile> tiles = {pl, pl, pl, wt, pl, pl, pl, pl, pl, pl,
                               pl, it, pl, wt, pl, pl, pl, pl, pl, pl,
                               pl, pl, pl, wt, pl, pl, pl, pl, pl, pl,
                               pl, pl, pl, wt, pl, pl, pl, pl, pl, pl,
                               wt, pl, wt, wt, pl, pl, ft, pl, pl, ft,
                               pl, pl, pl, pl, pl, pl, pl, pl, pl, pl,
                               pl, pl, pl, pl, tr, pl, pl, pl, pl, pl,
                               pl, pl, tr, tr, tr, pl, pl, pl, pl, pl,
                               pl, pl, pl, tr, tr, pl, pl, pl, pl, pl,
                               pl, pl, pl, pl, pl, pl, pl, pl, pl, pl};

    TiledMap map(tiles, 10, sprites, 10, 10);

    SDL_Event e;
    bool done = false;
    size_t idx = 0;

    while (!done) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) done = true;
        else if (e.type == SDL_KEYDOWN) {
          switch (e.key.keysym.sym) {
            case SDLK_LEFT:
              --idx;
              break;
            case SDLK_RIGHT:
              ++idx;
              break;
          }
        }
      }

      idx %= sprites.n_sprites();

      ctx.draw(sprites.texture(), sprites[idx], {0, 0, 480, 480});

      ctx.update();
    }
  } catch (const err::GenericError& e) {
    std::cerr << e.what() << "\n";
    std::cerr << IMG_GetError() << "\n";
    std::cerr << SDL_GetError() << "\n";
    std::exit(-1);
  }
}
