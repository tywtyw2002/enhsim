//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef ENHSIMCONFIG
#define ENHSIMCONFIG


#include "globalutil.h"
#include "enhsim.h"
#include <string>
#include <vector>
#ifndef NOTHREADS
#include "zthread/Thread.h"
#include "zthread/FastMutex.h"
#include "zthread/Condition.h"
#endif
//#include <boost/thread/thread.hpp>
//#include <boost/thread/mutex.hpp>
//#include <boost/thread/condition.hpp>
//#include <boost/bind.hpp>

class EnhSimConfig;

class EPThread
#ifndef NOTHREADS
  : public ZThread::Runnable
#endif
{
  public:
    EPThread(EnhSimConfig* enhsimconfig, const f32& hours);

    void run();
    void printEPValues();

  private:
    EnhSimConfig* enhsimconfig_;
    f32 hours_;
    unsigned int sim_index_;
#ifndef NOTHREADS
    ZThread::FastMutex lock_;
#endif
};

class SimulationThread
#ifndef NOTHREADS  
  : public ZThread::Runnable
#endif
{
  public:
    SimulationThread(EnhSimConfig* enhsimconfig, EnhSim* enhsim, const f32& hours);

    void run();

  private:
    EnhSimConfig* enhsimconfig_;
    EnhSim* sim_;
    f32 hours_;
#ifndef NOTHREADS
    ZThread::FastMutex lock_;
#endif
};


class EnhSimConfig {

  friend class EPThread;
  friend class SimulationThread;

  public:
    EnhSimConfig();
    ~EnhSimConfig();

    void reset();

    void setEP(bool ep_ap_base, const int& ap, const int& crit_rating, const int& hit_rating, const int& expertise, const int& haste_rating, const int& armor_ignore, const int& spellpower, const int& spellcrit_rating, const int& spellhit_rating, const f32& dps, const int& mana, const int& spirit, const int& mp5);
    void setThreads(const int& count);

    void setRotationCount(const int& count);
    void setRotation(const std::string& castable, const int& priority);
    void setRotationSettings(bool mh_attack, bool oh_attack, bool cast_ll_only_if_wf_on_cd_, const f32& lvb_ed, const int& lvb_fsdots, bool lvb_fs_active, /*const f32& mw_lvb_cd, */const int& fs_cast_dots, const int& ls_charges, const f32& sr_mana);
    // void setRotation(const std::string& rotation, const f32& average_shocks_per_minute, const int& use_approx)

    void setTalent(const std::string& name, const int& rank);

    void setMhWeaponEnchant(const std::string& name);
    void setOhWeaponEnchant(const std::string& name);

    void setMhEnchant(const std::string& name);
    void setOhEnchant(const std::string& name);

    void setMhWeapon(std::string name);
    void setOhWeapon(std::string name);

    void setTrinket(const std::string& name, const int& index);
    void setTotem(const std::string& name);
    void setSetBonus(const std::string& name);
    void setMetagem(const std::string& name);

    void setBuff(const std::string& name, const double& value);

    void setConsumable(const std::string& name);
    void setMiscItem(const std::string& name);

    // void setGlyph(const std::string& name);


    void setRace(const std::string& race);

    void setMhDps(const f32& dps) { mh_dps_ += dps; };
    void setOhDps(const f32& dps) { oh_dps_ += dps; };

    void setMhSpeed(const f32& speed) { mh_speed_ = static_cast<int64>(speed); };
    void setOhSpeed(const f32& speed) { oh_speed_ = static_cast<int64>(speed); };

    void setMhCrit(const f32& crit) { mh_crit_ += static_cast<int>(crit * 100); };
    void setOhCrit(const f32& crit) { oh_crit_ += static_cast<int>(crit * 100); };

    void setMhHit(const f32& hit) { mh_hit_ += static_cast<int>(hit * 100); };
    void setOhHit(const f32& hit) { oh_hit_ += static_cast<int>(hit * 100); };

    void setMhExpertiseRating(const f32& expertise) { mh_expertise_rating_ += expertise; };
    void setOhExpertiseRating(const f32& expertise) { oh_expertise_rating_ += expertise; };

    void setAttackPower(const int& ap) { attack_power_ += ap; };
    void setHaste(const f32& haste) { haste_ += haste / 100; };
    // void setArmorPenetration(const f32& armorp) { armor_penetration_ -= armorp / 100; };
    void setArmorIgnore(const int& ignore) { armor_ -= ignore; };

    void setMp5(const int& mp5) { mp5_ += mp5; };
    void setMaxMana(const f32& mana) { max_mana_ += mana; };

    void setStength(const int& str) { strength_ += str; };
    void setAgility(const int& agi) { agility_ += agi; };
    void setIntelligence(const int& intt) { intelligence_ += intt; };
    void setSpirit(const int& spi) { spirit_ += spi; };

    void setMiss(const f32& miss) { miss_ += static_cast<int>(miss * 100); };
    void setDodge(const f32& dodge) { dodge_ += static_cast<int>(dodge * 100); };
    void setGlancing(const f32& glancing) { glancing_ += static_cast<int>(glancing * 100); };
    void setSpellMiss(const f32& spell_miss) { spell_miss_ += static_cast<int>(spell_miss * 100); };
    void setArmor(const int& armor) { armor_ += armor; };

    void setNatureResistance(const int& nature_resistance) { nature_resistance_ += nature_resistance; };
    void setFireResistance(const int& fire_resistance) { fire_resistance_ += fire_resistance; };
    void setFrostResistance(const int& frost_resistance) { frost_resistance_ += frost_resistance; };

