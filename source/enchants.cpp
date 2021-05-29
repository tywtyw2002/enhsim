//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "enchants.h"
#include "enhsim.h"


void Enchant::proc(const int& proc_id) {
  //lets check which proc chance are we going to use, auto attack or instant
  if (proc_id & P_AUTO_ATTACK) {
    if (roll() < proc_chance_auto_attack_) {
      trigger();
    }
  }
  else {
    if (roll() < proc_chance_instant_) {
      trigger();
    }
  }
}

void Enchant::finalize() {
  if (buff_event_) {
    uptime_ += sim.now() - proc_start_time_;
  }
}

void StaticProcChanceEnchant::proc(const int& proc_id) {
  
  if (roll() < proc_chance_instant_) {
    trigger();
  }
}

void Deathfrost::proc(const int& proc_id) {

  if (proc_id & P_MELEE) {
    if (roll() < proc_chance_) {
      trigger();
    }
  }
  else {

    if (!cd_) {
      if (roll() < proc_chance_spell_) {
        trigger();

        cd_ = true;
        sim.addHighPrioEvent(cd_duration_, this);
      }
    }
  }
}

void Deathfrost::event(const int& event_id) {
  cd_ = false;
}

void Deathfrost::trigger() {
  ++sim.stats_.misc_hit_;

  if (roll() < sim.frost_crit_) {
    sim.stats_.misc_damage_ += 225 * sim.frost_damage_multiplier_;

    COMBATLOG_EFFECT("Deathfrost proc crits " << 225 * sim.frost_damage_multiplier_)
  }
  else {
    sim.stats_.misc_damage_ += 150 * sim.frost_damage_multiplier_;

    COMBATLOG_EFFECT("Deathfrost proc " << 150 * sim.frost_damage_multiplier_)
  }
}

void BuffEnchant::trigger() {

  //if buff_event_ is already there, we know that buff is already active, so lets move the buff fade event
  if (buff_event_) {
    sim.que_.moveEvent(buff_event_, duration_);
  }
  //oterwise
  else {
    //apply the buff
    addBuff();

    //record start time for statistics
    proc_start_time_ = sim.now();

    //add buff fade event to event queue and store it also to buff event for own use
    sim.addLowPrioEvent(buff_event_, duration_, this);
  }
}

//buff fade event
void BuffEnchant::event(const int& event_id) {

    //remove the buff
    removeBuff();

    //record uptime
    uptime_ += sim.now() - proc_start_time_;

    //reset our own pointer
    buff_event_ = 0;
}

void MhMongoose::addBuff() {
  sim.changeAgility(120);
  sim.changeMeleeHasteMultiplier(1.02f, HASTE_MH_MONGOOSE);

  COMBATLOG_EFFECT("MH Mongoose procs")
}

void MhMongoose::removeBuff() {
  sim.changeAgility(-120);
  sim.changeMeleeHasteMultiplier(1.00f, HASTE_MH_MONGOOSE);

  COMBATLOG_EFFECT("MH Mongoose fades")
}

void OhMongoose::addBuff() {
  sim.changeAgility(120);
  sim.changeMeleeHasteMultiplier(1.02f, HASTE_OH_MONGOOSE);

  COMBATLOG_EFFECT("OH Mongoose procs")
}

void OhMongoose::removeBuff() {
  sim.changeAgility(-120);
  sim.changeMeleeHasteMultiplier(1.00f, HASTE_OH_MONGOOSE);

  COMBATLOG_EFFECT("OH Mongoose fades")
}

void MhCrusader::addBuff() {
  sim.changeStrength(60);

  COMBATLOG_EFFECT("MH Crusader procs")
}

void MhCrusader::removeBuff() {
  sim.changeStrength(-60);

  COMBATLOG_EFFECT("MH Crusader fades")
}

void OhCrusader::addBuff() {
  sim.changeStrength(60);

  COMBATLOG_EFFECT("OH Crusader procs")
}

void OhCrusader::removeBuff() {
  sim.changeStrength(-60);

  COMBATLOG_EFFECT("OH Crusader fades")
}

void MhExecutioner::addBuff() {
  sim.changeArmor(-840);

  COMBATLOG_EFFECT("MH Executioner procs")
}

void MhExecutioner::removeBuff() {
  sim.changeArmor(840);

  COMBATLOG_EFFECT("MH Executioner fades")
}

void OhExecutioner::addBuff() {

  //if we have dual executioner, oh procs actually trigger mh executioners proc, because dual executioners do not create 2 buffs.
  if (mh_executioner_) {
    if (mh_executioner_->buff_event_) {
      sim.que_.moveEvent(mh_executioner_->buff_event_, mh_executioner_->duration_);
    }
    else {
      mh_executioner_->addBuff();

      mh_executioner_->proc_start_time_ = sim.now();

      sim.addLowPrioEvent(mh_executioner_->buff_event_, mh_executioner_->duration_, mh_executioner_);
    }
  }
  else {
    sim.changeArmor(-840);

    COMBATLOG_EFFECT("OH Executioner procs")
  }
}

void OhExecutioner::removeBuff() {

  //if we have dual executioners, we don't want to have any uptime for oh executioner
  if (mh_executioner_) {
    proc_start_time_ = sim.now();
  }
  else {
    sim.changeArmor(840);

    COMBATLOG_EFFECT("OH Executioner fades")
  }
}
