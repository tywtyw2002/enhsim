//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "stats.h"
#include <sstream>
#include <math.h>

Statistics::Statistics():  seconds_(1),

                           mh_miss_(0),
                           mh_dodge_(0),
                           mh_glancing_(0),
                           mh_hit_(0),
                           mh_crit_(0),
                           mh_wf_miss_(0),
                           mh_wf_dodge_(0),
                           mh_wf_hit_(0),
                           mh_wf_crit_(0),
                           mh_ft_miss_(0),
                           mh_ft_hit_(0),
                           mh_ft_crit_(0),
                           mh_ss_miss_(0),
                           mh_ss_dodge_(0),
                           mh_ss_hit_(0),
                           mh_ss_crit_(0),

                           oh_miss_(0),
                           oh_dodge_(0),
                           oh_glancing_(0),
                           oh_hit_(0),
                           oh_crit_(0),
                           oh_wf_miss_(0),
                           oh_wf_dodge_(0),
                           oh_wf_hit_(0),
                           oh_wf_crit_(0),
                           oh_ft_miss_(0),
                           oh_ft_hit_(0),
                           oh_ft_crit_(0),
                           oh_ss_miss_(0),
                           oh_ss_dodge_(0),
                           oh_ss_hit_(0),
                           oh_ss_crit_(0),
                           flurry_uptime_(0),
                           unleashed_rage_uptime_(0),
                           elemental_devastation_uptime_(0),
                           // elemental_oath_uptime_(0),
            
                           mh_glancing_damage_(0),
                           mh_hit_damage_(0),
                           mh_crit_damage_(0),
                           mh_wf_hit_damage_(0),
                           mh_wf_crit_damage_(0),
                           mh_ft_hit_damage_(0),
                           mh_ft_crit_damage_(0),
                           mh_ss_hit_damage_(0),
                           mh_ss_crit_damage_(0),
                           //mh_ft_damage_(0),
                           mh_enchant_uptime_(0),
            
                           oh_glancing_damage_(0),
                           oh_hit_damage_(0),
                           oh_crit_damage_(0),
                           oh_wf_hit_damage_(0),
                           oh_wf_crit_damage_(0),
                           oh_ft_hit_damage_(0),
                           oh_ft_crit_damage_(0),
                           oh_ss_hit_damage_(0),
                           oh_ss_crit_damage_(0),
                           //oh_ft_damage_(0),
                           oh_enchant_uptime_(0),

                           stormstrike_mana_(0),

                           trinket1_uptime_(0),
                           trinket2_uptime_(0),
                           totem_uptime_(0),
                           set_bonus_uptime_(0),
                           metagem_uptime_(0),

                           // maelstrom_weapon_procs_(0),

                           //searing_totem_miss_(0),
                           //searing_totem_hit_(0),
                           //searing_totem_crit_(0),
                           searing_totem_damage_(0),
                           searing_totem_crit_damage_(0),
                           searing_totem_cast_(0),
                           searing_totem_mana_(0),

                           earth_shock_miss_(0),
                           earth_shock_hit_(0),
                           earth_shock_crit_(0),

                           earth_shock_damage_(0),
                           earth_shock_crit_damage_(0),
                           earth_shock_mana_(0),

                           flame_shock_miss_(0),
                           flame_shock_hit_(0),
                           flame_shock_crit_(0),
                           flame_shock_dot_(0),
                    
                           flame_shock_damage_(0),
                           flame_shock_crit_damage_(0),
                           flame_shock_mana_(0),

                           frost_shock_miss_(0),
                           frost_shock_hit_(0),
                           frost_shock_crit_(0),

                           frost_shock_damage_(0),
                           frost_shock_crit_damage_(0),
                           frost_shock_mana_(0),

                           // lava_burst_miss_(0),
                           // lava_burst_hit_(0),
                           // lava_burst_crit_(0),

                           // lava_burst_damage_(0),
                           // lava_burst_crit_damage_(0),
                           // lava_burst_mana_(0),

                           // lava_lash_miss_(0),
                           // lava_lash_dodge_(0),
                           // lava_lash_hit_(0),
                           // lava_lash_crit_(0),

                           // lava_lash_hit_damage_(0),
                           // lava_lash_crit_damage_(0),
                           // lava_lash_mana_(0),

                           // lightning_bolt_miss_(0),
                           // lightning_bolt_hit_(0),
                           // lightning_bolt_crit_(0),

                           // lightning_bolt_damage_(0),
                           // lightning_bolt_crit_damage_(0),
                           // lightning_bolt_mana_(0),

                           // chain_lightning_miss_(0),
                           // chain_lightning_hit_(0),
                           // chain_lightning_crit_(0),

                           // chain_lightning_damage_(0),
                           // chain_lightning_crit_damage_(0),
                           // chain_lightning_mana_(0),

                           // lightning_shield_cast_(0),
                           // lightning_shield_miss_(0),
                           // lightning_shield_hit_(0),
                           // lightning_shield_crit_(0),

                           // lightning_shield_damage_(0),
                           // lightning_shield_crit_damage_(0),
                           // lightning_shield_mana_(0),

                           // lightning_overload_miss_(0),
                           // lightning_overload_hit_(0),
                           // lightning_overload_crit_(0),

                           // lightning_overload_damage_(0),
                           // lightning_overload_crit_damage_(0),
                           
                           misc_hit_(0),
                           misc_damage_(0),
                           
                           mana_regen_(0),
                           mana_overregen_(0),
                           mp5_regen_(0),
                           replenishment_regen_(0),
                           unrelenting_storm_regen_(0),
                           judgement_of_wisdom_regen_(0),
                           shamanistic_rage_regen_(0),
                           mana_potion_regen_(0),
                           misc_regen_(0),
                           
                           oom_time_(0)/*,
                           
                           mw_total_time_(0),
                           mw_total_sd_time_(0),
                           mw_stack_full_count_(0)*/ {
}

