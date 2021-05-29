//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "metagems.h"
#include "enhsim.h"

void ThunderingSkyfireDiamond::addBuff() {
  sim.changeHaste(240 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Thundering Skyfire Diamond procs")
}

void ThunderingSkyfireDiamond::removeBuff() {
  sim.changeHaste(-240 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Thundering Skyfire Diamond fades")
}
