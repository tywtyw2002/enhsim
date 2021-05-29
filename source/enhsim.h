//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef ENHSIM
#define ENHSIM

#include "globalutil.h"
#include "event_queue.h"
#include "rotation.h"
#include "skills.h"
#include "talents.h"
#include "weapon_enchants.h"
#include "consumables.h"
#include "trinkets.h"
#include "totems.h"
#include "setbonuses.h"
#include "metagems.h"
#include "hand.h"
#include "stats.h"
#include <string>
#include <fstream>

class Effect;
class Enchant;

class EnhSim {

  public:
#ifdef DEBUG
    EnhSim(Statistics& stats, std::fstream& combatlog);
#else
    EnhSim(Statistics& stats);
#endif
    ~EnhSim();

    //these setters are used for initializing the variables
    void setMhSpeed(const int64& mh_speed) { mh.speed_base_ = mh_speed; };
    void setOhSpeed(const int64& oh_speed) { oh.speed_base_ = oh_speed; };

    void setMhDps(const f32& mh_dps) { mh.dps_ = mh_dps; };
    void setOhDps(const f32& oh_dps) { oh.dps_ = oh_dps; };

    void setHaste(const f32& haste) { haste_multipliers_[0] = haste; };

    void setPhysicalDamageMultiplier(const f32& physical_damage_multiplier) { physical_damage_multiplier_ = physical_damage_multiplier; };
    void setPhysicalCritMultiplier(const f32& crit_multiplier) { physical_crit_multiplier_ = crit_multiplier; };

    void setMhCrit(const int& mh_crit) { mh.crit_base_ = mh_crit - 60; };
    void setOhCrit(const int& oh_crit) { oh.crit_base_ = oh_crit - 60; };

    void setMhHit(const int& mh_hit) { mh.hit_ = mh_hit; };
    void setOhHit(const int& oh_hit) { oh.hit_ = oh_hit; };

    // void setArmorPenetration(const f32& armorp) { armor_penetration_ = armorp; };
    void setArmorIgnore(const int& ignore) { armor_ignore_ -= ignore; };

    void setAttackPower(const int& ap) { ap_base_ = ap_ = ap; };
    void setStrength(const int& str) { str_base_ = str; };
    void setAgility(const int& agi) { agi_base_ = agi; };
    void setIntelligence(const int& intt) { int_base_ = intt; };
    void setSpirit(const int& spi) { spi_base_ = spi; };

    void setMaxMana(const f32& mana) { max_mana_base_ = mana; };
    void setMp5(const int& mp5) { mp5_regen_per_tick_ = static_cast<f32>(mp5 * MANA_REGEN_INTERVAL / 500.0f); };

    void setAttackPowerMultiplier(const f32& multiplier) { ap_multiplier_ = multiplier; };
    void setStrenghtMultiplier(const f32& multiplier) { strength_multiplier_ = multiplier; };
    void setAgilityMultiplier(const f32& multiplier) { agility_multiplier_ = multiplier; };
    void setIntelligenceMultiplier(const f32& multiplier) { intelligence_multiplier_ = multiplier; };
    void setSpiritMultiplier(const f32& multiplier) { spirit_multiplier_ = multiplier; };

    void setMhExpertiseRating(const f32& mh_expertise_rating) { mh.expertise_rating_ = mh_expertise_rating; };
    void setOhExpertiseRating(const f32& oh_expertise_rating) { oh.expertise_rating_ = oh_expertise_rating; };

    void setMiss(const int& miss) { mh.miss_base_ = oh.miss_base_ = miss; };
    void setDodge(const int& dodge) { mh.dodge_base_ = oh.dodge_base_ = dodge; };
    void setGlancing(const int& glancing) { mh.glancing_ = oh.glancing_ = glancing; };
    void setArmor(const int& armor) { armor_base_ = armor; };
    void setSpellMiss(const int& spell_miss) { spell_miss_base_ = spell_miss; };
    void setNatureResistance(const int& nature_res) { nature_resistance_ = nature_res; };
    void setFireResistance(const int& fire_res) { fire_resistance_ = fire_res; };
    void setFrostResistance(const int& frost_res) { frost_resistance_ = frost_res; };

