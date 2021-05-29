//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "skills.h"
#include "enhsim.h"
#include <math.h>

void GlobalCooldown::event(const int& event_id) {
  COMBATLOG_EFFECT("Global cooldown off")

  cd_ = false;
  sim.skill_rotation_->action();
}

void ShockCooldown::event(const int& event_id) {
  cd_ = false;
  sim.skill_rotation_->action();
}


void Stormstrike::event(const int& event_id) {
  cd_ = false;
  sim.skill_rotation_->action();
}

bool Stormstrike::cast() {
  
  if (!cd_ && (!sim.wf_cd_ || WF_COOLDOWN - (sim.now() - sim.last_wf_) > sim.wait_ss_wf_)) {

    if (!sim.requestMana(STORMSTRIKE_MANA,
      1.0f - sim.mental_quickness_mana_ - mana_reduction_)) {
      return false;
    }

    sim.stats_.stormstrike_mana_ += sim.useMana(STORMSTRIKE_MANA,
      1.0f - sim.mental_quickness_mana_ - mana_reduction_);

    charges_ = charges_per_cast_;
    sim.stormstrike_damage_multiplier_ = spell_damage_bonus_multiplier_;

    cd_ = true;
    sim.addLowPrioEvent(cooldown_, this, 0, sim.randomLag());

    sim.global_cooldown_->cd_ = true;
    sim.addLowPrioEvent(GCD, sim.global_cooldown_, 0, sim.randomLag());

    if (sim.mh.attack_) {
      ssMhSwing();
    }

    return true;
  }

  return false;
}

void Stormstrike::ssMhSwing() {

  int rol = roll();

  if (rol < sim.mh.yellow_miss_) {
    ++sim.stats_.mh_ss_miss_;
    
    COMBATLOG_EFFECT("MH SS miss")

    procList(sim.p_mh_stormstrike_miss, sim.p_mh_stormstrike_miss_count, P_MELEE | P_INSTANT | P_MH | P_STORMSTRIKE | P_MISS);
  }

  else if (rol < sim.mh.yellow_miss_dodge_) {
    ++sim.stats_.mh_ss_dodge_;
    
    COMBATLOG_EFFECT("MH SS dodge")

    procList(sim.p_mh_stormstrike_dodge, sim.p_mh_stormstrike_dodge_count, P_MELEE | P_INSTANT | P_MH | P_STORMSTRIKE | P_DODGE);
  }

  //2-roll system
  else {

    if (roll() < sim.mh.crit_) {
      ++sim.stats_.mh_ss_crit_;
      sim.stats_.mh_ss_crit_damage_ += sim.mh.damage_crit_ + bonus_damage_;
      
      COMBATLOG_EFFECT("MH SS crit " << sim.mh.damage_crit_ + bonus_damage_)

      procList(sim.p_mh_stormstrike_crit, sim.p_mh_stormstrike_crit_count, P_MELEE | P_INSTANT | P_MH | P_STORMSTRIKE | P_CRIT);
    }

    else {
      ++sim.stats_.mh_ss_hit_;
      sim.stats_.mh_ss_hit_damage_ += sim.mh.damage_ + bonus_damage_;
      
      COMBATLOG_EFFECT("MH SS hit " << sim.mh.damage_ + bonus_damage_)
      
      procList(sim.p_mh_stormstrike_hit, sim.p_mh_stormstrike_hit_count, P_MELEE | P_INSTANT | P_MH | P_STORMSTRIKE | P_HIT);
    }

    //if we hit, swing with OH too
    if (sim.oh.attack_) {
      ssOhSwing();
    }
  }
}

void Stormstrike::ssOhSwing() {

  int rol = roll();

  if (rol < sim.oh.yellow_miss_) {
    ++sim.stats_.oh_ss_miss_;
    
    COMBATLOG_EFFECT("OH SS miss")

    procList(sim.p_oh_stormstrike_miss, sim.p_oh_stormstrike_miss_count, P_MELEE | P_INSTANT | P_OH | P_STORMSTRIKE | P_MISS);
  }

  else if (rol < sim.oh.yellow_miss_dodge_) {
    ++sim.stats_.oh_ss_dodge_;
    
    COMBATLOG_EFFECT("OH SS dodge")

    procList(sim.p_oh_stormstrike_dodge, sim.p_oh_stormstrike_dodge_count, P_MELEE | P_INSTANT | P_OH | P_STORMSTRIKE | P_DODGE);
  }

  else {

    if (roll() < sim.oh.crit_) {
      ++sim.stats_.oh_ss_crit_;
      sim.stats_.oh_ss_crit_damage_ += sim.oh.damage_crit_ + bonus_damage_;
      
      COMBATLOG_EFFECT("OH SS crit " << sim.oh.damage_crit_ + bonus_damage_)

      procList(sim.p_oh_stormstrike_crit, sim.p_oh_stormstrike_crit_count, P_MELEE | P_INSTANT | P_OH | P_STORMSTRIKE | P_CRIT);
    }

    else {
      ++sim.stats_.oh_ss_hit_;
      sim.stats_.oh_ss_hit_damage_ += sim.oh.damage_ + bonus_damage_;
      
      COMBATLOG_EFFECT("OH SS hit " << sim.oh.damage_ + bonus_damage_)

      procList(sim.p_oh_stormstrike_hit, sim.p_oh_stormstrike_hit_count, P_MELEE | P_INSTANT | P_OH | P_STORMSTRIKE | P_HIT);
    }
  }
}