void Statistics::print() {
  std::cout << std::endl << std::fixed << std::setprecision(2);

  double dmg = getTotalDamage();

  double mhhits = mh_crit_ + mh_dodge_ + mh_glancing_ + mh_hit_ + mh_miss_;
  if (mhhits > 0) {
    std::cout << "\nMH:\n";
    printValueAndPercent("miss", mh_miss_, mhhits);
    printValueAndPercent("dodge", mh_dodge_, mhhits);
    printValueAndPercent("glancing", mh_glancing_, mhhits);
    printValueAndPercent("hit", mh_hit_, mhhits);
    printValueAndPercent("crit", mh_crit_, mhhits);
  }

  double mhsshits = mh_ss_crit_ + mh_ss_dodge_ + mh_ss_hit_ + mh_ss_miss_;
  double mhwfhits = mh_wf_crit_ + mh_wf_dodge_ + mh_wf_hit_ + mh_wf_miss_;
  if (mhwfhits > 0) {
    std::cout << "\nMH Windfury:\n";
    std::cout << std::setw(20) << "procs/hits" << mhwfhits / 2 / (mhhits - mh_miss_ - mh_dodge_ + mhsshits - mh_ss_miss_ - mh_ss_dodge_) * 100 << "%" << std::endl;
    std::cout << std::setw(20) << "procs/swings" << mhwfhits / 2 / (mhhits + mhsshits) * 100 << "%" << std::endl;
    printValueAndPercent("miss", mh_wf_miss_, mhwfhits);
    printValueAndPercent("dodge", mh_wf_dodge_, mhwfhits);
    printValueAndPercent("hit", mh_wf_hit_, mhwfhits);
    printValueAndPercent("crit", mh_wf_crit_, mhwfhits);
  }

  double mhfthits = mh_ft_crit_ + mh_ft_hit_ + mh_ft_miss_;
  if (mhfthits > 0) {
    std::cout << "\nMH Flametongue:\n";
    printValueAndPercent("miss", mh_ft_miss_, mhfthits);
    printValueAndPercent("hit", mh_ft_hit_, mhfthits);
    printValueAndPercent("crit", mh_ft_crit_, mhfthits);
  }

  if (mhsshits > 0) {
    std::cout << "\nMH Storsmtrike:\n";
    printValueAndPercent("miss", mh_ss_miss_, mhsshits);
    printValueAndPercent("dodge", mh_ss_dodge_, mhsshits);
    printValueAndPercent("hit", mh_ss_hit_, mhsshits);
    printValueAndPercent("crit", mh_ss_crit_, mhsshits);
  }

  double ohhits = oh_crit_ + oh_dodge_ + oh_glancing_ + oh_hit_ + oh_miss_;
  if (ohhits > 0) {
    std::cout << "\nOH:\n";
    printValueAndPercent("miss", oh_miss_, ohhits);
    printValueAndPercent("dodge", oh_dodge_, ohhits);
    printValueAndPercent("glancing", oh_glancing_, ohhits);
    printValueAndPercent("hit", oh_hit_, ohhits);
    printValueAndPercent("crit", oh_crit_, ohhits);
  }

  // double lavalash = lava_lash_hit_ + lava_lash_crit_ + lava_lash_miss_ + lava_lash_dodge_;
  double ohsshits = oh_ss_crit_ + oh_ss_dodge_ + oh_ss_hit_ + oh_ss_miss_;
  double ohwfhits = oh_wf_crit_ + oh_wf_dodge_ + oh_wf_hit_ + oh_wf_miss_;
  if (ohwfhits > 0) {
    std::cout << "\nOH Windfury:\n";
    std::cout << std::setw(20) << "procs/hits" << ohwfhits / 2 / (ohhits - oh_miss_ - oh_dodge_ + ohsshits - oh_ss_miss_ - oh_ss_dodge_ /*+ lavalash - lava_lash_miss_ - lava_lash_dodge_*/) * 100 << "%" << std::endl;
    std::cout << std::setw(20) << "procs/swings" << ohwfhits / 2 / (ohhits + ohsshits ) * 100 << "%" << std::endl;
    printValueAndPercent("miss", oh_wf_miss_, ohwfhits);
    printValueAndPercent("dodge", oh_wf_dodge_, ohwfhits);
    printValueAndPercent("hit", oh_wf_hit_, ohwfhits);
    printValueAndPercent("crit", oh_wf_crit_, ohwfhits);
  }

  double ohfthits = oh_ft_crit_ + oh_ft_hit_ + oh_ft_miss_;
  if (ohfthits > 0) {
    std::cout << "\nOH Flametongue:\n";
    printValueAndPercent("miss", oh_ft_miss_, ohfthits);
    printValueAndPercent("hit", oh_ft_hit_, ohfthits);
    printValueAndPercent("crit", oh_ft_crit_, ohfthits);
  }

  if (ohsshits > 0) {
    std::cout << "\nOH Stormstrike:\n";
    printValueAndPercent("miss", oh_ss_miss_, ohsshits);
    printValueAndPercent("dodge", oh_ss_dodge_, ohsshits);
    printValueAndPercent("hit", oh_ss_hit_, ohsshits);
    printValueAndPercent("crit", oh_ss_crit_, ohsshits);
  }

  double eshits = earth_shock_hit_ + earth_shock_crit_ + earth_shock_miss_;
  if (eshits > 0) {
    std::cout << "\nEarth Shock:\n";
    printValueAndPercent("miss", earth_shock_miss_, eshits);
    printValueAndPercent("hit", earth_shock_hit_, eshits);
    printValueAndPercent("crit", earth_shock_crit_, eshits);
  }

  double fshits = flame_shock_hit_ + flame_shock_crit_ + flame_shock_miss_;
  if (fshits > 0) {
    std::cout << "\nFlame Shock:\n";
    printValueAndPercent("miss", flame_shock_miss_, fshits);
    printValueAndPercent("hit", flame_shock_hit_, fshits);
    printValueAndPercent("crit", flame_shock_crit_, fshits);
    std::cout << std::setw(20) << std::left << "dots" << flame_shock_dot_ << std::endl;
  }

  double frosthits = frost_shock_hit_ + frost_shock_crit_ + frost_shock_miss_;
  if (frosthits > 0) {
    std::cout << "\nFrost Shock:\n";
    printValueAndPercent("miss", frost_shock_miss_, frosthits);
    printValueAndPercent("hit", frost_shock_hit_, frosthits);
    printValueAndPercent("crit", frost_shock_crit_, frosthits);
  }

  // double lavaburst = lava_burst_hit_ + lava_burst_crit_ + lava_burst_miss_;
  // if (lavaburst > 0) {
  //   std::cout << "\nLava Burst:\n";
  //   printValueAndPercent("miss", lava_burst_miss_, lavaburst);
  //   printValueAndPercent("hit", lava_burst_hit_, lavaburst);
  //   printValueAndPercent("crit", lava_burst_crit_, lavaburst);
  // }

  // if (lavalash > 0) {
  // std::cout << "\nLava Lash:\n";
  //   printValueAndPercent("miss", lava_lash_miss_, lavalash);
  //   printValueAndPercent("dodge", lava_lash_dodge_, lavalash);
  //   printValueAndPercent("hit", lava_lash_hit_, lavalash);
  //   printValueAndPercent("crit", lava_lash_crit_, lavalash);
  // }

  // double lb = lightning_bolt_hit_ + lightning_bolt_crit_ + lightning_bolt_miss_;
  // if (lb > 0) {
  //   std::cout << "\nLightning Bolt:\n";
  //   printValueAndPercent("miss", lightning_bolt_miss_, lb);
  //   printValueAndPercent("hit", lightning_bolt_hit_, lb);
  //   printValueAndPercent("crit", lightning_bolt_crit_, lb);
  // }

  // double cl = chain_lightning_hit_ + chain_lightning_crit_ + chain_lightning_miss_;
  // if (cl > 0) {
  //   std::cout << "\nChain Lightning:\n";
  //   printValueAndPercent("miss", chain_lightning_miss_, cl);
  //   printValueAndPercent("hit", chain_lightning_hit_, cl);
  //   printValueAndPercent("crit", chain_lightning_crit_, cl);
  // }

  // double ls = lightning_shield_hit_ + lightning_shield_crit_ + lightning_shield_miss_;
  // if (ls > 0) {
  //   std::cout << "\nLightning Shield:\n";
  //   printValueAndPercent("miss", lightning_shield_miss_, ls);
  //   printValueAndPercent("hit", lightning_shield_hit_, ls);
  //   printValueAndPercent("crit", lightning_shield_crit_, ls);
  // }

  // double lo = lightning_overload_hit_ + lightning_overload_crit_ + lightning_overload_miss_;
  // if (lo > 0) {
  //   std::cout << "\nLightning Overload:\n";
  //   printValueAndPercent("miss", lightning_overload_miss_, lo);
  //   printValueAndPercent("hit", lightning_overload_hit_, lo);
  //   printValueAndPercent("crit", lightning_overload_crit_, lo);
  // }

  // if (maelstrom_weapon_procs_ > 0) {
  //   std::cout << "\nMaelstrom Weapon:\n";
  //   std::cout << std::setw(20) << "PPM" << maelstrom_weapon_procs_ * 60 / seconds_ << std::endl;
  // }

  std::cout << std::endl;
  std::cout << std::setw(31) << "flurry uptime" << flurry_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "unleashed rage uptime" << unleashed_rage_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "elemental devastation uptime" << elemental_devastation_uptime_ / seconds_ << "%\n";
  // std::cout << std::setw(31) << "elemental oath uptime" << elemental_oath_uptime_ / seconds_ << "%\n\n";

  std::cout << std::setw(31) << "mh enchant uptime" << mh_enchant_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "oh enchant uptime" << oh_enchant_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "trinket1 uptime" << trinket1_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "trinket2 uptime" << trinket2_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "totem uptime" << totem_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "set bonus uptime" << set_bonus_uptime_ / seconds_ << "%\n";
  std::cout << std::setw(31) << "metagem uptime" << metagem_uptime_ / seconds_ << "%\n\n";

  std::cout << std::setw(20) << "" << "MRPS without overregen\n";
  printValueAndPercentRegen("mana regen", mana_regen_, getTotalManaRegen());
  printValueAndPercentRegen("mp5", mp5_regen_, getTotalManaRegen());
  printValueAndPercentRegen("replenishment", replenishment_regen_, getTotalManaRegen());
  printValueAndPercentRegen("unrelenting storm", unrelenting_storm_regen_, getTotalManaRegen());
  printValueAndPercentRegen("judgement of wisdom", judgement_of_wisdom_regen_, getTotalManaRegen());
  printValueAndPercentRegen("shamanistic rage", shamanistic_rage_regen_, getTotalManaRegen());
  printValueAndPercentRegen("mana potion", mana_potion_regen_, getTotalManaRegen());
  printValueAndPercentRegen("misc potion", misc_regen_, getTotalManaRegen());
  std::cout << std::endl;

  std::cout << std::setw(20) << "" << std::setw(20) << "DPS" << std::setw(10) << "PPM" << "MPS\n";
  printValueAndPercentFinal("white", mh_glancing_damage_ + mh_hit_damage_ + mh_crit_damage_ + oh_glancing_damage_ + oh_hit_damage_ + oh_crit_damage_, dmg, mhhits+ohhits);
  printValueAndPercentFinal("windfury", mh_wf_hit_damage_ + mh_wf_crit_damage_ + oh_wf_hit_damage_ + oh_wf_crit_damage_, dmg, (mhwfhits+ohwfhits)/2);
  printValueAndPercentFinal("flametongue", mh_ft_hit_damage_ + mh_ft_crit_damage_ + oh_ft_hit_damage_ + oh_ft_crit_damage_, dmg, mhfthits+ohfthits);
  printValueAndPercentFinalMana("stormstrike", mh_ss_hit_damage_ + mh_ss_crit_damage_ + oh_ss_hit_damage_ + oh_ss_crit_damage_, dmg, mhsshits, stormstrike_mana_, getTotalMana());
  // printValueAndPercentFinalMana("lava lash", lava_lash_hit_damage_ + lava_lash_crit_damage_, dmg, lavalash, lava_lash_mana_, getTotalMana());
  printValueAndPercentFinalMana("searing totem", searing_totem_damage_ + searing_totem_crit_damage_, dmg, searing_totem_cast_, searing_totem_mana_, getTotalMana());
  printValueAndPercentFinalMana("earth shock", earth_shock_damage_ + earth_shock_crit_damage_, dmg, eshits, earth_shock_mana_, getTotalMana());
  printValueAndPercentFinalMana("flame shock", flame_shock_damage_ + flame_shock_crit_damage_, dmg, fshits, flame_shock_mana_, getTotalMana());
  printValueAndPercentFinalMana("frost shock", frost_shock_damage_ + frost_shock_crit_damage_, dmg, frosthits, frost_shock_mana_, getTotalMana());
  // printValueAndPercentFinalMana("lava burst", lava_burst_damage_ + lava_burst_crit_damage_, dmg, lavaburst, lava_burst_mana_, getTotalMana());
  // printValueAndPercentFinalMana("lightning bolt", lightning_bolt_damage_ + lightning_bolt_crit_damage_, dmg, lb, lightning_bolt_mana_, getTotalMana());
  // printValueAndPercentFinalMana("chain lightning", chain_lightning_damage_ + chain_lightning_crit_damage_, dmg, cl, chain_lightning_mana_, getTotalMana());
  // printValueAndPercentFinalMana("lightning shield", lightning_shield_damage_ + lightning_shield_crit_damage_, dmg, lightning_shield_cast_, lightning_shield_mana_, getTotalMana());
  // printValueAndPercentFinal("lightning overload", lightning_overload_damage_ + lightning_overload_crit_damage_, dmg, lo);
  printValueAndPercentFinal("misc", misc_damage_, dmg, misc_hit_);
  std::cout << std::endl;
  std::cout << std::setw(20) << "DPS" << getTotalDPS() << std::endl;
  std::cout << std::setw(20) << "MPS" << getTotalMPS() << std::endl;
  std::cout << std::setw(20) << "MP2min" << getTotalMPS() * 120 << std::endl;
  std::cout << std::setw(20) << "MRPS" << getTotalMRPS() + mana_overregen_ / seconds_ << std::endl;
  std::cout << std::setw(20) << "Out of mana time" << oom_time_ / seconds_ << "%" << std::endl;

  /*if (mw_stack_full_count_ > 0) {
    double mw_avg = mw_total_time_ / mw_stack_full_count_;
    double mw_sd = sqrt((mw_total_sd_time_ / mw_stack_full_count_) - (mw_avg * mw_avg));

    std::cout << std::endl << "Average time to get 5 MW charges: " << mw_avg << std::endl;
    std::cout << "95% of times it is between " << mw_avg - 1.96 * mw_sd << "s and " << mw_avg + 1.96 * mw_sd << "s" << std::endl;
  }*/

  std::cout << std::endl;
}