    void setApToSpellpowerMultiplier(const f32 ap_to_spellpower) { ap_to_spellpower_multiplier_ = ap_to_spellpower; };
    void setIntToApMultiplier(const f32 int_to_ap) { int_to_ap_multiplier_ = int_to_ap; };

    void setSpellpower(const int& spellpower) { spellpower_base_ = spellpower; };
    void setNatureCrit(const int& nature_crit) { nature_crit_base_ = nature_crit; };
    void setFireCrit(const int& fire_crit) { fire_crit_base_ = fire_crit; };
    void setFrostCrit(const int& frost_crit) { frost_crit_base_ = frost_crit; };
    void setSpellHit(const int& spell_hit) { spell_hit_ = spell_hit; };
    void setSpellHitTotem(const int& spell_hit_totem) { spell_hit_totem_ = spell_hit_totem; };

    void setNatureDamageMultiplier(const f32& nature_damage_multiplier) { nature_damage_multiplier_ = nature_damage_multiplier; };
    void setFireDamageMultiplier(const f32& fire_damage_multiplier) { fire_damage_multiplier_ = fire_damage_multiplier; };
    void setFrostDamageMultiplier(const f32& frost_damage_multiplier) { frost_damage_multiplier_ = frost_damage_multiplier; };
    void setSpellCritMultiplier(const f32& spell_crit_multiplier) { spell_crit_multiplier_base_ = spell_crit_multiplier; };
    void setSpellCritBonus(const f32& spell_crit_bonus) { spell_crit_bonus_ = spell_crit_bonus; };
    void setFiretotemDamageMultiplier(const f32& fire_totem_multiplier) { firetotem_damage_multiplier_ = fire_totem_multiplier; };
    // void setLavaBurstDamageMultiplier(const f32& lava_burst_multiplier) { lava_burst_damage_multiplier_ = lava_burst_multiplier; };
    //void useSearingTotem() { use_searing_totem_ = true; };
    void setShockDamageMultiplier(const f32& shock_multiplier) { shock_damage_multiplier_ = shock_multiplier; };
    void setConvectionMana(const f32& mana) { convection_mana_ = mana; };
    void setMentalQuicknessMana(const f32& mana) { mental_quickness_mana_ = mana; };
    void setShamanisticFocusMana(const f32& mana) { shamanistic_focus_mana_ = mana; };

    void setWaitSSWithWFCD(const int& max_wait) { wait_ss_wf_ = max_wait; };

    void setRotationCount(const int& count) { rotation_ = new Castable*[count]; rotation_count_ = count; };

    void setLag(const int& min, const int& max) { min_lag_ = min; max_lag_ = max; };

    void setAutoAttack(bool mh_attack, bool oh_attack) { mh.attack_ = mh_attack; oh.attack_ = oh_attack; };


    //this function does the magic
    void simulate(const f32& hours);

    //registers and effect to be procced in certain events like white dmg crit
    void useEffect(Effect* effect);


    //quick n dirty skill rotation
    Rotation* skill_rotation_;

    int rotation_count_;
    Castable** rotation_;

    //event class to print progress report on the screen
    //inherited from base class Effect, to attach itself to the timeline(event queue)
    SimulationProgress* progress_;

