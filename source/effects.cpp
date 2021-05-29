//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "effects.h"
#include "items.h"
#include "enhsim.h"
#include <math.h>

void SimulationProgress::event(const int& event_id) {
  ++reported_count_;
  std::cout << ".";

  sim.addLowPrioEvent(interval_, this);
}



void MhEvent::event(const int& event_id) {
  sim.mh_swang_ = true;
  sim.mhSwing();
  //sim.mh.next_swing_node_ = 0;
  //sim.que_.addEvent(0, PRIORITY_MH_RESCHEDULE, sim.mh_reschedule_, 0);
}

void OhEvent::event(const int& event_id) {
  sim.oh_swang_ = true;
  sim.ohSwing();
  //sim.oh.next_swing_node_ = 0;
  //sim.que_.addEvent(0, PRIORITY_OH_RESCHEDULE, sim.oh_reschedule_, 0);
}

void CombatLength::event(const int& event_id) {

  //set mana to max
  sim.mana_ = sim.max_mana_;

  //reset bloodlust
  if (sim.bloodlust_->use_) {
    if (sim.bloodlust_->buff_event_) {
      sim.que_.deleteEvent(sim.bloodlust_->buff_event_);
      sim.changeHasteMultiplier(1.0f, HASTE_BLOODLUST);
      COMBATLOG_EFFECT("Bloodlust fades")
    }
    else {
      sim.que_.deleteEvent(sim.bloodlust_->cd_event_);
      sim.bloodlust_->cd_event_ = 0;
    }

    sim.bloodlust_->use();
  }

  //reset potion
  if (sim.potion_) {
    sim.potion_->potion_sickness_ = false;
    sim.potion_->use();
  }

  //reset misc item
  if (sim.misc_item_) {
    if (sim.misc_cooldown_->cd_event_) {
      sim.que_.deleteEvent(sim.misc_cooldown_->cd_event_);
      sim.misc_cooldown_->cd_event_ = 0;
    }
    if (sim.misc_item_->buff_event_) {
      sim.que_.deleteEvent(sim.misc_item_->buff_event_);
      MiscBuffItem* i = dynamic_cast<MiscBuffItem*>(sim.misc_item_);
      if (i) {
        i->removeBuff();
        i->buff_event_ = 0;
      }
    }

    sim.misc_cooldown_->event(0);
  }

  //reset trinket cooldown
  if (sim.trinket_cooldown_->cd_event_) {
    sim.que_.deleteEvent(sim.trinket_cooldown_->cd_event_);
    sim.trinket_cooldown_->cd_event_ = 0;
    sim.trinket_cooldown_->cd_ = false;
  }

  //if trinkets are on use trinkets:
  //delete the events from the event que, remove possible buff, reset the trinket
  if (sim.trinket1_) {
    ItemUse* t = dynamic_cast<ItemUse*>(sim.trinket1_);

    if (t) {
      if (t->buff_event_) {
        sim.que_.deleteEvent(t->buff_event_);
        t->removeBuff();
        t->uptime_ += sim.now() - t->proc_start_time_;
        t->buff_event_ = 0;
      }
      if (t->cd_event_) {
        sim.que_.deleteEvent(t->cd_event_);
        t->cd_ = false;
        t->cd_event_ = 0;
      }
    }
  }
  if (sim.trinket2_) {
    ItemUse* t = dynamic_cast<ItemUse*>(sim.trinket2_);

    if (t) {
      if (t->buff_event_) {
        sim.que_.deleteEvent(t->buff_event_);
        t->removeBuff();
        t->uptime_ += sim.now() - t->proc_start_time_;
        t->buff_event_ = 0;
      }
      if (t->cd_event_) {
        sim.que_.deleteEvent(t->cd_event_);
        t->cd_ = false;
        t->cd_event_ = 0;
      }
    }
  }

  //reset the searing totem
  if (sim.searing_totem_->cd_event_) {
    sim.que_.deleteEvent(sim.searing_totem_->cd_event_);
    sim.searing_totem_->cd_event_ = 0;
    sim.searing_totem_->ticks_ = 0;
  }

  //reset shamanistic rage
  if (sim.shamanistic_rage_->buff_event_) {
    sim.que_.deleteEvent(sim.shamanistic_rage_->buff_event_);
    sim.shamanistic_rage_->buff_event_ = 0;
  }
  if (sim.shamanistic_rage_->cd_event_) {
    sim.que_.deleteEvent(sim.shamanistic_rage_->cd_event_);
    sim.shamanistic_rage_->cd_event_ = 0;
  }
  sim.shamanistic_rage_->active_ = false;
  sim.shamanistic_rage_->cd_ = false;


  //use trinkets
  if (sim.trinket1_) sim.trinket1_->use();
  if (sim.trinket2_) sim.trinket2_->use();

  set();

  sim.skill_rotation_->action();
}

void CombatLength::set() {
  sim.addHighPrioEvent(duration_, this);
}

