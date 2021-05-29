//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef EFFECTS
#define EFFECTS

#include "globalutil.h"
//#include "event.h"

class EnhSim;
class Event;

//effect is the base class for every talent/spell/skill/enchant etc
class Effect {
  public:
    Effect(EnhSim* simulator): sim(*simulator) {};

    //proc is called if the effect has been registered for certain event
    virtual void proc(const int& proc_id) {};
    //event is called if the event has been placed on the timeline(event queue)
    //and the duration has passed
    virtual void event(const int& event_id) {};

    virtual void finalize() {};

  protected:
    EnhSim& sim;
};

//these are the proc classes which are used to define, when effect procs
class pMhAutoAttackMiss {};
class pMhAutoAttackDodge {};
class pMhAutoAttackGlancing {};
class pMhAutoAttackHit {};
class pMhAutoAttackCrit {};

class pOhAutoAttackMiss {};
class pOhAutoAttackDodge {};
class pOhAutoAttackGlancing {};
class pOhAutoAttackHit {};
class pOhAutoAttackCrit {};

class pMhWindfuryMiss {};
class pMhWindfuryDodge {};
class pMhWindfuryHit {};
class pMhWindfuryCrit {};

class pOhWindfuryMiss {};
class pOhWindfuryDodge {};
class pOhWindfuryHit {};
class pOhWindfuryCrit {};

class pMhFlametongueMiss {};
class pMhFlametongueHit {};
class pMhFlametongueCrit {};

class pOhFlametongueMiss {};
class pOhFlametongueHit {};
class pOhFlametongueCrit {};

class pMhStormstrikeMiss {};
class pMhStormstrikeDodge {};
class pMhStormstrikeHit {};
class pMhStormstrikeCrit {};

class pOhStormstrikeMiss {};
class pOhStormstrikeDodge {};
class pOhStormstrikeHit {};
class pOhStormstrikeCrit {};

class pLavaLashMiss {};
class pLavaLashDodge {};
class pLavaLashHit {};
class pLavaLashCrit {};

class pEarthShockMiss {};
class pEarthShockHit {};
class pEarthShockCrit {};

class pFlameShockMiss {};
class pFlameShockHit {};
class pFlameShockCrit {};

class pFrostShockMiss {};
class pFrostShockHit {};
class pFrostShockCrit {};

class pLightningBoltMiss {};
class pLightningBoltHit {};
class pLightningBoltCrit {};

class pChainLightningMiss {};
class pChainLightningHit {};
class pChainLightningCrit {};

class pLavaBurstMiss {};
class pLavaBurstHit {};
class pLavaBurstCrit {};

class pLightningShieldMiss {};
class pLightningShieldHit {};
class pLightningShieldCast {};

class pLightningOverloadMiss {};
class pLightningOverloadHit {};
class pLightningOverloadCrit {};


//these are the proc subclasses which group proc classes together for easier use
class pMhSwing:
  public pMhAutoAttackMiss,
  public pMhAutoAttackDodge,
  public pMhAutoAttackGlancing,
  public pMhAutoAttackHit,
  public pMhAutoAttackCrit
{};

class pOhSwing:
  public pOhAutoAttackMiss,
  public pOhAutoAttackDodge,
  public pOhAutoAttackGlancing,
  public pOhAutoAttackHit,
  public pOhAutoAttackCrit
{};

class pSwing:
  public pMhSwing,
  public pOhSwing
{};



class pMhAutoAttackDamage:
  public pMhAutoAttackGlancing,
  public pMhAutoAttackHit,
  public pMhAutoAttackCrit
{};

class pOhAutoAttackDamage:
  public pOhAutoAttackGlancing,
  public pOhAutoAttackHit,
  public pOhAutoAttackCrit
{};

class pAutoAttackDamage:
  public pMhAutoAttackDamage,
  public pOhAutoAttackDamage
{};

class pAutoAttackCrit:
  public pMhAutoAttackCrit,
  public pOhAutoAttackCrit
{};




class pMhWindfuryDamage:
  public pMhWindfuryHit,
  public pMhWindfuryCrit
{};

class pOhWindfuryDamage:
  public pOhWindfuryHit,
  public pOhWindfuryCrit
{};

