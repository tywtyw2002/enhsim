//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef TALENTS
#define TALENTS

#include "effects.h"

class UnleashedRage: public Effect,
  public pMeleeCrit
{
  public:
    UnleashedRage(EnhSim* simulator): Effect(simulator), ap_multiplier_(0), proc_stack_(0), buff_event_(0), proc_time_(-1), proc_start_time_(0) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);
    virtual void finalize();

    f32 ap_multiplier_;
    //how many multiple procs do we have?
    //they all create events and it would be slow to delete the old ur event from event queue
    //so I record the number of procs and take ur off when it is 0
    unsigned int proc_stack_;
    Event* buff_event_;

    //this is for making sure that there are no multiple procs in the same tick
    //it doesnt make any difference, it is just bit faster to make this check
    int64 proc_time_;

    //for statistics
    int64 proc_start_time_;
};



class Flurry: public Effect,
  public pMeleeCrit
{
  public:
    Flurry(EnhSim* simulator): Effect(simulator), flurry_charges_(0), haste_(0.0f), proc_start_time_(0)
                               #ifdef FLURRY_NOCONSUME_SAMETICK
                               ,proc_time_(-1)
                               #endif
                               {};

    virtual void proc(const int& proc_id);
    virtual void finalize();

    int flurry_charges_;
    f32 haste_;

    //this is for statistics
    int64 proc_start_time_;

    #ifdef FLURRY_NOCONSUME_SAMETICK
    int64 proc_time_;
    #endif
};

class FlurryConsume: public Effect,
  public pSwing
{
  public:
    FlurryConsume(EnhSim* simulator): Effect(simulator) {};

    virtual void proc(const int& proc_id);
};


class ElementalDevastation: public Effect,
  public pSpellCrit
{
  public:
    ElementalDevastation(EnhSim* simulator): Effect(simulator), proc_stack_(0), buff_event_(0), crit_(0), proc_start_time_(0), cd_time_(-10000) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);
    virtual void finalize();

    unsigned int proc_stack_;
    Event* buff_event_;
    int crit_;

    //this is for statistics
    int64 proc_start_time_;

    int64 cd_time_;
};

// class MaelstromWeapon: public Effect,
//   public pMeleeDamage
// {
//   public:
//     MaelstromWeapon(EnhSim* simulator): Effect(simulator), stack_(0), min_stack_to_action_(100), /*proc_chance_(0),*/ cd_event_(0), 
//       ppm_(0.0f), proc_chance_mh_auto_attack_(0), proc_chance_mh_instant_(0), proc_chance_oh_auto_attack_(0), proc_chance_oh_instant_(0), /*proc_start_time_(0), total_time_(0), total_sd_time_(0), stack_full_count_(0),*/ wait_(false) {};

//     virtual void proc(const int& proc_id);
//     virtual void event(const int& event_id);

//     virtual void reCalculateProcChance();
//     virtual void calculateProcChance();
//     void trig();

//     unsigned int stack_;
//     unsigned int min_stack_to_action_;
//     //int proc_chance_;
//     Event* cd_event_;
//     f32 ppm_;

//     int proc_chance_mh_auto_attack_;
//     int proc_chance_mh_instant_;
//     int proc_chance_oh_auto_attack_;
//     int proc_chance_oh_instant_;

//     int64 proc_start_time_;
//     int64 total_time_;
//     int64 total_sd_time_;
//     int64 stack_full_count_;

//     bool wait_;
// };

// class StaticShock: public Effect,
//   public pMeleeDamage,
//   public pSpellDirectDamage
// {
//   public:
//     StaticShock(EnhSim* simulator): Effect(simulator), proc_chance_(0) {};

//     virtual void proc(const int& proc_id);

//     int proc_chance_;
// };

// class ShamanisticFocus: public Effect,
//   public pMeleeCrit
// {
//   public:
//     ShamanisticFocus(EnhSim* simulator): Effect(simulator), up_(false) {};

//     virtual void proc(const int& proc_id);

//     bool up_;

//     // virtual bool procOnMhCrit() { return true; };
//     // virtual bool procOnOhCrit() { return true; };
//     // virtual bool procOnMhYellowCrit() { return true; };
//     // virtual bool procOnOhYellowCrit() { return true; };
// };

class ElementalFocus: public Effect,
  public pSpellCrit
{
  public:
    ElementalFocus(EnhSim* simulator): Effect(simulator), charges_(0) {};

    virtual void proc(const int& proc_id);

    int charges_;
};

// class ElementalOath: public Effect,
//   public pSpellCrit
// {
//   public:
//     ElementalOath(EnhSim* simulator): Effect(simulator), buff_event_(0), crit_bonus_(0), proc_start_time_(0) {};

//     virtual void proc(const int& proc_id);
//     virtual void event(const int& event_id);
//     virtual void finalize();

//     Event* buff_event_;
//     int crit_bonus_;

//     int64 proc_start_time_;
// };

// class LightningOverload: public Effect,
//   public pLightningBoltCast,
//   public pChainLightningCast
// {
//   public:
//     LightningOverload(EnhSim* simulator): Effect(simulator), proc_chance_(0) {};

//     virtual void proc(const int& proc_id);

//     int proc_chance_;
// };

// class UnrelentingStorm: public Effect {
//   public:
//     UnrelentingStorm(EnhSim* simulator): Effect(simulator), mana_regen_multiplier_(0.0f), use_(false) {};

//     virtual void event(const int& event_id);

//     f32 mana_regen_multiplier_;
//     bool use_;
// };

#endif