void Statistics::printValueAndPercentRegen(const std::string& label, const double& value, const double& total) {
  std::cout << std::setw(20) << std::left << label << std::setw(10) << value/seconds_ << std::setprecision(2) << value * 100 / total << "%" << std::endl;
}

void Statistics::printValueAndPercent(const std::string& label, const double& value, const double& total) {
  std::cout << std::setw(20) << std::left << label << std::setw(15) << std::setprecision(0) << value << std::setprecision(2) << value * 100 / total << "%" << std::endl;
}

void Statistics::printValueAndPercentFinal(const std::string& label, const double& value, const double& total, const double& procs) {
  if (value != 0.0) {
  
    std::stringstream out;
    out << (static_cast<int>((100.0 * value * 100 / total + 0.5))) / 100.0;
    std::string percent = out.str();
    percent.append("%");
    
    std::cout << std::setw(20) << std::left << label << std::setw(10) << value/seconds_ << std::setw(10) << percent << procs*60/seconds_ << std::endl;
  }
}

void Statistics::printValueAndPercentFinalMana(const std::string& label, const double& value, const double& total, const double& procs, const double& value2, const double& total2) {
  if (value != 0.0) {
  
    std::stringstream out;
    out << (static_cast<int>((100.0 * value * 100 / total + 0.5))) / 100.0;
    std::string percent = out.str();
    percent.append("%");

    std::cout << std::setw(20) << std::left << label << std::setw(10) << value/seconds_ << std::setw(10) << percent << std::setw(10) << procs*60/seconds_ << std::setw(10) << value2/seconds_ << value2 * 100 / total2 << "%" << std::endl;
  }
}

