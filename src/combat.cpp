#include <random>

#include "combat.h"
#include "random.hh"

namespace srpg {

static void nop() {}

constexpr int BONUS_EVADE = 15;
constexpr int BONUS_ACC = 15;
constexpr int BONUS_ATK = 1;
constexpr int AUTO_ENGAGE = -1;
constexpr int CRIT_BONUS = 3;

static bool can_fight(const Unit& unit) {
  return unit.clazz().usable_weapon_types != WeaponType::None;
}

static void attack(Unit& attacker, Unit& target, callback on_attacker_strike, callback on_defender_dodge) {
  on_attacker_strike();

  if (roll_hit(attacker, target)) {
    int dmg = damage_per_attack(attacker, target);

    if (roll_crit(attacker, target)) {
      dmg *= CRIT_BONUS;
    }

    target.offset_hp(dmg);
  } else {
    on_defender_dodge();
  }
}

bool can_engage(const Unit& unit, int range) {
  if (range == AUTO_ENGAGE) {
    return true;
  }

  bool can_perform_combat = can_fight(unit);

  std::tuple<int, int> combat_range = unit.equipped_weapon().value().get().get_range();
  bool can_attack_at_range = std::get<0>(combat_range) <= range && std::get<1>(combat_range) >= range;

  return can_perform_combat && can_attack_at_range;
}

void engage(Unit& attacker, Unit& target, int range) {
  engage(attacker, target, range, nop, nop, nop, nop, nop, nop, nop, nop);
}

int calculate_power(const Unit& unit) {
  auto wep = unit.equipped_weapon();

  if (wep) {
    return wep->get().might() + unit.stats().atk;
  }

  return 0;
}

int calculate_avoid(const Unit& unit) {
  return unit.stats().spd + unit.stats().luk;
}

int calculate_crit_evade(const Unit& unit) {
  return 2 * unit.stats().luk;
}

int calculate_crit(const Unit& unit) {
  return unit.stats().luk + unit.stats().skl;
}

int calculate_accuracy(const Unit& unit) {
  auto wep = unit.equipped_weapon();

  if (wep) {
    return std::min(std::max(0, wep->get().accuracy() + unit.stats().skl), 100);
  }

  return 0;
}

int calculate_attack_speed(const Unit& unit) {
  auto wep = unit.equipped_weapon();

  auto wt = wep ? wep->get().weight() : 0;
  return unit.stats().spd - std::max(0, wt - unit.stats().atk);
}

bool doubles(const Unit& attacker, const Unit& target) {
  return calculate_attack_speed(attacker) > calculate_attack_speed(target) + 4;
}

// TODO(matthew-c21): This function assumes that attacking can never damage the attacker or defender.
void engage(Unit& attacker, Unit& target, callback on_attacker_strike,
            callback on_defender_strike, callback on_attacker_dodge, callback on_defender_dodge,
            callback on_attacker_follow_up, callback on_defender_follow_up) {
  if (!can_fight(attacker) || attacker.dead() || target.dead()) return;

  bool can_counter = can_fight(target);

  attack(attacker, target, on_attacker_strike, on_defender_dodge);

  if (target.dead()) return;

  if (can_counter) {
    attack(target, attacker, on_defender_strike, on_attacker_dodge);

    if (attacker.dead()) return;

    if (doubles(target, attacker)) {
      attack(target, attacker, on_defender_follow_up, on_attacker_dodge);
      if (attacker.dead()) return;
    }
  }

  if (doubles(attacker, target)) {
    attack(attacker, target, on_attacker_follow_up, on_defender_dodge);
  }
}

bool has_advantage(const Unit& attacker, const Unit& target) {
  auto l_wep = attacker.equipped_weapon();
  auto r_wep = target.equipped_weapon();

  if (!(l_wep && r_wep)) {
    return false;
  }

  auto left = l_wep->get().type();
  auto right = r_wep->get().type();

  return ((left == WeaponType::Lance && right == WeaponType::Sword)
          || (left == WeaponType::Sword && right == WeaponType::Axe)
          || (left == WeaponType::Axe && right == WeaponType::Lance));
}

int calculate_prt(const Unit& unit) {
  auto item = unit.held_item();

  return unit.stats().res + (item ? item->get().stat_bonuses().res : 0);
}

int calculate_rsl(const Unit& unit) {
  auto item = unit.held_item();

  return unit.stats().def + (item ? item->get().stat_bonuses().def : 0);
}

bool is_effective(const Unit& attacker, const Unit& target) {
  auto wep = attacker.equipped_weapon();

  if (wep) {
    return (target.attributes() | (wep->get().effectiveness())) != UnitAttribute::None;
  }

  return false;
}

int damage_per_attack(const Unit& attacker, const Unit& target) {
  if (attacker.is_equipped()) {
    auto dmg = calculate_power(attacker) - calculate_prt(target);

    if (has_advantage(attacker, target)) {
      dmg += BONUS_ATK;
    }

    return std::max(1, dmg);
  }

  return 0;
}

int accuracy_against(const Unit& attacker, const Unit& target) {
  auto base_acc = std::max(0, std::min(calculate_accuracy(attacker) - calculate_avoid(target), 100));

  if (has_advantage(attacker, target)) {
    return base_acc + BONUS_ACC;
  } else if (has_advantage(target, attacker)) {
    return base_acc - BONUS_EVADE;
  }

  return base_acc;
}

int crit_against(const Unit& attacker, const Unit& target) {
  return std::max(0, calculate_crit(attacker) - calculate_crit_evade(target));
}

}  // end namespace srpg