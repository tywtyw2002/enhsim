//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "enhsim.h"
#include "effects.h"
#include "enchants.h"

#include <math.h>
#include <sstream>
#include <string>
#include <algorithm>

#ifdef DEBUG
EnhSim::EnhSim(Statistics& stats, std::fstream& combatlog):
#else
EnhSim::EnhSim(Statistics& stats):
#endif
                rotation_count_(0),
                stats_(stats),

                min_lag_(0),
                max_lag_(1),

                mh_enchant_(0),
                oh_enchant_(0),
                trinket1_(0),
                trinket2_(0),
                totem_(0),
                set_bonus_(0),
                metagem_(0),
                potion_(0),
                misc_item_(0),

                /*use_searing_totem_(0),
                use_shock_approximation_(false),
                average_shocks_per_minute_(0.0f),*/

                armor_base_(0),
                armor_(0),
                // armor_penetration_(1.0f),
               armor_ignore_(0),
                damage_reduction_(1.0f),
                spell_miss_(0),
                spell_miss_totem_(0),
                spell_miss_base_(0),
                nature_resistance_(0),
                fire_resistance_(0),
                frost_resistance_(0),
                nature_damage_reduction_(1.0f),
                fire_damage_reduction_(1.0f),
                frost_damage_reduction_(1.0f),

                old_melee_haste_divider_(1.0f),
                melee_haste_divider_(1.0f),
                spell_haste_divider_(1.0f),

                ap_base_(0),
                ap_(0),
                str_base_(0),
                str_(0),
                agi_base_(0),
                agi_(0),
                int_base_(0),
                int_(0),
                spi_base_(0),
                spi_(0),
                ap_multiplier_(1.0f),
                strength_multiplier_(1.0f),
                agility_multiplier_(1.0f),
                intelligence_multiplier_(1.0f),
                spirit_multiplier_(1.0f),

                physical_damage_multiplier_(1.0f),
                physical_crit_multiplier_(2.0f),

                ap_to_spellpower_multiplier_(0.0f),
                int_to_ap_multiplier_(0.0f),

                spellpower_(0),
                nature_crit_base_(0),
                nature_crit_(0),
                fire_crit_base_(0),
                fire_crit_(0),
                frost_crit_base_(0),
                frost_crit_(0),
                spell_hit_(0),
                spell_hit_totem_(0),
                nature_damage_multiplier_(1.0f),
                fire_damage_multiplier_(1.0f),
                frost_damage_multiplier_(1.0f),
                spell_crit_multiplier_base_(1.5f),
                spell_crit_multiplier_(1.5f),
                spell_crit_bonus_(0.0f),
                firetotem_damage_multiplier_(1.0f),
                // lava_burst_damage_multiplier_(1.0f),
                shock_damage_multiplier_(1.0f),
                stormstrike_damage_multiplier_(1.0f),

                base_mana_(0.0f),
                max_mana_(0.0f),
                max_mana_base_(0.0f),
                mana_(0.0f),
                mana_regen_per_tick_(0.0f),
                mp5_regen_per_tick_(0.0f),

                mental_quickness_mana_(0.0f),
                shamanistic_focus_mana_(0.0f),
                convection_mana_(0.0f),

                spell_gcd_duration_(GCD),

                duration_(0),

                wf_cd_(false),
                wait_ss_wf_(0),
                last_wf_(-10000),
                
                #ifdef DEBUG
                combatlog_(combatlog),
                #endif

                mh_swang_(false),
                oh_swang_(false),

                simulate_mana_(true),
                oom_(false),
                oom_start_time_(0),
                
                
                p_mh_auto_attack_miss_count(0),
                p_mh_auto_attack_dodge_count(0),
                p_mh_auto_attack_glancing_count(0),
                p_mh_auto_attack_hit_count(0),
                p_mh_auto_attack_crit_count(0),

                p_oh_auto_attack_miss_count(0),
                p_oh_auto_attack_dodge_count(0),
                p_oh_auto_attack_glancing_count(0),
                p_oh_auto_attack_hit_count(0),
                p_oh_auto_attack_crit_count(0),

                p_mh_windfury_miss_count(0),
                p_mh_windfury_dodge_count(0),
                p_mh_windfury_hit_count(0),
                p_mh_windfury_crit_count(0),

                p_oh_windfury_miss_count(0),
                p_oh_windfury_dodge_count(0),
                p_oh_windfury_hit_count(0),
                p_oh_windfury_crit_count(0),

                p_mh_flametongue_miss_count(0),
                p_mh_flametongue_hit_count(0),
                p_mh_flametongue_crit_count(0),

                p_oh_flametongue_miss_count(0),
                p_oh_flametongue_hit_count(0),
                p_oh_flametongue_crit_count(0),

                p_mh_stormstrike_miss_count(0),
                p_mh_stormstrike_dodge_count(0),
                p_mh_stormstrike_hit_count(0),
                p_mh_stormstrike_crit_count(0),

                p_oh_stormstrike_miss_count(0),
                p_oh_stormstrike_dodge_count(0),
                p_oh_stormstrike_hit_count(0),
                p_oh_stormstrike_crit_count(0)

                // p_lava_lash_miss_count(0),
                // p_lava_lash_dodge_count(0),
                // p_lava_lash_hit_count(0),
                // p_lava_lash_crit_count(0),

                // p_earth_shock_miss_count(0),
                // p_earth_shock_hit_count(0),
                // p_earth_shock_crit_count(0),

                // p_flame_shock_miss_count(0),
                // p_flame_shock_hit_count(0),
                // p_flame_shock_crit_count(0),

                // p_frost_shock_miss_count(0),
                // p_frost_shock_hit_count(0),
                // p_frost_shock_crit_count(0),

                // p_lightning_bolt_miss_count(0),
                // p_lightning_bolt_hit_count(0),
                // p_lightning_bolt_crit_count(0),

                // p_chain_lightning_miss_count(0),
                // p_chain_lightning_hit_count(0),
                // p_chain_lightning_crit_count(0),

                // p_lava_burst_miss_count(0),
                // p_lava_burst_hit_count(0),
                // p_lava_burst_crit_count(0),

                // p_lightning_shield_miss_count(0),
                // p_lightning_shield_hit_count(0),
                // p_lightning_shield_cast_count(0),

                // p_lightning_overload_miss_count(0),
                // p_lightning_overload_hit_count(0),
                // p_lightning_overload_crit_count(0)
    {
                


  //initialize random number generator
  init_random();

  skill_rotation_ = new PriorityRotation(this);

  for (unsigned int i=0; i<PROC_COUNT; ++i) {
    
    p_mh_auto_attack_miss[i] = 0;
    p_mh_auto_attack_dodge[i] = 0;
    p_mh_auto_attack_glancing[i] = 0;
    p_mh_auto_attack_hit[i] = 0;
    p_mh_auto_attack_crit[i] = 0;

    p_oh_auto_attack_miss[i] = 0;
    p_oh_auto_attack_dodge[i] = 0;
    p_oh_auto_attack_glancing[i] = 0;
    p_oh_auto_attack_hit[i] = 0;
    p_oh_auto_attack_crit[i] = 0;

    p_mh_windfury_miss[i] = 0;
    p_mh_windfury_dodge[i] = 0;
    p_mh_windfury_hit[i] = 0;
    p_mh_windfury_crit[i] = 0;

    p_oh_windfury_miss[i] = 0;
    p_oh_windfury_dodge[i] = 0;
    p_oh_windfury_hit[i] = 0;
    p_oh_windfury_crit[i] = 0;

    p_mh_flametongue_miss[i] = 0;
    p_mh_flametongue_hit[i] = 0;
    p_mh_flametongue_crit[i] = 0;

    p_oh_flametongue_miss[i] = 0;
    p_oh_flametongue_hit[i] = 0;
    p_oh_flametongue_crit[i] = 0;

    p_mh_stormstrike_miss[i] = 0;
    p_mh_stormstrike_dodge[i] = 0;
    p_mh_stormstrike_hit[i] = 0;
    p_mh_stormstrike_crit[i] = 0;

    p_oh_stormstrike_miss[i] = 0;
    p_oh_stormstrike_dodge[i] = 0;
    p_oh_stormstrike_hit[i] = 0;
    p_oh_stormstrike_crit[i] = 0;

    // p_lava_lash_miss[i] = 0;
    // p_lava_lash_dodge[i] = 0;
    // p_lava_lash_hit[i] = 0;
    // p_lava_lash_crit[i] = 0;

    p_earth_shock_miss[i] = 0;
    p_earth_shock_hit[i] = 0;
    p_earth_shock_crit[i] = 0;

    p_flame_shock_miss[i] = 0;
    p_flame_shock_hit[i] = 0;
    p_flame_shock_crit[i] = 0;

    p_frost_shock_miss[i] = 0;
    p_frost_shock_hit[i] = 0;
    p_frost_shock_crit[i] = 0;

    // p_lightning_bolt_miss[i] = 0;
    // p_lightning_bolt_hit[i] = 0;
    // p_lightning_bolt_crit[i] = 0;

    // p_chain_lightning_miss[i] = 0;
    // p_chain_lightning_hit[i] = 0;
    // p_chain_lightning_crit[i] = 0;

    // p_lava_burst_miss[i] = 0;
    // p_lava_burst_hit[i] = 0;
    // p_lava_burst_crit[i] = 0;

    // p_lightning_shield_miss[i] = 0;
    // p_lightning_shield_hit[i] = 0;
    // p_lightning_shield_cast[i] = 0;

    // p_lightning_overload_miss[i] = 0;
    // p_lightning_overload_hit[i] = 0;
    // p_lightning_overload_crit[i] = 0;
  }


  //init haste multiplier to 1.0f
  for (unsigned int i=0; i<HASTE_COUNT; ++i) {
    haste_multipliers_[i] = 1.0f;
  }

  //create the progress reporter
  progress_ = new SimulationProgress(this);

  //create Effects
  global_cooldown_ = new GlobalCooldown(this);
  mh_event_ = new MhEvent(this);
  oh_event_ = new OhEvent(this);
  mh_windfury_ = new MhWindfury(this);
  oh_windfury_ = new OhWindfury(this);
  unleashed_rage_ = new UnleashedRage(this);
  flurry_ = new Flurry(this);
  flurry_consume_ = new FlurryConsume(this);
  stormstrike_ = new Stormstrike(this);
  searing_totem_ = new SearingTotem(this);
  shock_cooldown_ = new ShockCooldown(this);
  earth_shock_ = new EarthShock(this);
  flame_shock_ = new FlameShock(this);
  frost_shock_ = new FrostShock(this);
  elemental_devastation_ = new ElementalDevastation(this);
  mh_flametongue_ = new MhFlametongue(this);
  oh_flametongue_ = new OhFlametongue(this);
  //potion_cooldown_ = new PotionCooldown(this);
  misc_cooldown_ = new MiscCooldown(this);
  // maelstrom_weapon_ = new MaelstromWeapon(this);
  // lava_burst_ = new LavaBurst(this);
  // lightning_bolt_ = new LightningBolt(this);
  // chain_lightning_ = new ChainLightning(this);
  // lightning_shield_ = new LightningShield(this);
  // static_shock_ = new StaticShock(this);
  //shamanistic_focus_ = new ShamanisticFocus(this);
  elemental_focus_ = new ElementalFocus(this);
  combat_length_ = new CombatLength(this);
  bloodlust_ = new Bloodlust(this);
  // lava_lash_ = new LavaLash(this);
  spell_casting_ = new SpellCasting(this);
  input_lag_ = new InputLag(this);
  // elemental_oath_ = new ElementalOath(this);
  // lightning_overload_ = new LightningOverload(this);
  mana_regen_ = new ManaRegen(this);
  fsr_ = new FiveSecRule(this);
  // unrelenting_storm_ = new UnrelentingStorm(this);
  shamanistic_rage_ = new ShamanisticRage(this);
  judgement_of_wisdom_ = new JudgementOfWisdom(this);

  trinket_cooldown_ = new TrinketCooldown(this);
}

