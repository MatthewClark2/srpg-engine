#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#ifndef SRPG_ENGINE_RANDOM_HH
#define SRPG_ENGINE_RANDOM_HH

#include <random>
#include "unit.h"
#include "combat.h"

namespace srpg {

// Global randomization variables.
std::random_device _RAND_DEV;
std::mt19937_64 _RNG(_RAND_DEV());
std::uniform_int_distribution<std::mt19937_64::result_type> _BASIC_ROLL(0, 100);

int randrange(int lo, int hi);
bool roll_crit(const Unit& attacker, const Unit& target);
bool roll_hit(const Unit& attacker, const Unit& target);

}  // end namespace srpg

#endif //SRPG_ENGINE_RANDOM_HH

#pragma clang diagnostic pop