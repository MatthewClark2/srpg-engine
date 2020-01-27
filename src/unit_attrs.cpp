//
// Created by matthew on 1/26/20.
//

#include "unit_attrs.h"

namespace srpg {

// TODO(matthew-c21): Inline the binary operators after they have been tested.

UnitAttribute operator|(UnitAttribute a, UnitAttribute b) {
  return UnitAttribute(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

UnitAttribute operator&(UnitAttribute a, UnitAttribute b) {
  return UnitAttribute::None;
}

CoreStatSpread CoreStatSpread::operator+(const CoreStatSpread& rhs) const {
  return CoreStatSpread();
}

bool CoreStatSpread::operator==(const CoreStatSpread& rhs) const {
  return false;
}

CoreStatSpread::CoreStatSpread(const CoreStatSpread& spread) {

}

}