EnhSim::~EnhSim() {
  delete skill_rotation_;
  delete[] rotation_;

  delete progress_;

  delete global_cooldown_;
  //delete mh_weapon_enchant_;
  //delete oh_weapon_enchant_;
  delete mh_event_;
  delete oh_event_;
  //delete mh_reschedule_;
  //delete oh_reschedule_;
  delete mh_windfury_;
  delete oh_windfury_;
  delete unleashed_rage_;
  delete flurry_;
  delete flurry_consume_;
  delete stormstrike_;
  delete searing_totem_;
  delete shock_cooldown_;
  delete earth_shock_;
  delete flame_shock_;
  delete frost_shock_;
  delete elemental_devastation_;
  delete mh_flametongue_;
  delete oh_flametongue_;
  delete potion_;
  delete misc_cooldown_;
  delete misc_item_;
  // delete maelstrom_weapon_;
  // elete lava_burst_;
  // delete lightning_bolt_;
  // delete chain_lightning_;
  // delete lightning_shield_;
  // delete static_shock_;
  delete elemental_focus_;
  delete combat_length_;
  delete bloodlust_;
  // delete lava_lash_;
  delete spell_casting_;
  delete input_lag_;
  // delete elemental_oath_;
  // delete lightning_overload_;
  delete mana_regen_;
  delete fsr_;
  // delete unrelenting_storm_;
  delete shamanistic_rage_;
  delete judgement_of_wisdom_;

  delete mh_enchant_;
  delete oh_enchant_;
  delete trinket_cooldown_;
  delete trinket1_;
  delete trinket2_;
  delete totem_;
  delete set_bonus_;
}

