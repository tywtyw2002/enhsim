//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "enhsim.h"
#include "enhsimconfig.h"

#include <iostream>
#include <time.h>
#include <map>
#include <fstream>
#include <sstream>

//std::string intToString(const int& i) {
//  std::stringstream out;
//  out << i;
//  return out.str();
//}
//
//int stringToInt(const std::string& str) {
//  std::istringstream buffer(str);
//  int value;
//  buffer >> value;
//  return value;
//}
//
//f32 stringToFloat(const std::string& str) {
//  std::istringstream buffer(str);
//  f32 value;
//  buffer >> value;
//  return value;
//}

std::map<std::string, std::string> config;

int getConfigInt(const std::string& key) {
  std::string value = config[key];
  if (value.empty()) {
    std::cout << key << " not found from config.\n";
  }

  return stringToInt(value);
}

f32 getConfigFloat(const std::string& key) {
  std::string value = config[key];
  if (value.empty()) {
    std::cout << key << " not found from config.\n";
  }

  return stringToFloat(value);
}

int getConfigTalent(const std::string& key) {
  std::string value = config[key];
  if (value.empty()) {
    std::cout << key << " not found from config.\n";
  }

  return stringToInt(value.substr(0,value.length()-2));
}

float getConfigBuff(const std::string& key) {
  std::string value = config[key];
  if (value.empty()) {
    std::cout << key << " not found from config.\n";
  }

  return stringToFloat(value.substr(0,value.find_first_of("/")));
}

