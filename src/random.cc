#include "random.hh"

namespace srpg {

int randrange(int lo, int hi) {
  std::uniform_int_distribution<std::mt19937_64::result_type> dist(lo, hi);
  return dist(_RNG);
}

bool roll_crit(const Unit& attacker, const Unit& target) {
  size_t crit = crit_against(attacker, target);
  return _BASIC_ROLL(_RNG) < crit;
}

bool roll_hit(const Unit& attacker, const Unit& target) {
  size_t acc = accuracy_against(attacker, target);
  return _BASIC_ROLL(_RNG) < acc;
}

}