//pre-calculate hit table
//also damage reduction, damage and haste
void EnhSim::initializeSimulation() {

  calculateSpellCritMultiplier();

  calculateStrength();
  calculateAgility();
  calculateIntelligence();
  calculateSpirit();

  //calculate miss chance, this also calculates hit tables
  calculateMiss();
  //calculate expertise, this also calculates dodge, which also calculates hit tables
  //so hit tables are calculated twice...but it doesnt matter
  calculateExpertise();

  //calculate armor
  //also calculates damage
  calculateArmor();

  //calculate haste
  calculateMeleeHaste();
  calculateSpellHaste();

  //calculate proc chances
  if (mh_enchant_) mh_enchant_->calculateProcChance();
  if (oh_enchant_) oh_enchant_->calculateProcChance();
  if (trinket1_) {
    if (trinket1_->ppm_flag_) trinket1_->calculateProcChance();
  }
  if (trinket2_) {
    if (trinket2_->ppm_flag_) trinket2_->calculateProcChance();
  }
  if (totem_) {
    if (totem_->ppm_flag_) totem_->calculateProcChance();
  }
  if (set_bonus_) {
    if (set_bonus_->ppm_flag_) set_bonus_->calculateProcChance();
  }
  if (metagem_) {
    if (metagem_->ppm_flag_) metagem_->calculateProcChance();
  }

  // maelstrom_weapon_->calculateProcChance();
  shamanistic_rage_->calculateProcChance();

  //calculate attack table for spells
  calculateSpellMiss();

  //calculate resistance reductions
  //these are damage multipliers, so we decrease the damage reduction from 1.0f
  if (nature_resistance_ < 0) nature_resistance_ = 0;
  if (fire_resistance_ < 0) fire_resistance_ = 0;
  if (frost_resistance_ < 0) frost_resistance_ = 0;

  int effective_nature_resistance = (nature_resistance_ + std::max<int>((TARGET_LEVEL - ATTACKER_LEVEL) * 5, 0) - std::min<int>(0/*spell penetration*/, 0));
  nature_damage_reduction_ = 1.0f - (effective_nature_resistance / (ATTACKER_LEVEL * 5.0f)) * 75.0f / 100.0f;

  int effective_fire_resistance = (fire_resistance_ + std::max<int>((TARGET_LEVEL - ATTACKER_LEVEL) * 5, 0) - std::min<int>(0/*spell penetration*/, 0));
  fire_damage_reduction_ = 1.0f - (effective_fire_resistance / (ATTACKER_LEVEL * 5.0f)) * 75.0f / 100.0f;

  int effective_frost_resistance = (frost_resistance_ + std::max<int>((TARGET_LEVEL - ATTACKER_LEVEL) * 5, 0) - std::min<int>(0/*spell penetration*/, 0));
  frost_damage_reduction_ = 1.0f - (effective_frost_resistance / (ATTACKER_LEVEL * 5.0f)) * 75.0f / 100.0f;
}

void EnhSim::calculateArmor() {
  // armor_ = static_cast<int>(armor_base_ * armor_penetration_);
  armor_ = static_cast<int>(armor_base_ - armor_ignore_);

  calculateDamageReduction();
}

void EnhSim::calculateDamage() {
  mh.damage_ = ((mh.dps_ + ap_ / 14.0f) * static_cast<f32>(mh.speed_base_) / 100) * damage_reduction_ * physical_damage_multiplier_;
  oh.damage_ = ((oh.dps_ + ap_ / 14.0f) * static_cast<f32>(oh.speed_base_) / 200) * damage_reduction_ * physical_damage_multiplier_;
  mh.damage_crit_ = mh.damage_ * physical_crit_multiplier_;
  oh.damage_crit_ = oh.damage_ * physical_crit_multiplier_;
}

void EnhSim::calculateDamageReduction() {
  
  //notice that damage reduction is a damage multiplier, so we decrease the damage reduction from 1.0f
  if (armor_ >= 0) {
    damage_reduction_ = 1.0f - (armor_ / (armor_ + 400.0f + 85.0f * (ATTACKER_LEVEL + 4.5f * (ATTACKER_LEVEL - 59.0f))));
  }
  //if armor is under 0, there is no damage reduction
  else {
    damage_reduction_ = 1.0f;
  }

  calculateDamage();
}


