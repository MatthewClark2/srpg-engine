#include <memory>

#include "unit.h"
#include "unit_attrs.h"


namespace srpg {

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
           const UnitClass& clazz, int base_weapon_rank)
    : Unit(base_stats, growths, attributes, clazz, base_weapon_rank, 0, 1) {
}

int Unit::rnk() const {
  return rnk_;
}

int Unit::exp() const {
  return exp_;
}

int Unit::level() const {
  return levels_gained_ + base_level_;
}

bool Unit::is_equipped() const {
  return equipped_;
}

void Unit::unequip() {
  equipped_ = false;
}

bool Unit::equip() {
  return equipped_ = can_equip();
}

bool Unit::has_attributes(UnitAttribute attributes) const {
  if (this->attributes() == UnitAttribute::None && attributes == UnitAttribute::None) {
    return true;
  }

  return (~this->attributes() & attributes) == UnitAttribute::None;
}

bool Unit::give_exp(int exp) {
  bool x;

  return give_exp(exp, x);
}

bool Unit::give_exp(int exp, bool& failed) {
  if (level() == MAX_LEVEL) {
    failed = true;
    return false;
  }

  exp = std::min(exp, EXP_PER_LEVEL);
  bool leveled = EXP_PER_LEVEL - (exp + exp_) <= 0;

  exp_ = (exp + exp_) % EXP_PER_LEVEL;

  if (leveled) {
    ++levels_gained_;

    if (level() == MAX_LEVEL) {
      exp_ = 0;
    }
  }

  return leveled;
}

CoreStatSpread Unit::stats() const {
  // Take the sum of base stats + buffs + growth + item bonuses for raw effective stats.
  auto effective_stats =
      stats_ + clazz_.stat_bonuses + buffs_ + growths() +
      (held_item().has_value() ? held_item()->get().stat_bonuses() : CoreStatSpread());

  // Ensure that no stat falls below the baseline.
  effective_stats = CoreStatSpread(std::max(1, effective_stats.hp),
                                   std::max(0, effective_stats.atk),
                                   std::max(0, effective_stats.def),
                                   std::max(0, effective_stats.res),
                                   std::max(0, effective_stats.luk),
                                   std::max(0, effective_stats.skl),
                                   std::max(0, effective_stats.spd));

  // If stat caps were a thing, they would be checked here.

  return effective_stats;
}

UnitAttribute Unit::attributes() const {
  return base_attributes_ | clazz_.class_attributes;
}

const UnitClass& Unit::clazz() const {
  return clazz_;
}

std::optional<std::reference_wrapper<InventoryItem>> Unit::held_item() {
  if (inventory_) {
    return std::make_optional(std::ref<InventoryItem>(*inventory_));
  }

  return std::nullopt;
}

std::optional<std::reference_wrapper<const InventoryItem>> Unit::held_item() const {
  if (inventory_) {
    return std::make_optional(std::ref<const InventoryItem>(*inventory_));
  }

  return std::nullopt;
}

std::unique_ptr<InventoryItem> Unit::drop_item(bool& successful) {
  successful = static_cast<bool>(inventory_);

  if (successful) {
    return std::move(inventory_);
  }

  return nullptr;
}

void Unit::give_item(std::unique_ptr<InventoryItem>&& item) {
  inventory_ = std::move(item);
}

bool Unit::dead() const {
  return remaining_hp_ <= 0;
}

void Unit::offset_hp(int amount) {
  auto max_hp = stats_.hp;

  remaining_hp_ = std::min(-amount > remaining_hp_ ? 0 : remaining_hp_ + amount, max_hp);
}

void Unit::buff(const CoreStatSpread& mod) {
  // TODO(matthew-c21): Debuffs should probably be capped.
  buffs_ = buffs_ + mod;
}

std::optional<std::reference_wrapper<Weapon>> Unit::equipped_weapon() {
  if (is_equipped()) {
    return std::make_optional(std::ref<Weapon>(dynamic_cast<Weapon&>(*inventory_)));
  }
  return std::nullopt;
}

std::optional<std::reference_wrapper<const Weapon>> Unit::equipped_weapon() const {
  if (is_equipped()) {
    return std::make_optional(std::ref<const Weapon>(dynamic_cast<Weapon&>(*inventory_)));
  }

  return std::nullopt;
}

int Unit::remaining_hp() const {
  return remaining_hp_;
}

bool Unit::can_equip() const {
  // TODO(matthew-c21): This implementation is bad and it should feel bad.
  if (inventory_ && inventory_->equipable()) {
    return can_equip(*dynamic_cast<Weapon*>(inventory_.get()));
  }

  return false;
}

bool Unit::can_equip(const Weapon& weapon) const {
  return (weapon.required_rank() <= rnk_) && ((clazz_.usable_weapon_types & weapon.type()) != WeaponType::None);
}

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
           const UnitClass& clazz, int base_weapon_rank, int base_exp) : Unit(base_stats, growths, attributes, clazz,
                                                                              base_weapon_rank, base_exp, 1) {

}

Unit::Unit(const CoreStatSpread& base_stats, const CoreStatSpread& growths, UnitAttribute attributes,
           const UnitClass& clazz, int base_weapon_rank, int base_exp, int base_level)
    : stats_(base_stats), growths_(growths), base_attributes_(attributes), clazz_(clazz), rnk_(base_weapon_rank),
    exp_(base_exp), base_level_(base_level), levels_gained_(0) {
  remaining_hp_ = base_stats.hp;
}

CoreStatSpread Unit::growths() const {
  return CoreStatSpread(growths_.hp * levels_gained_ / 100,
                        growths_.atk * levels_gained_ / 100,
                        growths_.def * levels_gained_ / 100,
                        growths_.res * levels_gained_ / 100,
                        growths_.luk * levels_gained_ / 100,
                        growths_.skl * levels_gained_ / 100,
                        growths_.spd * levels_gained_ / 100);
}

UnitClass::UnitClass(const CoreStatSpread& stats, MovementType mov, UnitAttribute attrs, WeaponType weps)
    : stat_bonuses(stats), movement_type(mov), class_attributes(attrs), usable_weapon_types(weps) {
}

} // namespace srpg
