//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef WEAPON_ENCHANTS
#define WEAPON_ENCHANTS

#include "effects.h"

class WeaponEnchant: public Effect {
  public:
    WeaponEnchant(EnhSim* simulator): Effect(simulator) {};
};

class MhWindfury: public WeaponEnchant,
  public pMhAutoAttackDamage,
  public pMhStormstrikeDamage
{
  public:
    MhWindfury(EnhSim* simulator): WeaponEnchant(simulator), proc_chance_(WINDFURY_PROC_CHANCE), bonus_ap_(WINDFURY_BONUS_AP), damage_multiplier_(1.0f) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);

    void wfSwing();

    int proc_chance_;
    int bonus_ap_;
    f32 damage_multiplier_;
};

class OhWindfury: public WeaponEnchant,
  public pOhAutoAttackDamage,
  public pOhStormstrikeDamage
  // public pLavaLashDamage
{
  public:
    OhWindfury(EnhSim* simulator): WeaponEnchant(simulator), proc_chance_(WINDFURY_PROC_CHANCE), bonus_ap_(WINDFURY_BONUS_AP), damage_multiplier_(1.0f) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);

    void wfSwing();

    int proc_chance_;
    int bonus_ap_;
    f32 damage_multiplier_;
};

class MhFlametongue: public WeaponEnchant,
  public pMhMeleeDamage
{
  public:
    MhFlametongue(EnhSim* simulator): WeaponEnchant(simulator), damage_multiplier_(1.0f) {};

    virtual void proc(const int& proc_id);

    f32 damage_multiplier_;
};

class OhFlametongue: public WeaponEnchant,
  public pOhMeleeDamage
{
  public:
    OhFlametongue(EnhSim* simulator): WeaponEnchant(simulator), damage_multiplier_(1.0f) {};

    virtual void proc(const int& proc_id);

    f32 damage_multiplier_;
};

#endif
