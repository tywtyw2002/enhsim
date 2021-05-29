//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef ENCHANTS
#define ENCHANTS

#include "effects.h"
#include "enhsim.h"

class Enchant: public Effect {
  public:
    Enchant(EnhSim* simulator, int64& weapon_speed_base, int64& weapon_speed, f32 ppm): Effect(simulator), weapon_speed_base_(weapon_speed_base), weapon_speed_(weapon_speed), proc_chance_auto_attack_(0), proc_chance_instant_(0), ppm_(ppm), uptime_(0), buff_event_(0), proc_start_time_(0) {};

    void reCalculateProcChance() { proc_chance_auto_attack_ = static_cast<int>(ppm_ * 100 * weapon_speed_ / 60); };
    //void setPPM(const f32& ppm) { ppm_ = ppm; calculateProcChance(); };
    void calculateProcChance() { proc_chance_instant_ = static_cast<int>(ppm_ * 100 * weapon_speed_base_ / 60); reCalculateProcChance(); };

    virtual void proc(const int& proc_id);
    virtual void trigger() = 0;
    virtual void finalize();

    int64& weapon_speed_base_;
    int64& weapon_speed_;
    int proc_chance_auto_attack_;
    int proc_chance_instant_;
    f32 ppm_;
    int64 uptime_;
    Event* buff_event_;
    //for statistics
    int64 proc_start_time_;
};

class StaticProcChanceEnchant: public Enchant {
  public:
    StaticProcChanceEnchant(EnhSim* simulator, int proc_chance): Enchant(simulator, dummy_, dummy_, 0), dummy_(0), proc_chance_(proc_chance) {};

    void reCalculateProcChance() {};
    void calculateProcChance() {};

    virtual void proc(const int& proc_id);

    int64 dummy_;
    int proc_chance_;
};

class Deathfrost: public StaticProcChanceEnchant {
  public:
    Deathfrost(EnhSim* simulator): StaticProcChanceEnchant(simulator, 800/*melee proc chance*/), proc_chance_spell_(5000), cd_duration_(2500), cd_(false) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);
    virtual void trigger();

    int proc_chance_spell_;
    int64 cd_duration_;

    bool cd_;
};

class MhDeathfrost: public Deathfrost,
  public pMhMeleeDamage,
  public pSpellDamage
{
  public:
    MhDeathfrost(EnhSim* simulator): Deathfrost(simulator) {};
};

class OhDeathfrost: public Deathfrost,
  public pOhMeleeDamage,
  public pSpellDamage
{
  public:
    OhDeathfrost(EnhSim* simulator): Deathfrost(simulator) {};
};

class BuffEnchant: public Enchant {
  public:
    BuffEnchant(EnhSim* simulator, int64& weapon_speed_base, int64& weapon_speed, f32 ppm, int64 duration): Enchant(simulator, weapon_speed_base, weapon_speed, ppm), duration_(duration) {};

    virtual void trigger();
    virtual void event(const int& event_id);
    virtual void addBuff() = 0;
    virtual void removeBuff() = 0;

    int64 duration_;
};

class MhMongoose: public BuffEnchant,
  public pMhMeleeDamage
{
  public:
    MhMongoose(EnhSim* simulator):
                BuffEnchant(simulator, simulator->mh.speed_base_, simulator->mh.speed_,
                /*PPM*/ 1.0f, /*Duration*/ 1500) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class OhMongoose: public BuffEnchant,
  public pOhMeleeDamage
{
  public:
    OhMongoose(EnhSim* simulator):
                BuffEnchant(simulator, simulator->oh.speed_base_, simulator->oh.speed_,
                /*PPM*/ 1.0f, /*Duration*/ 1500) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class MhCrusader: public BuffEnchant,
  public pMhMeleeDamage
{
  public:
    MhCrusader(EnhSim* simulator):
                BuffEnchant(simulator, simulator->mh.speed_base_, simulator->mh.speed_,
                /*PPM*/ 1.0f, /*Duration*/ 1500) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class OhCrusader: public BuffEnchant,
  public pOhMeleeDamage
{
  public:
    OhCrusader(EnhSim* simulator):
                BuffEnchant(simulator, simulator->oh.speed_base_, simulator->oh.speed_,
                /*PPM*/ 1.0f, /*Duration*/ 1500) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class MhExecutioner: public BuffEnchant,
  public pMhMeleeDamage
{
  public:
    MhExecutioner(EnhSim* simulator):
                  BuffEnchant(simulator, simulator->mh.speed_base_, simulator->mh.speed_,
                  /*PPM*/ 1.0f, /*Duration*/ 1500) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class OhExecutioner: public BuffEnchant,
  public pOhMeleeDamage
{
  public:
    OhExecutioner(EnhSim* simulator): 
                  BuffEnchant(simulator, simulator->oh.speed_base_, simulator->oh.speed_,
                  /*PPM*/ 1.0f, /*Duration*/ 1500), mh_executioner_(0) {};

    virtual void addBuff();
    virtual void removeBuff();

    MhExecutioner* mh_executioner_;
};

#endif