// MaelstromCaster::MaelstromCaster(EnhSim* simulator, Castable* spell, unsigned int min_charges): Castable(simulator, 0), spell_(spell), min_charges_(min_charges) {
//   if (sim.maelstrom_weapon_->min_stack_to_action_ > min_charges) {
//     sim.maelstrom_weapon_->min_stack_to_action_ = min_charges;
//   }
// }

// bool MaelstromCaster::cast() {
//   if (sim.maelstrom_weapon_->stack_ >= min_charges_) {
//     return spell_->cast();
//   }

//   return false;
// }

void SpellCasting::event(const int& event_id) {
  spell_->castingFinished();
  casting_ = false;
  sim.addHighPrioEvent(sim.randomLag(), sim.input_lag_);

  if (sim.mh.attack_) sim.addMhEvent(sim.mh.next_swing_node_, ceil(mh_swing_left_ * haste_divider_ / sim.melee_haste_divider_));
  if (sim.oh.attack_) sim.addOhEvent(sim.oh.next_swing_node_, ceil(oh_swing_left_ * haste_divider_ / sim.melee_haste_divider_));
}

void SpellCasting::startCasting(Castable* spell, const int64& time, bool reset_swing) {

  if (time == 0) {
    spell->castingFinished();
    return;
  }


  if (sim.mh.attack_) {
    if (sim.mh_swang_) {
      sim.mh_swang_ = false;
      mh_swing_left_ = sim.mh.speed_;
    }
    else {
      if (!reset_swing) {
        mh_swing_left_ = sim.mh.next_swing_node_->timestamp_ - sim.now();
      }
      else {
        mh_swing_left_ = sim.mh.speed_;
      }
      sim.que_.deleteEvent(sim.mh.next_swing_node_);
      //sim.mh.next_swing_node_ = 0;
    }
  }

  if (sim.oh.attack_) {
    if (sim.oh_swang_) {
      sim.oh_swang_ = false;
      oh_swing_left_ = sim.oh.speed_;
    }
    else {
      if (!reset_swing) {
        oh_swing_left_ = sim.oh.next_swing_node_->timestamp_ - sim.now();
      }
      else {
        oh_swing_left_ = sim.oh.speed_;
      }

      sim.que_.deleteEvent(sim.oh.next_swing_node_);
      //sim.oh.next_swing_node_ = 0;
    }
  }

  //take current haste divider, this is needed to calculate the remaining time with swings
  haste_divider_ = sim.melee_haste_divider_;


  COMBATLOG_EFFECT("Casting started");

  spell_ = spell;
  casting_ = true;
  sim.addHighPrioEvent(time , this);
}

void InputLag::event(const int& event_id) {
  sim.skill_rotation_->action();
}

void ManaRegen::event(const int& event_id) {
  
  sim.stats_.mp5_regen_ += sim.regenMana(sim.mp5_regen_per_tick_);

  if (!sim.fsr_->cd_) {
    sim.stats_.mana_regen_ += sim.regenMana(sim.mana_regen_per_tick_);
  }

  if (replenishment_) {
    sim.stats_.replenishment_regen_ += sim.regenMana(static_cast<f32>(sim.max_mana_ * 0.0025f * MANA_REGEN_INTERVAL / 100.0f));
  }

  sim.addHighPrioEvent(MANA_REGEN_INTERVAL, this);
}

void FiveSecRule::event(const int& event_id) {
  cd_ = false;
  cd_event_ = 0;
}

void FiveSecRule::trigger() {

  if (cd_event_) {
    sim.que_.moveEventSearchForward(cd_event_, 500);
  }
  else {
    cd_ = true;
    sim.addHighPrioEvent(cd_event_, 500, this);
  }
}

void JudgementOfWisdom::event(const int& event_id) {
  cd_ = false;
}

void JudgementOfWisdom::proc(const int& proc_id) {

  if (!cd_ && roll() < 5000) {
    sim.stats_.judgement_of_wisdom_regen_ += sim.regenMana(sim.max_mana_ * 0.01f);

    COMBATLOG_EFFECT("Judgement of Wisdom procs " << sim.max_mana_ * 0.01f)

    cd_ = true;
    sim.addHighPrioEvent(400, this);
  }
}

void Bloodlust::event(const int& event_id) {

  if (event_id == EVENT_ID_BUFF_FADE) {
    buff_event_ = 0;
    sim.changeHasteMultiplier(1.0f, HASTE_BLOODLUST);

    sim.addLowPrioEvent(cd_event_, cooldown_, this);

    COMBATLOG_EFFECT("Bloodlust fades")
  }
  else {
    cd_event_ = 0;

    use();
  }
}

void Bloodlust::use() {
  sim.changeHasteMultiplier(1.30f, HASTE_BLOODLUST);
  sim.addLowPrioEvent(buff_event_, duration_, this, EVENT_ID_BUFF_FADE);

  COMBATLOG_EFFECT("Bloodlust gained")
}
