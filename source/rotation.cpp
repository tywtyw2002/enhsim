//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "rotation.h"
#include "enhsim.h"

void PriorityRotation::action() {

  if (!sim.global_cooldown_->cd_ && !sim.spell_casting_->casting_) {

    for (int i=0; i<sim.rotation_count_; ++i) {

      if (sim.rotation_[i]->cast()) {
        return;
      }
    }
  }
}

bool GenericRotationNode::action() {
  return true;
}

void GenericRotationNode::addItem(const std::string& item) {
}

void GenericRotation::action() {
}

void GenericRotation::addNode(const std::string& node) {
}

// bool Rotation::waitSS_WF() {
//  return !sim.wf_cd_ || WF_COOLDOWN - (sim.now() - sim.last_wf_) > sim.wait_ss_wf_;
// }

// void FS_ES_Rotation::action() {
//  if (!sim.global_cooldown_->cd_) {
//    if (!sim.stormstrike_->cd_ && waitSS_WF()) {
//      sim.stormstrike_->cast();
//    }
//    else if (!sim.shock_cooldown_->cd_) {
//      if (sim.flame_shock_->dots_ > 0) {
//        sim.earth_shock_->cast();
//      }
//      else {
//        sim.flame_shock_->cast();
//      }      
//    }
//    else if (sim.maelstrom_weapon_) {
//      if (sim.maelstrom_weapon_->stack_ == 5) {
//        sim.maelstrom_weapon_->spell_->cast();
//      }
//    }
//  }
// }

// void ES_Rotation::action() {
//  if (!sim.global_cooldown_->cd_) {
//    if (!sim.stormstrike_->cd_ && waitSS_WF()) {
//      sim.stormstrike_->cast();
//    }
//    else if (!sim.shock_cooldown_->cd_) {
//      sim.earth_shock_->cast(); 
//    }
//  }
// }

// void FS_Rotation::action() {
//  if (!sim.global_cooldown_->cd_) {
//    if (!sim.stormstrike_->cd_ && waitSS_WF()) {
//      sim.stormstrike_->cast();
//    }
//    else if (!sim.shock_cooldown_->cd_) {
//      sim.flame_shock_->cast(); 
//    }
//  }
// }

// void Frost_Rotation::action() {
//  if (!sim.global_cooldown_->cd_) {
//    if (!sim.stormstrike_->cd_ && waitSS_WF()) {
//      sim.stormstrike_->cast();
//    }
//    else if (!sim.shock_cooldown_->cd_) {
//      sim.frost_shock_->cast(); 
//    }
//  }
// }

// void SS_Rotation::action() {
//  if (!sim.global_cooldown_->cd_) {
//    if (!sim.stormstrike_->cd_ && waitSS_WF()) {
//      sim.stormstrike_->cast();
//    }
//  }
// }