void EnhSim::calculateMeleeHaste() {
  //calculate haste from haste multipliers
  //this is a bit silly way for doing it but it is accurate
  //ill change this when I figure out a better way
  old_melee_haste_divider_ = melee_haste_divider_;

  melee_haste_divider_ = haste_multipliers_[HASTE_MELEE_RATING] *
                         haste_multipliers_[HASTE_FLURRY] *
                         haste_multipliers_[HASTE_BLOODLUST] *
                         haste_multipliers_[HASTE_MH_MONGOOSE] *
                         haste_multipliers_[HASTE_OH_MONGOOSE] *
                         haste_multipliers_[HASTE_BERSERKING] *
                         haste_multipliers_[HASTE_MELEE_RAID_BUFF];

  mh.speed_ = floor(static_cast<int64>(mh.speed_base_ / melee_haste_divider_));
  oh.speed_ = floor(static_cast<int64>(oh.speed_base_ / melee_haste_divider_));

  if (mh_enchant_) mh_enchant_->reCalculateProcChance();
  if (oh_enchant_) oh_enchant_->reCalculateProcChance();
  if (trinket1_) { if (trinket1_->ppm_flag_) trinket1_->reCalculateProcChance(); }
  if (trinket2_) { if (trinket2_->ppm_flag_) trinket2_->reCalculateProcChance(); }
  if (totem_) { if (totem_->ppm_flag_) totem_->reCalculateProcChance(); }
  if (set_bonus_) { if (set_bonus_->ppm_flag_) set_bonus_->reCalculateProcChance(); }
  if (metagem_) { if (metagem_->ppm_flag_) metagem_->reCalculateProcChance(); }

  // maelstrom_weapon_->reCalculateProcChance();
  shamanistic_rage_->reCalculateProcChance();
}

void EnhSim::calculateSpellHaste() {
  
  spell_haste_divider_ = haste_multipliers_[HASTE_SPELL_RATING] *
                         haste_multipliers_[HASTE_BLOODLUST] *
                         haste_multipliers_[HASTE_BERSERKING] *
                         haste_multipliers_[HASTE_SPELL_RAID_BUFF];

  spell_gcd_duration_ = floor(static_cast<int64>(GCD / spell_haste_divider_));
  if (spell_gcd_duration_ < 100) {
    spell_gcd_duration_ = 100;
  }
}

void EnhSim::calculateMiss() {
  mh.calculateMiss();
  oh.calculateMiss();
}

void EnhSim::calculateDodge() {
  mh.calculateDodge();
  oh.calculateDodge();
}

void EnhSim::calculateExpertise() {
  mh.calculateExpertise();
  oh.calculateExpertise();
}

void EnhSim::calculateSpellMiss() {
  spell_miss_ = spell_miss_base_ - spell_hit_;
  spell_miss_totem_ = spell_miss_base_ - spell_hit_totem_;

  if (spell_miss_ < MINIMUM_SPELL_MISS) spell_miss_ = MINIMUM_SPELL_MISS;
  if (spell_miss_totem_ < MINIMUM_SPELL_MISS) spell_miss_totem_ = MINIMUM_SPELL_MISS;
}

void EnhSim::calculateSpellpower() {
  spellpower_ = spellpower_base_ + static_cast<int>(ap_ * ap_to_spellpower_multiplier_);
}

void EnhSim::calculateAttackPower() {
  ap_ = static_cast<int>((ap_base_ + str_ * STRENGTH_TO_AP + agi_ * AGILITY_TO_AP + int_ * int_to_ap_multiplier_) * ap_multiplier_);

  calculateSpellpower();
  calculateDamage();
}

void EnhSim::calculateCrit() {
  mh.crit_ = mh.crit_base_ + static_cast<int>(agi_ * AGILITY_TO_CRIT);
  oh.crit_ = oh.crit_base_ + static_cast<int>(agi_ * AGILITY_TO_CRIT);

  //fix attack table
  mh.miss_dodge_glancing_crit_ = mh.miss_dodge_glancing_ + mh.crit_;
  oh.miss_dodge_glancing_crit_ = oh.miss_dodge_glancing_ + oh.crit_;
}

void EnhSim::calculateStrength() {
  str_ = static_cast<int>(str_base_ * strength_multiplier_);

  calculateAttackPower();
}

void EnhSim::calculateAgility() {
  agi_ = static_cast<int>(agi_base_ * agility_multiplier_);

  calculateAttackPower();
  calculateCrit();
}

void EnhSim::calculateIntelligence() {
  int_ = static_cast<int>(int_base_ * intelligence_multiplier_);

  calculateAttackPower();
  calculateSpellCrit();
  calculateMana();
  calculateManaRegen();
}

void EnhSim::calculateSpirit() {
  spi_ = static_cast<int>(spi_base_ * spirit_multiplier_);

  calculateManaRegen();
}

void EnhSim::calculateSpellCrit() {
  nature_crit_ = nature_crit_base_ + static_cast<int>(int_ * INTELLIGENCE_TO_SPELLCRIT);
  fire_crit_ = fire_crit_base_ + static_cast<int>(int_ * INTELLIGENCE_TO_SPELLCRIT);
  frost_crit_ = frost_crit_base_ + static_cast<int>(int_ * INTELLIGENCE_TO_SPELLCRIT);
}

void EnhSim::calculateMana() {
  max_mana_ = max_mana_base_ + int_ * INTELLIGENCE_TO_MANA;

  if (mana_ > max_mana_) {
    mana_ = max_mana_;
  }
}

void EnhSim::calculateManaRegen() {
  mana_regen_per_tick_ = static_cast<f32>((0.001f + spi_ * BASE_MANA_REGEN * sqrt(static_cast<f32>(int_))) * MANA_REGEN_INTERVAL / 100.0f);
}

void EnhSim::calculateSpellCritMultiplier() {
  spell_crit_multiplier_ = (spell_crit_multiplier_base_ - 1.0f) * (1.0f + spell_crit_bonus_) + 1.0f;
  // lava_burst_->crit_multiplier_ = (spell_crit_multiplier_base_ - 1.0f) * (1.0f + spell_crit_bonus_ + lava_burst_->crit_damage_bonus_) + 1.0f;
}

void EnhSim::changeHaste(const f32& haste) {
  changeMeleeHaste(haste);
  changeSpellHaste(haste);
}

void EnhSim::changeMeleeHaste(const f32& haste) {
  haste_multipliers_[HASTE_MELEE_RATING] += haste;

  calculateMeleeHaste();
  hasteMidSwing();
}

void EnhSim::changeSpellHaste(const f32& haste) {
  haste_multipliers_[HASTE_SPELL_RATING] += haste;

  calculateSpellHaste();
}

void EnhSim::changeHasteMultiplier(const f32& haste_multiplier, const unsigned int& index) {
  //indexes are constant values defined in globalutil.h, which Effects pass to this function
  haste_multipliers_[index] = haste_multiplier;

  calculateMeleeHaste();
  calculateSpellHaste();
  hasteMidSwing();
}

