#include <iostream>
#include <string>
#include "setup.h"
#include "sdl.h"
#include "exercises.h"

extern "C" {
#include <SDL_image.h>
}

SDL_Surface* optimize(SDL_Surface* window_surface, SDL_Surface* in) {
  SDL_Surface* opt = SDL_ConvertSurface(in, window_surface->format, 0);

  if (opt == nullptr) {
    std::cerr << "Unable to optimize surface." << std::endl;
    std::exit(-5);
  }

  SDL_FreeSurface(in);

  return opt;
}

SDL_Window* init() {
  SDL_Window* window = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL. Exiting." << std::endl;
    std::exit(-1);
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    std::cerr << "Could not initialize loading of PNGs." << std::endl;
    std::exit(-6);
  }

  window = SDL_CreateWindow("First Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                            SDL_WINDOW_SHOWN);

  if (!window) {
    std::cerr << "Could not open SDL window. Exiting." << std::endl;
    std::exit(-2);
  }

  return window;
}

// The return value of this function must be manually freed with SDL_FreeSurface().
SDL_Surface* load_media(const std::string& file) {
  SDL_Surface* surface = nullptr;  // SDL_LoadBMP(file.c_str());
  surface = IMG_Load(file.c_str());

  if (surface == nullptr) {
    std::cerr << "Unable to load file: '" << file << "'. " << IMG_GetError() << std::endl;
    std::exit(-3);
  }

  return surface;
}

SDL_Texture* load_media(const std::string& file, SDL_Renderer* renderer) {
  SDL_Texture* texture = nullptr;

  SDL_Surface* loaded_surface = load_media(file);

  texture = SDL_CreateTextureFromSurface(renderer, loaded_surface);

  if (texture == nullptr) {
    std::cerr << "Unable to create texture from surface." << std::endl;
    std::exit(-9);
  }

  SDL_FreeSurface(loaded_surface);

  return texture;
}

void close(SDL_Window* window, size_t n_surfaces, SDL_Surface** surfaces) {
  for (size_t i = 0; i < n_surfaces; ++i) {
    SDL_FreeSurface(surfaces[i]);
  }

  // Destroy the window. This probably also invalidates its surface.
  SDL_DestroyWindow(window);

  // Quit out.
  IMG_Quit();
  SDL_Quit();
}

SDL_Renderer* get_renderer(SDL_Window* window) {
  auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cerr << "Unable to create renderer for window." << std::endl;
    std::exit(-9);
  }

  return renderer;
}

GraphicalContext::GraphicalContext() {
  window = init();
  renderer = get_renderer(window);
  window_surface = SDL_GetWindowSurface(window);
}

GraphicalContext::~GraphicalContext() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();
}

Texture::Texture(GraphicalContext& ctx, const std::string& file) : Texture(ctx, load_media(file)) {}

Texture::Texture(GraphicalContext& ctx, SDL_Surface* surface) : width_(surface->w), height_(surface->h) {
  texture_ = SDL_CreateTextureFromSurface(ctx.renderer, surface);

  if (texture_ == nullptr) {
    std::cerr << "Unable to create texture." << std::endl;
    std::exit(-6);
  }

  SDL_FreeSurface(surface);
}

void Texture::draw(GraphicalContext& ctx, int x, int y) {
  SDL_Rect quad = {x, y, width_, height_};
  draw_scaled(ctx, quad);
}

Texture::~Texture() {
  if (texture_ != nullptr) {
    SDL_DestroyTexture(texture_);
  }
}

void Texture::draw_scaled(GraphicalContext& ctx, SDL_Rect& render_quad) {
  SDL_RenderCopy(ctx.renderer, texture_, nullptr, &render_quad);
}

void Texture::draw_clip(GraphicalContext& ctx, int x, int y, SDL_Rect& clip) {
  SDL_Rect quad = {x, y, clip.w, clip.h};
  SDL_RenderCopy(ctx.renderer, texture_, &clip, &quad);
}

void Texture::color(int r, int g, int b) {
  SDL_SetTextureColorMod(texture_, r, g, b);
}
