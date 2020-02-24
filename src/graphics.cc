#include <iostream>

#include "graphics.hh"
#include "error.hh"

namespace srpg {

static SDL_Surface* load_surface(const std::string& filename, int& width, int& height) {
  SDL_Surface* surface = IMG_Load(filename.c_str());

  if (surface == nullptr) {
    // Use IMG_GetError().
    throw err::NoSuchFileError(filename);
  }

  width = surface->w;
  height = surface->h;

  return surface;
}

static SDL_Texture* load_texture(SDLContext& ctx, const std::string& filename, int& width, int& height) {
  auto surface = load_surface(filename, width, height);
  auto texture = SDL_CreateTextureFromSurface(&ctx.renderer(), surface);

  if (texture == nullptr) {
    throw err::GenericError(SDL_GetError());
  }

  SDL_FreeSurface(surface);

  return texture;
}

SDLContext::SDLContext(size_t width, size_t height, int flags) : width_(width), height_(height), frame_(0) {
  // Init SDL.
  // if (!SDL_Init(SDL_INIT_EVERYTHING)) {
  // TODO(matthew-c21): There seems to be an issue when initializing some components, mostly from udev.
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw err::GenericError(SDL_GetError());
  }

  // Init SDL_Image.
  if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
    throw err::GenericError(SDL_GetError());
  }

  // Get the window.
  window_ = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

  if (window_ == nullptr) {
    throw err::GenericError(SDL_GetError());
  }

  // Set up the default renderer.
  renderer_ = SDL_CreateRenderer(window_, -1, flags);

  if (renderer_ == nullptr) {
    throw err::GenericError(SDL_GetError());
  }
}

SDLContext::~SDLContext() {
  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

SDL_Renderer& SDLContext::renderer() {
  return *renderer_;
}

SDL_Window& SDLContext::window() {
  return *window_;
}

int SDLContext::width() const {
  return width_;
}

int SDLContext::height() const {
  return height_;
}

size_t SDLContext::frame() const {
  return frame_;
}

void SDLContext::clear() {
  SDL_RenderClear(renderer_);
}

void SDLContext::clear(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}

void SDLContext::update() {
  SDL_RenderPresent(renderer_);
}

void SDLContext::draw(SDL_Texture& texture, const SDL_Rect& source, const SDL_Rect& dest) {
  SDL_RenderCopy(renderer_, &texture, &source, &dest);
}

SpriteSheet::SpriteSheet(SDLContext& ctx, const std::string& filename, int sprite_width, int sprite_height) {
  texture_ = load_texture(ctx, filename, width_, height_);

  int n_sprites = width_ / sprite_width * (height_ / sprite_height);

  int x_pos = 0, y_pos = 0;

  for (int i = 0; i < n_sprites; ++i) {
    x_pos = i * sprite_width % width_;
    y_pos = i * sprite_width / width_ * sprite_height;
    sprites_.push_back({x_pos, y_pos, sprite_width, sprite_height});
  }
}

SpriteSheet::SpriteSheet(SDLContext& ctx, const std::string& filename, std::vector<SDL_Rect> sprites) {
  texture_ = load_texture(ctx, filename, width_, height_);
  sprites_ = std::move(sprites);
}

SpriteSheet::~SpriteSheet() {
  SDL_DestroyTexture(texture_);
}

int SpriteSheet::n_sprites() const {
  return sprites_.size();
}

SDL_Rect SpriteSheet::operator[](size_t loc) const {
  return sprites_[loc % sprites_.size()];
}

size_t SpriteSheet::width_at(size_t loc) const {
  return (*this)[loc].w;
}

size_t SpriteSheet::height_at(size_t loc) const {
  return (*this)[loc].h;
}

SDL_Texture& SpriteSheet::texture() {
  return *texture_;
}

SDL_Rect scale(const SDL_Rect& base, double factor) {
  int w = static_cast<int>(base.w * factor);
  int h = static_cast<int>(base.h * factor);
  return {base.x, base.y, w, h};
}

} // namespace srpg