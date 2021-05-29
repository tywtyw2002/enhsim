//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "globalutil.h"

class EventNode;
class Event;

class Hand {
  public:
    Hand();

    void calculateMiss();
    void calculateDodge();
    void calculateHitTable();
    void calculateExpertise();

    //base miss chances before dual wield penalty and hit chance reduction
    int miss_base_;
    int miss_;
    int yellow_miss_;
    //base dodge chances before expertise reduction
    int dodge_base_;
    int dodge_;
    //glancing
    int glancing_;

    int64 last_swing_time_;
    //EventNode* next_swing_node_;
    Event* next_swing_node_;

    int64 speed_base_;
    //current weapon speed
    int64 speed_;
    f32 dps_;
    int crit_base_;
    int crit_;
    int hit_;

    //expertise rating have to be used instead of plain expertise
    //because otherwise on expertise buffs, it would be possible to
    //get less expertise because of the rounding down
    f32 expertise_rating_;
    int expertise_;

    //pre-calculated damages
    f32 damage_;
    f32 damage_crit_;

    //pre-calculated attack table
    int miss_dodge_;
    int miss_dodge_glancing_;
    int miss_dodge_glancing_crit_;
    int yellow_miss_dodge_;

    bool attack_;
};
