//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef ITEMS
#define ITEMS

#include "effects.h"

class Item: public Effect {
  public:
    Item(EnhSim* simulator, bool ppm_flag, int64 cd_duration): Effect(simulator), ppm_flag_(ppm_flag), cd_duration_(cd_duration), cd_(false), uptime_(0), proc_start_time_(0) {};

    virtual void reCalculateProcChance() {};
    virtual void calculateProcChance() {};
    virtual void use() {};
    virtual void finalize() {};

    bool ppm_flag_;
    int64 cd_duration_;
    bool cd_;
    int64 uptime_;
    //for statistics
    int64 proc_start_time_;
};

class TrinketCooldown: public Effect {
  public:
    TrinketCooldown(EnhSim* simulator): Effect(simulator), cd_(false), cd_event_(0) {};

    virtual void event(const int& event_id);

    bool cd_;
    Event* cd_event_;
};

class ItemUse: public Item {
  public:
    ItemUse(EnhSim* simulator, bool ppm_flag, int64 duration, int64 cd_duration): Item(simulator, ppm_flag, cd_duration), duration_(duration), buff_event_(0), cd_event_(0) {};

    virtual void event(const int& event_id);
    virtual void use();
    virtual void addBuff() = 0;
    virtual void removeBuff() = 0;
    virtual void finalize();
    
    int64 duration_;
    Event* buff_event_;
    Event* cd_event_;
};

class ItemProc: public Item {
  public:
    ItemProc(EnhSim* simulator, f32 ppm, bool ppm_flag, int64 cd_duration): Item(simulator, ppm_flag, cd_duration), proc_chance_mh_auto_attack_(0), proc_chance_mh_instant_(0), proc_chance_oh_auto_attack_(0), proc_chance_oh_instant_(0), ppm_(ppm) {};

    virtual void reCalculateProcChance();
    virtual void calculateProcChance();
    void setStaticProcChance(const unsigned int& proc_chance) { proc_chance_mh_auto_attack_ = proc_chance_mh_instant_ = proc_chance_oh_auto_attack_ = proc_chance_oh_instant_ = proc_chance; };

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);
    virtual void trig();
    virtual void trigger() = 0;

    int proc_chance_mh_auto_attack_;
    int proc_chance_mh_instant_;
    int proc_chance_oh_auto_attack_;
    int proc_chance_oh_instant_;
    f32 ppm_;
};

class BuffItemProc: public ItemProc {
  public:
    BuffItemProc(EnhSim* simulator, f32 ppm, bool ppm_flag, int64 duration, int64 cd_duration): ItemProc(simulator, ppm, ppm_flag, cd_duration), duration_(duration), proc_stack_(0), buff_event_(0) {};

    virtual void trigger();
    virtual void event(const int& event_id);
    virtual void addBuff() = 0;
    virtual void removeBuff() = 0;
    virtual void finalize();

    int64 duration_;
    unsigned int proc_stack_;
    //Event* cd_event_;
    //bool buff_event_;
    Event* buff_event_;
};

#endif