    void setSpellpower(const int& spellpower) { spellpower_ += spellpower; };
    void setSpellCrit(const f32& spell_crit) { nature_crit_ += static_cast<int>(spell_crit * 100);
                                               fire_crit_ += static_cast<int>(spell_crit * 100);
                                               frost_crit_ += static_cast<int>(spell_crit * 100);};
    void setSpellHit(const f32& spell_hit) { spell_hit_ += static_cast<int>(spell_hit * 100);
                                             spell_hit_totem_ += static_cast<int>(spell_hit * 100);};

    /*void setPhysicalCritBonus(const f32& crit_bonus) { physical_crit_multiplier_ *= 1.0f + crit_bonus / 100; };
    void setSpellCritBonus(const f32& crit_bonus) { spell_crit_multiplier_ *= 1.0f + crit_bonus / 100; };*/

    /*void setWindfuryAp(const int& wf_ap) { for (unsigned int i=0; i<enhsims_.size(); ++i) {
                                            enhsims_[i]->mh_windfury_->bonus_ap_ += wf_ap;
                                            enhsims_[i]->oh_windfury_->bonus_ap_ += wf_ap; }};*/

    /*void setStormstrikeCooldown(const f32& cd) { for (unsigned int i=0; i<enhsims_.size(); ++i) {
                                                  enhsims_[i]->stormstrike_->cooldown_ = static_cast<int64>(cd * 100); }};*/
    //void setStormstrikeNatureDamageBuff(const f32& dmgbuff) { nature_damage_multiplier_ *= 1.0f + dmgbuff / 100; };

    void setWaitSSWithWFCD(const f32& max_wait) { wait_ss_wf_ = static_cast<int>(max_wait * 100); };

    /*void useSearingTotem(const int& use_searing) { for (unsigned int i=0; i<enhsims_.size(); ++i) {
                                                    enhsims_[i]->use_searing_totem_ = use_searing; }};*/

    void setUseManaPotionMaxMana(const f32& potion_mana);

    void setCombatLength(const f32& minutes);
    void setBloodlust(const int& casters, const int& sync);

    void setLag(int min, int max);
    void setSimulateMana(bool simulate_mana);

    //void simulateDPS(const f32& hours, const int& report_count);
    void initializeEnhSims();
    f32 startSimulation(const f32& hours, const int& report_count);
    f32 calculateEPValues(const f32& hours);
    void printEPValues(const f32& hours);

    void fixStats();

  private:

    bool ep_;
    unsigned int threads_;
#ifndef NOTHREADS
    ZThread::FastMutex lock_;
    ZThread::Condition condition_;
#endif
    //boost::mutex lock_;
    //boost::condition condition_;

    bool ep_ap_base_;
    int ep_ap_;
    int ep_crit_rating_;
    int ep_hit_rating_;
    f32 ep_expertise_rating_;
    int ep_haste_rating_;
    // int ep_armor_penetration_;
    int ep_armor_ignore_;
    int ep_spellpower_;
    int ep_spellcrit_rating_;
    int ep_spellhit_rating_;
    f32 ep_dps_;
    int ep_mana_;
    int ep_spirit_;
    int ep_mp5_;
    int ep_skipped_;

    std::vector<EnhSim*> enhsims_;
    //Statistics stats_;
    std::vector<Statistics> statsv_;
    unsigned int ep_task_index_;

    f32 mh_dps_;
    f32 oh_dps_;
    f32 rockbiter_multiplier_;
    f32 improved_weapon_totems_multiplier_;

    int64 mh_speed_;
    int64 oh_speed_;

    int mh_crit_;
    int oh_crit_;

    int mh_hit_;
    int oh_hit_;

    int attack_power_;
    f32 haste_;

    f32 mh_expertise_rating_;
    f32 oh_expertise_rating_;

    // f32 armor_penetration_;
    int armor_ignore_;

    int mp5_;
    f32 max_mana_;

    int strength_;
    int agility_;
    int intelligence_;
    int spirit_;
    //f32 attribute_multiplier_;
    f32 int_to_ap_multiplier_;
    f32 strenght_multiplier_;
    f32 agility_multiplier_;
    f32 intelligence_multiplier_;
    f32 spirit_multiplier_;
    f32 ap_to_spellpower_multiplier_;

    int miss_;
    int dodge_;
    int glancing_;
    int spell_miss_;
    int armor_;

    int nature_resistance_;
    int fire_resistance_;
    int frost_resistance_;

    int spellpower_;
    int nature_crit_;
    int fire_crit_;
    int frost_crit_;
    int spell_hit_;
    int spell_hit_totem_;
    f32 mental_quickness_mana_;
    f32 shamanistic_focus_mana_;
    f32 convection_mana_;

    f32 physical_damage_multiplier_;
    f32 nature_damage_multiplier_;
    f32 fire_damage_multiplier_;
    f32 frost_damage_multiplier_;
    f32 firetotem_damage_multiplier_;

    f32 physical_crit_multiplier_;
    f32 spell_crit_multiplier_;
    f32 spell_crit_bonus_;

    std::string mh_weapon_enchant_;
    std::string oh_weapon_enchant_;

    std::string mh_weapon_;
    std::string oh_weapon_;

    int windfury_bonus_ap_;

    int wait_ss_wf_;

    bool ap_buff_multiplier_;
    bool spell_crit_buff_;

    f32 water_shield_multiplier_;

    bool simulate_mana_;
};

#endif
