//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "weapon_enchants.h"
#include "enhsim.h"

void MhWindfury::proc(const int& proc_id) {
  if (roll() < proc_chance_) {
    if (!sim.wf_cd_) {

      sim.wf_cd_ = true;
      sim.last_wf_ = sim.now();

      wfSwing();
      wfSwing();

      sim.addHighPrioEvent(WF_COOLDOWN, this);
    }else{
      COMBATLOG_EFFECT("MH WF CD_HIT")
    }
  }
}

void MhWindfury::event(const int& event_id) {
  sim.wf_cd_ = false;
  sim.skill_rotation_->action();
}

void MhWindfury::wfSwing() {

  int rol = roll();

  if (rol < sim.mh.yellow_miss_) {
    ++sim.stats_.mh_wf_miss_;

    COMBATLOG_EFFECT("MH WF miss")

    procList(sim.p_mh_windfury_miss, sim.p_mh_windfury_miss_count, P_MELEE | P_INSTANT | P_WINDFURY | P_MH | P_MISS);
  }

  else if (rol < sim.mh.yellow_miss_dodge_) {
    ++sim.stats_.mh_wf_dodge_;
    
    COMBATLOG_EFFECT("MH WF dodge")

    procList(sim.p_mh_windfury_dodge, sim.p_mh_windfury_dodge_count, P_MELEE | P_INSTANT | P_WINDFURY | P_MH | P_DODGE);
  }

  //2-roll system
  else {

    if (roll() < sim.mh.crit_) {
      ++sim.stats_.mh_wf_crit_;
      //here we add the normal damage plus wf bonus ap damage, and then multiply it with an multiplier(elemental weapons)
      sim.stats_.mh_wf_crit_damage_ += (sim.mh.damage_crit_ +
                                       (bonus_ap_ / 14.0f * sim.mh.speed_base_ / 100 * sim.damage_reduction_) *
                                        sim.physical_crit_multiplier_ * sim.physical_damage_multiplier_) * damage_multiplier_;
      
      COMBATLOG_EFFECT("MH WF crit " << (sim.mh.damage_crit_ + (bonus_ap_ / 14.0f * sim.mh.speed_base_ / 100 * sim.damage_reduction_) * sim.physical_crit_multiplier_ * sim.physical_damage_multiplier_) * damage_multiplier_)

      procList(sim.p_mh_windfury_crit, sim.p_mh_windfury_crit_count, P_MELEE | P_INSTANT | P_WINDFURY | P_MH | P_CRIT);
    }

    else {
      
      ++sim.stats_.mh_wf_hit_;
      sim.stats_.mh_wf_hit_damage_ += (sim.mh.damage_ +
                                      (bonus_ap_ / 14.0f * sim.mh.speed_base_ / 100 * sim.damage_reduction_ * sim.physical_damage_multiplier_)) * damage_multiplier_;
      
      COMBATLOG_EFFECT("MH WF hit " << (sim.mh.damage_ + (bonus_ap_ / 14.0f * sim.mh.speed_base_ / 100 * sim.damage_reduction_ * sim.physical_damage_multiplier_)) * damage_multiplier_)

      procList(sim.p_mh_windfury_hit, sim.p_mh_windfury_hit_count, P_MELEE | P_INSTANT | P_WINDFURY | P_MH | P_HIT);
    }
  }
}

void OhWindfury::proc(const int& proc_id) {
  if (roll() < proc_chance_) {
    if (!sim.wf_cd_) {

      sim.wf_cd_ = true;
      sim.last_wf_ = sim.now();

      wfSwing();
      wfSwing();

      sim.addHighPrioEvent(WF_COOLDOWN, this);
    }else{
      COMBATLOG_EFFECT("OH WF CD_HIT")
    }
  }
}

void OhWindfury::event(const int& event_id) {
  sim.wf_cd_ = false;
  sim.skill_rotation_->action();
}

