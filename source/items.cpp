//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "items.h"
#include "enhsim.h"

void TrinketCooldown::event(const int& event_id) {
  cd_ = false;
  cd_event_ = 0;

  if (sim.trinket1_) sim.trinket1_->use();
  if (sim.trinket2_) sim.trinket2_->use();
}

void ItemUse::event(const int& event_id) {
  if (event_id == EVENT_ID_BUFF_FADE) {
    removeBuff();
    uptime_ += sim.now() - proc_start_time_;
    buff_event_ = 0;
  }
  else {
    cd_ = false;
    cd_event_ = 0;
  }
  
  if (sim.trinket1_) sim.trinket1_->use();
  if (sim.trinket2_) sim.trinket2_->use();
}

void ItemUse::use() {
  if (!sim.trinket_cooldown_->cd_ && !cd_) {
    addBuff();
    proc_start_time_ = sim.now();

    cd_ = true;
    sim.trinket_cooldown_->cd_ = true;
    sim.addLowPrioEvent(buff_event_, duration_, this, EVENT_ID_BUFF_FADE);
    sim.addHighPrioEvent(sim.trinket_cooldown_->cd_event_, duration_, sim.trinket_cooldown_);
    sim.addHighPrioEvent(cd_event_, cd_duration_, this, EVENT_ID_COOLDOWN);
  }
}

void ItemUse::finalize() {
  if (buff_event_) {
    uptime_ += sim.now() - proc_start_time_;
  }
}

void ItemProc::reCalculateProcChance() {
  proc_chance_mh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_ / 60);
  proc_chance_oh_auto_attack_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_ / 60);
}

void ItemProc::calculateProcChance() {
  proc_chance_mh_instant_ = static_cast<int>(ppm_ * 100 * sim.mh.speed_base_ / 60); 
  proc_chance_oh_instant_ = static_cast<int>(ppm_ * 100 * sim.oh.speed_base_ / 60);
  reCalculateProcChance();
}

void ItemProc::proc(const int& proc_id) {

  if (!cd_) {

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

void ItemProc::trig() {
  if (cd_duration_) {
    cd_ = true;
    sim.addHighPrioEvent(cd_duration_, this, EVENT_ID_COOLDOWN);
  }

  trigger();
}

void ItemProc::event(const int& event_id) {
  cd_ = false;
}

void BuffItemProc::trigger() {

  if (buff_event_) {
    sim.que_.moveEvent(buff_event_, duration_);
  }
  else {
    addBuff();

    proc_start_time_ = sim.now();

    sim.addLowPrioEvent(buff_event_, duration_, this, EVENT_ID_BUFF_FADE);
  }
}

void BuffItemProc::event(const int& event_id) {

  if (event_id == EVENT_ID_BUFF_FADE) {
    removeBuff();

    uptime_ += sim.now() - proc_start_time_;

    buff_event_ = 0;
  }
  else {
    cd_ = false;
  }
}

void BuffItemProc::finalize() {
  if (buff_event_) {
    uptime_ += sim.now() - proc_start_time_;
  }
}