void EnhSim::changeMeleeHasteMultiplier(const f32& haste_multiplier, const unsigned int& index) {
  //indexes are constant values defined in globalutil.h, which Effects pass to this function
  haste_multipliers_[index] = haste_multiplier;

  calculateMeleeHaste();
  hasteMidSwing();
}

void EnhSim::changeSpellHasteMultiplier(const f32& haste_multiplier, const unsigned int& index) {
  //indexes are constant values defined in globalutil.h, which Effects pass to this function
  haste_multipliers_[index] = haste_multiplier;

  calculateSpellHaste();
}

void EnhSim::changeAttackPower(const int& ap) {
  ap_base_ += ap;

  calculateAttackPower();
}

void EnhSim::changeAttackPowerMultiplier(const f32& ap_multiplier) {
  ap_multiplier_ = ap_multiplier;
  
  calculateAttackPower();
}

void EnhSim::changeHit(const int& hit) {
  mh.hit_ += hit;
  oh.hit_ += hit;

  calculateMiss();
}

void EnhSim::changeExpertiseRating(const int& expertise_rating) {
  mh.expertise_rating_ += expertise_rating;
  oh.expertise_rating_ += expertise_rating;

  calculateExpertise();
}

void EnhSim::changeCrit(const int& crit) {
  mh.crit_base_ += crit;
  oh.crit_base_ += crit;

  calculateCrit();
}

void EnhSim::changeStrength(const int& str) {
  str_base_ += str;

  calculateStrength();
}

void EnhSim::changeAgility(const int& agi) {
  agi_base_ += agi;

  calculateAgility();
}

void EnhSim::changeIntelligence(const int& intt) {
  int_base_ += intt;

  calculateIntelligence();
}

void EnhSim::changeSpirit(const int& spi) {
  spi_base_ += spi;

  calculateSpirit();
}

void EnhSim::changeArmor(const int& armor) {
  armor_base_ += armor;

  calculateArmor();
}

// void EnhSim::changeArmorPenetration(const f32& armorp) {
//   armor_penetration_ -= armorp;

//   calculateArmor();
// }

void EnhSim::changeArmorIgnore(const int& armor_ignore) {
  armor_ignore_ -= armor_ignore;

  calculateArmor();
}

void EnhSim::changeSpellpower(const int& sp) {
  spellpower_base_ += sp;
  
  calculateSpellpower();
}

void EnhSim::changeSpellHit(const int& spell_hit) {
  spell_hit_ += spell_hit;
  spell_hit_totem_ += spell_hit;

  calculateSpellMiss();
}

void EnhSim::changeSpellCrit(const int& spell_crit) {
  nature_crit_base_ += spell_crit;
  fire_crit_base_ += spell_crit;
  frost_crit_base_ += spell_crit;

  calculateSpellCrit();
}


void EnhSim::hasteMidSwing() {
  if (!spell_casting_->casting_) {

    f32 haste = old_melee_haste_divider_ / melee_haste_divider_;
    int64 timeleft;

    if (!mh_swang_ && mh.attack_) {

      if (timeleft = ceil((mh.next_swing_node_->timestamp_ - now()) * haste)) {
        /*que_.deleteEvent(mh.next_swing_node_);
        addMhEvent(mh.next_swing_node_, timeleft);*/

        if (haste > 1.0) {
          que_.moveEventSearchForward(mh.next_swing_node_, timeleft);
        }
        else {
          que_.moveEventSearchBackward(mh.next_swing_node_, timeleft);
        }
      }
    }

    if (!oh_swang_ && oh.attack_) {

      if (timeleft = ceil((oh.next_swing_node_->timestamp_ - now()) * haste)) {
        /*que_.deleteEvent(oh.next_swing_node_);
        addOhEvent(oh.next_swing_node_, timeleft);*/

        if (haste > 1.0) {
          que_.moveEventSearchForward(oh.next_swing_node_, timeleft);
        }
        else {
          que_.moveEventSearchBackward(oh.next_swing_node_, timeleft);
        }
      }
    }
  }
}

//returns the actual regenerated amount of mana
f32 EnhSim::regenMana(const f32& mana) {

  mana_ += mana;

  if (mana_ > max_mana_) {

    f32 amount = mana - (mana_ - max_mana_);
    stats_.mana_overregen_ += mana - amount;

    mana_ = max_mana_;
    return amount;
  }

  return mana;
}

bool EnhSim::requestMana(const f32& percentage, const f32& multiplier) {

  if (!simulate_mana_ || mana_ >= BASE_MANA * percentage * multiplier) {

    if (oom_) {
      oom_ = false;
      stats_.oom_time_ += now() - oom_start_time_;
    }

    return true;
  }

  if (!oom_) {
    oom_ = true;
    oom_start_time_ = now();
  }

  return false;
}

f32 EnhSim::useMana(const f32& percentage, const f32& multiplier) {

  if (multiplier > 0.0f) {
    f32 mana = BASE_MANA * percentage * multiplier;

    if (simulate_mana_) {

      mana_ -= mana;
      if (mana_ < 0.0f) {
        mana_ = 0.0f;
      }

      fsr_->trigger();

      if (potion_) {
        potion_->use();
      }
    }

    return mana;
  }

  return 0;
}


f32 EnhSim::requestElementalFocus() {
  if (elemental_focus_->charges_ > 0) {
    return 0.4f;
  }

  return 0.0f;
}

f32 EnhSim::consumeElementalFocus() {
  if (elemental_focus_->charges_-- > 0) {
    return 0.4f;
  }

  return 0.0f;
}

void EnhSim::consumeStormstrikeCharge() {
  if (stormstrike_->charges_-- == 0) {
    stormstrike_damage_multiplier_ = 1.0f;
  }
}

int64 EnhSim::randomLag() {
  return random(max_lag_ - min_lag_) + min_lag_;
}











