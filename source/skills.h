//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef SKILLS
#define SKILLS

#include "effects.h"

class GlobalCooldown: public Effect {
  public:
    GlobalCooldown(EnhSim* simulator): Effect(simulator), cd_(false) {};

    virtual void event(const int& event_id);

    bool cd_;
};

class ShockCooldown: public Effect {
  public:
    ShockCooldown(EnhSim* simulator): Effect(simulator), cooldown_(BASE_SHOCK_COOLDOWN), cd_(false) {};

    virtual void event(const int& event_id);

    int64 cooldown_;
    bool cd_;
};


class Stormstrike: public Castable {
  public:
    Stormstrike(EnhSim* simulator): Castable(simulator, 0), cooldown_(1000), cd_(false), bonus_damage_(0), charges_(0), charges_per_cast_(2), spell_damage_bonus_multiplier_(1.20f) {};

    virtual void event(const int& event_id);

    virtual bool cast();
    void ssMhSwing();
    void ssOhSwing();

    int64 cooldown_;
    bool cd_;
    int bonus_damage_;
    int charges_;
    int charges_per_cast_;
    f32 spell_damage_bonus_multiplier_;
};

class EarthShock: public Castable {
  public:
    EarthShock(EnhSim* simulator): Castable(simulator, 0), gcd_reduction_(0) {};

    virtual bool cast();

    int64 gcd_reduction_;
};

class FlameShock: public Castable {
  public:
    FlameShock(EnhSim* simulator): Castable(simulator, 0), proc_time_(-1), dots_(0), max_dots_left_(0), dots_per_cast_(4), dot_damage_multiplier_(1.0f), next_dot_time_(0), dot_event_(0) {};

    virtual void event(const int& event_id);

    virtual bool cast();

    int64 proc_time_;
    int dots_;
    int max_dots_left_;
    int dots_per_cast_;
    f32 dot_damage_multiplier_;
    int64 next_dot_time_;
    Event* dot_event_;
};

class FrostShock: public Castable {
  public:
    FrostShock(EnhSim* simulator): Castable(simulator, 0) {};

    virtual bool cast();
};

// class LavaBurst: public Castable {
//   public:
//     LavaBurst(EnhSim* simulator): Castable(simulator, 200), cd_(false), cd_time_(-10000), max_fsdots_left_(4), /*max_wait_(0),*/ max_ed_left(ELEMENTAL_DEVASTATION_DURATION), crit_damage_bonus_(0.0f), crit_multiplier_(0.0f), coefficient_bonus_(0.0f), cast_only_if_fs_active_(false), consume_fs_(true) {};

//     virtual void event(const int& event_id);
//     virtual bool cast();
//     virtual void castingFinished();

//     bool cd_;
//     int64 cd_time_;
//     int max_fsdots_left_;
//     //int64 max_wait_;
//     int64 max_ed_left;
//     f32 crit_damage_bonus_;
//     f32 crit_multiplier_;
//     f32 coefficient_bonus_;
//     bool cast_only_if_fs_active_;
//     bool consume_fs_;
// };

// class LightningBolt: public Castable {
//   public:
//     LightningBolt(EnhSim* simulator): Castable(simulator, 250), crit_bonus_(0), spellpower_bonus_(0), damage_multiplier_(1.0f) {};

//     virtual bool cast();
//     virtual void castingFinished();

//     int crit_bonus_;
//     int spellpower_bonus_;
//     f32 damage_multiplier_;
// };

// class ChainLightning: public Castable {
//   public:
//     ChainLightning(EnhSim* simulator): Castable(simulator, 150), crit_bonus_(0), spellpower_bonus_(0), damage_multiplier_(1.0f), cd_duration_(600), cd_(false) {};

//     virtual void event(const int& event_id);
//     virtual bool cast();
//     virtual void castingFinished();

//     int crit_bonus_;
//     int spellpower_bonus_;
//     f32 damage_multiplier_;
//     int64 cd_duration_;
//     bool cd_;
// };

// class LightningShield: public Castable {
//   public:
//     LightningShield(EnhSim* simulator): Castable(simulator, 0), charges_(0), charges_per_cast_(3), max_charges_to_recast_(0), damage_multiplier_(1.0f) {};

//     virtual bool cast();
//     void consumeCharge();

//     unsigned int charges_;
//     unsigned int charges_per_cast_;
//     unsigned int max_charges_to_recast_;
//     f32 damage_multiplier_;
// };

// class LavaLash: public Castable {
//   public:
//     LavaLash(EnhSim* simulator): Castable(simulator, 0), damage_multiplier_(1.00f), cd_(false), cast_only_if_wf_on_cd_(false) /*, crit_multiplier_(2.0f)*/ {};

//     virtual void event(const int& event_id);
//     virtual bool cast();

//     f32 damage_multiplier_;
//     bool cd_;
//     bool cast_only_if_wf_on_cd_;
//     //f32 crit_multiplier_;
// };

class SearingTotem: public Castable {
  public:
    SearingTotem(EnhSim* simulator): Castable(simulator, 0), cd_event_(0), ticks_(0), ticks_per_cast_(static_cast<int>(6000 / SEARING_TOTEM_INTERVAL)) {};

    virtual void event(const int& event_id);
    virtual bool cast();

    Event* cd_event_;
    int ticks_;
    int ticks_per_cast_;
};

class ShamanisticRage: public Castable,
  public pMeleeDamage
{
  public:
    ShamanisticRage(EnhSim* simulator): Castable(simulator, 0), buff_event_(0), cd_event_(0), max_mana_to_cast_(0.0f),
      ppm_(15.0f), proc_chance_mh_auto_attack_(0), proc_chance_mh_instant_(0), proc_chance_oh_auto_attack_(0), proc_chance_oh_instant_(0), active_(false), cd_(false) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);
    virtual bool cast();

    virtual void reCalculateProcChance();
    virtual void calculateProcChance();
    void trig();

    Event* buff_event_;
    Event* cd_event_;
    f32 ppm_;
    f32 max_mana_to_cast_;

    int proc_chance_mh_auto_attack_;
    int proc_chance_mh_instant_;
    int proc_chance_oh_auto_attack_;
    int proc_chance_oh_instant_;

    bool active_;
    bool cd_;
};

#endif
