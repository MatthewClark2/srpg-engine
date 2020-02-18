//
// Created by matthew on 2/12/20.
//

#ifndef SRPG_ENGINE_MAP_H
#define SRPG_ENGINE_MAP_H

#include "unit.h"

class Texture;

namespace srpg {

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

  // TODO(matthew-c21): Add script triggers.
  const int texture_index_;

 public:
  Terrain terrain() const;

  /**
   * Obtain texture information about this tile.
   *
   * This index is largely meaningless on its own, and is mostly for mapping different texture sheets onto a larger
   * srpg::TiledMap.
   * @return
   */
  int texture_index() const;

  void on_turn_start();
  void on_turn_end();
  void on_wait();
};

class TiledMap {
 private:
  std::vector<Tile> tiles_;
  const int width, height;
  Texture* texture_;

 public:
  TiledMap();



  const Tile& operator[](std::pair<int, int> xy_pos) const;
};

int determine_movement_cost(const Unit& unit, Terrain terrain);

}  // end namespace srpg

#endif //SRPG_ENGINE_MAP_H
