//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "consumables.h"
#include "enhsim.h"

//void PotionCooldown::event(const int& event_id) {
//  sim.potion_->use();
//
//  sim.addLowPrioEvent(cooldown_, this);
//}

void Potion::use() {
  
  if (!potion_sickness_) {

    if (applyPotion()) {
      potion_sickness_ = true;
    }
  }
}

void BuffPotion::event(const int& event_id) {
  removeBuff();
}

void BuffPotion::use() {

  if (!potion_sickness_) {

    potion_sickness_ = true;
    applyBuff();

    sim.addLowPrioEvent(1500, this);
  }
}

void HastePotion::applyBuff() {
  sim.changeHaste(400 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Haste Potion used")
}

void HastePotion::removeBuff() {
  sim.changeHaste(-400 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Haste Potion fades")
}

void InsaneStrengthPotion::applyBuff() {
  sim.changeStrength(120);
  COMBATLOG_EFFECT("Insane Strength Potion used")
}

void InsaneStrengthPotion::removeBuff() {
  sim.changeStrength(-120);
  COMBATLOG_EFFECT("Insane Strength Potion fades")
}

void HeroicPotion::applyBuff() {
  sim.changeStrength(70);
  COMBATLOG_EFFECT("Heroic Potion used")
}

void HeroicPotion::removeBuff() {
  sim.changeStrength(-70);
  COMBATLOG_EFFECT("Heroic Potion fades")
}

bool ManaPotion::applyPotion() {

  //lets check do we have little enough mana to use mana potion
  //do not use mana potion if shamanistic rage is active
  if (sim.mana_ <= max_mana_to_use_ && !sim.shamanistic_rage_->active_) {

    sim.stats_.mana_potion_regen_ += sim.regenMana(mana_);
    COMBATLOG_EFFECT("Mana Potion used")

    return true;
  }

  return false;
}

void MiscCooldown::event(const int& event_id) {
  sim.misc_item_->use();

  sim.addHighPrioEvent(cd_event_, MISC_ITEM_COOLDOWN, this);
}

void MiscBuffItem::event(const int& event_id) {
  removeBuff();

  buff_event_ = 0;
}

void MiscBuffItem::use() {
  applyBuff();

  sim.addLowPrioEvent(buff_event_, duration_, this);
}

void DrumsOfBattle::applyBuff() {
  sim.changeHaste(80 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Drums of Battle used")
}

void DrumsOfBattle::removeBuff() {
  sim.changeHaste(-80 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Drums of Battle fades")
}
