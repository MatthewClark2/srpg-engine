#ifndef SRPG_ENGINE_SETUP_H
#define SRPG_ENGINE_SETUP_H

#include "sdl.h"
#include <string>
#include <optional>

class GraphicalContext {
 public:
  SDL_Renderer* renderer;
  SDL_Window* window;
  SDL_Surface* window_surface;

  GraphicalContext();

  GraphicalContext(const GraphicalContext& o) = delete;

  ~GraphicalContext();
};

SDL_Surface* optimize(SDL_Surface* window_surface, SDL_Surface* in);

SDL_Window* init();
SDL_Renderer* get_renderer(SDL_Window* window);

SDL_Surface* load_media(const std::string& file);
SDL_Texture* load_media(const std::string& file, SDL_Renderer* renderer);

void close(SDL_Window* window, size_t n_surfaces, SDL_Surface** surfaces);

#endif //SRPG_ENGINE_SETUP_H