    //every skill/spell/talent is its own class(inherited from Effect)
    GlobalCooldown* global_cooldown_;
    //WeaponEnchant* mh_weapon_enchant_;
    //WeaponEnchant* oh_weapon_enchant_;
    MhEvent* mh_event_;
    OhEvent* oh_event_;
    //MhReschedule* mh_reschedule_;
    //OhReschedule* oh_reschedule_;
    Enchant* mh_enchant_;
    Enchant* oh_enchant_;
    TrinketCooldown* trinket_cooldown_;
    Item* trinket1_;
    Item* trinket2_;
    Item* totem_;
    Item* set_bonus_;
    Item* metagem_;
    MhWindfury* mh_windfury_;
    OhWindfury* oh_windfury_;
    UnleashedRage* unleashed_rage_;
    Flurry* flurry_;
    FlurryConsume* flurry_consume_;
    Stormstrike* stormstrike_;
    SearingTotem* searing_totem_;
    ShockCooldown* shock_cooldown_;
    EarthShock* earth_shock_;
    FlameShock* flame_shock_;
    FrostShock* frost_shock_;
    ElementalDevastation* elemental_devastation_;
    MhFlametongue* mh_flametongue_;
    OhFlametongue* oh_flametongue_;
    //PotionCooldown* potion_cooldown_;
    Potion* potion_;
    MiscCooldown* misc_cooldown_;
    MiscItem* misc_item_;
    // MaelstromWeapon* maelstrom_weapon_;
    // LavaBurst* lava_burst_;
    // LightningBolt* lightning_bolt_;
    // ChainLightning* chain_lightning_;
    // LightningShield* lightning_shield_;
    // StaticShock* static_shock_;
    //ShamanisticFocus* shamanistic_focus_;
    ElementalFocus* elemental_focus_;
    CombatLength* combat_length_;
    Bloodlust* bloodlust_;
    // LavaLash* lava_lash_;
    SpellCasting* spell_casting_;
    InputLag* input_lag_;
    // ElementalOath* elemental_oath_;
    // LightningOverload* lightning_overload_;
    ManaRegen* mana_regen_;
    FiveSecRule* fsr_;
    // UnrelentingStorm* unrelenting_storm_;
    ShamanisticRage* shamanistic_rage_;
    JudgementOfWisdom* judgement_of_wisdom_;

  //private:
    void initializeSimulation();

    void calculateArmor();
    void calculateDamage();
    void calculateDamageReduction();
    void calculateMeleeHaste();
    void calculateSpellHaste();
    void calculateMiss();
    void calculateDodge();
    void calculateExpertise();
    void calculateSpellMiss();
    void calculateSpellpower();
    void calculateAttackPower();
    void calculateCrit();
    void calculateStrength();
    void calculateAgility();
    void calculateIntelligence();
    void calculateSpirit();
    void calculateSpellCrit();
    void calculateMana();
    void calculateManaRegen();
    void calculateSpellCritMultiplier();


    void changeHaste(const f32& haste);
    void changeMeleeHaste(const f32& haste);
    void changeSpellHaste(const f32& haste);
    void changeHasteMultiplier(const f32& haste_multiplier, const unsigned int& index);
    void changeMeleeHasteMultiplier(const f32& haste_multiplier, const unsigned int& index);
    void changeSpellHasteMultiplier(const f32& haste_multiplier, const unsigned int& index);

    void changeAttackPower(const int& ap);
    void changeAttackPowerMultiplier(const f32& ap_multiplier);
    void changeHit(const int& hit);
    void changeExpertiseRating(const int& expertise_rating);
    void changeCrit(const int& crit);
    void changeStrength(const int& str);
    void changeAgility(const int& agi);
    void changeIntelligence(const int& intt);
    void changeSpirit(const int& spi);

    void changeArmor(const int& armor);
    // void changeArmorPenetration(const f32& armorp);
    void changeArmorIgnore(const int& armor_ignore);