int main(int argc, char* argv[]) {

  //clock_t start_config = clock();
  clock_t start = clock();

  if (argc == 1) {
    std::cout << "No config file specified. Pass the config file as parameter to this program.";
    std::cin.get();

    return 1;
  }

  std::ifstream is(argv[1]);
  if (is.fail()) {
    std::cout << "Could not open config file " << argv[1];
    std::cin.get();
    return 1;
  }

  std::string line;

  //read the config
  while(is.good()) {

    std::getline(is, line);

    if (line.length() >= 2) {
      if (!(line[0] == '#' || line.substr(2) == "//")) {
        std::stringstream ss(line);
        ss >> line;
        ss >> config[line];
      }
    }
  }

  is.close();


  EnhSimConfig sc;

  if (argc > 2) {
    sc.setEP(config["ep_base_stat"] == "ap", getConfigInt("ep_ap"), getConfigInt("ep_crit_rating"), getConfigInt("ep_hit_rating"), getConfigInt("ep_expertise"), getConfigInt("ep_haste_rating"), getConfigInt("ep_armor_ignore"), getConfigInt("ep_spellpower"), getConfigInt("ep_spellcrit_rating"), getConfigInt("ep_spellhit_rating"), getConfigFloat("ep_dps"), getConfigInt("ep_mana"), getConfigInt("ep_spirit"), getConfigInt("ep_mp5"));
  }
#ifdef DEBUG
  sc.setThreads(1);
#else
#ifndef NOTHREADS
  sc.setThreads(getConfigInt("threads"));
#else
  sc.setThreads(1);
#endif
#endif

#ifdef DEBUG
  setupCombatLog("combatlog.txt");
#endif

  sc.setLag(getConfigInt("min_lag"), getConfigInt("max_lag"));
  sc.setSimulateMana(getConfigInt("simulate_mana") == 1);

  int rotation_count = getConfigInt("rotation_priority_count");
  sc.setRotationCount(rotation_count);

  for (int i=0; i<rotation_count; ++i) {
    std::string str = "rotation_priority";
    str.append(intToString(i+1));
    sc.setRotation(config[str], i);
  }

  sc.setMhWeaponEnchant(config["mh_imbue"]);
  sc.setOhWeaponEnchant(config["oh_imbue"]);

  sc.setRotationSettings(getConfigInt("mh_auto_attack") == 1,
                         getConfigInt("oh_auto_attack") == 1,
                         // getConfigInt("cast_ll_only_if_wf_on_cd") == 1,
                         0,
                         // getConfigFloat("cast_lvb_only_if_ed_left"),
                         0.0,
                         // getConfigInt("cast_lvb_only_if_fsdots_left"),
                         0,
                         // getConfigInt("cast_lvb_only_if_fs_active") == 1,
                         0,
                         /*getConfigFloat("wait_mw_if_lvb_cd_left"),*/
                         // getConfigInt("cast_fs_only_if_dots_left"),
                         0,
                         // getConfigInt("cast_ls_only_if_charges_left"),
                         0,
                         getConfigFloat("cast_sr_only_if_mana_left"));

  sc.setMhEnchant(config["mh_enchant"]);
  sc.setOhEnchant(config["oh_enchant"]);

  sc.setMhWeapon(config["mh_weapon"]);
  sc.setOhWeapon(config["oh_weapon"]);

  sc.setRace(config["race"]);

  sc.setTrinket(config["trinket1"], 1);
  sc.setTrinket(config["trinket2"], 2);
  sc.setTotem(config["totem"]);
  sc.setSetBonus(config["set_bonus"]);
  sc.setMetagem(config["metagem"]);

  // sc.setGlyph(config["glyph_major1"]);
  // sc.setGlyph(config["glyph_major2"]);
  // sc.setGlyph(config["glyph_major3"]);
  // //sc.setGlyph(config["glyph_major4"]);
  // sc.setGlyph(config["glyph_minor1"]);
  // sc.setGlyph(config["glyph_minor2"]);
  // sc.setGlyph(config["glyph_minor3"]);

  sc.setMhDps(getConfigFloat("mh_dps"));
  sc.setOhDps(getConfigFloat("oh_dps"));
  sc.setMhSpeed(getConfigFloat("mh_speed") * 100);
  sc.setOhSpeed(getConfigFloat("oh_speed") * 100);
  sc.setMhCrit(getConfigFloat("mh_crit"));
  sc.setOhCrit(getConfigFloat("oh_crit"));
  sc.setMhHit(getConfigFloat("mh_hit"));
  sc.setOhHit(getConfigFloat("oh_hit"));
  sc.setMhExpertiseRating(getConfigFloat("mh_expertise_rating"));
  sc.setOhExpertiseRating(getConfigFloat("oh_expertise_rating"));
  sc.setAttackPower(getConfigInt("ap"));
  sc.setHaste(getConfigFloat("haste"));
  // sc.setArmorPenetration(getConfigFloat("armor_penetration"));
  sc.setArmorIgnore(getConfigInt("ignore_armor"));
  sc.setStength(getConfigInt("str"));
  sc.setAgility(getConfigInt("agi"));
  sc.setIntelligence(getConfigInt("int"));
  sc.setSpirit(getConfigInt("spi"));
  sc.setMiss(getConfigFloat("miss"));
  sc.setDodge(getConfigFloat("dodge"));
  sc.setGlancing(getConfigFloat("glancing"));
  sc.setSpellMiss(getConfigFloat("spell_miss"));
  sc.setArmor(getConfigInt("armor"));
  sc.setNatureResistance(getConfigInt("nature_resistance"));
  sc.setFireResistance(getConfigInt("fire_resistance"));
  sc.setFrostResistance(getConfigInt("frost_resistance"));
  sc.setSpellpower(getConfigInt("spellpower"));
  sc.setSpellCrit(getConfigFloat("spell_crit"));
  sc.setSpellHit(getConfigFloat("spell_hit"));
  sc.setMaxMana(getConfigFloat("max_mana"));
  sc.setMp5(getConfigInt("mp5"));


  sc.setBuff("attack_power_buff_multiplier", getConfigBuff("attack_power_buff_multiplier"));
  sc.setBuff("spell_crit_chance_buff", getConfigBuff("spell_crit_chance_buff"));

  sc.setTalent("flurry", getConfigTalent("flurry"));
  sc.setTalent("improved_weapon_totems", getConfigTalent("improved_weapon_totems"));
  sc.setTalent("elemental_weapons", getConfigTalent("elemental_weapons"));
  sc.setTalent("mental_quickness", getConfigTalent("mental_quickness"));
  // sc.setTalent("mental_dexterity", getConfigTalent("mental_dexterity"));
  // sc.setTalent("ancestral_knowledge", getConfigTalent("ancestral_knowledge"));
  // sc.setTalent("shamanistic_focus", getConfigTalent("shamanistic_focus"));
  sc.setTalent("weapon_mastery", getConfigTalent("weapon_mastery"));
  sc.setTalent("dual_wield_specialization", getConfigTalent("dual_wield_specialization"));
  // sc.setTalent("improved_stormstrike", getConfigTalent("improved_stormstrike"));
  sc.setTalent("unleashed_rage", getConfigTalent("unleashed_rage"));
  sc.setTalent("natures_guidance", getConfigTalent("natures_guidance"));
  // sc.setTalent("improved_shields", getConfigTalent("improved_shields"));
  // sc.setTalent("static_shock", getConfigTalent("static_shock"));
  sc.setTalent("shamanistic_rage", getConfigTalent("shamanistic_rage"));
  // sc.setTalent("maelstrom_weapon", getConfigTalent("maelstrom_weapon"));
  sc.setTalent("concussion", getConfigTalent("concussion"));
  // sc.setTalent("convection", getConfigTalent("convection"));
  sc.setTalent("call_of_flame", getConfigTalent("call_of_flame"));
  // sc.setTalent("call_of_thunder", getConfigTalent("call_of_thunder"));
  // sc.setTalent("unrelenting_storm", getConfigTalent("unrelenting_storm"));
  // sc.setTalent("reverberation", getConfigTalent("reverberation"));
  sc.setTalent("elemental_devastation", getConfigTalent("elemental_devastation"));
  // sc.setTalent("elemental_focus", getConfigTalent("elemental_focus"));
  sc.setTalent("elemental_fury", getConfigTalent("elemental_fury"));
  sc.setTalent("elemental_precision", getConfigTalent("elemental_precision"));
  // sc.setTalent("lightning_mastery", getConfigTalent("lightning_mastery"));
  // sc.setTalent("elemental_oath", getConfigTalent("elemental_oath"));
  // sc.setTalent("lightning_overload", getConfigTalent("lightning_overload"));
  // sc.setTalent("lava_flows", getConfigTalent("lava_flows"));
  // sc.setTalent("storm_earth_and_fire", getConfigTalent("storm_earth_and_fire"));

  sc.fixStats();

  sc.setBuff("armor_debuff_major", getConfigBuff("armor_debuff_major"));
  sc.setBuff("armor_debuff_minor", getConfigBuff("armor_debuff_minor"));
  sc.setBuff("physical_vulnerability_debuff", getConfigBuff("physical_vulnerability_debuff"));
  sc.setBuff("melee_haste_buff", getConfigBuff("melee_haste_buff"));
  sc.setBuff("melee_crit_chance_buff", getConfigBuff("melee_crit_chance_buff"));
  sc.setBuff("attack_power_buff_flat", getConfigBuff("attack_power_buff_flat"));
  sc.setBuff("spell_haste_buff", getConfigBuff("spell_haste_buff"));
  sc.setBuff("spell_crit_chance_debuff", getConfigBuff("spell_crit_chance_debuff"));
  sc.setBuff("spell_damage_debuff", getConfigBuff("spell_damage_debuff"));
  sc.setBuff("spellpower_buff", getConfigBuff("spellpower_buff"));
  sc.setBuff("spell_hit_chance_debuff", getConfigBuff("spell_hit_chance_debuff"));
  sc.setBuff("haste_buff", getConfigBuff("haste_buff"));
  sc.setBuff("percentage_damage_increase", getConfigBuff("percentage_damage_increase"));
  sc.setBuff("crit_chance_debuff", getConfigBuff("crit_chance_debuff"));
  sc.setBuff("stat_multiplier", getConfigBuff("stat_multiplier"));
  sc.setBuff("stat_add_buff", getConfigBuff("stat_add_buff"));
  sc.setBuff("agi_and_strength_buff", getConfigBuff("agi_and_strength_buff"));
  sc.setBuff("intellect_buff", getConfigBuff("intellect_buff"));
  sc.setBuff("replenishment", getConfigInt("replenishment"));
  sc.setBuff("water_shield", getConfigInt("water_shield"));
  sc.setBuff("mana_spring_totem", getConfigInt("mana_spring_totem"));
  sc.setBuff("blessing_of_wisdom", getConfigInt("blessing_of_wisdom"));
  sc.setBuff("judgement_of_wisdom", getConfigInt("judgement_of_wisdom"));

  sc.setConsumable(config["flask_elixir"]);
  sc.setConsumable(config["guardian_elixir"]);
  sc.setConsumable(config["potion"]);
  sc.setConsumable(config["food"]);
  sc.setMiscItem(config["misc_item"]);

  sc.setUseManaPotionMaxMana(getConfigFloat("use_mana_potion_if_mana_left"));

  sc.setCombatLength(getConfigFloat("combat_length"));
  sc.setWaitSSWithWFCD(getConfigFloat("wait_ss_with_wf_cd"));
  //sc.useSearingTotem(getConfigInt("use_searing_totem"));
  sc.setBloodlust(getConfigInt("bloodlust_casters"), getConfigInt("sync_bloodlust_with_trinkets"));

#ifdef DEBUG
  f32 hours = getConfigFloat("simulation_time_combatlog") / 60.0f;
#else
  f32 hours = getConfigFloat("simulation_time");
#endif

  hours = sc.startSimulation(hours, getConfigInt("report_count"));
  clock_t end = clock();

#ifdef DEBUG
    closeCombatLog();
#endif

  std::cout << "elapsed simulation time: " << hours << "h\n";
  std::cout << "elapsed real time: " << (f32)(end-start) / CLOCKS_PER_SEC << "s\n";
  std::cout << "simulation speed: " << static_cast<int>(hours*3600 / ((f32)(end-start) / CLOCKS_PER_SEC)) << "x\n";

  std::cin.get();

  return 0;
}