bool EarthShock::cast() {

  if (sim.shock_cooldown_->cd_ == true) {
    return false;
  }

  if (!sim.requestMana(EARTH_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.requestElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_)) {
    return false;
  }

  sim.stats_.earth_shock_mana_ += sim.useMana(EARTH_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.consumeElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_);

  sim.shock_cooldown_->cd_ = true;
  sim.addLowPrioEvent(sim.shock_cooldown_->cooldown_, sim.shock_cooldown_, 0, sim.randomLag());

  sim.global_cooldown_->cd_ = true;
  sim.addLowPrioEvent((GCD - gcd_reduction_) / sim.spell_haste_divider_, sim.global_cooldown_, 0, sim.randomLag());

  if (roll() < sim.spell_miss_) {
    ++sim.stats_.earth_shock_miss_;

    COMBATLOG_EFFECT("Earth shock miss")

    procList(sim.p_earth_shock_miss, sim.p_earth_shock_miss_count, P_SPELL | P_SHOCK | P_EARTH_SHOCK | P_MISS);
  }

  else {

    sim.consumeStormstrikeCharge();

    if (roll() < sim.nature_crit_) {
      ++sim.stats_.earth_shock_crit_;
      sim.stats_.earth_shock_crit_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
                                            ((EARTH_SHOCK_DAMAGE + sim.spellpower_ * EARTH_SHOCK_COEFFICIENT) *
                                            sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_);
      
      COMBATLOG_EFFECT("Earth shock crit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((EARTH_SHOCK_DAMAGE + sim.spellpower_ * EARTH_SHOCK_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_))
    
      procList(sim.p_earth_shock_crit, sim.p_earth_shock_crit_count, P_SPELL | P_SHOCK | P_EARTH_SHOCK | P_CRIT);
    }

    else {
      ++sim.stats_.earth_shock_hit_;
      sim.stats_.earth_shock_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
                                        ((EARTH_SHOCK_DAMAGE + sim.spellpower_ * EARTH_SHOCK_COEFFICIENT)
                                        * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_);
      
      COMBATLOG_EFFECT("Earth shock hit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((EARTH_SHOCK_DAMAGE + sim.spellpower_ * EARTH_SHOCK_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_))
    
      procList(sim.p_earth_shock_hit, sim.p_earth_shock_hit_count, P_SPELL | P_SHOCK | P_EARTH_SHOCK | P_HIT);
    }
  }

  return true;
}

void FlameShock::event(const int& event_id) {

  ++sim.stats_.flame_shock_dot_;
  sim.stats_.flame_shock_damage_ += dot_damage_multiplier_ * sim.fire_damage_reduction_ *
                                    (FLAME_SHOCK_DOT_DAMAGE + sim.spellpower_ * FLAME_SHOCK_DOT_COEFFICIENT) *
                                    sim.fire_damage_multiplier_;
  
  COMBATLOG_EFFECT("Flame shock dot " << dot_damage_multiplier_ * sim.fire_damage_reduction_ * (FLAME_SHOCK_DOT_DAMAGE + sim.spellpower_ * FLAME_SHOCK_DOT_COEFFICIENT) * sim.fire_damage_multiplier_)

  proc_time_ = sim.now();

  if (--dots_ > 0) {
    sim.addLowPrioEvent(dot_event_, FLAME_SHOCK_DOT_INTERVAL, this);
    next_dot_time_ = sim.now() + FLAME_SHOCK_DOT_INTERVAL;
  }
  else {
    dot_event_= 0;
  }
}

bool FlameShock::cast() {

  if (sim.shock_cooldown_->cd_ || dots_ > max_dots_left_) {
    return false;
  }

  if (!sim.requestMana(FLAME_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.requestElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_)) {
    return false;
  }

  sim.stats_.flame_shock_mana_ += sim.useMana(FLAME_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.consumeElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_);

  sim.shock_cooldown_->cd_ = true;
  sim.addLowPrioEvent(sim.shock_cooldown_->cooldown_, sim.shock_cooldown_, 0, sim.randomLag());

  sim.global_cooldown_->cd_ = true;
  sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

  if (roll() < sim.spell_miss_) {
    ++sim.stats_.flame_shock_miss_;

    COMBATLOG_EFFECT("Flame shock miss")

    procList(sim.p_flame_shock_miss, sim.p_flame_shock_miss_count, P_SPELL | P_SHOCK | P_FLAME_SHOCK | P_MISS);
  }

  else {

    if (roll() < sim.fire_crit_) {
      ++sim.stats_.flame_shock_crit_;
      sim.stats_.flame_shock_crit_damage_ += sim.fire_damage_reduction_ *
                                            ((FLAME_SHOCK_DAMAGE + sim.spellpower_ * FLAME_SHOCK_COEFFICIENT) *
                                            sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.fire_damage_multiplier_);
      
      COMBATLOG_EFFECT("Flame shock crit " << sim.fire_damage_reduction_ * ((FLAME_SHOCK_DAMAGE + sim.spellpower_ * FLAME_SHOCK_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.fire_damage_multiplier_))
    
      procList(sim.p_flame_shock_crit, sim.p_flame_shock_crit_count, P_SPELL | P_SHOCK | P_FLAME_SHOCK | P_CRIT);
    }

    else {
      ++sim.stats_.flame_shock_hit_;
      sim.stats_.flame_shock_damage_ += sim.fire_damage_reduction_ *
                                        ((FLAME_SHOCK_DAMAGE + sim.spellpower_ * FLAME_SHOCK_COEFFICIENT) *
                                        sim.shock_damage_multiplier_ * sim.fire_damage_multiplier_);
      
      COMBATLOG_EFFECT("Flame shock hit " << sim.fire_damage_reduction_ * ((FLAME_SHOCK_DAMAGE + sim.spellpower_ * FLAME_SHOCK_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.fire_damage_multiplier_))
    
      procList(sim.p_flame_shock_hit, sim.p_flame_shock_hit_count, P_SPELL | P_SHOCK | P_FLAME_SHOCK | P_HIT);
    }

    proc_time_ = sim.now();
    dots_ = dots_per_cast_;
    
    if (dot_event_) {
      sim.que_.moveEvent(dot_event_, FLAME_SHOCK_DOT_INTERVAL);
    }
    else {
      sim.addLowPrioEvent(dot_event_, FLAME_SHOCK_DOT_INTERVAL, this);
    }
    next_dot_time_ = sim.now() + FLAME_SHOCK_DOT_INTERVAL;
  }

  return true;
}


bool FrostShock::cast() {

  if (sim.shock_cooldown_->cd_ == true) {
    return false;
  }

  if (!sim.requestMana(FROST_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.requestElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_)) {
    return false;
  }

  sim.stats_.frost_shock_mana_ += sim.useMana(FROST_SHOCK_MANA,
    1.0f - sim.shamanistic_focus_mana_ - sim.consumeElementalFocus() - sim.mental_quickness_mana_ - sim.convection_mana_ - mana_reduction_);


  sim.shock_cooldown_->cd_ = true;
  sim.addLowPrioEvent(sim.shock_cooldown_->cooldown_, sim.shock_cooldown_, 0, sim.randomLag());

  sim.global_cooldown_->cd_ = true;
  sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

  if (roll() < sim.spell_miss_) {
    ++sim.stats_.frost_shock_miss_;

    COMBATLOG_EFFECT("Frost shock miss")

    procList(sim.p_frost_shock_miss, sim.p_frost_shock_miss_count, P_SPELL | P_SHOCK | P_FROST_SHOCK | P_MISS);
  }

  else {

    if (roll() < sim.frost_crit_) {
      ++sim.stats_.frost_shock_crit_;
      sim.stats_.frost_shock_crit_damage_ += sim.frost_damage_reduction_ *
                                            ((FROST_SHOCK_DAMAGE + sim.spellpower_ * FROST_SHOCK_COEFFICIENT) *
                                            sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.frost_damage_multiplier_);
      
      COMBATLOG_EFFECT("Frost shock crit " << sim.frost_damage_reduction_ * ((FROST_SHOCK_DAMAGE + sim.spellpower_ * FROST_SHOCK_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.frost_damage_multiplier_))
    
      procList(sim.p_frost_shock_crit, sim.p_frost_shock_crit_count, P_SPELL | P_SHOCK | P_FROST_SHOCK | P_CRIT);
    }

    else {
      ++sim.stats_.frost_shock_hit_;
      sim.stats_.frost_shock_damage_ += sim.frost_damage_reduction_ *
                                        ((FROST_SHOCK_DAMAGE + sim.spellpower_ * FROST_SHOCK_COEFFICIENT)
                                        * sim.shock_damage_multiplier_ * sim.frost_damage_multiplier_);
      
      COMBATLOG_EFFECT("Frost shock hit " << sim.frost_damage_reduction_ * ((FROST_SHOCK_DAMAGE + sim.spellpower_ * FROST_SHOCK_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.frost_damage_multiplier_))
    
      procList(sim.p_frost_shock_hit, sim.p_frost_shock_hit_count, P_SPELL | P_SHOCK | P_FROST_SHOCK | P_HIT);
    }
  }

  return true;
}

// bool LavaBurst::cast() {

//   //is mw stack full?
//   /*if (sim.maelstrom_weapon_->stack_ < 5) {
//     return false;
//   }*/

//   int64 casttime = floor(casting_time_ / sim.spell_haste_divider_);

//   if (sim.now() + casttime > sim.flame_shock_->next_dot_time_) {
//     if (max_fsdots_left_ < sim.flame_shock_->dots_ - 1) {
//       return false;
//     }

//     if (cast_only_if_fs_active_) {
//       if (sim.flame_shock_->dots_ - 1 <= 0) {
//         return false;
//       }
//     }
//   }

//   else {
//     if (max_fsdots_left_ < sim.flame_shock_->dots_) {
//       return false;
//     }

//     if (cast_only_if_fs_active_) {
//       if (sim.flame_shock_->dots_ == 0) {
//         return false;
//       }
//     }
//   }

//   if (sim.elemental_devastation_->cd_time_ - sim.now() > max_ed_left) {
//     return false;
//   }

//   //is LvB on cd? Do we wait for the cd?
//   if (cd_) {
//     /*if (cd_time_ - sim.now() <= max_wait_) {
//       sim.maelstrom_weapon_->wait_ = true;
//     }*/

//     return false;
//   }

//   if (!sim.requestMana(LAVA_BURST_MANA,
//     1.0f - sim.requestElementalFocus() - sim.convection_mana_ - mana_reduction_)) {
//     return false;
//   }


//   sim.global_cooldown_->cd_ = true;
//   sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

//   //int64 casttime = floor(casting_time_ / sim.spell_haste_divider_ * (1.0 - (0.2 * sim.maelstrom_weapon_->stack_)));
//   sim.spell_casting_->startCasting(this, casttime, true);

//   return true;
// }

// void LavaBurst::event(const int& event_id) {
//   cd_ = false;
//   //sim.maelstrom_weapon_->wait_ = false;
//   sim.skill_rotation_->action();
// }

// void LavaBurst::castingFinished() {

//   //sim.maelstrom_weapon_->wait_ = false;
//   //sim.maelstrom_weapon_->stack_ = 0;

//   cd_time_ = sim.now() + 800;

//   sim.stats_.lava_burst_mana_ += sim.useMana(LAVA_BURST_MANA,
//     1.0f - sim.consumeElementalFocus() - sim.convection_mana_ - mana_reduction_);

//   cd_ = true;
//   sim.addLowPrioEvent(800, this, 0, sim.randomLag());


//   if (roll() < sim.spell_miss_) {
//     ++sim.stats_.lava_burst_miss_;

//     COMBATLOG_EFFECT("Lava Burst miss")

//     procList(sim.p_lava_burst_miss, sim.p_lava_burst_miss_count, P_SPELL | P_LAVA_BURST | P_MISS);
//   }

//   else {

//     if (sim.flame_shock_->dots_ > 0 || roll() < sim.fire_crit_) {
      
//       //consume flame shocks dots, delete event and reset dots
//       if (consume_fs_) {
//         if (sim.flame_shock_->dot_event_) {
//           sim.que_.deleteEvent(sim.flame_shock_->dot_event_);
//           sim.flame_shock_->dot_event_ = 0;
//           sim.flame_shock_->dots_ = 0;
//         }
//       }

//       ++sim.stats_.lava_burst_crit_;
//       sim.stats_.lava_burst_crit_damage_ += sim.fire_damage_reduction_ *
//                                             ((LAVA_BURST_DAMAGE + sim.spellpower_ * (LAVA_BURST_COEFFICIENT + coefficient_bonus_)) *
//                                             crit_multiplier_ * sim.shock_damage_multiplier_ * sim.lava_burst_damage_multiplier_ * sim.fire_damage_multiplier_/* * crit_damage_multiplier_*/);
      
//       COMBATLOG_EFFECT("Lava Burst crit " << sim.fire_damage_reduction_ * ((LAVA_BURST_DAMAGE + sim.spellpower_ * (LAVA_BURST_COEFFICIENT + coefficient_bonus_)) * crit_multiplier_ * sim.shock_damage_multiplier_ * sim.lava_burst_damage_multiplier_  * sim.fire_damage_multiplier_/* * crit_damage_multiplier_*/))
    
//       procList(sim.p_lava_burst_crit, sim.p_lava_burst_crit_count, P_SPELL | P_LAVA_BURST | P_CRIT);
//     }

//     else {
//       ++sim.stats_.lava_burst_hit_;
//       sim.stats_.lava_burst_damage_ += sim.fire_damage_reduction_ *
//                                         ((LAVA_BURST_DAMAGE + sim.spellpower_ * (LAVA_BURST_COEFFICIENT + coefficient_bonus_))
//                                         * sim.shock_damage_multiplier_ * sim.lava_burst_damage_multiplier_  * sim.fire_damage_multiplier_);
      
//       COMBATLOG_EFFECT("Lava Burst hit " << sim.fire_damage_reduction_ * ((LAVA_BURST_DAMAGE + sim.spellpower_ * (LAVA_BURST_COEFFICIENT + coefficient_bonus_)) * sim.shock_damage_multiplier_ * sim.lava_burst_damage_multiplier_  * sim.fire_damage_multiplier_))
    
//       procList(sim.p_lava_burst_hit, sim.p_lava_burst_hit_count, P_SPELL | P_LAVA_BURST | P_HIT);
//     }
//   }
// }

// bool LightningBolt::cast() {

//   /*if (sim.maelstrom_weapon_->stack_ < 5) {
//     return false;
//   }*/

//   if (!sim.requestMana(LIGHTNING_BOLT_MANA,
//     1.0f - sim.requestElementalFocus() - sim.convection_mana_ - mana_reduction_)) {
//     return false;
//   }

//   /*if (sim.maelstrom_weapon_->wait_) {
//     return false;
//   }*/

//   sim.global_cooldown_->cd_ = true;
//   sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

//   int64 casttime = floor(casting_time_ / sim.spell_haste_divider_ * (1.0 - (0.2 * sim.maelstrom_weapon_->stack_)));
//   sim.spell_casting_->startCasting(this, casttime, !(sim.maelstrom_weapon_->stack_ > 0));

//   return true;
// }

// void LightningBolt::castingFinished() {

//   sim.maelstrom_weapon_->stack_ = 0;

//   sim.stats_.lightning_bolt_mana_ += sim.useMana(LIGHTNING_BOLT_MANA,
//     1.0f - sim.consumeElementalFocus() - sim.convection_mana_ - mana_reduction_);


//   if (roll() < sim.spell_miss_) {
//     ++sim.stats_.lightning_bolt_miss_;

//     COMBATLOG_EFFECT("Lightning Bolt miss")

//     procList(sim.p_lightning_bolt_miss, sim.p_lightning_bolt_miss_count, P_SPELL | P_LIGHTNING_BOLT | P_MISS);
//   }

//   else {

//     sim.consumeStormstrikeCharge();

//     if (roll() < sim.nature_crit_ + crit_bonus_) {

//       ++sim.stats_.lightning_bolt_crit_;
//       sim.stats_.lightning_bolt_crit_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                             ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) *
//                                             sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_);
      
//       COMBATLOG_EFFECT("Lightning Bolt crit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_))
    
//       procList(sim.p_lightning_bolt_crit, sim.p_lightning_bolt_crit_count, P_SPELL | P_LIGHTNING_BOLT | P_CRIT);
//     }

//     else {
//       ++sim.stats_.lightning_bolt_hit_;
//       sim.stats_.lightning_bolt_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                         ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT)
//                                         * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_);
      
//       COMBATLOG_EFFECT("Lightning Bolt hit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_))
    
//       procList(sim.p_lightning_bolt_hit, sim.p_lightning_bolt_hit_count, P_SPELL | P_LIGHTNING_BOLT | P_HIT);
//     }
//   }
// }

// bool ChainLightning::cast() {

//   /*if (sim.maelstrom_weapon_->stack_ < 5) {
//     return false;
//   }*/

//   if (sim.maelstrom_weapon_->wait_) {
//     return false;
//   }

//   if (cd_) {
//     return false;
//   }

//   if (!sim.requestMana(CHAIN_LIGHTNING_MANA,
//     1.0f - sim.requestElementalFocus() - sim.convection_mana_ - mana_reduction_)) {
//     return false;
//   }

//   sim.global_cooldown_->cd_ = true;
//   sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

//   int64 casttime = floor(casting_time_ / sim.spell_haste_divider_ * (1.0 - (0.2 * sim.maelstrom_weapon_->stack_)));
//   sim.spell_casting_->startCasting(this, casttime, !(sim.maelstrom_weapon_->stack_ > 0));

//   return true;
// }

// void ChainLightning::event(const int& event_id) {
//   cd_ = false;
//   sim.maelstrom_weapon_->wait_ = false;
//   sim.skill_rotation_->action();
// }

// void ChainLightning::castingFinished() {

//   sim.maelstrom_weapon_->stack_ = 0;

//   sim.stats_.chain_lightning_mana_ += sim.useMana(CHAIN_LIGHTNING_MANA,
//     1.0f - sim.consumeElementalFocus() - sim.convection_mana_ - mana_reduction_);

//   cd_ = true;
//   sim.addLowPrioEvent(cd_duration_, this, 0, sim.randomLag());


//   if (roll() < sim.spell_miss_) {
//     ++sim.stats_.chain_lightning_miss_;

//     COMBATLOG_EFFECT("Chain Lightning miss")

//     procList(sim.p_chain_lightning_miss, sim.p_chain_lightning_miss_count, P_SPELL | P_CHAIN_LIGHTNING | P_MISS);
//   }

//   else {

//     sim.consumeStormstrikeCharge();

//     if (roll() < sim.nature_crit_ + crit_bonus_) {

//       ++sim.stats_.chain_lightning_crit_;
//       sim.stats_.chain_lightning_crit_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                             ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) *
//                                             sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_);
      
//       COMBATLOG_EFFECT("Chain Lightning crit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_))
    
//       procList(sim.p_chain_lightning_crit, sim.p_chain_lightning_crit_count, P_SPELL | P_CHAIN_LIGHTNING | P_CRIT);
//     }

//     else {
//       ++sim.stats_.chain_lightning_hit_;
//       sim.stats_.chain_lightning_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                         ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT)
//                                         * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_);
      
//       COMBATLOG_EFFECT("Chain Lightning hit " << sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * damage_multiplier_))
    
//       procList(sim.p_chain_lightning_hit, sim.p_chain_lightning_hit_count, P_SPELL | P_CHAIN_LIGHTNING | P_HIT);
//     }
//   }
// };

// bool LightningShield::cast() {

//   if (charges_ > max_charges_to_recast_) {
//     return false;
//   }

//   ++sim.stats_.lightning_shield_cast_;

//   charges_ = charges_per_cast_;


//   sim.global_cooldown_->cd_ = true;
//   sim.addLowPrioEvent(sim.spell_gcd_duration_, sim.global_cooldown_, 0, sim.randomLag());

//   COMBATLOG_EFFECT("Lightning Shield cast")

//   procList(sim.p_lightning_shield_cast, sim.p_lightning_shield_cast_count, P_SPELL | P_LIGHTNING_SHIELD);

//   return true;
// }

// void LightningShield::consumeCharge() {

//   if (charges_) {

//     if (roll() < sim.spell_miss_) {
//       ++sim.stats_.lightning_shield_miss_;

//       COMBATLOG_EFFECT("Lightning Shield miss")

//       procList(sim.p_lightning_shield_miss, sim.p_lightning_shield_miss_count, P_SPELL | P_LIGHTNING_SHIELD | P_MISS);
//     }

//     else {

//       //sim.consumeStormstrikeCharge();

//       //if (roll() < sim.nature_crit_) {

//       //  ++sim.stats_.lightning_shield_crit_;
//       //  sim.stats_.lightning_shield_crit_damage_ += sim.nature_damage_reduction_ *
//       //                                        ((LIGHTNING_SHIELD_DAMAGE + sim.spellpower_ * LIGHTNING_SHIELD_COEFFICIENT) *
//       //                                        sim.spell_crit_multiplier_ * sim.lightning_shield_damage_multiplier_ * sim.nature_damage_multiplier_);
//       //  
//       //  COMBATLOG_EFFECT("Lightning Shield crit " << sim.nature_damage_reduction_ * ((LIGHTNING_SHIELD_DAMAGE + sim.spellpower_ * LIGHTNING_SHIELD_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.lightning_shield_damage_multiplier_ * sim.nature_damage_multiplier_))
//       //
//       //  //procList(sim.spell_crit_procs_, sim.spell_crit_procs_count_, PROC_ID_SPELL);
//       //}

//       //else {
//         ++sim.stats_.lightning_shield_hit_;
//         sim.stats_.lightning_shield_damage_ += sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                           ((LIGHTNING_SHIELD_DAMAGE + sim.spellpower_ * LIGHTNING_SHIELD_COEFFICIENT)
//                                           * sim.nature_damage_multiplier_ * damage_multiplier_);
        
//         f32 dmg = sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((LIGHTNING_SHIELD_DAMAGE + sim.spellpower_ * LIGHTNING_SHIELD_COEFFICIENT) * sim.nature_damage_multiplier_ * damage_multiplier_);
//         COMBATLOG_EFFECT("Lightning Shield hit " << dmg << " (" << charges_ << ")")

//         procList(sim.p_lightning_shield_hit, sim.p_lightning_shield_hit_count, P_SPELL | P_LIGHTNING_SHIELD | P_HIT);
//       //}
//     }

//     --charges_;

//     if (charges_ <= max_charges_to_recast_) {
//       COMBATLOG_EFFECT("Lightning Shield fades")
//       sim.addHighPrioEvent(sim.randomLag(), sim.input_lag_);
//     }
//   }
// }

// bool LavaLash::cast() {

//   if (cd_) {
//     return false;
//   }

//   if (!sim.oh.attack_) {
//     return false;
//   }

//   if (cast_only_if_wf_on_cd_ && !sim.wf_cd_) {
//     return false;
//   }

//   if (!sim.requestMana(LAVA_LASH_MANA,
//     1.0f - sim.requestElementalFocus() - sim.mental_quickness_mana_ - mana_reduction_)) {
//     return false;
//   }

//   sim.stats_.lava_lash_mana_ += sim.useMana(LAVA_LASH_MANA,
//     1.0f - sim.consumeElementalFocus() - sim.mental_quickness_mana_ - mana_reduction_);

//   cd_ = true;
//   sim.addLowPrioEvent(600, this, 0, sim.randomLag());

//   sim.global_cooldown_->cd_ = true;
//   sim.addLowPrioEvent(GCD, sim.global_cooldown_, 0, sim.randomLag());


//   int rol = roll();

//   if (rol < sim.oh.yellow_miss_) {
//     ++sim.stats_.lava_lash_miss_;
    
//     COMBATLOG_EFFECT("Lava Lash miss")

//     procList(sim.p_lava_lash_miss, sim.p_lava_lash_miss_count, P_MELEE | P_INSTANT | P_OH | P_LAVA_LASH | P_MISS);
//   }

//   else if (rol < sim.oh.yellow_miss_dodge_) {
//     ++sim.stats_.lava_lash_dodge_;
    
//     COMBATLOG_EFFECT("Lava Lash dodge")

//     procList(sim.p_lava_lash_dodge, sim.p_lava_lash_dodge_count, P_MELEE | P_INSTANT | P_OH | P_LAVA_LASH | P_DODGE);
//   }

//   //2-roll system
//   else {

//     if (roll() < sim.oh.crit_) {
//       ++sim.stats_.lava_lash_crit_;
//       sim.stats_.lava_lash_crit_damage_ += damage_multiplier_ * sim.oh.damage_crit_ * sim.fire_damage_multiplier_ * sim.fire_damage_reduction_;
      
//       COMBATLOG_EFFECT("Lava Lash crit " << damage_multiplier_ * sim.oh.damage_crit_ * sim.fire_damage_multiplier_ * sim.fire_damage_reduction_)

//       procList(sim.p_lava_lash_crit, sim.p_lava_lash_crit_count, P_MELEE | P_INSTANT | P_OH | P_LAVA_LASH | P_CRIT);
//     }

//     else {
//       ++sim.stats_.lava_lash_hit_;
//       sim.stats_.lava_lash_hit_damage_ += damage_multiplier_ * sim.oh.damage_ * sim.fire_damage_multiplier_ * sim.fire_damage_reduction_;
      
//       COMBATLOG_EFFECT("Lava Lash hit " << damage_multiplier_ * sim.oh.damage_ * sim.fire_damage_multiplier_ * sim.fire_damage_reduction_)
      
//       procList(sim.p_lava_lash_hit, sim.p_lava_lash_hit_count, P_MELEE | P_INSTANT | P_OH | P_LAVA_LASH | P_HIT);
//     }
//   }

//   return true;
// }

// void LavaLash::event(const int& event_id) {
//   cd_ = false;

//   sim.skill_rotation_->action();
// }

bool SearingTotem::cast() {

  //dont cast if there are ticks still left
  if ( ticks_ > 0) {
    return false;
  }

  if (!sim.requestMana(SEARING_TOTEM_MANA,
    1.0f - sim.mental_quickness_mana_ - mana_reduction_)) {
    return false;
  }

  sim.stats_.searing_totem_mana_ += sim.useMana(SEARING_TOTEM_MANA,
    1.0f - sim.mental_quickness_mana_ - mana_reduction_);

  //update statistics
  ++sim.stats_.searing_totem_cast_;

  //set global cooldown
  sim.global_cooldown_->cd_ = true;
  sim.addLowPrioEvent(100, sim.global_cooldown_, 0, sim.randomLag());

  //replenish the ticks
  ticks_ = ticks_per_cast_;

  //if searing totem is already active, we move the existing event
  if (cd_event_) {
    sim.que_.moveEventSearchForward(cd_event_, SEARING_TOTEM_INTERVAL);
  }
  //otherwise add a new event
  else {
    sim.addHighPrioEvent(cd_event_, SEARING_TOTEM_INTERVAL, this);
  }

  COMBATLOG_EFFECT("Searing totem cast")

  return true;
}

void SearingTotem::event(const int& event_id) {

  if (roll() < sim.spell_miss_totem_) {
    //++sim.stats_.searing_totem_miss_;
    COMBATLOG_EFFECT("Searing totem miss")
  }

  else {
    
    if (roll() < sim.fire_crit_) {
      //++sim.stats_.searing_totem_crit_;
      sim.stats_.searing_totem_crit_damage_ += sim.fire_damage_reduction_ *
                                               (SEARING_TOTEM_DAMAGE +
                                               sim.spellpower_ * SEARING_TOTEM_COEFFICIENT)
                                               * sim.spell_crit_multiplier_ * sim.fire_damage_multiplier_ * sim.firetotem_damage_multiplier_;
      
      COMBATLOG_EFFECT("Searing totem crit " << sim.fire_damage_reduction_ * (SEARING_TOTEM_DAMAGE + sim.spellpower_ * SEARING_TOTEM_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.fire_damage_multiplier_ * sim.firetotem_damage_multiplier_)
    }

    else {
      //++sim.stats_.searing_totem_hit_;
      sim.stats_.searing_totem_damage_ += sim.fire_damage_reduction_ *
                                          (SEARING_TOTEM_DAMAGE +
                                          sim.spellpower_ * SEARING_TOTEM_COEFFICIENT) *
                                          sim.fire_damage_multiplier_ * sim.firetotem_damage_multiplier_;
      
      COMBATLOG_EFFECT("Searing totem hit " << sim.fire_damage_reduction_ * (SEARING_TOTEM_DAMAGE + sim.spellpower_ * SEARING_TOTEM_COEFFICIENT) * sim.fire_damage_multiplier_ * sim.firetotem_damage_multiplier_)
    }
  }

  if (--ticks_ > 0) {
    sim.addHighPrioEvent(cd_event_, SEARING_TOTEM_INTERVAL, this);
  }
  else {
    cd_event_ = 0;
    sim.addHighPrioEvent(sim.randomLag(), sim.input_lag_);
  }
}


void ShamanisticRage::reCalculateProcChance() {
  proc_chance_mh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_ / 60);
  proc_chance_oh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_ / 60);
}

void ShamanisticRage::calculateProcChance() {
  proc_chance_mh_instant_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_base_ / 60); 
  proc_chance_oh_instant_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_base_ / 60);
  reCalculateProcChance();
}

void ShamanisticRage::proc(const int& proc_id) {

  if (active_) {

    if (proc_id & P_MH) {
      if (proc_id & P_AUTO_ATTACK) {
        if (roll() < proc_chance_mh_auto_attack_) {
          trig();
        }
      }
      else {
        if (roll() < proc_chance_mh_instant_) {
          trig();
        }
      }
    }
    else {
      if (proc_id & P_AUTO_ATTACK) {
        if (roll() < proc_chance_oh_auto_attack_) {
          trig();
        }
      }
      else {
        if (roll() < proc_chance_oh_instant_) {
          trig();
        }
      }
    }
  }
}

void ShamanisticRage::trig() {

  sim.stats_.shamanistic_rage_regen_ += sim.regenMana(sim.ap_ * 0.30f);

  COMBATLOG_EFFECT("Shamanistic Rage procs " << sim.ap_ * 0.30f)
}

bool ShamanisticRage::cast() {

  if (cd_) {
    return false;
  }

  if (sim.mana_ > max_mana_to_cast_) {
    return false;
  }

  COMBATLOG_EFFECT("Shamanistic Rage casted")

  //set global cooldown
  sim.global_cooldown_->cd_ = true;
  sim.addLowPrioEvent(GCD, sim.global_cooldown_, 0, sim.randomLag());

  active_ = true;
  cd_ = true;
  sim.addLowPrioEvent(buff_event_, 1500, this, EVENT_ID_BUFF_FADE);

  return true;
}

void ShamanisticRage::event(const int& event_id) {

  if (event_id == EVENT_ID_BUFF_FADE) {
    active_ = false;
    buff_event_ = 0;

    sim.addHighPrioEvent(cd_event_, 10500, this, EVENT_ID_COOLDOWN);

    COMBATLOG_EFFECT("Shamanistic Rage fades")
  }
  else {
    cd_ = false;
    cd_event_ = 0;
  }
}