double Statistics::getTotalDamage() {
  return mh_glancing_damage_ + mh_hit_damage_ + mh_crit_damage_ +
          mh_wf_hit_damage_ + mh_wf_crit_damage_ +
          mh_ft_hit_damage_ + mh_ft_crit_damage_ +
          mh_ss_hit_damage_ + mh_ss_crit_damage_ +

          oh_glancing_damage_ + oh_hit_damage_ + oh_crit_damage_ +
          oh_wf_hit_damage_ + oh_wf_crit_damage_ +
          oh_ft_hit_damage_ + oh_ft_crit_damage_ +
          oh_ss_hit_damage_ + oh_ss_crit_damage_ +

          searing_totem_damage_ + searing_totem_crit_damage_ +
          earth_shock_damage_ + earth_shock_crit_damage_ +
          flame_shock_damage_ + flame_shock_crit_damage_ +
          frost_shock_damage_ + frost_shock_crit_damage_ +
          // lava_burst_damage_ + lava_burst_crit_damage_ +
          // lava_lash_hit_damage_ + lava_lash_crit_damage_ +
          // lightning_bolt_damage_ + lightning_bolt_crit_damage_ +
          // chain_lightning_damage_ + chain_lightning_crit_damage_ +
          // lightning_shield_damage_ + lightning_shield_crit_damage_+
          // lightning_overload_damage_ + lightning_overload_crit_damage_+
          
          misc_damage_;
}

