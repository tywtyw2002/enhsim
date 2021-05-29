//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "totems.h"
#include "enhsim.h"

void StonebreakersTotem::addBuff() {
  sim.changeAttackPower(110);
  COMBATLOG_EFFECT("Stonebreaker's Totem procs")
}

void StonebreakersTotem::removeBuff() {
  sim.changeAttackPower(-110);
  COMBATLOG_EFFECT("Stonebreaker's Totem fades")
}

// void SkycallTotem::addBuff() {
//   sim.changeSpellHaste(100 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Skycall Totem procs")
// }

// void SkycallTotem::removeBuff() {
//   sim.changeSpellHaste(-100 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Skycall Totem fades")
// }
