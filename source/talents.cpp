//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "talents.h"
#include "enhsim.h"

void UnleashedRage::proc(const int& proc_id) {
  //we dont want to have another ur event if it already happened this same tick
  //its waste of cpu power
  if (proc_time_ != sim.now()) {
    if (buff_event_) {
      sim.que_.moveEventSearchForward(buff_event_, UR_DURATION);
    }
    else {
      proc_start_time_ = sim.now();
      sim.changeAttackPowerMultiplier(ap_multiplier_);
      COMBATLOG_EFFECT("Unleashed Rage procs")

      sim.addLowPrioEvent(buff_event_, UR_DURATION, this);
    }

    proc_time_ = sim.now();
  }
}

void UnleashedRage::event(const int& event_id) {
  sim.changeAttackPowerMultiplier(1.0f);
  COMBATLOG_EFFECT("Unleashed Rage fades")
  sim.stats_.unleashed_rage_uptime_ += sim.now() - proc_start_time_;
  buff_event_ = 0;
}

void UnleashedRage::finalize() {
  if (buff_event_) {
    sim.stats_.unleashed_rage_uptime_ += sim.now() - proc_start_time_;
  }
}


void Flurry::proc(const int& proc_id) {

  if (flurry_charges_ < 1) {
    //ADD BUFF
    sim.changeMeleeHasteMultiplier(haste_, HASTE_FLURRY);

    COMBATLOG_EFFECT("Flurry procs")

    proc_start_time_ = sim.now();
  }

  //replenish flurry charges
  flurry_charges_ = FLURRY_CHARGES;

  #ifdef FLURRY_NOCONSUME_SAMETICK
  proc_time_ = sim.now();
  #endif
}

void Flurry::finalize() {
  if (flurry_charges_ > 0) {
    sim.stats_.flurry_uptime_ += sim.now() - proc_start_time_;
  }
}

void FlurryConsume::proc(const int& proc_id) {
  #ifdef FLURRY_NOCONSUME_SAMETICK
  if (sim.now() != sim.flurry_->proc_time_) {
  #endif

  if (--sim.flurry_->flurry_charges_ == 0) {
    //REMOVE BUFF
    sim.changeMeleeHasteMultiplier(1.00f, HASTE_FLURRY);

    COMBATLOG_EFFECT("Flurry fades")

    sim.stats_.flurry_uptime_ += sim.now() - sim.flurry_->proc_start_time_;
  }

  #ifdef FLURRY_NOCONSUME_SAMETICK
  }
  #endif
}

void ElementalDevastation::proc(const int& proc_id) {

  if (buff_event_) {
    sim.que_.moveEventSearchForward(buff_event_, ELEMENTAL_DEVASTATION_DURATION);
  }
  else {
    proc_start_time_ = sim.now();
    sim.changeCrit(crit_);
    COMBATLOG_EFFECT("Elemental Devastation procs")
    
    sim.addLowPrioEvent(buff_event_, ELEMENTAL_DEVASTATION_DURATION, this);
  }
}

void ElementalDevastation::event(const int& event_id) {

  sim.changeCrit(-crit_);

  COMBATLOG_EFFECT("Elemental Devastation fades")

  sim.stats_.elemental_devastation_uptime_ += sim.now() - proc_start_time_;
  
  buff_event_ = 0;

  sim.skill_rotation_->action();
}

void ElementalDevastation::finalize() {
  if (buff_event_ > (Event *) 0) {
    sim.stats_.elemental_devastation_uptime_ += sim.now() - proc_start_time_;
  }
}

// void MaelstromWeapon::proc(const int& proc_id) {

//   if (proc_id & P_MH) {
//     if (proc_id & P_AUTO_ATTACK) {
//       if (roll() < proc_chance_mh_auto_attack_) {
//         trig();
//       }
//     }
//     else {
//       if (roll() < proc_chance_mh_instant_) {
//         trig();
//       }
//     }
//   }
//   else {
//     if (proc_id & P_AUTO_ATTACK) {
//       if (roll() < proc_chance_oh_auto_attack_) {
//         trig();
//       }
//     }
//     else {
//       if (roll() < proc_chance_oh_instant_) {
//         trig();
//       }
//     }
//   }
// }