void EnhSim::simulate(const f32& hours) {

  //first calculate the duration
  //one duration unit is 0.01 seconds
  duration_ = static_cast<int64>(hours * 360000);

  //init all the variables
  initializeSimulation();

  //lets init event queue
  que_.initialize();

  if (mh.attack_) {
    addMhEvent(mh.next_swing_node_, 0);
  }
  if (oh.attack_) {
    addOhEvent(oh.next_swing_node_, 0);
  }

  //if we want progress repots, add the first one to timeline
  if (progress_->report_count_) {
    progress_->interval_ = duration_ / progress_->report_count_;
    addLowPrioEvent(progress_->interval_, progress_);
  }

  combat_length_->set();

  //set mana to max
  mana_ = max_mana_;

  if (bloodlust_->use_) {
    bloodlust_->use();
  }
  if (potion_) {
    potion_->use();
  }
  if (misc_item_) {
    misc_cooldown_->event(0);
  }
  if (trinket1_) {
    trinket1_->use();
  }
  if (trinket2_) {
    trinket2_->use();
  }

  //use unrelenting storm or mana regen only if we simulate mana
  if (simulate_mana_) {
    // if (unrelenting_storm_->use_) {
    //   unrelenting_storm_->event(0);
    // }

    mana_regen_->event(0);
  }

  //start skill rotation
  skill_rotation_->action();

  que_.start();
  int64 time = now();

  while (time <= duration_) {
    Event& event = que_.first();

    event.effect_->event(event.event_id_);

    if (time != event.next_->timestamp_) {
      if (mh_swang_) { addMhEvent(mh.next_swing_node_, mh.speed_); mh_swang_ = false; }
      if (oh_swang_) { addOhEvent(oh.next_swing_node_, oh.speed_); oh_swang_ = false; }
    }

    que_.pop();

    time = now();
  }

  //simulation done

  que_.clear();

  //set uptime variables for statistics
  unleashed_rage_->finalize();
  flurry_->finalize();
  elemental_devastation_->finalize();
  // elemental_oath_->finalize();
  

  if (mh_enchant_)  {
    mh_enchant_->finalize();
    stats_.mh_enchant_uptime_ += mh_enchant_->uptime_;
  }
  if (oh_enchant_) {
    oh_enchant_->finalize();
    stats_.oh_enchant_uptime_ += oh_enchant_->uptime_;
  }

  if (trinket1_) {
    trinket1_->finalize();
    stats_.trinket1_uptime_ += trinket1_->uptime_;
  }
  if (trinket2_) {
    trinket2_->finalize();
    stats_.trinket2_uptime_ += trinket2_->uptime_;
  }

  if (totem_) {
    totem_->finalize();
    stats_.totem_uptime_ += totem_->uptime_;
  }

  if (set_bonus_) {
    set_bonus_->finalize();
    stats_.set_bonus_uptime_ += set_bonus_->uptime_;
  }

  if (metagem_) {
    metagem_->finalize();
    stats_.metagem_uptime_ += metagem_->uptime_;
  }

  /*stats_.mw_total_time_ = maelstrom_weapon_->total_time_ / 100.0;
  stats_.mw_total_sd_time_ = maelstrom_weapon_->total_sd_time_ / 10000.0;
  stats_.mw_stack_full_count_ = maelstrom_weapon_->stack_full_count_;*/
}





