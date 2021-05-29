//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include <iostream>
#include <iomanip>
#include <string>

class Statistics {
  public:
    Statistics();

    void print();
    void printValueAndPercentRegen(const std::string& label, const double& value, const double& total);
    void printValueAndPercent(const std::string& label, const double& value, const double& total);
    void printValueAndPercentFinal(const std::string& label, const double& value, const double& total, const double& procs);
    void printValueAndPercentFinalMana(const std::string& label, const double& value, const double& total, const double& procs, const double& value2, const double& total2);

    double getTotalDamage();
    double getTotalDPS();

    double getTotalMana();
    double getTotalMPS();

    double getTotalManaRegen();
    double getTotalMRPS();

    void combine(const Statistics& o);



    //I use doubles only because there is a bug with int64: It is limited to something like 8900000000,
    //at least on my computer and compiler settings(?). Damn that bug was hard to find...and notice...:EEE
    //ps. that limit was only with the damage variables...wtf?
    double seconds_;

    double mh_miss_;
    double mh_dodge_;
    double mh_glancing_;
    double mh_hit_;
    double mh_crit_;
    double mh_wf_miss_;
    double mh_wf_dodge_;
    double mh_wf_hit_;
    double mh_wf_crit_;
    double mh_ft_miss_;
    double mh_ft_hit_;
    double mh_ft_crit_;
    double mh_ss_miss_;
    double mh_ss_dodge_;
    double mh_ss_hit_;
    double mh_ss_crit_;

    double oh_miss_;
    double oh_dodge_;
    double oh_glancing_;
    double oh_hit_;
    double oh_crit_;
    double oh_wf_miss_;
    double oh_wf_dodge_;
    double oh_wf_hit_;
    double oh_wf_crit_;
    double oh_ft_miss_;
    double oh_ft_hit_;
    double oh_ft_crit_;
    double oh_ss_miss_;
    double oh_ss_dodge_;
    double oh_ss_hit_;
    double oh_ss_crit_;

    double flurry_uptime_;
    double unleashed_rage_uptime_;
    double elemental_devastation_uptime_;
    // double elemental_oath_uptime_;

    double mh_glancing_damage_;
    double mh_hit_damage_;
    double mh_crit_damage_;
    double mh_wf_hit_damage_;
    double mh_wf_crit_damage_;
    double mh_ft_hit_damage_;
    double mh_ft_crit_damage_;
    double mh_ss_hit_damage_;
    double mh_ss_crit_damage_;
    double mh_enchant_uptime_;

    double oh_glancing_damage_;
    double oh_hit_damage_;
    double oh_crit_damage_;
    double oh_wf_hit_damage_;
    double oh_wf_crit_damage_;
    double oh_ft_hit_damage_;
    double oh_ft_crit_damage_;
    double oh_ss_hit_damage_;
    double oh_ss_crit_damage_;
    double oh_enchant_uptime_;

    double stormstrike_mana_;

    double trinket1_uptime_;
    double trinket2_uptime_;
    double totem_uptime_;
    double set_bonus_uptime_;
    double metagem_uptime_;

    // double maelstrom_weapon_procs_;

    //double searing_totem_miss_;
    //double searing_totem_hit_;
    //double searing_totem_crit_;
    double searing_totem_damage_;
    double searing_totem_crit_damage_;
    double searing_totem_cast_;
    double searing_totem_mana_;

    double earth_shock_miss_;
    double earth_shock_hit_;
    double earth_shock_crit_;

    double earth_shock_damage_;
    double earth_shock_crit_damage_;
    double earth_shock_mana_;

    double flame_shock_miss_;
    double flame_shock_hit_;
    double flame_shock_crit_;
    double flame_shock_dot_;

    double flame_shock_damage_;
    double flame_shock_crit_damage_;
    double flame_shock_mana_;

    double frost_shock_miss_;
    double frost_shock_hit_;
    double frost_shock_crit_;

    double frost_shock_damage_;
    double frost_shock_crit_damage_;
    double frost_shock_mana_;

    // double lava_burst_miss_;
    // double lava_burst_hit_;
    // double lava_burst_crit_;

    // double lava_burst_damage_;
    // double lava_burst_crit_damage_;
    // double lava_burst_mana_;

    // double lava_lash_miss_;
    // double lava_lash_dodge_;
    // double lava_lash_hit_;
    // double lava_lash_crit_;

    // double lava_lash_hit_damage_;
    // double lava_lash_crit_damage_;
    // double lava_lash_mana_;

    // double lightning_bolt_miss_;
    // double lightning_bolt_hit_;
    // double lightning_bolt_crit_;

    // double lightning_bolt_damage_;
    // double lightning_bolt_crit_damage_;
    // double lightning_bolt_mana_;

    // double chain_lightning_miss_;
    // double chain_lightning_hit_;
    // double chain_lightning_crit_;

    // double chain_lightning_damage_;
    // double chain_lightning_crit_damage_;
    // double chain_lightning_mana_;

    // double lightning_shield_cast_;
    // double lightning_shield_miss_;
    // double lightning_shield_hit_;
    // double lightning_shield_crit_;

    // double lightning_shield_damage_;
    // double lightning_shield_crit_damage_;
    // double lightning_shield_mana_;

    // double lightning_overload_miss_;
    // double lightning_overload_hit_;
    // double lightning_overload_crit_;

    // double lightning_overload_damage_;
    // double lightning_overload_crit_damage_;

    double misc_hit_;
    double misc_damage_;

    double mana_regen_;
    double mana_overregen_;
    double mp5_regen_;
    double replenishment_regen_;
    double unrelenting_storm_regen_;
    double judgement_of_wisdom_regen_;
    double shamanistic_rage_regen_;
    double mana_potion_regen_;
    double misc_regen_;

    double oom_time_;

    /*double mw_total_time_;
    double mw_total_sd_time_;
    double mw_stack_full_count_;*/
};
