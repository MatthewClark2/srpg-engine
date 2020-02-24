//
// Created by matthew on 2/2/20.
//

#ifndef SRPG_ENGINE_COMBAT_H
#define SRPG_ENGINE_COMBAT_H

#include <functional>
#include "unit.h"
#include "weapon.h"

namespace srpg {

// TODO(matthew-c21): Some of these calculations should also include terrain, so the full implementation should be
//  delayed until the map API is fully set up.

// This is safe as a const reference since the underlying callable shouldn't be destroyed over the lifetime of a call to
// a function within this module.
typedef const std::function<void()>& callback;

/**
 * Determine whether or not the given unit can attack at a range.
 *
 * This function takes the unit's equipped weapon into account, including the weapon's range as well as whether or not
 * it is broken. If the unit has no combative weapons equipped either due to having unequipped or due to a class
 * limitation, this function returns false.
 * @param unit the attacking unit.
 * @param range optional(default 1), the range at which the unit is trying to attack.
 * @return whether or no the unit can engage at the provided range.
 */
bool can_engage(const Unit& unit, int range = 1);

/**
 * Perform combat initiated by the attacker.
 *
 * This takes care of doubling, decreasing HP, countering, and early termination for broken weapons. If the attacking
 * unit is unable to engage the target, then this method does nothing.
 * @param attacker the initiating unit
 * @param target the defending unit
 * @param range the range at which combat occurs
 */
void engage(Unit& attacker, Unit& target, int range);

/**
 * Similar to srpg::engage(Unit&, Unit&, int), but with a series of callbacks used to hook into various parts of combat.
 *
 * Note that this function isn't made for scripted combat scenarios. Callbacks are designed for mostly interactive
 * elements, such as playing certain animations or sound effects to go along with various aspects of combat.
 * This function still manages all of the same aspects of combat as the unhooked variant.
 * @param attacker
 * @param target
 * @param range
 * @param on_attacker_strike function called when the attacker tries to strike
 * @param on_defender_strike called when the defender attempts to attack
 * @param on_attacker_dodge called when the attacker dodges a counter attack
 * @param on_defender_dodge called when the defender dodges an attack
 * @param on_attacker_follow_up called when the attacker follows up
 * @param on_target_follow_up called when the defender follows up
 * @param on_attacker_crit called when the attacker lands a critical hit
 * @param on_defender_crit called when the defender lands a critical hit
 */
void engage(Unit& attacker, Unit& target, int range, callback on_attacker_strike, callback on_defender_strike,
            callback on_attacker_crit, callback on_defender_crit,
            callback on_attacker_dodge, callback on_defender_dodge, callback on_attacker_follow_up,
            callback on_target_follow_up);

/**
 * Determine the total offensive power of a particular unit.
 *
 * This function is separate from srpg::damage_per_attack, which is used for actual damage calculation during combat.
 * @param unit
 * @return
 */
int calculate_power(const Unit& unit);

/**
 * Calculate the effective physical defense of a unit.
 */
int calculate_prt(const Unit& unit);

/**
 * Calculate the effective magical resistance of a unit.
 */
int calculate_rsl(const Unit& unit);

/**
 * Odds of the unit to dodge an attack before factoring weapon triangle advantage or terrain effects.
 */
int calculate_avoid(const Unit& unit);

/**
 * Amount that critical odds should be reduced when attacking this unit.
 */
int calculate_crit_evade(const Unit& unit);

/**
 * Odds of this unit landing a critical hit before factoring in enemy's critical avoid.
 */
int calculate_crit(const Unit& unit);

/**
 * Odds of landing an attack with the currently equipped weapon, before factoring in weapon triangle advantage or enemy
 * avoidance.
 */
int calculate_accuracy(const Unit& unit);

/**
 * Attack speed is based on the speed and attack stats of the unit, offset by any weapon weight.
 * @param unit
 * @return
 */
int calculate_attack_speed(const Unit& unit);

/**
 * Determines whether or not the attacker is able to double the target.
 *
 * A unit is double attacked by another unit if it's five or more higher.
 */
bool doubles(const Unit& attacker, const Unit& target);

/**
 * Determine if a unit has weapon triangle advantage over another one.
 *
 * This function is based on the currently equipped weapons of both the attacker and target.
 */
bool has_advantage(const Unit& attacker, const Unit& target);

/**
 * Determine whether or not a unit has effective damage against another unit.
 *
 * The results of this function are based on the effectiveness of the attacker's equipped weapons and the effective
 * UnitAttributes of the target.
 */
bool is_effective(const Unit& attacker, const Unit& target);

/**
 * Determine damage per attack, based on weapon triangle advantage, effectiveness, offensive power of the attacking
 * unit, and defensive power of the target unit.
 *
 * This function automatically categorizes damage as magical or physical, and determines the appropriate defense
 * correctly.
 */
int damage_per_attack(const Unit& attacker, const Unit& target);

int accuracy_against(const Unit& attacker, const Unit& target);

int crit_against(const Unit& attacker, const Unit& target);

}  // end namespace srpg

#endif //SRPG_ENGINE_COMBAT_H