double Statistics::getTotalDPS() {
  return getTotalDamage() / seconds_;
}

double Statistics::getTotalMana() {
  return stormstrike_mana_ +
         earth_shock_mana_ +
         flame_shock_mana_ +
         frost_shock_mana_ +
         // lava_burst_mana_ +
         // lava_lash_mana_ +
         // lightning_bolt_mana_ +
         // chain_lightning_mana_ +
         // lightning_shield_mana_ +
         searing_totem_mana_;
}

double Statistics::getTotalMPS() {
  return getTotalMana() / seconds_;
}

double Statistics::getTotalManaRegen() {
  return mana_regen_ +
         mp5_regen_ +
         replenishment_regen_ +
         unrelenting_storm_regen_ +
         judgement_of_wisdom_regen_ +
         shamanistic_rage_regen_ +
         mana_potion_regen_ +
         misc_regen_;
}

double Statistics::getTotalMRPS() {
  return getTotalManaRegen() / seconds_;
}

void Statistics::combine(const Statistics& o) {
  mh_miss_ += o.mh_miss_;
  mh_dodge_ += o.mh_dodge_;
  mh_glancing_ += o.mh_glancing_;
  mh_hit_ += o.mh_hit_;
  mh_crit_ += o.mh_crit_;
  mh_wf_miss_ += o.mh_wf_miss_;
  mh_wf_dodge_ += o.mh_wf_dodge_;
  mh_wf_hit_ += o.mh_wf_hit_;
  mh_wf_crit_ += o.mh_wf_crit_;
  mh_ft_miss_ += o.mh_ft_miss_;
  mh_ft_hit_ += o.mh_ft_hit_;
  mh_ft_crit_ += o.mh_ft_crit_;
  mh_ss_miss_ += o.mh_ss_miss_;
  mh_ss_dodge_ += o.mh_ss_dodge_;
  mh_ss_hit_ += o.mh_ss_hit_;
  mh_ss_crit_ += o.mh_ss_crit_;

  oh_miss_ += o.oh_miss_;
  oh_dodge_ += o.oh_dodge_;
  oh_glancing_ += o.oh_glancing_;
  oh_hit_ += o.oh_hit_;
  oh_crit_ += o.oh_crit_;
  oh_wf_miss_ += o.oh_wf_miss_;
  oh_wf_dodge_ += o.oh_wf_dodge_;
  oh_wf_hit_ += o.oh_wf_hit_;
  oh_wf_crit_ += o.oh_wf_crit_;
  oh_ft_miss_ += o.oh_ft_miss_;
  oh_ft_hit_ += o.oh_ft_hit_;
  oh_ft_crit_ += o.oh_ft_crit_;
  oh_ss_miss_ += o.oh_ss_miss_;
  oh_ss_dodge_ += o.oh_ss_dodge_;
  oh_ss_hit_ += o.oh_ss_hit_;
  oh_ss_crit_ += o.oh_ss_crit_;

  flurry_uptime_ += o.flurry_uptime_;
  unleashed_rage_uptime_ += o.unleashed_rage_uptime_;
  elemental_devastation_uptime_ += o.elemental_devastation_uptime_;
  // elemental_oath_uptime_ += o.elemental_oath_uptime_;

  mh_glancing_damage_ += o.mh_glancing_damage_;
  mh_hit_damage_ += o.mh_hit_damage_;
  mh_crit_damage_ += o.mh_crit_damage_;
  mh_wf_hit_damage_ += o.mh_wf_hit_damage_;
  mh_wf_crit_damage_ += o.mh_wf_crit_damage_;
  mh_ft_hit_damage_ += o.mh_ft_hit_damage_;
  mh_ft_crit_damage_ += o.mh_ft_crit_damage_;
  mh_ss_hit_damage_ += o.mh_ss_hit_damage_;
  mh_ss_crit_damage_ += o.mh_ss_crit_damage_;
  mh_enchant_uptime_ += o.mh_enchant_uptime_;

  oh_glancing_damage_ += o.oh_glancing_damage_;
  oh_hit_damage_ += o.oh_hit_damage_;
  oh_crit_damage_ += o.oh_crit_damage_;
  oh_wf_hit_damage_ += o.oh_wf_hit_damage_;
  oh_wf_crit_damage_ += o.oh_wf_crit_damage_;
  oh_ft_hit_damage_ += o.oh_ft_hit_damage_;
  oh_ft_crit_damage_ += o.oh_ft_crit_damage_;
  oh_ss_hit_damage_ += o.oh_ss_hit_damage_;
  oh_ss_crit_damage_ += o.oh_ss_crit_damage_;
  oh_enchant_uptime_ += o.oh_enchant_uptime_;

  stormstrike_mana_ += o.stormstrike_mana_;

  trinket1_uptime_ += o.trinket1_uptime_;
  trinket2_uptime_ += o.trinket2_uptime_;
  totem_uptime_ += o.totem_uptime_;
  set_bonus_uptime_ += o.set_bonus_uptime_;
  metagem_uptime_ += o.metagem_uptime_;

  // maelstrom_weapon_procs_ += o.maelstrom_weapon_procs_;

  searing_totem_damage_ += o.searing_totem_damage_;
  searing_totem_crit_damage_ += o.searing_totem_crit_damage_;
  searing_totem_cast_ += o.searing_totem_cast_;
  searing_totem_mana_ += o.searing_totem_mana_;

  earth_shock_miss_ += o.earth_shock_miss_;
  earth_shock_hit_ += o.earth_shock_hit_;
  earth_shock_crit_ += o.earth_shock_crit_;

  earth_shock_damage_ += o.earth_shock_damage_;
  earth_shock_crit_damage_ += o.earth_shock_crit_damage_;
  earth_shock_mana_ += o.earth_shock_mana_;

  flame_shock_miss_ += o.flame_shock_miss_;
  flame_shock_hit_ += o.flame_shock_hit_;
  flame_shock_crit_ += o.flame_shock_crit_;
  flame_shock_dot_ += o.flame_shock_dot_;

  flame_shock_damage_ += o.flame_shock_damage_;
  flame_shock_crit_damage_ += o.flame_shock_crit_damage_;
  flame_shock_mana_ += o.flame_shock_mana_;

  frost_shock_miss_ += o.frost_shock_miss_;
  frost_shock_hit_ += o.frost_shock_hit_;
  frost_shock_crit_ += o.frost_shock_crit_;

  frost_shock_damage_ += o.frost_shock_damage_;
  frost_shock_crit_damage_ += o.frost_shock_crit_damage_;
  frost_shock_mana_ += o.frost_shock_mana_;

  // lava_burst_miss_ += o.lava_burst_miss_;
  // lava_burst_hit_ += o.lava_burst_hit_;
  // lava_burst_crit_ += o.lava_burst_crit_;

  // lava_burst_damage_ += o.lava_burst_damage_;
  // lava_burst_crit_damage_ += o.lava_burst_crit_damage_;
  // lava_burst_mana_ += o.lava_burst_mana_;

  // lava_lash_miss_ += o.lava_lash_miss_;
  // lava_lash_dodge_ += o.lava_lash_dodge_;
  // lava_lash_hit_ += o.lava_lash_hit_;
  // lava_lash_crit_ += o.lava_lash_crit_;

  // lava_lash_hit_damage_ += o.lava_lash_hit_damage_;
  // lava_lash_crit_damage_ += o.lava_lash_crit_damage_;
  // lava_lash_mana_ += o.lava_lash_mana_;

  // lightning_bolt_miss_ += o.lightning_bolt_miss_;
  // lightning_bolt_hit_ += o.lightning_bolt_hit_;
  // lightning_bolt_crit_ += o.lightning_bolt_crit_;

  // lightning_bolt_damage_ += o.lightning_bolt_damage_;
  // lightning_bolt_crit_damage_ += o.lightning_bolt_crit_damage_;
  // lightning_bolt_mana_ += o.lightning_bolt_mana_;

  // chain_lightning_miss_ += o.chain_lightning_miss_;
  // chain_lightning_hit_ += o.chain_lightning_hit_;
  // chain_lightning_crit_ += o.chain_lightning_crit_;

  // chain_lightning_damage_ += o.chain_lightning_damage_;
  // chain_lightning_crit_damage_ += o.chain_lightning_crit_damage_;
  // chain_lightning_mana_ += o.chain_lightning_mana_;

  // lightning_shield_cast_ += o.lightning_shield_cast_;
  // lightning_shield_miss_ += o.lightning_shield_miss_;
  // lightning_shield_hit_ += o.lightning_shield_hit_;
  // lightning_shield_crit_ += o.lightning_shield_crit_;

  // lightning_shield_damage_ += o.lightning_shield_damage_;
  // lightning_shield_crit_damage_ += o.lightning_shield_crit_damage_;
  // lightning_shield_mana_ += o.lightning_shield_mana_;

  // lightning_overload_miss_ += o.lightning_overload_miss_;
  // lightning_overload_hit_ += o.lightning_overload_hit_;
  // lightning_overload_crit_ += o.lightning_overload_crit_;

  // lightning_overload_damage_ += o.lightning_overload_damage_;
  // lightning_overload_crit_damage_ += o.lightning_overload_crit_damage_;

  misc_hit_ += o.misc_hit_;
  misc_damage_ += o.misc_damage_;

  mana_regen_ += o.mana_regen_;
  mana_overregen_ += o.mana_overregen_;
  mp5_regen_ += o.mp5_regen_;
  replenishment_regen_ += o.replenishment_regen_;
  unrelenting_storm_regen_ += o.unrelenting_storm_regen_;
  judgement_of_wisdom_regen_ += o.judgement_of_wisdom_regen_;
  shamanistic_rage_regen_ += o.shamanistic_rage_regen_;
  mana_potion_regen_ += o.mana_potion_regen_;
  misc_regen_ += o.misc_regen_;

  oom_time_ += o.oom_time_;

  /*mw_total_time_ += o.mw_total_time_;
  mw_total_sd_time_ += o.mw_total_sd_time_;
  mw_stack_full_count_ += o.mw_stack_full_count_;*/
}