    void changeSpellpower(const int& sp);
    void changeSpellHit(const int& spell_hit);
    void changeSpellCrit(const int& spell_crit);


    
    //different types of Events have own function, its for performance
    void addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0, const int64& lag = 0);
    void addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0, const int64& lag = 0);
    void addHighPrioEvent(Event*& e, const int64& timestamp, Effect* effect, const int& event_id = 0, const int64& lag = 0);
    void addLowPrioEvent(Event*& e, const int64& timestamp, Effect* effect, const int& event_id = 0, const int64& lag = 0);
    void addMhEvent(Event*& e, const int64& mh_speed);
    void addOhEvent(Event*& e, const int64& oh_speed);

    int64 now() { return que_.now(); };

    void mhSwing();
    void ohSwing();

    void hasteMidSwing();

    f32 regenMana(const f32& mana);
    bool requestMana(const f32& percentage, const f32& multiplier);
    f32 useMana(const f32& percentage, const f32& multiplier);
    f32 requestElementalFocus();
    f32 consumeElementalFocus();

    void consumeStormstrikeCharge();

    int64 randomLag();
    int min_lag_;
    int max_lag_;


    std::string timestamp();

    //int use_searing_totem_;
    //f32 average_shocks_per_minute_;
    //bool use_shock_approximation_;
    //std::string rotation_;

    //hand specific variables
    Hand mh;
    Hand oh;

    int armor_base_;
    int armor_;
    // f32 armor_penetration_;
    int armor_ignore_;
    //damage reduction is damage multiplier: 1.0f - real damage reduction
    f32 damage_reduction_;
    int spell_miss_base_;
    int spell_miss_;
    int spell_miss_totem_;
    int nature_resistance_;
    int fire_resistance_;
    int frost_resistance_;
    f32 nature_damage_reduction_;
    f32 fire_damage_reduction_;
    f32 frost_damage_reduction_;


    f32 old_melee_haste_divider_;
    f32 melee_haste_divider_;
    f32 spell_haste_divider_;
    //holds all the haste multipliers
    f32 haste_multipliers_[HASTE_COUNT];

    //base attack power without modifiers
    int ap_base_;
    int ap_;

    int str_base_;
    int str_;
    int agi_base_;
    int agi_;
    int int_base_;
    int int_;
    int spi_base_;
    int spi_;
    //ap multiplier is used in for example, unleashed rage
    f32 ap_multiplier_;

    f32 strength_multiplier_;
    f32 agility_multiplier_;
    f32 intelligence_multiplier_;
    f32 spirit_multiplier_;

    f32 physical_damage_multiplier_;
    f32 physical_crit_multiplier_;

    //mental quickness multiplier
    f32 ap_to_spellpower_multiplier_;
    f32 int_to_ap_multiplier_;
    int spellpower_base_;
    int spellpower_;
    int nature_crit_base_;
    int nature_crit_;
    int fire_crit_base_;
    int fire_crit_;
    int frost_crit_base_;
    int frost_crit_;
    int spell_hit_;
    int spell_hit_totem_;
    f32 nature_damage_multiplier_;
    f32 fire_damage_multiplier_;
    f32 frost_damage_multiplier_;
    f32 spell_crit_multiplier_base_;
    f32 spell_crit_multiplier_;
    f32 spell_crit_bonus_;
    f32 firetotem_damage_multiplier_;
    // f32 lava_burst_damage_multiplier_;
    f32 shock_damage_multiplier_;
    //this is not for ss damage, but the damage bonus ss gives
    f32 stormstrike_damage_multiplier_;

    f32 base_mana_;
    f32 max_mana_;
    f32 max_mana_base_;
    f32 mana_;
    f32 mana_regen_per_tick_;
    f32 mp5_regen_per_tick_;

    f32 mental_quickness_mana_;
    f32 shamanistic_focus_mana_;
    f32 convection_mana_;

    int64 spell_gcd_duration_;


    LinkedEventQueue que_;

    int64 duration_;


    //wf cooldown has to be placed here, because there are one wf class
    //for each hand and they share the cooldown
    bool wf_cd_;
    int64 wait_ss_wf_;
    int64 last_wf_;

    //statistical data
    Statistics& stats_;

    bool mh_swang_;
    bool oh_swang_;

    bool simulate_mana_;
    bool oom_;
    int64 oom_start_time_;

    


    Effect* p_mh_auto_attack_miss[PROC_COUNT];
    Effect* p_mh_auto_attack_dodge[PROC_COUNT];
    Effect* p_mh_auto_attack_glancing[PROC_COUNT];
    Effect* p_mh_auto_attack_hit[PROC_COUNT];
    Effect* p_mh_auto_attack_crit[PROC_COUNT];

    Effect* p_oh_auto_attack_miss[PROC_COUNT];
    Effect* p_oh_auto_attack_dodge[PROC_COUNT];
    Effect* p_oh_auto_attack_glancing[PROC_COUNT];
    Effect* p_oh_auto_attack_hit[PROC_COUNT];
    Effect* p_oh_auto_attack_crit[PROC_COUNT];

    Effect* p_mh_windfury_miss[PROC_COUNT];
    Effect* p_mh_windfury_dodge[PROC_COUNT];
    Effect* p_mh_windfury_hit[PROC_COUNT];
    Effect* p_mh_windfury_crit[PROC_COUNT];

    Effect* p_oh_windfury_miss[PROC_COUNT];
    Effect* p_oh_windfury_dodge[PROC_COUNT];
    Effect* p_oh_windfury_hit[PROC_COUNT];
    Effect* p_oh_windfury_crit[PROC_COUNT];

    Effect* p_mh_flametongue_miss[PROC_COUNT];
    Effect* p_mh_flametongue_hit[PROC_COUNT];
    Effect* p_mh_flametongue_crit[PROC_COUNT];

    Effect* p_oh_flametongue_miss[PROC_COUNT];
    Effect* p_oh_flametongue_hit[PROC_COUNT];
    Effect* p_oh_flametongue_crit[PROC_COUNT];

    Effect* p_mh_stormstrike_miss[PROC_COUNT];
    Effect* p_mh_stormstrike_dodge[PROC_COUNT];
    Effect* p_mh_stormstrike_hit[PROC_COUNT];
    Effect* p_mh_stormstrike_crit[PROC_COUNT];

    Effect* p_oh_stormstrike_miss[PROC_COUNT];
    Effect* p_oh_stormstrike_dodge[PROC_COUNT];
    Effect* p_oh_stormstrike_hit[PROC_COUNT];
    Effect* p_oh_stormstrike_crit[PROC_COUNT];

    // Effect* p_lava_lash_miss[PROC_COUNT];
    // Effect* p_lava_lash_dodge[PROC_COUNT];
    // Effect* p_lava_lash_hit[PROC_COUNT];
    // Effect* p_lava_lash_crit[PROC_COUNT];

    Effect* p_earth_shock_miss[PROC_COUNT];
    Effect* p_earth_shock_hit[PROC_COUNT];
    Effect* p_earth_shock_crit[PROC_COUNT];

    Effect* p_flame_shock_miss[PROC_COUNT];
    Effect* p_flame_shock_hit[PROC_COUNT];
    Effect* p_flame_shock_crit[PROC_COUNT];

    Effect* p_frost_shock_miss[PROC_COUNT];
    Effect* p_frost_shock_hit[PROC_COUNT];
    Effect* p_frost_shock_crit[PROC_COUNT];

    // Effect* p_lightning_bolt_miss[PROC_COUNT];
    // Effect* p_lightning_bolt_hit[PROC_COUNT];
    // Effect* p_lightning_bolt_crit[PROC_COUNT];

    // Effect* p_chain_lightning_miss[PROC_COUNT];
    // Effect* p_chain_lightning_hit[PROC_COUNT];
    // Effect* p_chain_lightning_crit[PROC_COUNT];

    // Effect* p_lava_burst_miss[PROC_COUNT];
    // Effect* p_lava_burst_hit[PROC_COUNT];
    // Effect* p_lava_burst_crit[PROC_COUNT];

    // Effect* p_lightning_shield_miss[PROC_COUNT];
    // Effect* p_lightning_shield_hit[PROC_COUNT];
    // Effect* p_lightning_shield_cast[PROC_COUNT];

    // Effect* p_lightning_overload_miss[PROC_COUNT];
    // Effect* p_lightning_overload_hit[PROC_COUNT];
    // Effect* p_lightning_overload_crit[PROC_COUNT];






    unsigned int p_mh_auto_attack_miss_count;
    unsigned int p_mh_auto_attack_dodge_count;
    unsigned int p_mh_auto_attack_glancing_count;
    unsigned int p_mh_auto_attack_hit_count;
    unsigned int p_mh_auto_attack_crit_count;

    unsigned int p_oh_auto_attack_miss_count;
    unsigned int p_oh_auto_attack_dodge_count;
    unsigned int p_oh_auto_attack_glancing_count;
    unsigned int p_oh_auto_attack_hit_count;
    unsigned int p_oh_auto_attack_crit_count;

    unsigned int p_mh_windfury_miss_count;
    unsigned int p_mh_windfury_dodge_count;
    unsigned int p_mh_windfury_hit_count;
    unsigned int p_mh_windfury_crit_count;

    unsigned int p_oh_windfury_miss_count;
    unsigned int p_oh_windfury_dodge_count;
    unsigned int p_oh_windfury_hit_count;
    unsigned int p_oh_windfury_crit_count;

    unsigned int p_mh_flametongue_miss_count;
    unsigned int p_mh_flametongue_hit_count;
    unsigned int p_mh_flametongue_crit_count;

    unsigned int p_oh_flametongue_miss_count;
    unsigned int p_oh_flametongue_hit_count;
    unsigned int p_oh_flametongue_crit_count;

    unsigned int p_mh_stormstrike_miss_count;
    unsigned int p_mh_stormstrike_dodge_count;
    unsigned int p_mh_stormstrike_hit_count;
    unsigned int p_mh_stormstrike_crit_count;

    unsigned int p_oh_stormstrike_miss_count;
    unsigned int p_oh_stormstrike_dodge_count;
    unsigned int p_oh_stormstrike_hit_count;
    unsigned int p_oh_stormstrike_crit_count;

    // unsigned int p_lava_lash_miss_count;
    // unsigned int p_lava_lash_dodge_count;
    // unsigned int p_lava_lash_hit_count;
    // unsigned int p_lava_lash_crit_count;

    unsigned int p_earth_shock_miss_count;
    unsigned int p_earth_shock_hit_count;
    unsigned int p_earth_shock_crit_count;

    unsigned int p_flame_shock_miss_count;
    unsigned int p_flame_shock_hit_count;
    unsigned int p_flame_shock_crit_count;

    unsigned int p_frost_shock_miss_count;
    unsigned int p_frost_shock_hit_count;
    unsigned int p_frost_shock_crit_count;

    // unsigned int p_lightning_bolt_miss_count;
    // unsigned int p_lightning_bolt_hit_count;
    // unsigned int p_lightning_bolt_crit_count;

    // unsigned int p_chain_lightning_miss_count;
    // unsigned int p_chain_lightning_hit_count;
    // unsigned int p_chain_lightning_crit_count;

    // unsigned int p_lava_burst_miss_count;
    // unsigned int p_lava_burst_hit_count;
    // unsigned int p_lava_burst_crit_count;

    // unsigned int p_lightning_shield_miss_count;
    // unsigned int p_lightning_shield_hit_count;
    // unsigned int p_lightning_shield_cast_count;

    // unsigned int p_lightning_overload_miss_count;
    // unsigned int p_lightning_overload_hit_count;
    // unsigned int p_lightning_overload_crit_count;



#ifdef DEBUG
    std::fstream& combatlog_;
#endif
};

#endif //ENHSIM