class pWindfuryDamage:
  public pMhWindfuryDamage,
  public pOhWindfuryDamage
{};

class pWindfuryCrit:
  public pMhWindfuryCrit,
  public pOhWindfuryCrit
{};




class pMhStormstrikeDamage:
  public pMhStormstrikeHit,
  public pMhStormstrikeCrit
{};

class pOhStormstrikeDamage:
  public pOhStormstrikeHit,
  public pOhStormstrikeCrit
{};

class pStormstrikeDamage:
  public pMhStormstrikeDamage,
  public pOhStormstrikeDamage
{};

class pStormstrikeCrit:
  public pMhStormstrikeCrit,
  public pOhStormstrikeCrit
{};




class pLavaLashDamage:
  public pLavaLashHit,
  public pLavaLashCrit
{};



class pMhSpecialDamage:
  public pMhWindfuryDamage,
  public pMhStormstrikeDamage
{};

class pOhSpecialDamage:
  public pOhWindfuryDamage,
  public pOhStormstrikeDamage,
  public pLavaLashDamage
{};

class pSpecialDamage:
  public pMhSpecialDamage,
  public pOhSpecialDamage
{};


class pMhSpecialCrit:
  public pMhWindfuryCrit,
  public pMhStormstrikeCrit
{};

class pOhSpecialCrit:
  public pOhWindfuryCrit,
  public pOhStormstrikeCrit,
  public pLavaLashCrit
{};

class pSpecialCrit:
  public pMhSpecialCrit,
  public pOhSpecialCrit
{};



class pMhMeleeDamage:
  public pMhAutoAttackDamage,
  public pMhSpecialDamage
{};

class pOhMeleeDamage:
  public pOhAutoAttackDamage,
  public pOhSpecialDamage
{};

class pMeleeDamage:
  public pMhMeleeDamage,
  public pOhMeleeDamage
{};

class pMhMeleeCrit:
  public pMhAutoAttackCrit,
  public pMhSpecialCrit
{};

class pOhMeleeCrit:
  public pOhAutoAttackCrit,
  public pOhSpecialCrit
{};

class pMeleeCrit:
  public pMhMeleeCrit,
  public pOhMeleeCrit
{};




class pMhFlametongueDamage:
  public pMhFlametongueHit,
  public pMhFlametongueCrit
{};

class pOhFlametongueDamage:
  public pOhFlametongueHit,
  public pOhFlametongueCrit
{};

class pFlametongueDamage:
  public pMhFlametongueDamage,
  public pOhFlametongueDamage
{};

class pFlametongueCrit:
  public pMhFlametongueCrit,
  public pOhFlametongueCrit
{};




class pEarthShockDamage:
  public pEarthShockHit,
  public pEarthShockCrit
{};

class pEarthShockCast:
  public pEarthShockDamage,
  public pEarthShockMiss
{};

class pFlameShockDamage:
  public pFlameShockHit,
  public pFlameShockCrit
{};

class pFlameShockCast:
  public pFlameShockDamage,
  public pFlameShockMiss
{};

class pFrostShockDamage:
  public pFrostShockHit,
  public pFrostShockCrit
{};

class pFrostShockCast:
  public pFrostShockDamage,
  public pFrostShockMiss
{};

class pShockDamage:
  public pEarthShockDamage,
  public pFlameShockDamage,
  public pFrostShockDamage
{};

class pShockCrit:
  public pEarthShockCrit,
  public pFlameShockCrit,
  public pFrostShockCrit
{};

class pShockCast:
  public pEarthShockCast,
  public pFlameShockCast,
  public pFrostShockCast
{};

class pLightningBoltDamage:
  public pLightningBoltHit,
  public pLightningBoltCrit
{};

class pLightningBoltCast:
  public pLightningBoltDamage,
  public pLightningBoltMiss
{};

class pLightningOverloadDamage:
  public pLightningOverloadHit,
  public pLightningOverloadCrit
{};

class pLightningOverloadCast:
  public pLightningOverloadDamage,
  public pLightningOverloadMiss
{};

class pChainLightningDamage:
  public pChainLightningHit,
  public pChainLightningCrit
{};

class pChainLightningCast:
  public pChainLightningDamage,
  public pChainLightningMiss
{};

