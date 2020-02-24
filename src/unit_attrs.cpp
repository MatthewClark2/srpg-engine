#include "unit_attrs.h"

namespace srpg {

// TODO(matthew-c21): Inline the binary operators after they have been tested.

UnitAttribute operator|(UnitAttribute a, UnitAttribute b) {
  return UnitAttribute(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

UnitAttribute operator&(UnitAttribute a, UnitAttribute b) {
  return UnitAttribute(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}

UnitAttribute operator~(UnitAttribute a) {
  return UnitAttribute(~static_cast<unsigned int>(a));
}

CoreStatSpread CoreStatSpread::operator+(const CoreStatSpread& rhs) const {
  return CoreStatSpread(
      hp + rhs.hp,
      atk + rhs.atk,
      def + rhs.def,
      res + rhs.res,
      luk + rhs.luk,
      skl + rhs.skl,
      spd + rhs.spd
  );
}

bool CoreStatSpread::operator==(const CoreStatSpread& rhs) const {
  return hp == rhs.hp &&
         atk == rhs.atk &&
         def == rhs.def &&
         res == rhs.res &&
         luk == rhs.luk &&
         skl == rhs.skl &&
         spd == rhs.spd;
}

CoreStatSpread::CoreStatSpread(const CoreStatSpread& spread) : CoreStatSpread(spread.hp, spread.atk, spread.def,
                                                                              spread.res, spread.luk, spread.skl,
                                                                              spread.spd) {
}

}