// void MaelstromWeapon::trig() {

//   ++sim.stats_.maelstrom_weapon_procs_;

//   if (cd_event_) {
//     sim.que_.moveEvent(cd_event_, MAELSTROM_WEAPON_DURATION);
//   }
//   else {
//     sim.addLowPrioEvent(cd_event_, MAELSTROM_WEAPON_DURATION, this, EVENT_ID_BUFF_FADE);
//   }

//   if (stack_ < 5) {

//     COMBATLOG_EFFECT("Maelstrom Weapon stacks (" << stack_+1 << ")")

//     /*if (stack_ == 0) {
//       proc_start_time_ = sim.now();
//     }*/

//     if (++stack_ >= min_stack_to_action_) {
//       //sim.addHighPrioEvent(sim.randomLag(), this);
//       sim.addHighPrioEvent(sim.randomLag(), sim.input_lag_);
      
//       /*int64 time = sim.now() - proc_start_time_;
//       total_time_ += time;
//       total_sd_time_ += time * time;
//       ++stack_full_count_;*/
//     }
//   }

// }

// void MaelstromWeapon::event(const int& event_id) {

//   /*if (event_id != EVENT_ID_BUFF_FADE) {
//     sim.skill_rotation_->action();
//   }
//   else {*/
//     cd_event_ = 0;

//     if (stack_ > 0) {
//       stack_ = 0;

//       COMBATLOG_EFFECT("Maelstrom Weapon fades")
//     }
//   /*}*/
// }

// void MaelstromWeapon::reCalculateProcChance() {
//   proc_chance_mh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_base_ / 60);
//   proc_chance_oh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_base_ / 60);
// }

// void MaelstromWeapon::calculateProcChance() {
//   proc_chance_mh_instant_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_base_ / 60); 
//   proc_chance_oh_instant_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_base_ / 60);
//   reCalculateProcChance();
// }

// void StaticShock::proc(const int& proc_id) {
  
//   if (roll() < proc_chance_) {

//     sim.lightning_shield_->consumeCharge();
//   }
// }

void ElementalFocus::proc(const int& proc_id) {

  if (charges_ <= 0) {
    COMBATLOG_EFFECT("Elemental Focus procs")
  }

  charges_ = 2;
}

// void ElementalOath::proc(const int& proc_id) {

//   if (buff_event_) {
//     sim.que_.moveEventSearchForward(buff_event_, 1500);
//   }
//   else {
//     proc_start_time_ = sim.now();

//     sim.changeSpellCrit(crit_bonus_);

//     COMBATLOG_EFFECT("Elemental Oath procs");

//     sim.addLowPrioEvent(buff_event_, 1500, this);
//   }
// }

// void ElementalOath::event(const int& event_id) {
  
//   sim.changeSpellCrit(-crit_bonus_);

//   COMBATLOG_EFFECT("Elemental Oath fades");

//   sim.stats_.elemental_oath_uptime_ += sim.now() - proc_start_time_;

//   buff_event_ = 0;
// }

// void ElementalOath::finalize() {
//   if (buff_event_ > (Event *) 0) {
//     sim.stats_.elemental_oath_uptime_ += sim.now() - proc_start_time_;
//   }
// }


// void LightningOverload::proc(const int& proc_id) {

//   if (roll() < proc_chance_) {
  
//     if (proc_id & P_LIGHTNING_BOLT) {

//       if (roll() < sim.spell_miss_) {
//         ++sim.stats_.lightning_overload_miss_;

//         COMBATLOG_EFFECT("Lightning Overload miss")

//         procList(sim.p_lightning_overload_miss, sim.p_lightning_overload_miss_count, P_SPELL | P_LIGHTNING_BOLT | P_MISS);
//       }

//       else {

//         sim.consumeStormstrikeCharge();

