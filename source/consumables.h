//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef CONSUMABLES
#define CONSUMABLES

#include "effects.h"

//class PotionCooldown: public Effect {
//  public:
//    PotionCooldown(EnhSim* simulator): Effect(simulator), cooldown_(0) {};
//
//    virtual void event(const int& event_id);
//
//    int64 cooldown_;
//};

class Potion: public Effect {
  public:
    Potion(EnhSim* simulator): Effect(simulator), potion_sickness_(false) {};

    virtual void use();
    virtual bool applyPotion() { return false; };

    bool potion_sickness_;
};

class BuffPotion: public Potion {
  public:
    BuffPotion(EnhSim* simulator): Potion(simulator) {};

    virtual void event(const int& event_id);
    virtual void use();
    virtual void applyBuff() = 0;
    virtual void removeBuff() = 0;
};

class HastePotion: public BuffPotion {
  public:
    HastePotion(EnhSim* simulator): BuffPotion(simulator) {};

    virtual void applyBuff();
    virtual void removeBuff();
};

class InsaneStrengthPotion: public BuffPotion {
  public:
    InsaneStrengthPotion(EnhSim* simulator): BuffPotion(simulator) {};

    virtual void applyBuff();
    virtual void removeBuff();
};

class HeroicPotion: public BuffPotion {
  public:
    HeroicPotion(EnhSim* simulator): BuffPotion(simulator) {};

    virtual void applyBuff();
    virtual void removeBuff();
};

class ManaPotion: public Potion {
  public:
    ManaPotion(EnhSim* simulator, f32 mana): Potion(simulator), mana_(mana), max_mana_to_use_(0) {};

    virtual bool applyPotion();

    f32 mana_;
    f32 max_mana_to_use_;
};

class SuperManaPotion: public ManaPotion {
  public:
    SuperManaPotion(EnhSim* simulator): ManaPotion(simulator, 1800) {};
};

class RunicManaPotion: public ManaPotion {
  public:
    RunicManaPotion(EnhSim* simulator): ManaPotion(simulator, 4200) {};
};

class MiscCooldown: public Effect {
  public:
    MiscCooldown(EnhSim* simulator): Effect(simulator), cd_event_(0) {};

    virtual void event(const int& event_id);

    Event* cd_event_;
};

class MiscItem: public Effect {
  public:
    MiscItem(EnhSim* simulator): Effect(simulator), buff_event_(0) {};

    virtual void use() = 0;

    Event* buff_event_;
};

class MiscBuffItem: public MiscItem {
  public:
    MiscBuffItem(EnhSim* simulator, int64 duration): MiscItem(simulator), duration_(duration) {};

    virtual void event(const int& event_id);
    virtual void use();
    virtual void applyBuff() = 0;
    virtual void removeBuff() = 0;

    int64 duration_;
};

class DrumsOfBattle: public MiscBuffItem {
  public:
    DrumsOfBattle(EnhSim* simulator): MiscBuffItem(simulator, 3000) {};

    virtual void applyBuff();
    virtual void removeBuff();
};

#endif
