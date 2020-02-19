#ifndef SRPG_ENGINE_SETUP_H
#define SRPG_ENGINE_SETUP_H

#include "sdl.h"
#include <string>
#include <vector>

class GraphicalContext {
 public:
  SDL_Renderer* renderer;
  SDL_Window* window;
  SDL_Surface* window_surface;

  GraphicalContext();

  explicit GraphicalContext(int renderer_flags);

  GraphicalContext(const GraphicalContext& o) = delete;

  ~GraphicalContext();
};

class Texture {
 public:
  const int width_;
  const int height_;

  Texture(GraphicalContext& ctx, const std::string& file);
  Texture(GraphicalContext& ctx, SDL_Surface* surface);

  Texture(const Texture& o) = delete;
  Texture(Texture&& moved) noexcept;

  void color(int r, int g, int b);

  void set_blend_mode(SDL_BlendMode mode);
  void alpha(int a);

  void draw(GraphicalContext& ctx, int x, int y);

  void draw(GraphicalContext& ctx, const SDL_Rect& dest);

  void draw(GraphicalContext& ctx, int x, int y, const SDL_Rect& clip);

  void draw(GraphicalContext& ctx, const SDL_Rect& clip, const SDL_Rect& dest);

  ~Texture();

 private:
  SDL_Texture* texture_;
};

class SpriteSheet {
 public:
  const int sprite_width_, sprite_height_;

  SpriteSheet(Texture&& texture, int sprite_width, int sprite_height);

  int n_sprites() const;

  SDL_Rect operator[](size_t loc) const;

  void draw(GraphicalContext& ctx, int x, int y, int idx);

  void draw(GraphicalContext& ctx, int x, int y, int scale, int idx);

 private:
  Texture t;
  std::vector<SDL_Rect> sprites;
};

SDL_Surface* optimize(SDL_Surface* window_surface, SDL_Surface* in);

SDL_Window* init();
SDL_Renderer* get_renderer(SDL_Window* window, int renderer_flags);

SDL_Surface* load_media(const std::string& file);
SDL_Texture* load_media(const std::string& file, SDL_Renderer* renderer);

void close(SDL_Window* window, size_t n_surfaces, SDL_Surface** surfaces);

#endif //SRPG_ENGINE_SETUP_H