//         if (roll() < sim.nature_crit_ + sim.lightning_bolt_->crit_bonus_) {

//           ++sim.stats_.lightning_overload_crit_;
//           sim.stats_.lightning_overload_crit_damage_ +=  0.5f * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                                 ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + sim.lightning_bolt_->spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) *
//                                                 sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.lightning_bolt_->damage_multiplier_);
          
//           COMBATLOG_EFFECT("Lightning Overload crit " << 0.5f * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + sim.lightning_bolt_->spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.lightning_bolt_->damage_multiplier_))
        
//           procList(sim.p_lightning_overload_crit, sim.p_lightning_overload_crit_count, P_SPELL | P_LIGHTNING_BOLT | P_CRIT);
//         }

//         else {
//           ++sim.stats_.lightning_overload_hit_;
//           sim.stats_.lightning_overload_damage_ += 0.5f * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                             ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + sim.lightning_bolt_->spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT)
//                                             * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.lightning_bolt_->damage_multiplier_);
          
//           COMBATLOG_EFFECT("Lightning Overload hit " << 0.5f * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((LIGHTNING_BOLT_DAMAGE + (sim.spellpower_ + sim.lightning_bolt_->spellpower_bonus_) * LIGHTNING_BOLT_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.lightning_bolt_->damage_multiplier_))
        
//           procList(sim.p_lightning_overload_hit, sim.p_lightning_overload_hit_count, P_SPELL | P_LIGHTNING_BOLT | P_HIT);
//         }
//       }

//     }

//     //chain lightning
//     else {

//       if (roll() < sim.spell_miss_) {
//         ++sim.stats_.lightning_overload_miss_;

//         COMBATLOG_EFFECT("Lightning Overload miss")

//         procList(sim.p_lightning_overload_miss, sim.p_lightning_overload_miss_count, P_SPELL | P_CHAIN_LIGHTNING | P_MISS);
//       }

//       else {

//         sim.consumeStormstrikeCharge();

//         if (roll() < sim.nature_crit_ + sim.chain_lightning_->crit_bonus_) {

//           ++sim.stats_.lightning_overload_crit_;
//           sim.stats_.lightning_overload_crit_damage_ += 0.5 * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                                 ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + sim.chain_lightning_->spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) *
//                                                 sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.chain_lightning_->damage_multiplier_);
          
//           COMBATLOG_EFFECT("Lightning Overload crit " << 0.5 * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + sim.chain_lightning_->spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) * sim.spell_crit_multiplier_ * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.chain_lightning_->damage_multiplier_))
        
//           procList(sim.p_lightning_overload_crit, sim.p_lightning_overload_crit_count, P_SPELL | P_CHAIN_LIGHTNING | P_CRIT);
//         }

//         else {
//           ++sim.stats_.lightning_overload_hit_;
//           sim.stats_.lightning_overload_damage_ += 0.5 * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ *
//                                             ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + sim.chain_lightning_->spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT)
//                                             * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.chain_lightning_->damage_multiplier_);
          
//           COMBATLOG_EFFECT("Lightning Overload hit " << 0.5 * sim.stormstrike_damage_multiplier_ * sim.nature_damage_reduction_ * ((CHAIN_LIGHTNING_DAMAGE + (sim.spellpower_ + sim.chain_lightning_->spellpower_bonus_) * CHAIN_LIGHTNING_COEFFICIENT) * sim.shock_damage_multiplier_ * sim.nature_damage_multiplier_ * sim.chain_lightning_->damage_multiplier_))
        
//           procList(sim.p_lightning_overload_hit, sim.p_lightning_overload_hit_count, P_SPELL | P_CHAIN_LIGHTNING | P_HIT);
//         }
//       }

//     }
//   }
// }

// void UnrelentingStorm::event(const int& event_id) {
  
//   sim.stats_.unrelenting_storm_regen_ += sim.regenMana(sim.int_ * mana_regen_multiplier_);

//   sim.addHighPrioEvent(500, this);
// }
