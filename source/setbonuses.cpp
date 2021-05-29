//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "setbonuses.h"
#include "enhsim.h"

void DesolationBattlegear::addBuff() {
  sim.changeAttackPower(160);
  COMBATLOG_EFFECT("Desolation Battlegear procs")
}

void DesolationBattlegear::removeBuff() {
  sim.changeAttackPower(-160);
  COMBATLOG_EFFECT("Desolation Battlegear fades")
}

void SkyshatterHarness::addBuff() {
  sim.changeAttackPower(70);
  COMBATLOG_EFFECT("Skyshatter procs")
}

void SkyshatterHarness::removeBuff() {
  sim.changeAttackPower(-70);
  COMBATLOG_EFFECT("Skyshatter fades")
}
