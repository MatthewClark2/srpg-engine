#include <utility>

#include "map.hh"

namespace srpg {

static void nop(Unit&) {}

Tile::Tile(Terrain terrain, int texture_index) : Tile(terrain, texture_index, nop, nop, nop) {}

Tile::Tile(Terrain terrain, int texture_index, map_script on_turn_start, map_script on_turn_end, map_script on_wait)
    : terrain_(terrain), texture_index_(texture_index),
    on_turn_start_(std::move(on_turn_start)), on_turn_end_(std::move(on_turn_end)), on_wait_(std::move(on_wait)) {
}

Terrain Tile::terrain() const {
  return terrain_;
}

int Tile::texture_index() const {
  return texture_index_;
}

void Tile::on_turn_start(Unit& unit) {
  on_turn_start_(unit);
}

void Tile::on_turn_end(Unit& unit) {
  on_turn_end_(unit);
}

void Tile::on_wait(Unit& unit) {
  on_wait_(unit);
}

TiledMap::TiledMap(std::vector<Tile> tiles, int width, SpriteSheet& sprites, int vp_width, int vp_height)
    : tiles_(std::move(tiles)), width_(width), height_(static_cast<int>(tiles.size()) / width), vp_width_(vp_width),
    vp_height_(vp_height), sprites_(sprites) {
}

void TiledMap::draw(SDLContext& ctx) {
  auto x_scale = static_cast<double>(ctx.width()) / vp_width_;
  auto y_scale = static_cast<double>(ctx.height()) / vp_height_;
  auto factor = std::min(x_scale, y_scale);

  int x, y;
  x = y = 0;

  for (auto const& tile : tiles_) {
    auto clip = sprites_[tile.texture_index()];

    x = (x + clip.w) % ctx.width();
    y = (y + clip.h) / ctx.width();

    auto dest = scale({x, y, clip.w, clip.h}, factor);

    ctx.draw(sprites_.texture(), clip, dest);
  }
}

void TiledMap::draw(SDLContext& ctx, int cursor_x, int cursor_y) {
  auto block_size_w = ctx.width() / vp_width_;
  auto block_size_h = ctx.height() / vp_height_;

  auto y_pos = std::max(0, cursor_y - vp_height_ / 2);

  for (int i = 0; i < vp_height_; ++i) {
    // Calculate the x position on the map.
    auto x_pos = std::max(0, cursor_x + (cursor_y * width_) - vp_width_ / 2);

    for (int j = 0; j < vp_width_; ++j) {
      // Find the appropriate tile and corresponding texture clip.
      auto tile = tiles_[y_pos * width_ + x_pos];
      auto clip = sprites_[tile.texture_index()];

      // Calculate the destination by scaling against the block size.
      SDL_Rect dest = {j * block_size_w, i * block_size_h, block_size_w, block_size_h};

      ctx.draw(sprites_.texture(), clip, dest);

      ++x_pos;
    }

    ++y_pos;
  }
}

const Tile& TiledMap::operator()(int x, int y) const {
  return tiles_[y * width_ + x];
}

int determine_movement_cost(const Unit& unit, Terrain terrain) {
  return 1;
}

int defensive_bonus(Terrain terrain) {
  switch (terrain) {
    case Terrain::THRONE:
      return 3;
    case Terrain::HEAVY_DEFENSIVE:
      return 2;
    case Terrain::LIGHT_DEFENSIVE:
      return 1;
    default:
      return 0;
  }
}

int avoid_bonus(Terrain terrain) {
  switch (terrain) {
    case Terrain::THRONE:
      return 30;
    case Terrain::OCEAN:
    case Terrain::HEAVY_DEFENSIVE:
      return 20;
    case Terrain::LIGHT_DEFENSIVE:
      return 10;
    default:
      return 0;
  }
}

}