//register an effect to proc on certain event
void EnhSim::useEffect(Effect* effect) {

  if (dynamic_cast<pMhAutoAttackMiss*>(effect)) p_mh_auto_attack_miss[p_mh_auto_attack_miss_count++] = effect;
  if (dynamic_cast<pMhAutoAttackDodge*>(effect)) p_mh_auto_attack_dodge[p_mh_auto_attack_dodge_count++] = effect;
  if (dynamic_cast<pMhAutoAttackGlancing*>(effect)) p_mh_auto_attack_glancing[p_mh_auto_attack_glancing_count++] = effect;
  if (dynamic_cast<pMhAutoAttackHit*>(effect)) p_mh_auto_attack_hit[p_mh_auto_attack_hit_count++] = effect;
  if (dynamic_cast<pMhAutoAttackCrit*>(effect)) p_mh_auto_attack_crit[p_mh_auto_attack_crit_count++] = effect;

  if (dynamic_cast<pOhAutoAttackMiss*>(effect)) p_oh_auto_attack_miss[p_oh_auto_attack_miss_count++] = effect;
  if (dynamic_cast<pOhAutoAttackDodge*>(effect)) p_oh_auto_attack_dodge[p_oh_auto_attack_dodge_count++] = effect;
  if (dynamic_cast<pOhAutoAttackGlancing*>(effect)) p_oh_auto_attack_glancing[p_oh_auto_attack_glancing_count++] = effect;
  if (dynamic_cast<pOhAutoAttackHit*>(effect)) p_oh_auto_attack_hit[p_oh_auto_attack_hit_count++] = effect;
  if (dynamic_cast<pOhAutoAttackCrit*>(effect)) p_oh_auto_attack_crit[p_oh_auto_attack_crit_count++] = effect;

  if (dynamic_cast<pMhWindfuryMiss*>(effect)) p_mh_windfury_miss[p_mh_windfury_miss_count++] = effect;
  if (dynamic_cast<pMhWindfuryDodge*>(effect)) p_mh_windfury_dodge[p_mh_windfury_dodge_count++] = effect;
  if (dynamic_cast<pMhWindfuryHit*>(effect)) p_mh_windfury_hit[p_mh_windfury_hit_count++] = effect;
  if (dynamic_cast<pMhWindfuryCrit*>(effect)) p_mh_windfury_crit[p_mh_windfury_crit_count++] = effect;

  if (dynamic_cast<pOhWindfuryMiss*>(effect)) p_oh_windfury_miss[p_oh_windfury_miss_count++] = effect;
  if (dynamic_cast<pOhWindfuryDodge*>(effect)) p_oh_windfury_dodge[p_oh_windfury_dodge_count++] = effect;
  if (dynamic_cast<pOhWindfuryHit*>(effect)) p_oh_windfury_hit[p_oh_windfury_hit_count++] = effect;
  if (dynamic_cast<pOhWindfuryCrit*>(effect)) p_oh_windfury_crit[p_oh_windfury_crit_count++] = effect;

  if (dynamic_cast<pMhFlametongueMiss*>(effect)) p_mh_flametongue_miss[p_mh_flametongue_miss_count++] = effect;
  if (dynamic_cast<pMhFlametongueHit*>(effect)) p_mh_flametongue_hit[p_mh_flametongue_hit_count++] = effect;
  if (dynamic_cast<pMhFlametongueCrit*>(effect)) p_mh_flametongue_crit[p_mh_flametongue_crit_count++] = effect;

  if (dynamic_cast<pOhFlametongueMiss*>(effect)) p_oh_flametongue_miss[p_oh_flametongue_miss_count++] = effect;
  if (dynamic_cast<pOhFlametongueHit*>(effect)) p_oh_flametongue_hit[p_oh_flametongue_hit_count++] = effect;
  if (dynamic_cast<pOhFlametongueCrit*>(effect)) p_oh_flametongue_crit[p_oh_flametongue_crit_count++] = effect;

  if (dynamic_cast<pMhStormstrikeMiss*>(effect)) p_mh_stormstrike_miss[p_mh_stormstrike_miss_count++] = effect;
  if (dynamic_cast<pMhStormstrikeDodge*>(effect)) p_mh_stormstrike_dodge[p_mh_stormstrike_dodge_count++] = effect;
  if (dynamic_cast<pMhStormstrikeHit*>(effect)) p_mh_stormstrike_hit[p_mh_stormstrike_hit_count++] = effect;
  if (dynamic_cast<pMhStormstrikeCrit*>(effect)) p_mh_stormstrike_crit[p_mh_stormstrike_crit_count++] = effect;

  if (dynamic_cast<pOhStormstrikeMiss*>(effect)) p_oh_stormstrike_miss[p_oh_stormstrike_miss_count++] = effect;
  if (dynamic_cast<pOhStormstrikeDodge*>(effect)) p_oh_stormstrike_dodge[p_oh_stormstrike_dodge_count++] = effect;
  if (dynamic_cast<pOhStormstrikeHit*>(effect)) p_oh_stormstrike_hit[p_oh_stormstrike_hit_count++] = effect;
  if (dynamic_cast<pOhStormstrikeCrit*>(effect)) p_oh_stormstrike_crit[p_oh_stormstrike_crit_count++] = effect;

  // if (dynamic_cast<pLavaLashMiss*>(effect)) p_lava_lash_miss[p_lava_lash_miss_count++] = effect;
  // if (dynamic_cast<pLavaLashDodge*>(effect)) p_lava_lash_dodge[p_lava_lash_dodge_count++] = effect;
  // if (dynamic_cast<pLavaLashHit*>(effect)) p_lava_lash_hit[p_lava_lash_hit_count++] = effect;
  // if (dynamic_cast<pLavaLashCrit*>(effect)) p_lava_lash_crit[p_lava_lash_crit_count++] = effect;

  if (dynamic_cast<pEarthShockMiss*>(effect)) p_earth_shock_miss[p_earth_shock_miss_count++] = effect;
  if (dynamic_cast<pEarthShockHit*>(effect)) p_earth_shock_hit[p_earth_shock_hit_count++] = effect;
  if (dynamic_cast<pEarthShockCrit*>(effect)) p_earth_shock_crit[p_earth_shock_crit_count++] = effect;

  if (dynamic_cast<pFlameShockMiss*>(effect)) p_flame_shock_miss[p_flame_shock_miss_count++] = effect;
  if (dynamic_cast<pFlameShockHit*>(effect)) p_flame_shock_hit[p_flame_shock_hit_count++] = effect;
  if (dynamic_cast<pFlameShockCrit*>(effect)) p_flame_shock_crit[p_flame_shock_crit_count++] = effect;

  if (dynamic_cast<pFrostShockMiss*>(effect)) p_frost_shock_miss[p_frost_shock_miss_count++] = effect;
  if (dynamic_cast<pFrostShockHit*>(effect)) p_frost_shock_hit[p_frost_shock_hit_count++] = effect;
  if (dynamic_cast<pFrostShockCrit*>(effect)) p_frost_shock_crit[p_frost_shock_crit_count++] = effect;

//   if (dynamic_cast<pLightningBoltMiss*>(effect)) p_lightning_bolt_miss[p_lightning_bolt_miss_count++] = effect;
//   if (dynamic_cast<pLightningBoltHit*>(effect)) p_lightning_bolt_hit[p_lightning_bolt_hit_count++] = effect;
//   if (dynamic_cast<pLightningBoltCrit*>(effect)) p_lightning_bolt_crit[p_lightning_bolt_crit_count++] = effect;

//   if (dynamic_cast<pChainLightningMiss*>(effect)) p_chain_lightning_miss[p_chain_lightning_miss_count++] = effect;
//   if (dynamic_cast<pChainLightningHit*>(effect)) p_chain_lightning_hit[p_chain_lightning_hit_count++] = effect;
//   if (dynamic_cast<pChainLightningCrit*>(effect)) p_chain_lightning_crit[p_chain_lightning_crit_count++] = effect;

//   if (dynamic_cast<pLavaBurstMiss*>(effect)) p_lava_burst_miss[p_lava_burst_miss_count++] = effect;
//   if (dynamic_cast<pLavaBurstHit*>(effect)) p_lava_burst_hit[p_lava_burst_hit_count++] = effect;
//   if (dynamic_cast<pLavaBurstCrit*>(effect)) p_lava_burst_crit[p_lava_burst_crit_count++] = effect;

//   if (dynamic_cast<pLightningShieldMiss*>(effect)) p_lightning_shield_miss[p_lightning_shield_miss_count++] = effect;
//   if (dynamic_cast<pLightningShieldHit*>(effect)) p_lightning_shield_hit[p_lightning_shield_hit_count++] = effect;
//   if (dynamic_cast<pLightningShieldCast*>(effect)) p_lightning_shield_cast[p_lightning_shield_cast_count++] = effect;

//   if (dynamic_cast<pLightningOverloadMiss*>(effect)) p_lightning_overload_miss[p_lightning_overload_miss_count++] = effect;
//   if (dynamic_cast<pLightningOverloadHit*>(effect)) p_lightning_overload_hit[p_lightning_overload_hit_count++] = effect;
//   if (dynamic_cast<pLightningOverloadCrit*>(effect)) p_lightning_overload_crit[p_lightning_overload_crit_count++] = effect;
}



//Event* EnhSim::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//  //que_.addHighPrioEvent(timestamp + lag, effect, event_id);
//  return que_.addEvent(timestamp + lag, PRIORITY_HIGH, effect, event_id);
//}
//
//Event* EnhSim::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//  //que_.addLowPrioEvent(timestamp + lag, effect, event_id);
//  return que_.addEvent(timestamp + lag, PRIORITY_LOW, effect, event_id);
//}

