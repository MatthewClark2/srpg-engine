#ifndef SRPG_ENGINE_GRAPHICS_HH
#define SRPG_ENGINE_GRAPHICS_HH

#include <string>
#include <memory>
#include <vector>
#include "sdl.hh"

namespace srpg {

class SDLContext {
 private:
  SDL_Renderer* renderer_;
  SDL_Window* window_;
  int width_, height_;
  size_t frame_;

 public:
  SDLContext(size_t width, size_t height, int flags = SDL_RENDERER_ACCELERATED);

  SDLContext(const SDLContext& copy) = delete;

  ~SDLContext();

  SDL_Renderer& renderer();

  SDL_Window& window();

  int width() const;

  int height() const;

  size_t frame() const;

  void clear();

  void clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

  void draw(SDL_Texture& texture, const SDL_Rect& source, const SDL_Rect& dest);

  void update();
};

class SpriteSheet {
 public:
  SpriteSheet(SDLContext& ctx, const std::string& filename, int sprite_width, int sprite_height);

  SpriteSheet(SDLContext& ctx, const std::string& filename, std::vector<SDL_Rect> sprites);

  ~SpriteSheet();

  int n_sprites() const;

  SDL_Rect operator[](size_t loc) const;

  size_t width_at(size_t loc) const;

  size_t height_at(size_t loc) const;

  SDL_Texture& texture();

 private:
  SDL_Texture* texture_;
  std::vector<SDL_Rect> sprites_;

  // Texture dimensions.
  int width_, height_;
};

SDL_Rect scale(const SDL_Rect& base, double factor);

template<typename T>
class Entity {
 private:
  const std::string name_;
  std::unique_ptr<T> val_;
  SpriteSheet& sprites_;
  size_t curr_pos_;
  const size_t refresh_rate_;
  size_t cycle_length_;

 public:
  Entity(std::string name, T* value, SpriteSheet& sheet, size_t cycle_length, size_t refresh_rate = 12)
      : name_(std::move(name)), val_(value), sprites_(sheet), curr_pos_(0), refresh_rate_(refresh_rate),
      cycle_length_(cycle_length) {}

  const std::string& name() const { return name_; }

  const T& val() const { return val_; }

  T& val() { return val_; }

  size_t curr_pos() const { return curr_pos_; }

  void curr_pos(size_t new_pos) { curr_pos_ = new_pos % sprites_.n_sprites(); }

  void set_new_cycle(size_t new_pos, size_t new_cycle_len) {
    curr_pos(new_pos);
    cycle_length_ = new_cycle_len;
  }

  const SpriteSheet& sprites() const { return sprites_; }

  void draw(SDLContext& ctx, int x, int y) {
    draw(ctx, x, y, curr_pos_);
  }

  void draw(SDLContext& ctx, const SDL_Rect& dest) {
    draw(ctx, dest, curr_pos_);
  }

  void draw(SDLContext& ctx, int x, int y, size_t idx) {
    auto r = sprites_[idx];
    draw(ctx, {x, y, r.w, r.h}, idx);
  }

  void draw(SDLContext& ctx, const SDL_Rect& dest, size_t idx) {
    ctx.draw(sprites_.texture(), sprites_[idx], dest);
  }
};


}  // namespace srpg

#endif //SRPG_ENGINE_GRAPHICS_HH
