  //EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "enhsimconfig.h"
#include "enchants.h"
#include <cctype>
#include <math.h>

const int EPTEST_COUNT = 15;

EPThread::EPThread(EnhSimConfig* enhsimconfig, const f32& hours): enhsimconfig_(enhsimconfig), hours_(hours),
#ifndef NOTHREADS
  lock_(),
#endif
  sim_index_(0) {
}

void EPThread::run() {
//void SimulationThread::operator()() {
//void SimulationThread(EnhSimConfig* enhsimconfig_, f32 hours_) {
  std::string message;
  bool skip = false;

  while (true) {

    std::stringstream msg;

#ifndef NOTHREADS
    lock_.acquire();
#endif
    /*{
    boost::mutex::scoped_lock lock(mutex);*/

    if (enhsimconfig_->ep_task_index_ == 0) {
      msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Baseline DPS calculated.";
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 1) {
      if (enhsimconfig_->ep_ap_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Attack power skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setAttackPower(enhsimconfig_->attack_power_ + enhsimconfig_->ep_ap_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Attack power calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 2) {
      if (enhsimconfig_->ep_crit_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Crit(physical) skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMhCrit(enhsimconfig_->mh_crit_ + static_cast<int>(enhsimconfig_->ep_crit_rating_ * CRIT_RATING_TO_CRIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setOhCrit(enhsimconfig_->oh_crit_ + static_cast<int>(enhsimconfig_->ep_crit_rating_ * CRIT_RATING_TO_CRIT));
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Crit(physical) calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 3) {
      if (enhsimconfig_->ep_spellcrit_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Crit(spell) skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setNatureCrit(enhsimconfig_->nature_crit_ + static_cast<int>(enhsimconfig_->ep_spellcrit_rating_ * SPELLCRIT_RATING_TO_SPELLCRIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setFireCrit(enhsimconfig_->fire_crit_ + static_cast<int>(enhsimconfig_->ep_spellcrit_rating_ * SPELLCRIT_RATING_TO_SPELLCRIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setFrostCrit(enhsimconfig_->frost_crit_ + static_cast<int>(enhsimconfig_->ep_spellcrit_rating_ * SPELLCRIT_RATING_TO_SPELLCRIT));
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Crit(spell) calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 4) {
      if (enhsimconfig_->ep_hit_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Hit(physical) skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMhHit(enhsimconfig_->mh_hit_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_HIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setOhHit(enhsimconfig_->oh_hit_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_HIT));
        // enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpellHit(enhsimconfig_->spell_hit_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_SPELLHIT));
        // enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpellHitTotem(enhsimconfig_->spell_hit_totem_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_SPELLHIT));
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Hit(physical) calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 5) {
      if (enhsimconfig_->ep_spellhit_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Hit(spell) skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        // enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMhHit(enhsimconfig_->mh_hit_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_HIT));
        // enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setOhHit(enhsimconfig_->oh_hit_ + static_cast<int>(enhsimconfig_->ep_hit_rating_ * HIT_RATING_TO_HIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpellHit(enhsimconfig_->spell_hit_ + static_cast<int>(enhsimconfig_->ep_spellhit_rating_ * SPELLHIT_RATING_TO_SPELLHIT));
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpellHitTotem(enhsimconfig_->spell_hit_totem_ + static_cast<int>(enhsimconfig_->ep_spellhit_rating_ * SPELLHIT_RATING_TO_SPELLHIT));
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Hit(spell) calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 6) {
      if (enhsimconfig_->ep_expertise_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Expertise skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMhExpertiseRating(enhsimconfig_->mh_expertise_rating_ + enhsimconfig_->ep_expertise_rating_);
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setOhExpertiseRating(enhsimconfig_->oh_expertise_rating_ + enhsimconfig_->ep_expertise_rating_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Expertise calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 7) {
      if (enhsimconfig_->ep_haste_rating_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Haste skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setHaste(enhsimconfig_->haste_ + enhsimconfig_->ep_haste_rating_ * HASTE_RATING_TO_HASTE);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Haste calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 8) {
      if (enhsimconfig_->ep_armor_ignore_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Armor Ignore skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        // enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setArmorPenetration(enhsimconfig_->armor_penetration_ - enhsimconfig_->ep_armor_penetration_ * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setArmorIgnore(enhsimconfig_->ep_armor_ignore_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Armor Ignore calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }


    else if (enhsimconfig_->ep_task_index_ == 9) {
      if (enhsimconfig_->ep_spellpower_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Spellpower skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpellpower(enhsimconfig_->spellpower_ + enhsimconfig_->ep_spellpower_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Spellpower calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 10) {
      if (enhsimconfig_->ep_dps_ == 0.0f) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mh Dps skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMhDps(enhsimconfig_->mh_dps_ + enhsimconfig_->ep_dps_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mh Dps calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 11) {
      if (enhsimconfig_->ep_dps_ == 0.0f) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Oh Dps skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setOhDps(enhsimconfig_->oh_dps_ + enhsimconfig_->ep_dps_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Oh Dps calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 12) {
      if (enhsimconfig_->ep_mana_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mana skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMaxMana(enhsimconfig_->max_mana_ + enhsimconfig_->ep_mana_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mana calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 13) {
      if (enhsimconfig_->ep_spirit_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Spirit skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setSpirit(enhsimconfig_->spirit_ + enhsimconfig_->ep_spirit_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Spirit calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == 14) {
      if (enhsimconfig_->ep_mp5_ == 0) {
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mp5 skipped.";
        skip = true;
        enhsimconfig_->ep_skipped_++;
      }
      else {
        enhsimconfig_->enhsims_[enhsimconfig_->ep_task_index_]->setMp5(enhsimconfig_->mp5_ + enhsimconfig_->ep_mp5_);
        msg << "Calculation " << enhsimconfig_->ep_task_index_+1 << "/" << EPTEST_COUNT << ": Mp5 calculated.";
      }
      sim_index_ = enhsimconfig_->ep_task_index_;
    }

    else if (enhsimconfig_->ep_task_index_ == EPTEST_COUNT - 1 + enhsimconfig_->threads_) {
      enhsimconfig_->printEPValues(hours_);
#ifndef NOTHREADS
      enhsimconfig_->condition_.signal();
#endif
      //enhsimconfig_->condition_.notify_one();
      return;
    }
    else {
      ++enhsimconfig_->ep_task_index_;
      return;
    }

    ++enhsimconfig_->ep_task_index_;

#ifndef NOTHREADS
    lock_.release();
#endif
    //}

    if (!skip) {
      enhsimconfig_->enhsims_[sim_index_]->simulate(hours_);
      enhsimconfig_->statsv_[sim_index_].seconds_ = static_cast<int64>(hours_ * 3600);
    }
    skip = false;
    std::getline(msg, message);
    std::cout << message << std::endl;
  }
}

SimulationThread::SimulationThread(EnhSimConfig* enhsimconfig, EnhSim* enhsim, const f32& hours): enhsimconfig_(enhsimconfig), sim_(enhsim),
#ifndef NOTHREADS
  lock_(),
#endif
  hours_(hours) {
}

void SimulationThread::run() {
  sim_->simulate(hours_);

#ifndef NOTHREADS
  lock_.acquire();

  //i use the ep_task_index to see if all the threads are finished
  if (++enhsimconfig_->ep_task_index_ == enhsimconfig_->threads_) {
    enhsimconfig_->condition_.signal();
  }

  lock_.release();
#endif
}

void EnhSimConfig::printEPValues(const f32& hours_) {
  double ap_dps = (statsv_[1].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_ap_) / (hours_ * 3600); if (ep_ap_ == 0) ap_dps = 0;
  double critp_dps = (statsv_[2].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_crit_rating_) / (hours_ * 3600); if (ep_crit_rating_ == 0) critp_dps = 0;
  double spellcrit_dps = (statsv_[3].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_spellcrit_rating_) / (hours_ * 3600); if (ep_spellcrit_rating_ == 0) spellcrit_dps = 0;
  double hit_dps = (statsv_[4].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_hit_rating_) / (hours_ * 3600); if (ep_hit_rating_ == 0) hit_dps = 0;
  double spellhit_dps = (statsv_[5].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_spellhit_rating_) / (hours_ * 3600); if (ep_spellhit_rating_ == 0) spellhit_dps = 0;
  double expertise_dps = (statsv_[6].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_expertise_rating_) / (hours_ * 3600); if (ep_expertise_rating_ == 0) expertise_dps = 0;
  double haste_dps = (statsv_[7].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_haste_rating_) / (hours_ * 3600); if (ep_haste_rating_ == 0) haste_dps = 0;
  double armor_ignore_dps = (statsv_[8].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_armor_ignore_) / (hours_ * 3600); if (ep_armor_ignore_ == 0) armor_ignore_dps = 0;
  double spellpower_dps = (statsv_[9].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_spellpower_) / (hours_ * 3600); if (ep_spellpower_ == 0) spellpower_dps = 0;
  double mh_dps = (statsv_[10].getTotalDamage() - statsv_[0].getTotalDamage()) / fabs(ep_dps_) / (hours_ * 3600); if (ep_dps_ == 0) mh_dps = 0;
  double oh_dps = (statsv_[11].getTotalDamage() - statsv_[0].getTotalDamage()) / fabs(ep_dps_) / (hours_ * 3600); if (ep_dps_ == 0) oh_dps = 0;
  double mana_dps = (statsv_[12].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_mana_) / (hours_ * 3600); if (ep_mana_ == 0) mana_dps = 0;
  double spirit_dps = (statsv_[13].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_spirit_) / (hours_ * 3600); if (ep_spirit_ == 0) spirit_dps = 0;
  double mp5_dps = (statsv_[14].getTotalDamage() - statsv_[0].getTotalDamage()) / abs(ep_mp5_) / (hours_ * 3600); if (ep_mp5_ == 0) mp5_dps = 0;

  double base_dps;
  if (ep_ap_base_) {
    base_dps = ap_dps;
  }
  else {
    base_dps = spellpower_dps;
  }

  if (base_dps == 0) {
    base_dps = 8.9884656743115795e+307;
  }
  
  //used to notify is part of ep value is missing because of skipped tests
  bool valuemissing = false;
  std::string vmissing = "";

  std::cout << "\n\n";
  std::cout << std::setw(26) << std::left << "EP" << std::setw(10) << "value" << std::setw(10) << "DPS" << std::setw(15) << "total DPS" << "difference\n\n" << std::fixed << std::setprecision(2);
  std::cout << std::setw(46) << "baseline" << statsv_[0].getTotalDamage() / (hours_ * 3600) << std::endl;

  std::cout << std::setw(26) << std::left << "ap" << std::setw(10) << ap_dps / base_dps << std::setw(10) << ap_dps << std::setw(15) << statsv_[1].getTotalDPS() << statsv_[1].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "crit rating" << std::setw(10) << (critp_dps) / base_dps << std::setw(10) << critp_dps << std::setw(15) << statsv_[2].getTotalDPS() - statsv_[0].getTotalDPS() << statsv_[2].getTotalDPS() - statsv_[0].getTotalDPS() * 2 << std::endl;
  std::cout << std::setw(26) << std::left << "hit rating" << std::setw(10) << hit_dps / base_dps << std::setw(10) << hit_dps << std::setw(15) << statsv_[4].getTotalDPS() << statsv_[4].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "spellcrit rating" << std::setw(10) << spellcrit_dps / base_dps << std::setw(10) << spellcrit_dps << std::setw(15) <<  statsv_[3].getTotalDPS() - statsv_[0].getTotalDPS() <<  statsv_[3].getTotalDPS() - statsv_[0].getTotalDPS() * 2 << std::endl;
  std::cout << std::setw(26) << std::left << "spellhit rating" << std::setw(10) << spellhit_dps / base_dps << std::setw(10) << hit_dps << std::setw(15) << statsv_[5].getTotalDPS() << statsv_[5].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;
  
  std::cout << std::setw(26) << std::left << "expertise rating" << std::setw(10) << expertise_dps / base_dps << std::setw(10) << expertise_dps << std::setw(15) << statsv_[6].getTotalDPS() << statsv_[6].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "haste rating" << std::setw(10) << haste_dps / base_dps << std::setw(10) << haste_dps << std::setw(15) << statsv_[7].getTotalDPS() << statsv_[7].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "armor ignore" << std::setw(10) << armor_ignore_dps / base_dps << std::setw(10) << armor_ignore_dps << std::setw(15) << statsv_[8].getTotalDPS() << statsv_[8].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "spellpower" << std::setw(10) << spellpower_dps / base_dps << std::setw(10) << spellpower_dps << std::setw(15) << statsv_[9].getTotalDPS() << statsv_[9].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "mh dps" << std::setw(10) << mh_dps / base_dps << std::setw(10) << mh_dps << std::setw(15) << statsv_[10].getTotalDPS() << statsv_[10].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;
  std::cout << std::setw(26) << std::left << "oh dps" << std::setw(10) << oh_dps / base_dps << std::setw(10) << oh_dps << std::setw(15) << statsv_[11].getTotalDPS() << statsv_[11].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;
  
  vmissing = ""; if (ep_ap_ == 0) { vmissing = "*"; valuemissing = true; }
  std::cout << std::setw(26) << std::left << "strength" + vmissing << std::setw(10) << ap_dps / base_dps * STRENGTH_TO_AP * strenght_multiplier_ << std::endl;
  
  vmissing = ""; if (ep_ap_ == 0 || ep_crit_rating_ == 0) { vmissing = "*"; valuemissing = true; }
  std::cout << std::setw(26) << std::left << "agility" + vmissing << std::setw(10) << (//ap_dps / base_dps * AGILITY_TO_AP +
                                                                                       critp_dps / base_dps * (AGILITY_TO_CRIT / CRIT_RATING_TO_CRIT)) * agility_multiplier_ << std::endl;
  
  vmissing = ""; if (ep_ap_ == 0 || ep_crit_rating_ == 0 || ep_spirit_ == 0 || ep_mp5_ == 0 || ep_mana_ == 0) { vmissing = "*"; valuemissing = true; }
  std::cout << std::setw(26) << std::left << "intelligence" + vmissing << std::setw(10) << (//ap_dps / base_dps * int_to_ap_multiplier_ +
                                                                                            spellcrit_dps / base_dps * (INTELLIGENCE_TO_SPELLCRIT / SPELLCRIT_RATING_TO_SPELLCRIT) +
                                                                                            // (sqrt(static_cast<double>(intelligence_ + ep_spirit_)) - sqrt(static_cast<double>(intelligence_))) / ep_spirit_ * spirit_dps / base_dps / spirit_multiplier_ +
                                                                                            // mp5_dps / base_dps + //* enhsims_[0]->unrelenting_storm_->mana_regen_multiplier_ +
                                                                                            mana_dps / base_dps * INTELLIGENCE_TO_MANA) * intelligence_multiplier_ << std::endl;

  std::cout << std::setw(26) << std::left << "spirit" << std::setw(10) << spirit_dps / base_dps << std::setw(10) << spirit_dps << std::setw(15) << statsv_[12].getTotalDPS() << statsv_[13].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "mana" << std::setw(10) << mana_dps / base_dps << std::setw(10) << mana_dps << std::setw(15) << statsv_[11].getTotalDPS() << statsv_[12].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  std::cout << std::setw(26) << std::left << "mp5" << std::setw(10) << mp5_dps / base_dps << std::setw(10) << mp5_dps << std::setw(15) << statsv_[14].getTotalDPS() << statsv_[14].getTotalDPS() - statsv_[0].getTotalDPS() << std::endl;

  if (valuemissing) {
    std::cout << "\n* part of the EP value is missing because of skipped tests.";
  }
  std::cout << "\n\n";
}

EnhSimConfig::EnhSimConfig()
#ifndef NOTHREADS
  : lock_(), condition_(lock_)
#endif
  {
  reset();
}

EnhSimConfig::~EnhSimConfig() {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    delete enhsims_[i];
  }
}

void EnhSimConfig::reset() {
  ep_ = false;
  threads_ = 1;

  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    delete enhsims_[i];
  }
  enhsims_.clear();
  statsv_.clear();

  ep_ap_base_ = true;
  ep_ap_ = 0;
  ep_crit_rating_ = 0;
  ep_hit_rating_ = 0;
  ep_expertise_rating_ = 0.0f;
  ep_haste_rating_ = 0;
  ep_armor_ignore_ = 0;
  // ep_armor_penetration_ = 0;
  ep_spellcrit_rating_ = 0;
  ep_spellhit_rating_ = 0;
  ep_spellpower_ = 0;
  ep_dps_ = 0.0f;
  ep_spirit_ = 0;
  ep_mp5_ = 0;

  ep_skipped_ = 0;

  ep_task_index_ = 0;

  mh_dps_ = 0.0f;
  oh_dps_ = 0.0f;
  rockbiter_multiplier_ = 1.0f;
  improved_weapon_totems_multiplier_ = 1.0f;

  mh_speed_ = 0;
  oh_speed_ = 0;

  mh_crit_ = 0;
  oh_crit_ = 0;

  mh_hit_ = 0;
  oh_hit_ = 0;

  attack_power_ = 0;
  haste_ = 1.0f;

  mh_expertise_rating_ = 0.0f;
  oh_expertise_rating_ = 0.0f;

  // armor_penetration_ = 1.0f;
  armor_ignore_ = 0;

  mp5_ = 0;
  max_mana_ = 0.0f;

  strength_ = 0;
  agility_ = 0;
  intelligence_ = 0;
  spirit_ = 0;

  // int_to_ap_multiplier_ = 0.0f;
  strenght_multiplier_ = 1.0f;
  agility_multiplier_ = 1.0f;
  intelligence_multiplier_ = 1.0f;
  spirit_multiplier_ = 1.0f;
  ap_to_spellpower_multiplier_ = 0.0f;

  miss_ = 0;
  dodge_ = 0;
  glancing_ = 0;
  spell_miss_ = 0;
  armor_ = 0;

  nature_resistance_ = 0;
  fire_resistance_ = 0;
  frost_resistance_ = 0;

  spellpower_ = 0;
  nature_crit_ = 0;
  fire_crit_ = 0;
  frost_crit_ = 0;
  spell_hit_ = 0;
  spell_hit_totem_ = 0;
  mental_quickness_mana_ = 0.0f;
  convection_mana_ = 0.0f;

  physical_damage_multiplier_ = 1.0f;
  nature_damage_multiplier_ = 1.0f;
  fire_damage_multiplier_ = 1.0f;
  frost_damage_multiplier_ = 1.0f;
  firetotem_damage_multiplier_ = 1.0f;

  physical_crit_multiplier_ = PHYSICAL_CRITICAL_MULTIPLIER;
  spell_crit_multiplier_ = SPELL_CRITICAL_MULTIPLIER;
  spell_crit_bonus_ = 0.0f;

  windfury_bonus_ap_ = 0;

  wait_ss_wf_ = 0;

  ap_buff_multiplier_ = false;
  spell_crit_buff_ = false;

  water_shield_multiplier_ = 1.0f;

  simulate_mana_ = true;

  mh_weapon_enchant_.clear();
  oh_weapon_enchant_.clear();
  mh_weapon_.clear();
  oh_weapon_.clear();
}

void EnhSimConfig::setEP(bool ep_ap_base, const int& ap, const int& crit_rating, const int& hit_rating, const int& expertise, const int& haste_rating, const int& armor_ignore, const int& spellpower, const int& spellcrit_rating, const int& spellhit_rating, const f32& dps, const int& mana, const int& spirit, const int& mp5){
  ep_ap_base_ = ep_ap_base;
  
  ep_ap_ = ap;
  ep_crit_rating_ = crit_rating;
  ep_hit_rating_ = hit_rating;
  ep_expertise_rating_ = expertise * EXPERTISE_RATING_TO_EXPERTISE;
  ep_haste_rating_ = haste_rating;
  ep_armor_ignore_ = armor_ignore;
  ep_spellcrit_rating_ = spellcrit_rating;
  ep_spellhit_rating_ = spellhit_rating;
  // ep_armor_penetration_ = armor_penetration;
  ep_spellpower_ = spellpower;
  ep_dps_ = dps;
  ep_mana_ = mana;
  ep_spirit_ = spirit;
  ep_mp5_ = mp5;

  ep_ = true;
}

void EnhSimConfig::setThreads(const int& count) {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    delete enhsims_[i];
  }

  threads_ = count;

  if (ep_) {
    enhsims_.resize(EPTEST_COUNT);
    statsv_.clear();
    statsv_.resize(EPTEST_COUNT);

    for (unsigned int i=0; i<EPTEST_COUNT; ++i) {
#ifdef DEBUG
      enhsims_[i] = new EnhSim(statsv_[i], getCombatLog());
#else
      enhsims_[i] = new EnhSim(statsv_[i]);
#endif
    }
  }
  else {
    enhsims_.resize(threads_);
    statsv_.clear();
    statsv_.resize(threads_);

    for (unsigned int i=0; i<threads_; ++i) {
#ifdef DEBUG
      enhsims_[i] = new EnhSim(statsv_[i], getCombatLog());
#else
      enhsims_[i] = new EnhSim(statsv_[i]);
#endif
    }
  }
}

// void EnhSimConfig::setMaelstromWeapon(const std::string& spell) {
//  for (unsigned int i=0; i<enhsims_.size(); ++i) {

//    if (spell == "lvb") {
//      enhsims_[i]->maelstrom_weapon_->spell_ = enhsims_[i]->lava_burst_;
//      enhsims_[i]->useEffect(enhsims_[i]->maelstrom_weapon_);
//    }
//    else if (spell == "lb") {
//      enhsims_[i]->maelstrom_weapon_->spell_ = enhsims_[i]->lightning_bolt_;
//      enhsims_[i]->useEffect(enhsims_[i]->maelstrom_weapon_);
//    }
//  }
// }

void EnhSimConfig::setRotationCount(const int& count) {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    enhsims_[i]->setRotationCount(count);
  }
}

void EnhSimConfig::setRotation(const std::string& castable, const int& priority) {

  static bool sr = false;
  static bool sr_added = false;

  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    Castable* c = 0;

    if (toLower(castable) == "ss") {
      c = enhsims_[i]->stormstrike_;
    }
    else if (toLower(castable) == "fs") {
      c = enhsims_[i]->flame_shock_;
    }
    else if (toLower(castable) == "es") {
      c = enhsims_[i]->earth_shock_;
    }
    else if (toLower(castable) == "frost") {
      c = enhsims_[i]->frost_shock_;
    }
    // else if (toLower(castable).find("mw") != std::string::npos) {

    //   if (toLower(castable).find("lb") != std::string::npos) {
    //     c = new MaelstromCaster(enhsims_[i], enhsims_[i]->lightning_bolt_, stringToInt(castable.substr(2,1)));
    //   }
    //   else if (toLower(castable).find("cl") != std::string::npos) {
    //     c = new MaelstromCaster(enhsims_[i], enhsims_[i]->chain_lightning_, stringToInt(castable.substr(2,1)));
    //   }
    // }
    // else if (toLower(castable) == "ls") {
    //   c = enhsims_[i]->lightning_shield_;
    // }
    // else if (toLower(castable) == "ll") {
    //   c = enhsims_[i]->lava_lash_;
    // }
    // else if (toLower(castable) == "lb") {
    //   c = enhsims_[i]->lightning_bolt_;
    // }
    // else if (toLower(castable) == "cl") {
    //   c = enhsims_[i]->chain_lightning_;
    // }
    // else if (toLower(castable) == "lvb") {
    //   c = enhsims_[i]->lava_burst_;
    // }
    else if (toLower(castable) == "st") {
      c = enhsims_[i]->searing_totem_;
    }
    else if (toLower(castable) == "sr") {
        c = enhsims_[i]->shamanistic_rage_;
        sr = true;
    }

    enhsims_[i]->rotation_[priority] = c;
  }

  //set the Shamanistic Rage, check that it is added only once in every case
  if (sr && simulate_mana_) {
    if (!sr_added) {
      for (unsigned int i=0; i<enhsims_.size(); ++i) {
        enhsims_[i]->useEffect(enhsims_[i]->shamanistic_rage_);
      }
      sr_added = true;
    }
  }
  
}

void EnhSimConfig::setRotationSettings(bool mh_attack, bool oh_attack, bool cast_ll_only_if_wf_on_cd_, const f32& lvb_ed, const int& lvb_fsdots, bool lvb_fs_active, /*const f32& mw_lvb_cd, */const int& fs_cast_dots, const int& ls_charges, const f32& sr_mana) {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    // if (mh_weapon_enchant_ == "windfury" && oh_weapon_enchant_ == "windfury") {
    //   enhsims_[i]->lava_lash_->cast_only_if_wf_on_cd_ = cast_ll_only_if_wf_on_cd_;
    // }

    enhsims_[i]->setAutoAttack(mh_attack, oh_attack);

    // enhsims_[i]->lava_burst_->max_ed_left = static_cast<int64>(lvb_ed * 100);

    // enhsims_[i]->lava_burst_->max_fsdots_left_ = lvb_fsdots;

    // enhsims_[i]->lava_burst_->cast_only_if_fs_active_ = lvb_fs_active;

    //enhsims_[i]->lava_burst_->max_wait_ = static_cast<int64>(mw_lvb_cd * 100);

    enhsims_[i]->flame_shock_->max_dots_left_ = fs_cast_dots;

    // enhsims_[i]->lightning_shield_->max_charges_to_recast_ = ls_charges;

    enhsims_[i]->shamanistic_rage_->max_mana_to_cast_ = sr_mana;
  }
}

// void EnhSimConfig::setRotation(const std::string& rotation, const f32& average_shocks_per_minute, const int& use_approx) {
//   for (unsigned int i=0; i<enhsims_.size(); ++i) {

//     if (use_approx == 1) {
//       enhsims_[i]->use_shock_approximation_ = true;
//     }
//     else {
//       enhsims_[i]->use_shock_approximation_ = false;
//     }

//     if (!enhsims_[i]->use_shock_approximation_) {
//       if (rotation == "fs_es") {
//         enhsims_[i]->skill_rotation_ = new FS_ES_Rotation(enhsims_[i]);
//       }
//       else if (rotation == "es") {
//         enhsims_[i]->skill_rotation_ = new ES_Rotation(enhsims_[i]);
//       }
//       else if (rotation == "fs") {
//         enhsims_[i]->skill_rotation_ = new FS_Rotation(enhsims_[i]);
//       }
//       else if (rotation == "frost") {
//         enhsims_[i]->skill_rotation_ = new Frost_Rotation(enhsims_[i]);
//       }
//       else {
//         //"empty" rotation, only SS
//         enhsims_[i]->skill_rotation_ = new SS_Rotation(enhsims_[i]);
//       }

//       enhsims_[i]->shock_cooldown_->cooldown_ = 6000 / average_shocks_per_minute;

//     }
//     else {
//       //average shocks, use "empty" rotation, only SS
//       enhsims_[i]->skill_rotation_ = new SS_Rotation(enhsims_[i]);
//       enhsims_[i]->average_shocks_per_minute_ = average_shocks_per_minute;
//       enhsims_[i]->rotation_ = rotation;
//     }
//   }
// }

void EnhSimConfig::setRace(const std::string& race) {

  if (race == "orc") {

    if (mh_weapon_ == "axe") {
      mh_expertise_rating_ += ceil(5 * EXPERTISE_RATING_TO_EXPERTISE);
    }
    if (oh_weapon_ == "axe") {
      oh_expertise_rating_ += ceil(5 * EXPERTISE_RATING_TO_EXPERTISE);
    }
  }

  if (race == "draenei") {
    // mh_hit_ += 100;
    // oh_hit_ += 100;
    spell_hit_ += 100;
    spell_hit_totem_ += 100;
  }
}

void EnhSimConfig::setMhWeapon(std::string name) {
  mh_weapon_ = name;
}

void EnhSimConfig::setOhWeapon(std::string name) {
  oh_weapon_ = name;
}

void EnhSimConfig::setTalent(const std::string& name, const int& rank) {
  if (rank > 0) {

    bool once = true;
    for (unsigned int i=0; i<enhsims_.size(); ++i) {

      if (name == "flurry") {
        enhsims_[i]->useEffect(enhsims_[i]->flurry_);
        enhsims_[i]->useEffect(enhsims_[i]->flurry_consume_);
        enhsims_[i]->flurry_->haste_ += 1.05f + rank * FLURRY_HASTE;
      }

      else if (name == "improved_weapon_totems") {
        if (once) {
          improved_weapon_totems_multiplier_ = 1.0f + rank * IMPROVED_WEAPON_TOTEMS;
        }
      }

      else if (name == "elemental_weapons") {
        enhsims_[i]->mh_windfury_->damage_multiplier_ = 1.0f + rank * WINDFURY_ELEMENTAL_WEAPONS;
        enhsims_[i]->oh_windfury_->damage_multiplier_ = 1.0f + rank * WINDFURY_ELEMENTAL_WEAPONS;
        enhsims_[i]->mh_flametongue_->damage_multiplier_ = 1.0f + rank * FLAMETONGUE_ELEMENTAL_WEAPONS;
        enhsims_[i]->oh_flametongue_->damage_multiplier_ = 1.0f + rank * FLAMETONGUE_ELEMENTAL_WEAPONS;

        if (once) {
          rockbiter_multiplier_ = 1.0f + rank * ROCKBITER_ELEMENTAL_WEAPONS;

          // if (mh_weapon_enchant_ == "flametongue") spellpower_ += static_cast<int>(FLAMETONGUE_BONUS_SPELLPOWER * rank * FLAMETONGUE_ELEMENTAL_WEAPONS);
          // if (oh_weapon_enchant_ == "flametongue") spellpower_ += static_cast<int>(FLAMETONGUE_BONUS_SPELLPOWER * rank * FLAMETONGUE_ELEMENTAL_WEAPONS);
        }
      }

      else if (name == "mental_quickness") {
        if (once) {
          ap_to_spellpower_multiplier_ = rank * MENTAL_QUICKNESS;
          mental_quickness_mana_ = rank * MENTAL_QUICKNESS_MANA;
        }
      }

      // else if (name == "mental_dexterity") {
      //   if (once) {
      //     int_to_ap_multiplier_ = rank * MENTAL_DEXTERITY;
      //   }
      // }

      else if (name == "shamanistic_focus") {
        if (once) {
          shamanistic_focus_mana_ = SHAMANISTIC_FOCUS_MANA;
        }
      }

      // else if (name == "ancestral_knowledge") {
      //   if (once) {
      //     intelligence_multiplier_ *= 1.0f + rank * ANCESTRAL_KNOWLEDGE;
      //   }
      // }

      // else if (name == "weapon_mastery") {
      //   if (once) {
      //     if (rank == 1) {
      //       physical_damage_multiplier_ *= 1.0f + WEAPON_MASTERY_RANK1;
      //     }
      //     if (rank == 2) {
      //       physical_damage_multiplier_ *= 1.0f + WEAPON_MASTERY_RANK2;
      //     }
      //     if (rank == 3) {
      //       physical_damage_multiplier_ *= 1.0f + WEAPON_MASTERY_RANK3;
      //     }
      //   }
      // }
      else if (name == "weapon_mastery") {
        if (once) {
          physical_damage_multiplier_ *= 1.0f + rank * WEAPON_MASTERY;
        }
      }

      else if (name == "dual_wield_specialization") {
        if (once) {
          mh_hit_ += rank * DUAL_WIELD_SPECIALIZATION;
          oh_hit_ += rank * DUAL_WIELD_SPECIALIZATION;
          //spell_hit_ += rank * DUAL_WIELD_SPECIALIZATION;
          //spell_hit_totem_ += rank * DUAL_WIELD_SPECIALIZATION;
        }
      }

      // else if (name == "improved_stormstrike") {
      //   enhsims_[i]->stormstrike_->charges_per_cast_ += rank;
      //   enhsims_[i]->stormstrike_->cooldown_ -= rank * IMPROVED_STORMSTRIKE;
      // }

      else if (name == "unleashed_rage") {
        if (!ap_buff_multiplier_) {
          enhsims_[i]->useEffect(enhsims_[i]->unleashed_rage_);
          enhsims_[i]->unleashed_rage_->ap_multiplier_ = 1.0f + rank * UNLEASHED_RAGE;
        }
      }

      else if (name == "natures_guidance") {
        if (once) {
          mh_hit_ += rank * NATURES_GUIDANCE;
          oh_hit_ += rank * NATURES_GUIDANCE;

          spell_hit_ += rank * NATURES_GUIDANCE;
          spell_hit_totem_ += rank * NATURES_GUIDANCE;
        }
      }

      // else if (name == "maelstrom_weapon") {
      //   enhsims_[i]->maelstrom_weapon_->ppm_ = rank * MAELSTROM_WEAPON;
      //   enhsims_[i]->useEffect(enhsims_[i]->maelstrom_weapon_);
      // }

      // else if (name == "improved_shields") {
      //   enhsims_[i]->lightning_shield_->damage_multiplier_ *= 1.0f + rank * IMPROVED_SHIELDS;
      // }

      // else if (name == "static_shock") {
      //   enhsims_[i]->useEffect(enhsims_[i]->static_shock_);
      //   enhsims_[i]->static_shock_->proc_chance_ = rank * STATIC_SHOCK;
      //   enhsims_[i]->lightning_shield_->charges_per_cast_ += rank * 2;
      // }

      /*else if (name == "shamanistic_rage") {
        enhsims_[i]->useEffect(enhsims_[i]->shamanistic_rage_);
      }*/

      else if (name == "concussion") {
        enhsims_[i]->setShockDamageMultiplier(1.0f + rank * CONCUSSION);
      }

      else if (name == "convection") {
        if (once) {
          convection_mana_ = rank * CONVECTION_MANA;
        }
      }

      else if (name == "call_of_flame") {
        enhsims_[i]->setFiretotemDamageMultiplier(1.0f + rank * CALL_OF_FLAME);
        // enhsims_[i]->setLavaBurstDamageMultiplier(1.0f + rank * CALL_OF_FLAME_LAVA_BURST);
      }

      // else if (name == "call_of_thunder") {
      //   enhsims_[i]->lightning_bolt_->crit_bonus_ = CALL_OF_THUNDER;
      //   enhsims_[i]->chain_lightning_->crit_bonus_ = CALL_OF_THUNDER;
      // }

      // else if (name == "unrelenting_storm") {
      //   enhsims_[i]->unrelenting_storm_->mana_regen_multiplier_ = rank * UNRELENTING_STORM;
      //   enhsims_[i]->unrelenting_storm_->use_ = true;
      // }

      // else if (name == "reverberation") {
      //   enhsims_[i]->shock_cooldown_->cooldown_ -= rank * REVERBERATION;
      // }

      else if (name == "elemental_devastation") {
        enhsims_[i]->useEffect(enhsims_[i]->elemental_devastation_);
        enhsims_[i]->elemental_devastation_->crit_ = rank * ELEMENTAL_DEVASTATION;
      }

      else if (name == "elemental_focus") {
        enhsims_[i]->useEffect(enhsims_[i]->elemental_focus_);
      }

      else if (name == "elemental_fury") {
        if (once) {
          spell_crit_bonus_ += ELEMENTAL_FURY * rank;
        }
      }

      else if (name == "elemental_precision") {
        if (once) {
          spell_hit_ += rank * ELEMENTAL_PRECISION;
        }
      }

      // else if (name == "lightning_mastery") {
      //   enhsims_[i]->lightning_bolt_->casting_time_ -= rank * LIGHTNING_MASTERY;
      //   enhsims_[i]->chain_lightning_->casting_time_ -= rank * LIGHTNING_MASTERY;
      //   enhsims_[i]->lava_burst_->casting_time_ -= rank * LIGHTNING_MASTERY;
      // }

      // else if (name == "elemental_oath") {
      //   if (!spell_crit_buff_) {
      //     enhsims_[i]->useEffect(enhsims_[i]->elemental_oath_);
      //     if (rank == 1) {
      //       enhsims_[i]->elemental_oath_->crit_bonus_ = ELEMENTAL_OATH_RANK1;
      //     }
      //     if (rank == 2) {
      //       enhsims_[i]->elemental_oath_->crit_bonus_ = ELEMENTAL_OATH_RANK2;
      //     }
      //   }
      // }

      // else if (name == "lightning_overload") {
      //   enhsims_[i]->useEffect(enhsims_[i]->lightning_overload_);
      //   enhsims_[i]->lightning_overload_->proc_chance_ = rank * LIGHTNING_OVERLOAD;
      // }

      // else if (name == "lava_flows") {
      //   if (rank == 1) {
      //     enhsims_[i]->lava_burst_->crit_damage_bonus_ += LAVA_FLOWS_RANK1;
      //   }
      //   if (rank == 2) {
      //     enhsims_[i]->lava_burst_->crit_damage_bonus_ += LAVA_FLOWS_RANK2;
      //   }
      //   if (rank == 3) {
      //     enhsims_[i]->lava_burst_->crit_damage_bonus_ += LAVA_FLOWS_RANK3;
      //   }
      // }

      // else if (name == "storm_earth_and_fire") {
      //   enhsims_[i]->flame_shock_->dot_damage_multiplier_ *= 1.0f + (rank * STORM_EARTH_AND_FIRE_FS);
      //   enhsims_[i]->chain_lightning_->cd_duration_ -= rank * STORM_EARTH_AND_FIRE_CL;
      // }

      once = false;
    }
  }
}

void EnhSimConfig::setMhWeaponEnchant(const std::string& name) {

  mh_weapon_enchant_ = name;

  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (mh_weapon_enchant_ == "windfury" && oh_weapon_enchant_ == "windfury") {
      enhsims_[i]->mh_windfury_->proc_chance_ = WINDFURY_DUALWIELD_PROC_CHANCE;
      enhsims_[i]->oh_windfury_->proc_chance_ = WINDFURY_DUALWIELD_PROC_CHANCE;
    }
    /*else {
      enhsims_[i]->mh_windfury_->proc_chance_ = WINDFURY_PROC_CHANCE;
      enhsims_[i]->oh_windfury_->proc_chance_ = WINDFURY_PROC_CHANCE;
    }*/

    if (mh_weapon_enchant_ == "windfury") {
      enhsims_[i]->useEffect(enhsims_[i]->mh_windfury_);
      //enhsims_[i]->mh_windfury_->bonus_ap_ += WINDFURY_BONUS_AP;
    }
    else if (mh_weapon_enchant_ == "flametongue") {
      enhsims_[i]->useEffect(enhsims_[i]->mh_flametongue_);
      if (once) {
        // spellpower_ += FLAMETONGUE_BONUS_SPELLPOWER;
        mh_dps_ += rockbiter_multiplier_ * ROCKBITER_DPS;
      }
    }
    else {
      if (once && name != "-") {
        std::cout << "Imbue " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setOhWeaponEnchant(const std::string& name) {
  
  oh_weapon_enchant_ = name;

  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (mh_weapon_enchant_ == "windfury" && oh_weapon_enchant_ == "windfury") {
      enhsims_[i]->mh_windfury_->proc_chance_ = WINDFURY_DUALWIELD_PROC_CHANCE;
      enhsims_[i]->oh_windfury_->proc_chance_ = WINDFURY_DUALWIELD_PROC_CHANCE;
    }
    /*else {
      enhsims_[i]->mh_windfury_->proc_chance_ = WINDFURY_PROC_CHANCE;
      enhsims_[i]->oh_windfury_->proc_chance_ = WINDFURY_PROC_CHANCE;
    }*/

    if (oh_weapon_enchant_ == "windfury") {
      enhsims_[i]->useEffect(enhsims_[i]->oh_windfury_);
      //enhsims_[i]->oh_windfury_->bonus_ap_ += WINDFURY_BONUS_AP;
    }
    else if (oh_weapon_enchant_ == "flametongue") {
      enhsims_[i]->useEffect(enhsims_[i]->oh_flametongue_);
      // enhsims_[i]->lava_lash_->damage_multiplier_ += 0.25f;
      if (once) {
        // spellpower_ += FLAMETONGUE_BONUS_SPELLPOWER;
        oh_dps_ += rockbiter_multiplier_ * ROCKBITER_DPS;
      }
    }
    else {
      if (once && name != "-") {
        std::cout << "Imbue " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setMhEnchant(const std::string& name) {

  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "mongoose") {
      Enchant* mh = new MhMongoose(enhsims_[i]);
      enhsims_[i]->useEffect(mh);
      enhsims_[i]->mh_enchant_ = mh;
    }
    else if (name == "crusader") {
      Enchant* mh = new MhCrusader(enhsims_[i]);
      enhsims_[i]->useEffect(mh);
      enhsims_[i]->mh_enchant_ = mh;
    }
    else if (name == "executioner") {
      Enchant* mh = new MhExecutioner(enhsims_[i]);
      enhsims_[i]->useEffect(mh);
      enhsims_[i]->mh_enchant_ = mh;

      OhExecutioner* oe = dynamic_cast<OhExecutioner*>(enhsims_[i]->oh_enchant_);
      if (oe) {
        oe->mh_executioner_ = dynamic_cast<MhExecutioner*>(mh);
      }
    }
    // else if (name == "deathfrost") {
    //   Enchant* mh = new MhDeathfrost(enhsims_[i]);
    //   enhsims_[i]->useEffect(mh);
    //   enhsims_[i]->mh_enchant_ = mh;
    // }
    else {
      if (once && name != "-") {
        std::cout << "Enchant " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setOhEnchant(const std::string& name) {

  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "mongoose") {
      Enchant* oh = new OhMongoose(enhsims_[i]);
      enhsims_[i]->useEffect(oh);
      enhsims_[i]->oh_enchant_ = oh;
    }
    else if (name == "crusader") {
      Enchant* oh = new OhCrusader(enhsims_[i]);
      enhsims_[i]->useEffect(oh);
      enhsims_[i]->oh_enchant_ = oh;
    }
    else if (name == "executioner") {
      Enchant* oh = new OhExecutioner(enhsims_[i]);
      enhsims_[i]->useEffect(oh);
      enhsims_[i]->oh_enchant_ = oh;

      MhExecutioner* me = dynamic_cast<MhExecutioner*>(enhsims_[i]->mh_enchant_);
      if (me) {
        dynamic_cast<OhExecutioner*>(oh)->mh_executioner_ = me;
      }
    }
    // else if (name == "deathfrost") {
    //   Enchant* oh = new OhDeathfrost(enhsims_[i]);
    //   enhsims_[i]->useEffect(oh);
    //   enhsims_[i]->oh_enchant_ = oh;
    // }
    else {
      if (once && name != "-") {
        std::cout << "Enchant " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setTrinket(const std::string& name, const int& index) {
  
  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "dragonspine_trophy") {
      Item* t = new DragonspineTrophy(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "madness_of_the_betrayer") {
      Item* t = new MadnessOfTheBetrayer(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "hourglass_of_the_unraveller") {
      Item* t = new HourglassOfTheUnraveller(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "tsunami_talisman") {
      Item* t = new TsunamiTalisman(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "shard_of_contempt") {
      Item* t = new ShardOfContempt(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "berserkers_call") {
      Item* t = new BerserkersCall(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "bloodlust_brooch") {
      Item* t = new BloodlustBrooch(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "abacus_of_violent_odds") {
      Item* t = new AbacusOfViolentOdds(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "badge_of_tenacity") {
      Item* t = new BadgeOfTenacity(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "shadowsong_panther") {
      Item* t = new ShadowsongPanther(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "ashtongue_talisman") {
      Item* t = new AshtongueTalisman(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "blackened_naaru_sliver") {
      Item* t = new BlackenedNaaruSliver(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    else if (name == "darkmoon_card_crusade") {
      Item* t = new DarkmoonCardCrusade(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    }
    // else if (name == "fury_of_the_five_flights") {
    //   Item* t = new FuryOfTheFiveFlights(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "grim_toll") {
    //   Item* t = new GrimToll(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "loathebs_shadow") {
    //   Item* t = new LoathebsShadow(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "mirror_of_truth") {
    //   Item* t = new MirrorOfTruth(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "the_skull_of_guldan") {
    //   Item* t = new TheSkullOfGuldan(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "meteorite_whetstone") {
    //   Item* t = new MeteoriteWhetstone(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "embrace_of_the_spider") {
    //   Item* t = new EmbraceOfTheSpider(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "dying_curse") {
    //   Item* t = new DyingCurse(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "illustration_of_the_dragon_soul") {
    //   Item* t = new IllustrationOfTheDragonSoul(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "sundial_of_the_exiled") {
    //   Item* t = new SundialOfTheExiled(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "forge_ember") {
    //   Item* t = new ForgeEmber(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "incisor_fragment") {
    //   Item* t = new IncisorFragment(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "mark_of_the_war_prisoner") {
    //   Item* t = new MarkOfTheWarPrisoner(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "sphere_of_the_red_dragons_blood") {
    //   Item* t = new SphereOfTheRedDragonsBlood(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    // else if (name == "tome_of_arcane_phenomena") {
    //   Item* t = new TomeOfArcanePhenomena(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   if (index == 1) enhsims_[i]->trinket1_ = t; else enhsims_[i]->trinket2_ = t;
    // }
    else {
      if (once && name != "-") {
        std::cout << "Trinket " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setTotem(const std::string& name) {
  
  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "stonebreakers_totem") {
      Item* t = new StonebreakersTotem(enhsims_[i]);
      enhsims_[i]->useEffect(t);
      enhsims_[i]->totem_ = t;
    }
    // else if (name == "skycall_totem") {
    //   Item* t = new SkycallTotem(enhsims_[i]);
    //   enhsims_[i]->useEffect(t);
    //   enhsims_[i]->totem_ = t;
    // }
    else if (name == "totem_of_the_astral_winds") {
      if (once) {
        windfury_bonus_ap_ += 80;
      }
    }
    // else if (name == "totem_of_ancestral_guidance") {
    //   enhsims_[i]->lightning_bolt_->spellpower_bonus_ += 85;
    //   enhsims_[i]->chain_lightning_->spellpower_bonus_ += 85;
    // }
    // else if (name == "totem_of_the_void") {
    //   enhsims_[i]->lightning_bolt_->spellpower_bonus_ += 55;
    //   enhsims_[i]->chain_lightning_->spellpower_bonus_ += 55;
    // }
    // else if (name == "totem_of_hex") {
    //   enhsims_[i]->lightning_bolt_->spellpower_bonus_ += 182;
    //   enhsims_[i]->chain_lightning_->spellpower_bonus_ += 182;
    // }
    // else if (name == "totem_of_splintering") {
    //   if (once) {
    //     windfury_bonus_ap_ += 212;
    //   }
    // }
    else {
      if (once && name != "-") {
        std::cout << "Totem " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setSetBonus(const std::string& name) {
  
  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "desolation_battlegear") {
      Item* set = new DesolationBattlegear(enhsims_[i]);
      enhsims_[i]->useEffect(set);
      enhsims_[i]->set_bonus_ = set;
    }
    else if (name == "cyclone_harness") {
      enhsims_[i]->stormstrike_->bonus_damage_ += 30;
    }
    else if (name == "cataclysm_harness") {
      enhsims_[i]->flurry_->haste_ += 0.05f;
    }
    else if (name == "skyshatter_harness_2") {
      enhsims_[i]->earth_shock_->mana_reduction_ += 0.10f;
      enhsims_[i]->flame_shock_->mana_reduction_ += 0.10f;
      enhsims_[i]->frost_shock_->mana_reduction_ += 0.10f;
    }
    else if (name == "skyshatter_harness_4") {
      enhsims_[i]->earth_shock_->mana_reduction_ += 0.10f;
      enhsims_[i]->flame_shock_->mana_reduction_ += 0.10f;
      enhsims_[i]->frost_shock_->mana_reduction_ += 0.10f;
      Item* set = new SkyshatterHarness(enhsims_[i]);
      enhsims_[i]->useEffect(set);
      enhsims_[i]->set_bonus_ = set;
    }
    // else if (name == "skyshatter_regalia_2") {
    //   if (once) {
    //     spellpower_ += 45;
    //     nature_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //     fire_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //     frost_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //   }
    // }
    // else if (name == "skyshatter_regalia_4") {
    //   if (once) {
    //     spellpower_ += 45;
    //     nature_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //     fire_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //     frost_crit_ += static_cast<int>(35 * CRIT_RATING_TO_SPELLCRIT);
    //   }
    //   enhsims_[i]->lightning_bolt_->damage_multiplier_ *= 1.05f;
    // }
    // else if (name == "naxx_melee_2") {
    //   enhsims_[i]->lightning_shield_->damage_multiplier_ *= 1.10f;
    // }
    // else if (name == "naxx_melee_4") {
    //   enhsims_[i]->lightning_shield_->damage_multiplier_ *= 1.10f;
    //   enhsims_[i]->flurry_->haste_ += 0.05f;
    // }
    // else if (name == "naxx_nuker_2") {
    //   enhsims_[i]->lightning_bolt_->mana_reduction_ += 0.05f;
    // }
    // else if (name == "naxx_nuker_4") {
    //   enhsims_[i]->lightning_bolt_->mana_reduction_ += 0.05f;
    //   enhsims_[i]->lava_burst_->crit_damage_bonus_ += 0.10f;
    // }
    // else if (name == "gladiators_earthshaker") {
    //   enhsims_[i]->stormstrike_->cooldown_ -= 100;
    // }
    else {
      if (once && name != "-") {
        std::cout << "Set bonus " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setMetagem(const std::string& name) {
  
  bool once = true;
  for (unsigned int i=0; i<enhsims_.size(); ++i) {

    if (name == "thundering_skyfire_diamond") {
      Item* meta = new ThunderingSkyfireDiamond(enhsims_[i]);
      enhsims_[i]->useEffect(meta);
      enhsims_[i]->metagem_ = meta;
    }
    else if (name == "relentless_earthstorm_diamond") {
      if (once) {
        physical_crit_multiplier_ *= 1.03f;
        spell_crit_multiplier_ *= 1.03f;
      }
    }
    else if (name == "chaotic_skyfire_diamond") {
      if (once) {
        physical_crit_multiplier_ *= 1.03f;
        spell_crit_multiplier_ *= 1.03f;
      }
    }
    // else if (name == "chaotic_skyflare_diamond") {
    //   if (once) {
    //     physical_crit_multiplier_ *= 1.03f;
    //     spell_crit_multiplier_ *= 1.03f;
    //   }
    // }
    // else if (name == "relentless_earthsiege_diamond") {
    //   if (once) {
    //     physical_crit_multiplier_ *= 1.03f;
    //     spell_crit_multiplier_ *= 1.03f;
    //   }
    // }
    // else if (name == "ember_skyflare_diamond") {
    //   if (once) {
    //     intelligence_multiplier_ *= 1.02f;
    //   }
    // }
    else {
      if (once && name != "-") {
        std::cout << "Metagem " << name << " not found." << std::endl;
      }
    }

    once = false;
  }
}

void EnhSimConfig::setBuff(const std::string& name, const double& value) {

  if (name == "armor_debuff_major") {
    armor_ -= static_cast<int>(value);
  }

  else if (name == "armor_debuff_minor") {
    armor_ -= static_cast<int>(value);
  }

  else if (name == "physical_vulnerability_debuff") {
    physical_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
  }

  else if (name == "melee_haste_buff") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->haste_multipliers_[HASTE_MELEE_RAID_BUFF] *= static_cast<f32>(value / 100 + 1.0);
    }
  }

  else if (name == "melee_crit_chance_buff") {
    mh_crit_ += static_cast<int>(value * 100);
    oh_crit_ += static_cast<int>(value * 100);
  }

  else if (name == "attack_power_buff_flat") {
    attack_power_ += static_cast<int>(value);
  }

  else if (name == "attack_power_buff_multiplier") {
    if (value > 0) {
      for (unsigned int i=0; i<enhsims_.size(); ++i) {
        enhsims_[i]->setAttackPowerMultiplier(1.1f * static_cast<f32>(value / 100));
      }

      //this flag is used to disable unleashed rage
      ap_buff_multiplier_ = true;
    }
  }

  else if (name == "spell_haste_buff") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->haste_multipliers_[HASTE_SPELL_RAID_BUFF] *= static_cast<f32>(value / 100 + 1.0);
    }
  }

  else if (name == "spell_crit_chance_buff") {
    if (value > 0) {
      nature_crit_ += static_cast<int>(value * 100);
      fire_crit_ += static_cast<int>(value * 100);
      frost_crit_ += static_cast<int>(value * 100);

      //this flag disables elemental oath
      spell_crit_buff_ = true;
    }
  }

  else if (name == "spell_crit_chance_debuff") {
    nature_crit_ += static_cast<int>(value * 100);
    fire_crit_ += static_cast<int>(value * 100);
    frost_crit_ += static_cast<int>(value * 100);
  }

  else if (name == "spell_damage_debuff") {
    nature_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    fire_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    frost_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
  }

  else if (name == "spellpower_buff") {
    spellpower_ += static_cast<int>(value);
  }

  else if (name == "spell_hit_chance_debuff") {
    spell_hit_ += static_cast<int>(value * 100);
    spell_hit_totem_ += static_cast<int>(value * 100);
  }

  else if (name == "haste_buff") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->haste_multipliers_[HASTE_MELEE_RAID_BUFF] *= static_cast<f32>(value / 100 + 1.0);
      enhsims_[i]->haste_multipliers_[HASTE_SPELL_RAID_BUFF] *= static_cast<f32>(value / 100 + 1.0);
    }
  }

  else if (name == "percentage_damage_increase") {
    physical_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    nature_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    fire_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    frost_damage_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
  }

  else if (name == "crit_chance_debuff") {
    mh_crit_ += static_cast<int>(value * 100);
    oh_crit_ += static_cast<int>(value * 100);
    // nature_crit_ += static_cast<int>(value * 100);
    // fire_crit_ += static_cast<int>(value * 100);
    // frost_crit_ += static_cast<int>(value * 100);
  }

  else if (name == "stat_multiplier") {
    strenght_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    agility_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    intelligence_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
    spirit_multiplier_ *= static_cast<f32>(value / 100 + 1.0);
  }

  if (name == "stat_add_buff") {
    strength_ += static_cast<int>(value);
    agility_ += static_cast<int>(value);
    intelligence_ += static_cast<int>(value);
    spirit_ += static_cast<int>(value);
  }

  else if (name == "agi_and_strength_buff") {
    strength_ += static_cast<int>(value);
    agility_ += static_cast<int>(value);
  }

  if (name == "intellect_buff") {
    intelligence_ += static_cast<int>(value);
  }

  if (name == "replenishment") {
    if (value > 0) {
      for (unsigned int i=0; i<enhsims_.size(); ++i) {
        enhsims_[i]->mana_regen_->replenishment_ = true;
      }
    }
  }

  if (name == "water_shield") {
    if (value > 0) {
      mp5_ += static_cast<int>(WATER_SHIELD_MP5 * water_shield_multiplier_);
    }
  }

  if (name == "mana_spring_totem") {
    if (value > 0) {
      mp5_ += MANA_SPRING_MP5;
    }
  }

  if (name == "blessing_of_wisdom") {
    if (value > 0) {
      mp5_ += BLESSING_OF_WISDOM_MP5;
    }
  }

  if (name == "judgement_of_wisdom") {
    if (value > 0) {
      for (unsigned int i=0; i<enhsims_.size(); ++i) {
        enhsims_[i]->useEffect(enhsims_[i]->judgement_of_wisdom_);
      }
    }
  }
}

void EnhSimConfig::setConsumable(const std::string& name) {

  if (name == "flask_of_relentless_assault") {
    attack_power_ += 120;
  }

  else if (name == "elixir_of_major_agility") {
    agility_ += 35;
    mh_crit_ += static_cast<int>(20 * CRIT_RATING_TO_CRIT);
    oh_crit_ += static_cast<int>(20 * CRIT_RATING_TO_CRIT);
    // nature_crit_ += static_cast<int>(20 * CRIT_RATING_TO_SPELLCRIT);
    // fire_crit_ += static_cast<int>(20 * CRIT_RATING_TO_SPELLCRIT);
    // frost_crit_ += static_cast<int>(20 * CRIT_RATING_TO_SPELLCRIT);
  }

  else if (name == "fel_strength_elixir") {
    attack_power_ += 90;
  }

  else if (name == "elixir_of_major_strength") {
    strength_ += 35;
  }

  else if (name == "elixir_of_demonslaying") {
    attack_power_ += 265;
  }

  else if (name == "elixir_of_the_mongoose") {
    agility_ += 25;
    mh_crit_ += static_cast<int>(28 * CRIT_RATING_TO_CRIT);
    oh_crit_ += static_cast<int>(28 * CRIT_RATING_TO_CRIT);
    // nature_crit_ += static_cast<int>(28 * CRIT_RATING_TO_SPELLCRIT);
    // fire_crit_ += static_cast<int>(28 * CRIT_RATING_TO_SPELLCRIT);
    // frost_crit_ += static_cast<int>(28 * CRIT_RATING_TO_SPELLCRIT);
  }

  else if (name == "elixir_of_mastery") {
    agility_ += 15;
    strength_ += 15;
    intelligence_ += 15;
    spirit_ += 15;
  }

  else if (name == "gurus_elixir") {
    agility_ += 20;
    strength_ += 20;
    intelligence_ += 20;
    spirit_ += 20;
  }

  else if (name == "elixir_of_mighty_agility") {
    agility_ += 45;
  }

  else if (name == "elixir_of_mighty_strength") {
    strength_ += 50;
  }

  else if (name == "elixir_of_draenic_wisdom") {
    intelligence_ += 30;
    spirit_ += 30;
  }

  else if (name == "haste_potion") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->potion_ = new HastePotion(enhsims_[i]);
    }
  }

  else if (name == "insane_strength_potion") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->potion_ = new InsaneStrengthPotion(enhsims_[i]);
    }
  }

  else if (name == "heroic_potion") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->potion_ = new HeroicPotion(enhsims_[i]);
    }
  }

  else if (name == "super_mana_potion") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->potion_ = new SuperManaPotion(enhsims_[i]);
    }
  }

  else if (name == "runic_mana_potion") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->potion_ = new RunicManaPotion(enhsims_[i]);
    }
  }

  else if (name == "roasted_clefthoof") {
    strength_ += 20;
  }

  // else if (name == "spice_hot_talbuk") {
  //   mh_hit_ += static_cast<int>(20 * HIT_RATING_TO_HIT);
  //   oh_hit_ += static_cast<int>(20 * HIT_RATING_TO_HIT);
  //   spell_hit_ += static_cast<int>(20 * HIT_RATING_TO_SPELLHIT);
  //   spell_hit_totem_ += static_cast<int>(20 * HIT_RATING_TO_SPELLHIT);
  // }

  else if (name == "ravager_dog") {
    attack_power_ += 40;
  }

  else if (name == "warp_burger") {
    agility_ += 20;
  }

  else if (name == "skullfish_soup") {
    // mh_crit_ += static_cast<int>(20 * CRIT_RATING_TO_CRIT);
    // oh_crit_ += static_cast<int>(20 * CRIT_RATING_TO_CRIT);
    nature_crit_ += static_cast<int>(20 * SPELLCRIT_RATING_TO_SPELLCRIT);
    fire_crit_ += static_cast<int>(20 * SPELLCRIT_RATING_TO_SPELLCRIT);
    frost_crit_ += static_cast<int>(20 * SPELLCRIT_RATING_TO_SPELLCRIT);
  }

  else {
    if (name != "-") {
      std::cout << "Consumable " << name << " not found." << std::endl;
    }
  }
}

void EnhSimConfig::setUseManaPotionMaxMana(const f32& potion_mana) {

  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    ManaPotion* potion = dynamic_cast<ManaPotion*>(enhsims_[i]->potion_);

    if (potion) {
      potion->max_mana_to_use_ = potion_mana;
    }
  }
}

void EnhSimConfig::setMiscItem(const std::string& name) {

  if (name == "drums_of_battle") {
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->misc_item_ = new DrumsOfBattle(enhsims_[i]);
    }
  }

  else {
    if (name != "-") {
      std::cout << "Misc item " << name << " not found." << std::endl;
    }
  }
}

// void EnhSimConfig::setGlyph(const std::string& name) {

//   bool once = true;
//   for (unsigned int i=0; i<enhsims_.size(); ++i) {

//     if (name == "lightning_shield") {
//       enhsims_[i]->lightning_shield_->damage_multiplier_ *= 1.20f;
//     }

//     else if (name == "flametongue_weapon") {
//       if (once) {
//         if (mh_weapon_enchant_ == "flametongue" || oh_weapon_enchant_ == "flametongue") {
//           nature_crit_ += 200;
//           fire_crit_ += 200;
//           frost_crit_ += 200;
//         }
//       }
//     }

//     else if (name == "lightning_bolt") {
//       enhsims_[i]->lightning_bolt_->mana_reduction_ += 0.10f;
//     }

//     else if (name == "windfury_weapon") {
//       enhsims_[i]->mh_windfury_->bonus_ap_ = static_cast<int>(enhsims_[i]->mh_windfury_->bonus_ap_ * 1.40f);
//       enhsims_[i]->oh_windfury_->bonus_ap_ = static_cast<int>(enhsims_[i]->oh_windfury_->bonus_ap_ * 1.40f);
//     }

//     else if (name == "stormstrike") {
//       enhsims_[i]->stormstrike_->spell_damage_bonus_multiplier_ += 0.08f;
//     }

//     else if (name == "earth_shock") {
//       enhsims_[i]->earth_shock_->gcd_reduction_ = 100;
//     }

//     else if (name == "flame_shock") {
//       enhsims_[i]->flame_shock_->dots_per_cast_ += 2;
//       enhsims_[i]->lava_burst_->consume_fs_ = false;
//     }

//     else if (name == "lava") {
//       enhsims_[i]->lava_burst_->coefficient_bonus_ += 0.10f;
//     }

//     else if (name == "lava_lash") {
//       if (oh_weapon_enchant_ == "flametongue") {
//         enhsims_[i]->lava_lash_->damage_multiplier_ += 0.10f;
//       }
//     }

//     else if (name == "water_mastery") {
//       water_shield_multiplier_ *= 1.30f;
//     }

//     else {
//       if (once && name != "-") {
//           std::cout << "Glyph " << name << " not found." << std::endl;
//       }
//     }

//     once = false;
//   }
// }

void EnhSimConfig::setCombatLength(const f32& minutes) {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    //enhsims_[i]->potion_cooldown_->cooldown_ = minutes * 6000;
    enhsims_[i]->combat_length_->duration_ = minutes * 6000;
  }
}

void EnhSimConfig::setBloodlust(const int& casters, const int& sync) {
  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    
    if (casters == 1) {
      enhsims_[i]->bloodlust_->cooldown_ = 60000 - enhsims_[i]->bloodlust_->duration_;
      enhsims_[i]->bloodlust_->use_ = true;
    }
    if (casters >= 2) {
      if (sync == 1) {
        enhsims_[i]->bloodlust_->cooldown_ = 32000;
      }
      else {
        enhsims_[i]->bloodlust_->cooldown_ = 30000;
      }
      enhsims_[i]->bloodlust_->use_ = true;
    }
  }
}

void EnhSimConfig::initializeEnhSims() {

  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    enhsims_[i]->setMhSpeed(mh_speed_);
    enhsims_[i]->setOhSpeed(oh_speed_);
    enhsims_[i]->setMhDps(mh_dps_);
    enhsims_[i]->setOhDps(oh_dps_);
    enhsims_[i]->setMhCrit(mh_crit_);
    enhsims_[i]->setOhCrit(oh_crit_);
    enhsims_[i]->setMhHit(mh_hit_);
    enhsims_[i]->setOhHit(oh_hit_);
    enhsims_[i]->setPhysicalCritMultiplier(physical_crit_multiplier_);
    enhsims_[i]->setPhysicalDamageMultiplier(physical_damage_multiplier_);
    enhsims_[i]->setSpellCritMultiplier(spell_crit_multiplier_);
    enhsims_[i]->setSpellCritBonus(spell_crit_bonus_);
    enhsims_[i]->setAttackPower(attack_power_);
    enhsims_[i]->setHaste(haste_);
    enhsims_[i]->setMhExpertiseRating(mh_expertise_rating_);
    enhsims_[i]->setOhExpertiseRating(oh_expertise_rating_);
    enhsims_[i]->setMp5(mp5_);
    enhsims_[i]->setMaxMana(max_mana_);
    enhsims_[i]->setStrength(strength_);
    enhsims_[i]->setAgility(agility_);
    enhsims_[i]->setIntelligence(intelligence_);
    enhsims_[i]->setSpirit(spirit_);
    enhsims_[i]->setIntToApMultiplier(int_to_ap_multiplier_);
    enhsims_[i]->setStrenghtMultiplier(strenght_multiplier_);
    enhsims_[i]->setAgilityMultiplier(agility_multiplier_);
    enhsims_[i]->setIntelligenceMultiplier(intelligence_multiplier_);
    enhsims_[i]->setSpiritMultiplier(spirit_multiplier_);
    enhsims_[i]->setApToSpellpowerMultiplier(ap_to_spellpower_multiplier_);
    enhsims_[i]->setMiss(miss_);
    enhsims_[i]->setDodge(dodge_);
    enhsims_[i]->setGlancing(glancing_);
    enhsims_[i]->setArmor(armor_);
    // enhsims_[i]->setArmorPenetration(armor_penetration_);
    // enhsims_[i]->setArmorIgnore()
    enhsims_[i]->setSpellMiss(spell_miss_);
    enhsims_[i]->setNatureResistance(nature_resistance_);
    enhsims_[i]->setFireResistance(fire_resistance_);
    enhsims_[i]->setFrostResistance(frost_resistance_);
    enhsims_[i]->setSpellpower(spellpower_);
    enhsims_[i]->setNatureCrit(nature_crit_);
    enhsims_[i]->setFireCrit(fire_crit_);
    enhsims_[i]->setFrostCrit(frost_crit_);
    enhsims_[i]->setSpellHit(spell_hit_);
    enhsims_[i]->setSpellHitTotem(spell_hit_totem_);
    enhsims_[i]->setMentalQuicknessMana(mental_quickness_mana_);
    enhsims_[i]->setShamanisticFocusMana(shamanistic_focus_mana_);
    enhsims_[i]->setConvectionMana(convection_mana_);
    enhsims_[i]->setNatureDamageMultiplier(nature_damage_multiplier_);
    enhsims_[i]->setFireDamageMultiplier(fire_damage_multiplier_);
    enhsims_[i]->setFrostDamageMultiplier(frost_damage_multiplier_);
    enhsims_[i]->setWaitSSWithWFCD(wait_ss_wf_);
    enhsims_[i]->mh_windfury_->bonus_ap_ += windfury_bonus_ap_;
    enhsims_[i]->oh_windfury_->bonus_ap_ += windfury_bonus_ap_;
  }
}

f32 EnhSimConfig::startSimulation(const f32& hours, const int& report_count) {

  f32 total_hours;

  initializeEnhSims();

  if (ep_) {
    total_hours = calculateEPValues(hours);
    /*{
    boost::mutex::scoped_lock lock(lock_);
    condition_.wait(lock);
    }*/
  }
  else {

    total_hours = hours;
    f32 duration = hours / enhsims_.size();
    int reports = report_count / enhsims_.size();

#ifndef NOTHREADS
    for (unsigned int i=0; i<enhsims_.size(); ++i) {
      enhsims_[i]->progress_->report_count_ = reports;

      ZThread::Thread thread(new SimulationThread(this, enhsims_[i], duration));
    }
    lock_.acquire();
    condition_.wait();
    lock_.release();
#else
    enhsims_[0]->progress_->report_count_ = reports;
    SimulationThread thread(this, enhsims_[0], duration);
    thread.run();
#endif

    for (unsigned int i=1; i<statsv_.size(); ++i) {
      statsv_[0].combine(statsv_[i]);
    }

    //set seconds variable for statistics
    statsv_[0].seconds_ = static_cast<int64>(hours * 3600);
    //print statistics
    statsv_[0].print();
  }

  return total_hours;
}

f32 EnhSimConfig::calculateEPValues(const f32& hours) {
  int skipped = 0;

  double miss = miss_ + DUAL_WIELD_MISS;
  double mhhit = mh_hit_ + ep_hit_rating_ * HIT_RATING_TO_HIT;
  double ohhit = oh_hit_ + ep_hit_rating_ * HIT_RATING_TO_HIT;
  double spellhit = spell_hit_ + ep_spellhit_rating_ * SPELLHIT_RATING_TO_SPELLHIT;
  double expcap = ceil(dodge_ / EXPERTISE_DODGE_BONUS * EXPERTISE_RATING_TO_EXPERTISE);
  double mhexp = mh_expertise_rating_ + ep_expertise_rating_;
  double ohexp = oh_expertise_rating_ + ep_expertise_rating_;

  if (mh_hit_ >= miss &&
      oh_hit_ >= miss &&
      spell_hit_ >= spell_miss_ &&
      ep_hit_rating_ >= 0) {

    ep_hit_rating_ = 0;
    std::cout << "Hit is past caps, EP hit test will be skipped." << std::endl;
  }
  else {
    if (mhhit > miss) {
      std::cout << "Mh hit + EP range goes past cap by " << (mhhit - miss)/100 << "% (" << (mhhit - miss) / HIT_RATING_TO_HIT << " hit rating)." << std::endl;
    }
    if (ohhit > miss) {
      std::cout << "Oh hit + EP range goes past cap by " << (ohhit - miss)/100 << "% (" << (ohhit - miss) / HIT_RATING_TO_HIT << " hit rating)." << std::endl;
    }
    if (spellhit > spell_miss_) {
      std::cout << "Spell hit + EP range goes past cap by " << (spellhit - spell_miss_)/100 << "% (" << (spellhit - spell_miss_) / SPELLHIT_RATING_TO_SPELLHIT << " hit rating)." << std::endl;
    }
  }
  if (mh_expertise_rating_ >= expcap &&
      oh_expertise_rating_ >= expcap &&
      ep_expertise_rating_ >= 0) {

    ep_expertise_rating_ = 0;
    std::cout << "Expertise is past cap, EP expertise test will be skipped." << std::endl;
  }
  else {
    if (mhexp > expcap) {
      std::cout << "Mh expertise + EP range goes past cap by " << (mhexp - expcap) / EXPERTISE_RATING_TO_EXPERTISE << " expertise (" << mhexp - expcap << " expertise rating)." << std::endl;
    }
    if (ohexp > expcap) {
      std::cout << "Oh expertise + EP range goes past cap by " << (ohexp - expcap) / EXPERTISE_RATING_TO_EXPERTISE << " expertise (" << ohexp - expcap << " expertise rating)." << std::endl;
    }
  }
  std::cout << std::endl;

  

  std::cout << "Calculating EP values...\n";

#ifndef NOTHREADS
  for (unsigned int i=0; i<threads_; ++i) {
    ZThread::Thread thread(new EPThread(this, hours));
    //boost::thread t(boost::bind(&SimulationThread, this, hours));
    
    //t.join();
  }
#else
  EPThread thread(this, hours);
  thread.run();
#endif

#ifndef NOTHREADS
  lock_.acquire();
  condition_.wait();
  lock_.release();
#endif

  return hours * (EPTEST_COUNT - ep_skipped_);
}

void EnhSimConfig::setLag(int min, int max) {

  min /= 10;
  max /= 10;
  if (max <= 1) max = 2;
  if (max <= min) max = min+1;
  if (min < 1) min = 1;

  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    enhsims_[i]->setLag(min, max);
  }
}

void EnhSimConfig::setSimulateMana(bool simulate_mana) {
  simulate_mana_ = simulate_mana;

  for (unsigned int i=0; i<enhsims_.size(); ++i) {
    enhsims_[i]->simulate_mana_ = simulate_mana;
  }
}

void EnhSimConfig::fixStats() {

  //take ap portion off from spellpower
  spellpower_ -= static_cast<int>(ap_to_spellpower_multiplier_ * attack_power_);

  //take int portion off from ap
  attack_power_ -= static_cast<int>(int_to_ap_multiplier_ * intelligence_);

  //take int portion off from spell crit
  nature_crit_ -= static_cast<int>(intelligence_ * INTELLIGENCE_TO_SPELLCRIT);
  fire_crit_ -= static_cast<int>(intelligence_ * INTELLIGENCE_TO_SPELLCRIT);
  frost_crit_ -= static_cast<int>(intelligence_ * INTELLIGENCE_TO_SPELLCRIT);

  max_mana_ -= intelligence_ * INTELLIGENCE_TO_MANA;

  //set intelligence to normal value before talents
  intelligence_ = static_cast<int>(intelligence_ / intelligence_multiplier_);

  //take str portion off from ap
  attack_power_ -= strength_ * STRENGTH_TO_AP;

  //take agi portion off from ap
  attack_power_ -= agility_ * AGILITY_TO_AP;

  //take agi portion off from cirt
  mh_crit_ -= static_cast<int>(agility_ * AGILITY_TO_CRIT);
  oh_crit_ -= static_cast<int>(agility_ * AGILITY_TO_CRIT);
}
