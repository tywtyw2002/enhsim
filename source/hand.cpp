//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "hand.h"

Hand::Hand(): miss_base_(0),
              miss_(0),
              yellow_miss_(0),
              dodge_base_(0),
              dodge_(0),
              glancing_(0),

              last_swing_time_(0),
              next_swing_node_(0),

              speed_base_(0),
              speed_(0),
              dps_(0.0f),
              crit_base_(0),
              crit_(0),
              hit_(0),

              expertise_rating_(0.0f),
              expertise_(0),

              damage_(0.0f),
              damage_crit_(0.0f),

              miss_dodge_(0),
              miss_dodge_glancing_(0),
              miss_dodge_glancing_crit_(0),
              yellow_miss_dodge_(0),

              attack_(false) {

}

void Hand::calculateMiss() {
  //yellow miss is lower than normal miss
  yellow_miss_ = miss_base_ - hit_;
  miss_ = miss_base_ + DUAL_WIELD_MISS - hit_;

  if (miss_ < 0) miss_ = 0;

  if (yellow_miss_ < 0) yellow_miss_ = 0;

  //lets calculate the hit table too
  calculateHitTable();
}

void Hand::calculateDodge() {
  //expertise reduces boss's dodge
  dodge_ = dodge_base_ - expertise_ * EXPERTISE_DODGE_BONUS;

  if (dodge_ < 0) dodge_ = 0;

  calculateHitTable();
}

void Hand::calculateHitTable() {
  //hit table consists of these variables + miss_
  //first hit roll is tested against miss, then miss_dodge, then miss_dodge_glancing etc
  miss_dodge_ = miss_ + dodge_;
  miss_dodge_glancing_ = miss_dodge_ + glancing_;
  miss_dodge_glancing_crit_ = miss_dodge_glancing_ + crit_;
  yellow_miss_dodge_ = yellow_miss_ + dodge_;
}

void Hand::calculateExpertise() {
  expertise_ = static_cast<int>(expertise_rating_ / EXPERTISE_RATING_TO_EXPERTISE);

  calculateDodge();
}