void EnhSim::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
  //que_.addHighPrioEvent(timestamp + lag, effect, event_id);
  que_.addEvent(timestamp + lag, PRIORITY_HIGH, effect, event_id);
}

void EnhSim::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
  //que_.addLowPrioEvent(timestamp + lag, effect, event_id);
  que_.addEvent(timestamp + lag, PRIORITY_LOW, effect, event_id);
}

void EnhSim::addHighPrioEvent(Event*& e, const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
  //que_.addHighPrioEvent(timestamp + lag, effect, event_id);
  que_.addEvent(e, timestamp + lag, PRIORITY_HIGH, effect, event_id);
}

void EnhSim::addLowPrioEvent(Event*& e, const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
  //que_.addLowPrioEvent(timestamp + lag, effect, event_id);
  que_.addEvent(e, timestamp + lag, PRIORITY_LOW, effect, event_id);
}

void EnhSim::addMhEvent(Event*& e, const int64& mh_speed) {
  //return que_.addMhEvent(mh_speed, mh_event_);
  que_.addEvent(e, mh_speed, PRIORITY_MH, mh_event_, 0);
}

void EnhSim::addOhEvent(Event*& e, const int64& oh_speed) {
  //return que_.addOhEvent(oh_speed, oh_event_);
  que_.addEvent(e, oh_speed, PRIORITY_OH, oh_event_, 0);
}



//mhSwing and ohSwing are pretty much the same
void EnhSim::mhSwing() {

  #ifndef FLURRY_SYNCED
  mh.next_swing_node_ = addMhEvent(mh.speed_);
  #endif

  mh.last_swing_time_ = now();

  //make the attack roll
  int rol = roll();

  if (rol < mh.miss_) {
    ++stats_.mh_miss_;
    COMBATLOG("MH miss")

    procList(p_mh_auto_attack_miss, p_mh_auto_attack_miss_count, P_MELEE | P_AUTO_ATTACK | P_MH | P_MISS);
  }

  else if (rol < mh.miss_dodge_) {
    ++stats_.mh_dodge_;
    COMBATLOG("MH dodge")

    procList(p_mh_auto_attack_dodge, p_mh_auto_attack_dodge_count, P_MELEE | P_AUTO_ATTACK | P_MH | P_DODGE);
  }

  else if (rol < mh.miss_dodge_glancing_) {
    ++stats_.mh_glancing_;
    stats_.mh_glancing_damage_ += mh.damage_ * GLANCING_REDUCTION;
    COMBATLOG("MH glancing " << mh.damage_ * GLANCING_REDUCTION)

    //if we hit, proc the hit procs..like some enchant
    procList(p_mh_auto_attack_glancing, p_mh_auto_attack_glancing_count, P_MELEE | P_AUTO_ATTACK | P_MH | P_GLANCING);
  }

  else if (rol < mh.miss_dodge_glancing_crit_) {
    ++stats_.mh_crit_;
    stats_.mh_crit_damage_ += mh.damage_crit_;
    COMBATLOG("MH crit " << mh.damage_crit_)

    //if we crit, proc the crit procs..like flurry or UR
    procList(p_mh_auto_attack_crit, p_mh_auto_attack_crit_count, P_MELEE | P_AUTO_ATTACK | P_MH | P_CRIT);
  }

  else {
    ++stats_.mh_hit_;
    stats_.mh_hit_damage_ += mh.damage_;
    COMBATLOG("MH hit " << mh.damage_)

    procList(p_mh_auto_attack_hit, p_mh_auto_attack_hit_count, P_MELEE | P_AUTO_ATTACK | P_MH | P_HIT);
  }
}





void EnhSim::ohSwing() {

  #ifndef FLURRY_SYNCED
  oh.next_swing_node_ = addOhEvent(oh.speed_);
  #endif

  oh.last_swing_time_ = now();

  int rol = roll();

  if (rol < oh.miss_) {

    ++stats_.oh_miss_;
    COMBATLOG("OH miss")

    procList(p_oh_auto_attack_miss, p_oh_auto_attack_miss_count, P_MELEE | P_AUTO_ATTACK | P_OH | P_MISS);
  }
  else if (rol < oh.miss_dodge_) {
    ++stats_.oh_dodge_;
    COMBATLOG("OH dodge")

    procList(p_oh_auto_attack_dodge, p_oh_auto_attack_dodge_count, P_MELEE | P_AUTO_ATTACK | P_OH | P_DODGE);
  }
  else if (rol < oh.miss_dodge_glancing_) {
    ++stats_.oh_glancing_;
    stats_.oh_glancing_damage_ += oh.damage_ * GLANCING_REDUCTION;
    COMBATLOG("OH glancing " << oh.damage_ * GLANCING_REDUCTION)

    procList(p_oh_auto_attack_glancing, p_oh_auto_attack_glancing_count, P_MELEE | P_AUTO_ATTACK | P_OH | P_GLANCING);
  }
  else if (rol < oh.miss_dodge_glancing_crit_) {
    ++stats_.oh_crit_;
    stats_.oh_crit_damage_ += oh.damage_crit_;
    COMBATLOG("OH crit " << oh.damage_crit_)

    procList(p_oh_auto_attack_crit, p_oh_auto_attack_crit_count, P_MELEE | P_AUTO_ATTACK | P_OH | P_CRIT);
  }
  else {
    ++stats_.oh_hit_;
    stats_.oh_hit_damage_ += oh.damage_;
    COMBATLOG("OH hit " << oh.damage_)

    procList(p_oh_auto_attack_hit, p_oh_auto_attack_hit_count, P_MELEE | P_AUTO_ATTACK | P_OH | P_HIT);
  }
}


std::string EnhSim::timestamp() {
  unsigned int hours = static_cast<unsigned int>(floor(que_.now() / 360000));
  unsigned int minutes = static_cast<unsigned int>(floor(que_.now() / 6000)) - hours * 60;
  double seconds = que_.now() / 100 - hours * 3600 - minutes * 60;

  std::stringstream ss;
  ss << hours << "h " << minutes << "m " << seconds << "s\t";

  return ss.str();
}
