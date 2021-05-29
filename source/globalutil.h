//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef GLOBALUTIL
#define GLOBALUTIL


//I changed from __int64 to double
//it increased speed and it is easier to compile on different platforms
typedef double int64;
typedef float f32;

#include "SFMT/SFMT.h"
#include <iostream>
#include <string>
#include <sstream>

class Effect;
class EnhSim;

//defines, does swings stay synced, if the weapons speeds are same
//example: mh hits first, then oh crits and procs flurry
//if flurry is synced, both mh and oh get the flurry haste bonus
#define FLURRY_SYNCED

//defines, does swings consume flurry, which procced the same tick
//example: mh hits first and crits, thus procs flurry
//then oh hits the same tick and if FLURRY_NOCONSUME_SAMETICK is defined, the
//oh hit does not consume flurry charge
#define FLURRY_NOCONSUME_SAMETICK

//#define DEBUG

//combat log is printed in debug build
#ifdef DEBUG
  #define COMBATLOG(message) combatlog_ << timestamp() << message << std::endl;
  #define COMBATLOG_EFFECT(message) sim.combatlog_ << sim.timestamp() << message << std::endl;
#else
  #define COMBATLOG(message)
  #define COMBATLOG_EFFECT(message)
#endif

#ifdef DEBUG
//void COMBATLOG(std::string message);
void setupCombatLog(std::string filename);
void closeCombatLog();
std::fstream& getCombatLog();
#endif


//game mechanics constants
const int64 GCD = 150;
const int64 BASE_SHOCK_COOLDOWN = 600;
const int64 WF_COOLDOWN = 300;
const int64 POTION_COOLDOWN = 12000;
const int64 MISC_ITEM_COOLDOWN = 12000;
//const int64 TRINKET_COOLDOWN = 1500;
const int64 MANA_REGEN_INTERVAL = 100;

const int64 UR_DURATION = 1000;
const int64 ELEMENTAL_DEVASTATION_DURATION = 1000;
// const int64 MAELSTROM_WEAPON_DURATION = 3000;
// const int64 MAELSTROM_WEAPON_DURATION = 1500;

const f32 PHYSICAL_CRITICAL_MULTIPLIER = 2.00f;
const f32 SPELL_CRITICAL_MULTIPLIER = 1.50f;

const int FLURRY_CHARGES = 3;

const f32 GLANCING_REDUCTION = 0.7f;

const int DUAL_WIELD_MISS = 1900;

const int MINIMUM_SPELL_MISS = 0;

const f32 INTELLIGENCE_TO_MANA = 15.0f;

// #ifndef LVL80

const int ATTACKER_LEVEL = 70;
const int TARGET_LEVEL = 73;

const f32 BASE_MANA = 2678;
const f32 BASE_MANA_REGEN = 0.009327f;

//RATINGS

const f32 EXPERTISE_RATING_TO_EXPERTISE = 3.94230819f;
const int EXPERTISE_DODGE_BONUS = 25;

//80 int is 1% spell crit
const f32 INTELLIGENCE_TO_SPELLCRIT = 1.25f;

//1 str is 1 ap
const int STRENGTH_TO_AP = 2;

//1 agi is 0.04% crit
const f32 AGILITY_TO_CRIT = 4.0f;
const int AGILITY_TO_AP = 0;

const f32 CRIT_RATING_TO_CRIT = 4.5296167f;
// const f32 CRIT_RATING_TO_SPELLCRIT = 4.5296167f;
const f32 HIT_RATING_TO_HIT = 6.34146262f;
// const f32 HIT_RATING_TO_SPELLHIT = 7.926829f;
const f32 HASTE_RATING_TO_HASTE = 0.000634146f;
// const f32 ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION = 0.001350649f;

const f32 SPELLCRIT_RATING_TO_SPELLCRIT = 4.529f;
const f32 SPELLHIT_RATING_TO_SPELLHIT = 7.924f;


const f32 ROCKBITER_DPS = 62.0f;

const f32 STORMSTRIKE_MANA = 0.08f;

const int WINDFURY_DUALWIELD_PROC_CHANCE = 3600;
const int WINDFURY_PROC_CHANCE = 2000;
const int WINDFURY_BONUS_AP = 445;

const int FLAMETONGUE_BONUS_SPELLPOWER = 96;