void OhWindfury::wfSwing() {

  int rol = roll();

  if (rol < sim.oh.yellow_miss_) {
    ++sim.stats_.oh_wf_miss_;
    
    COMBATLOG_EFFECT("OH WF miss")

    procList(sim.p_oh_windfury_miss, sim.p_oh_windfury_miss_count, P_MELEE | P_INSTANT | P_WINDFURY | P_OH | P_MISS);
  }
  
  else if (rol < sim.oh.yellow_miss_dodge_) {
    ++sim.stats_.oh_wf_dodge_;
    
    COMBATLOG_EFFECT("OH WF dodge")

    procList(sim.p_oh_windfury_dodge, sim.p_oh_windfury_dodge_count, P_MELEE | P_INSTANT | P_WINDFURY | P_OH | P_DODGE);
  }
  
  else {

    if (roll() < sim.oh.crit_) {
      ++sim.stats_.oh_wf_crit_;
      sim.stats_.oh_wf_crit_damage_ += (sim.oh.damage_crit_ +
                                       (bonus_ap_ / 14.0f * sim.oh.speed_base_ / 100 * sim.damage_reduction_) *
                                        sim.physical_crit_multiplier_ * sim.physical_damage_multiplier_) * damage_multiplier_;
      
      COMBATLOG_EFFECT("OH WF crit " << (sim.oh.damage_crit_ + (bonus_ap_ / 14.0f * sim.oh.speed_base_ / 100 * sim.damage_reduction_) * sim.physical_crit_multiplier_ * sim.physical_damage_multiplier_) * damage_multiplier_)

      procList(sim.p_oh_windfury_crit, sim.p_oh_windfury_crit_count, P_MELEE | P_INSTANT | P_WINDFURY | P_OH | P_CRIT);
    }
    
    else {
      ++sim.stats_.oh_wf_hit_;
      sim.stats_.oh_wf_hit_damage_ += (sim.oh.damage_ +
                                      (bonus_ap_ / 14.0f * sim.oh.speed_base_ / 100 * sim.damage_reduction_ * sim.physical_damage_multiplier_)) * damage_multiplier_;
      
      COMBATLOG_EFFECT("OH WF hit " << (sim.oh.damage_ + (bonus_ap_ / 14.0f * sim.oh.speed_base_ / 100 * sim.damage_reduction_ * sim.physical_damage_multiplier_)) * damage_multiplier_)

      procList(sim.p_oh_windfury_hit, sim.p_oh_windfury_hit_count, P_MELEE | P_INSTANT | P_WINDFURY | P_OH | P_HIT);
    }
  }
}


void MhFlametongue::proc(const int& proc_id) {
  int rol = roll();

  if (rol < sim.spell_miss_) {
    ++sim.stats_.mh_ft_miss_;
    COMBATLOG_EFFECT("MH Flametongue miss")

    procList(sim.p_mh_flametongue_miss, sim.p_mh_flametongue_miss_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_MH | P_MISS);
  }

  else {
    
    if (roll() < sim.fire_crit_) {
      ++sim.stats_.mh_ft_crit_;
      sim.stats_.mh_ft_crit_damage_ += sim.fire_damage_reduction_ *
                                  (FLAMETONGUE_DAMAGE * sim.mh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) *
                                  sim.spell_crit_multiplier_ * damage_multiplier_;

      COMBATLOG_EFFECT("MH Flametongue crit " << sim.fire_damage_reduction_ * (FLAMETONGUE_DAMAGE * sim.mh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) * sim.spell_crit_multiplier_ * damage_multiplier_)

      procList(sim.p_mh_flametongue_crit, sim.p_mh_flametongue_crit_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_MH | P_CRIT);
    }

    else {
      ++sim.stats_.mh_ft_hit_;
      sim.stats_.mh_ft_hit_damage_ += sim.fire_damage_reduction_ *
                                  (FLAMETONGUE_DAMAGE * sim.mh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) *
                                  damage_multiplier_;

      COMBATLOG_EFFECT("MH Flametongue hit " << sim.fire_damage_reduction_ * (FLAMETONGUE_DAMAGE * sim.mh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) * damage_multiplier_)
    
      procList(sim.p_mh_flametongue_hit, sim.p_mh_flametongue_hit_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_MH | P_HIT);
    }

  }
}

void OhFlametongue::proc(const int& proc_id) {
  int rol = roll();

  if (rol < sim.spell_miss_) {
    ++sim.stats_.oh_ft_miss_;
    COMBATLOG_EFFECT("OH Flametongue miss")

    procList(sim.p_oh_flametongue_miss, sim.p_oh_flametongue_miss_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_OH | P_MISS);
  }

  else {
    
    if (roll() < sim.fire_crit_) {
      ++sim.stats_.oh_ft_crit_;
      sim.stats_.oh_ft_crit_damage_ += sim.fire_damage_reduction_ *
                                  (FLAMETONGUE_DAMAGE * sim.oh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) *
                                  sim.spell_crit_multiplier_ * damage_multiplier_;

      COMBATLOG_EFFECT("OH Flametongue crit " << sim.fire_damage_reduction_ * (FLAMETONGUE_DAMAGE * sim.oh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) * sim.spell_crit_multiplier_ * damage_multiplier_)

      procList(sim.p_oh_flametongue_crit, sim.p_oh_flametongue_crit_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_OH | P_CRIT);
    }

    else {
      ++sim.stats_.oh_ft_hit_;
      sim.stats_.oh_ft_hit_damage_ += sim.fire_damage_reduction_ *
                                  (FLAMETONGUE_DAMAGE * sim.oh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) *
                                  damage_multiplier_;

      COMBATLOG_EFFECT("OH Flametongue hit " << sim.fire_damage_reduction_ * (FLAMETONGUE_DAMAGE * sim.oh.speed_base_ / 100 + sim.spellpower_ * FLAMETONGUE_COEFFICIENT) * damage_multiplier_)

      procList(sim.p_oh_flametongue_hit, sim.p_oh_flametongue_hit_count, P_MELEE | P_INSTANT | P_FLAMETONGUE | P_OH | P_HIT);
    }

  }
}
