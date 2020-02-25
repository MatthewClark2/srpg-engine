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
    SDLContext ctx(1280, 960, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SpriteSheet sprites(ctx, "images/chipset01.jpg", 16, 16);

    Tile pl(Terrain::PLAIN, 7);
    Tile tr(Terrain::LIGHT_DEFENSIVE, 24 * 15 + 21);
    Tile ft(Terrain::HEAVY_DEFENSIVE, 24 * 12 + 23);
    Tile wt(Terrain::OCEAN, 24 * 4 + 0);
    Tile sz(Terrain::THRONE, 24 * 8 + 15);
    Tile it(Terrain::IMPASSABLE, 24 * 10 + 22);

    std::vector<Tile> tiles = {pl, pl, pl, wt, pl, pl, pl, pl, sz, pl,
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

    while (!done) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) done = true;
      }

      // idx %= sprites.n_sprites();

      // ctx.draw(sprites.texture(), sprites[idx], {0, 0, 480, 480});

       map.draw(ctx);
//      map.draw(ctx, 5, 5);

      ctx.update();
    }
  } catch (const err::GenericError& e) {
    std::cerr << e.what() << "\n";
    std::cerr << IMG_GetError() << "\n";
    std::cerr << SDL_GetError() << "\n";
    std::exit(-1);
  }
}