const int WINDFURY_TOTEM_PROC_CHANCE = 2000;
const int WINDFURY_TOTEM_BONUS_AP = 445;

const f32 FLAMETONGUE_COEFFICIENT = 0.1f;
const f32 FLAMETONGUE_DAMAGE = 35.0f;

const f32 SEARING_TOTEM_COEFFICIENT = 0.08f;
const int64 SEARING_TOTEM_INTERVAL = 255;
const f32 SEARING_TOTEM_DAMAGE = 58.0f;
const f32 SEARING_TOTEM_MANA = 0.07f;

const f32 EARTH_SHOCK_COEFFICIENT = 0.386f;
const f32 EARTH_SHOCK_DAMAGE = 675.0f;
const f32 EARTH_SHOCK_MANA = 0.18f;

const f32 FLAME_SHOCK_COEFFICIENT = 0.21f;
const f32 FLAME_SHOCK_DAMAGE = 377.0f;
const f32 FLAME_SHOCK_DOT_COEFFICIENT = 0.0975f;
const f32 FLAME_SHOCK_DOT_DAMAGE = 105.0f;
const int64 FLAME_SHOCK_DOT_INTERVAL = 300;
const f32 FLAME_SHOCK_MANA = 0.17f;

const f32 FROST_SHOCK_COEFFICIENT = 0.386f;
const f32 FROST_SHOCK_DAMAGE = 658.0f;
const f32 FROST_SHOCK_MANA = 0.18f;

// const f32 LAVA_BURST_COEFFICIENT = 0.5714f;
// const f32 LAVA_BURST_DAMAGE = 1151.0f;
// const f32 LAVA_BURST_MANA = 0.10f;

// const f32 LAVA_LASH_MANA = 0.04f;

// const f32 LIGHTNING_BOLT_COEFFICIENT = 0.794f;
// const f32 LIGHTNING_BOLT_DAMAGE = 603.0f;
// const f32 LIGHTNING_BOLT_MANA = 0.10f;

// const f32 CHAIN_LIGHTNING_COEFFICIENT = 0.5714f;
// const f32 CHAIN_LIGHTNING_DAMAGE = 786.0f;
// const f32 CHAIN_LIGHTNING_MANA = 0.26f;

// const f32 LIGHTNING_SHIELD_COEFFICIENT = 0.267f;
// const f32 LIGHTNING_SHIELD_DAMAGE = 287.0f;
// const f32 LIGHTNING_SHIELD_MANA = 0.00f;

const int WATER_SHIELD_MP5 = 50;
const int MANA_SPRING_MP5 = 50;
const int BLESSING_OF_WISDOM_MP5 = 41;

// #else
// #include "level80.h"
// #endif

//talent constants, these are per rank
const f32 WINDFURY_ELEMENTAL_WEAPONS = 0.133333f;
const f32 ROCKBITER_ELEMENTAL_WEAPONS = 0.0666666f;
const f32 FLAMETONGUE_ELEMENTAL_WEAPONS = 0.05f;
const f32 UNLEASHED_RAGE = 0.02f;
const f32 WEAPON_MASTERY = 0.02f;
// const f32 WEAPON_MASTERY_RANK1 = 0.04f;
// const f32 WEAPON_MASTERY_RANK2 = 0.07f;
// const f32 WEAPON_MASTERY_RANK3 = 0.10f;
const int DUAL_WIELD_SPECIALIZATION = 200;
const int NATURES_GUIDANCE = 100;
const f32 FLURRY_HASTE = 0.05f;
const f32 CALL_OF_FLAME = 0.05f;
// const f32 CALL_OF_FLAME_LAVA_BURST = 0.02f;
// const int CALL_OF_THUNDER = 100;
const f32 ELEMENTAL_FURY = 1.0f;
const f32 MENTAL_QUICKNESS = 0.1f;
const f32 MENTAL_QUICKNESS_MANA = 0.02f;
// const f32 MENTAL_DEXTERITY = 0.3333f;
const f32 CONCUSSION = 0.01f;
const f32 CONVECTION_MANA = 0.02f;
const int REVERBERATION = 20;
const f32 IMPROVED_WEAPON_TOTEMS = 0.15f;
const int ELEMENTAL_PRECISION = 100;
const int ELEMENTAL_DEVASTATION = 300;
// const f32 IMPROVED_SHIELDS = 0.05f;
// const int STATIC_SHOCK = 200;
// const f32 ANCESTRAL_KNOWLEDGE = 0.02f;
const f32 SHAMANISTIC_FOCUS_MANA = 0.45f;
// const int IMPROVED_STORMSTRIKE = 100;
// const f32 MAELSTROM_WEAPON = 2.00f;
// const int64 LIGHTNING_MASTERY = 10;
// const int ELEMENTAL_OATH_RANK1 = 300;
// const int ELEMENTAL_OATH_RANK2 = 500;
// const f32 STORM_EARTH_AND_FIRE_FS = 0.10f;
// const int64 STORM_EARTH_AND_FIRE_CL = 50;
// const f32 LAVA_FLOWS_RANK1 = 0.06f;
// const f32 LAVA_FLOWS_RANK2 = 0.12f;
// const f32 LAVA_FLOWS_RANK3 = 0.24f;
// const int LIGHTNING_OVERLOAD = 400;
// const f32 UNRELENTING_STORM = 0.02f;