class pLavaBurstDamage:
  public pLavaBurstHit,
  public pLavaBurstCrit
{};

class pLavaBurstCast:
  public pLavaBurstDamage,
  public pLavaBurstMiss
{};

class pLightningShieldDamage:
  public pLightningShieldHit
{};

class pSpellDirectDamage:
  public pShockDamage,
  public pLightningBoltDamage,
  public pLightningOverloadDamage,
  public pChainLightningDamage,
  public pLavaBurstDamage
{};

class pSpellDamage:
  public pSpellDirectDamage,
  public pLightningShieldDamage
{};

class pSpellCrit:
  public pShockCrit,
  public pLightningBoltCrit,
  public pLightningOverloadCrit,
  public pChainLightningCrit,
  public pLavaBurstCrit
{};

class pSpellCast:
  public pShockCast,
  public pLightningBoltCast,
  public pLightningOverloadCast,
  public pChainLightningCast,
  public pLavaBurstCast,
  public pLightningShieldCast
{};


//this is just for printing the simulation progress during simulation
class SimulationProgress: public Effect {
  public:
    SimulationProgress(EnhSim* simulator): Effect(simulator), report_count_(0), reported_count_(0), interval_(0) {};

    virtual void event(const int& event_id);

    int report_count_;
    int reported_count_;
    int64 interval_;
};




class Castable: public Effect {
  public:
    Castable(EnhSim* simulator, int64 casting_time): Effect(simulator), mana_reduction_(0.0f), casting_time_(casting_time) {};

    virtual bool cast() = 0;
    virtual void castingFinished() {};

    f32 mana_reduction_;
    int64 casting_time_;
};

class MhEvent: public Effect {
  public:
    MhEvent(EnhSim* simulator): Effect(simulator) {};

    virtual void event(const int& event_id);
};

class OhEvent: public Effect {
  public:
    OhEvent(EnhSim* simulator): Effect(simulator) {};

    virtual void event(const int& event_id);
};

class CombatLength: public Effect {
  public:
    CombatLength(EnhSim* simulator): Effect(simulator), duration_(0) {};

    virtual void event(const int& event_id);
    void set();

    int64 duration_;
};

class MaelstromCaster: public Castable {
  public:
    MaelstromCaster(EnhSim* simulator, Castable* spell, unsigned int min_charges);

    virtual bool cast();

    Castable* spell_;
    unsigned int min_charges_;
};

class SpellCasting: public Effect {
  public:
    SpellCasting(EnhSim* simulator): Effect(simulator), spell_(0), mh_swing_left_(0), oh_swing_left_(0), haste_divider_(1.0f), casting_(false) {};

    virtual void event(const int& event_id);

    void startCasting(Castable* spell, const int64& time, bool reset_swing);

    Castable* spell_;
    int64 mh_swing_left_;
    int64 oh_swing_left_;
    f32 haste_divider_;
    bool casting_;
};

class InputLag: public Effect {
  public:
    InputLag(EnhSim* simulator): Effect(simulator) {};

    virtual void event(const int& event_id);
};

class ManaRegen: public Effect {
  public:
    ManaRegen(EnhSim* simulator): Effect(simulator), replenishment_(false) {};

    virtual void event(const int& event_id);

    bool replenishment_;
};

class FiveSecRule: public Effect {
  public:
    FiveSecRule(EnhSim* simulator): Effect(simulator), cd_event_(0), cd_(false) {};

    virtual void event(const int& event_id);
    void trigger();

    Event* cd_event_;
    bool cd_;
};

class JudgementOfWisdom: public Effect,
  public pMeleeDamage
{
  public:
    JudgementOfWisdom(EnhSim* simulator): Effect(simulator), cd_(false) {};

    virtual void event(const int& event_id);
    virtual void proc(const int& proc_id);

    bool cd_;
};

class Bloodlust: public Effect {
  public:
    Bloodlust(EnhSim* simulator): Effect(simulator), duration_(4000), cooldown_(0), buff_event_(0), cd_event_(0), use_(false) {};

    virtual void event(const int& event_id);
    void use();

    int64 duration_;
    int64 cooldown_;

    Event* buff_event_;
    Event* cd_event_;

    bool use_;
};

#endif
