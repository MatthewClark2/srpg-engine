//
// Created by matthew on 2/2/20.
//

#include "combat.h"

namespace srpg {

bool can_engage(const Unit& unit, int range) {
  bool can_perform_combat = unit.clazz().usable_weapon_types != WeaponType::None;

  std::tuple<int, int> combat_range = unit.equipped_weapon()->get_range();
  bool can_attack_at_range = std::get<0>(combat_range) <= range && std::get<1>(combat_range) >= range;

  return can_perform_combat && can_attack_at_range;
}

void engage(Unit& attacker, Unit& target) {

}

int calculate_power(const Unit& unit) {
  return 0;
}

int calculate_avoid(const Unit& unit) {
  return 0;
}

int calculate_crit_evade(const Unit& unit) {
  return 0;
}

int calculate_crit(const Unit& unit) {
  return 0;
}

int calculate_accuracy(const Unit& unit) {
  return 0;
}

int calculate_attack_speed(const Unit& unit) {
  return 0;
}

bool doubles(const Unit& attacker, const Unit& target) {
  return false;
}

void engage(Unit& attacker, Unit& target, callback on_attacker_strike,
            callback on_defender_strike, callback on_attacker_dodge, callback on_defender_dodge,
            callback on_attacker_follow_up, callback on_target_follow_up) {

}

bool has_advantage(const Unit& attacker, const Unit& target) {
  return false;
}

int calculate_prt(const Unit& unit) {
  return 0;
}

int calculate_rsl(const Unit& unit) {
  return 0;
}

bool is_effective(const Unit& attacker, const Unit& target) {
  return false;
}

int damage_per_attack(const Unit& attacker, const Unit& target) {
  return 0;
}

}  // end namespace srpg