//sets the size of event arrays
//const unsigned int EVENT_COUNT = 10;
//sets the size of proc arrays
const unsigned int PROC_COUNT = 15;
//set the size of haste multipliers array
const unsigned int HASTE_COUNT = 9;

//index in the haste_multipliers_ array
const unsigned int HASTE_MELEE_RATING = 0;
const unsigned int HASTE_SPELL_RATING = 1;
const unsigned int HASTE_FLURRY = 2;
const unsigned int HASTE_BLOODLUST = 3;
const unsigned int HASTE_MH_MONGOOSE = 4;
const unsigned int HASTE_OH_MONGOOSE = 5;
const unsigned int HASTE_BERSERKING = 6;
const unsigned int HASTE_MELEE_RAID_BUFF = 7;
const unsigned int HASTE_SPELL_RAID_BUFF = 8;

void init_random();
//void init_random();
//random function used everywhere
inline int random(const int& max) {return gen_rand32() % max;};

inline int roll() {return gen_rand32() % 10000;};

//this executes the proc() functions from proc_array's Effects
//just to make the code cleaner
//#define procList(array, count, proc_id) if (count > 0) pList(array, count, proc_id);
void procList(Effect* (&proc_array)[PROC_COUNT], const unsigned int& count, const int& proc_id);


std::string toLower(const std::string& str);

std::string intToString(const int& i);
int stringToInt(const std::string& str);
f32 stringToFloat(const std::string& str);



const int P_MISS =              0x00000001;
const int P_DODGE =             0x00000002;
const int P_GLANCING =          0x00000004;
const int P_HIT =               0x00000008;
const int P_CRIT =              0x00000010;
const int P_MH =                0x00000020;
const int P_OH =                0x00000040;
const int P_AUTO_ATTACK =       0x00000080;
const int P_INSTANT =           0x00000100;
const int P_WINDFURY =          0x00000200;
const int P_STORMSTRIKE =       0x00000400;
const int P_FLAMETONGUE =       0x00000800;
const int P_LAVA_LASH =         0x00001000;
const int P_SPELL =             0x00002000;
const int P_SHOCK =             0x00004000;
const int P_EARTH_SHOCK =       0x00008000;
const int P_FLAME_SHOCK =       0x00010000;
const int P_FROST_SHOCK =       0x00020000;
const int P_LIGHTNING_BOLT =    0x00040000;
const int P_CHAIN_LIGHTNING =   0x00080000;
const int P_LAVA_BURST =        0x00100000;
const int P_LIGHTNING_SHIELD =  0x00200000;
const int P_MELEE =             0x00400000;


const int EVENT_ID_COOLDOWN = 1;
const int EVENT_ID_BUFF_FADE = 2;
const int EVENT_ID_BUFF2_FADE = 3;
const int EVENT_ID_BUFF3_FADE = 4;

const int PRIORITY_HIGH = 1;
const int PRIORITY_MH = 2;
const int PRIORITY_OH = 3;
const int PRIORITY_LOW = 4;
//const int PRIORITY_MH_RESCHEDULE = 5;
//const int PRIORITY_OH_RESCHEDULE = 6;
const int PRIORITY_LOWEST = 7;


#endif
