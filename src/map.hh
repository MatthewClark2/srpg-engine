#ifndef SRPG_ENGINE_MAP_HH
#define SRPG_ENGINE_MAP_HH

#include <functional>

#include "unit.hh"
#include "graphics.hh"

class Texture;

namespace srpg {

typedef std::function<void(Unit&)> map_script;

constexpr int DEFAULT_VIEWPORT_WIDTH = 20;
constexpr int DEFAULT_VIEWPORT_HEIGHT = 20;

enum class Terrain {
  PLAIN,
  LIGHT_DEFENSIVE,
  HEAVY_DEFENSIVE,
  THRONE,
  OCEAN,
  IMPASSABLE,
};

// TODO(matthew-c21): Rendering logic.

/**
 * Internal class used to maintain information about a single square on a map.
 */
class Tile {
 private:
  const Terrain terrain_;
  const int texture_index_;

  map_script on_turn_start_;
  map_script on_turn_end_;
  map_script on_wait_;

 public:
  explicit Tile(Terrain terrain, int texture_index);

  Tile(Terrain terrain, int texture_index, map_script on_turn_start, map_script on_turn_end, map_script on_wait);

  Terrain terrain() const;

  /**
   * Obtain texture information about this tile.
   *
   * This index is largely meaningless on its own, and is mostly for mapping different texture sheets onto a larger
   * srpg::TiledMap.
   * @return
   */
  int texture_index() const;

  void on_turn_start(Unit& unit);

  void on_turn_end(Unit& unit);

  void on_wait(Unit& unit);
};

class TiledMap {
 private:
  std::vector<Tile> tiles_;
  const int width_, height_;
  const int vp_width_, vp_height_;
  SpriteSheet& sprites_;

 public:
  // TODO(matthew-c21): Note - this constructor may lead to undefined behavior if there are more than 2bn tiles given.
  //  However, since this is not a likely scenario, it has been ignored. Fixing it requires changing all related ints to
  //  size_t, which conflicts with SDL's interface.
  TiledMap(std::vector<Tile> tiles, int width, SpriteSheet& sprites,
           int vp_width = DEFAULT_VIEWPORT_WIDTH, int vp_height = DEFAULT_VIEWPORT_HEIGHT);

  /**
   * Draw the entire map to the screen, scaled to fit.
   */
  void draw(SDLContext& ctx);

  /**
   * Draw a part of the map around the provided cursor position. If the cursor position is too close to the edge of the
   * screen, the part around the outside of the map will not be drawn to, and (cx, cy) will still be at the center of
   * the screen. This behavior may change in the future.
   * @param ctx the SDL context in which the map will be drawn.
   * @param cursor_x x position of the central tile.
   * @param cursor_y y position of the central tile.
   */
  void draw(SDLContext& ctx, int cursor_x, int cursor_y);

  /**
   * Matrix like subscript operation to access tiles by index.
   * @param x 0-indexed x position of the tile.
   * @param y 0-indexed y position of the tile.
   * @return the tile at the given position (x, y).
   */
  const Tile& operator()(int x, int y) const;
};

int determine_movement_cost(const Unit& unit, Terrain terrain);

int defensive_bonus(Terrain terrain);

int avoid_bonus(Terrain terrain);

}  // end namespace srpg

#endif //SRPG_ENGINE_MAP_HH
