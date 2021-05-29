//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef TRINKETS
#define TRINKETS

#include "items.h"

class DragonspineTrophy: public BuffItemProc,
  public pMeleeDamage
{
  public:
    DragonspineTrophy(EnhSim* simulator):
        BuffItemProc(simulator, 1.0f,/*PPM*/
                                true,/*using PPM*/
                                1000,/*duration*/
                                2000/*cd duration*/) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class MadnessOfTheBetrayer: public BuffItemProc,
  public pMeleeDamage
{
  public:
    MadnessOfTheBetrayer(EnhSim* simulator):
        BuffItemProc(simulator, 1.0f,/*PPM*/
                                true,/*using PPM*/
                                1000,/*duration*/
                                0/*cd duration*/) {};

    virtual void addBuff();
    virtual void removeBuff();
};

class HourglassOfTheUnraveller: public BuffItemProc,
  public pMeleeCrit
{
  public:
    HourglassOfTheUnraveller(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1000,/*duration*/
                                4500/*cd duration*/) { setStaticProcChance(1000); };

    virtual void addBuff();
    virtual void removeBuff();
};

class TsunamiTalisman: public BuffItemProc,
  public pMeleeCrit
{
  public:
    TsunamiTalisman(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1000,/*duration*/
                                4500/*cd duration*/) { setStaticProcChance(1000); };

    virtual void addBuff();
    virtual void removeBuff();
};

class ShardOfContempt: public BuffItemProc,
  public pMeleeDamage
{
  public:
    ShardOfContempt(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                2000,/*duration*/
                                4500/*cd duration*/) { setStaticProcChance(1000); };

    virtual void addBuff();
    virtual void removeBuff();
};

class BerserkersCall: public ItemUse {
  public:
    BerserkersCall(EnhSim* simulator):
        ItemUse(simulator, false,
                           2000,/*duration*/
                           12000)/*cd duration*/ {};

    virtual void addBuff();
    virtual void removeBuff();
};

class BloodlustBrooch: public ItemUse {
  public:
    BloodlustBrooch(EnhSim* simulator):
        ItemUse(simulator, false,
                           2000,/*duration*/
                           12000)/*cd duration*/ {};

    virtual void addBuff();
    virtual void removeBuff();
};

class AbacusOfViolentOdds: public ItemUse {
  public:
    AbacusOfViolentOdds(EnhSim* simulator):
        ItemUse(simulator, false,
                           1000,/*duration*/
                           12000)/*cd duration*/ {};

    virtual void addBuff();
    virtual void removeBuff();
};

class BadgeOfTenacity: public ItemUse {
  public:
    BadgeOfTenacity(EnhSim* simulator):
        ItemUse(simulator, false,
                           2000,/*duration*/
                           12000)/*cd duration*/ {};

    virtual void addBuff();
    virtual void removeBuff();
};

class ShadowsongPanther: public ItemUse {
  public:
    ShadowsongPanther(EnhSim* simulator):
        ItemUse(simulator, false,
                           1500,/*duration*/
                           9000)/*cd duration*/ {};

    virtual void addBuff();
    virtual void removeBuff();
};

class AshtongueTalisman: public BuffItemProc,
  public pMhStormstrikeDamage
{
  public:
    AshtongueTalisman(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1000,/*duration*/
                                0/*cd duration*/) { setStaticProcChance(5000); };

    virtual void addBuff();
    virtual void removeBuff();
};

class BlackenedNaaruSliver: public Item,
  public pMeleeDamage
{
  public:
    BlackenedNaaruSliver(EnhSim* simulator): Item(simulator, 
      false, //ppm?
      4500),//cd duration 
      duration_(2000),//duration
      proc_chance_(1000),//proc chance
      buff_up_(false), buff_stack_(0) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);

    int64 duration_;
    int proc_chance_;
    bool buff_up_;
    int buff_stack_;
};

class DarkmoonCardCrusade: public Item,
  public pMeleeDamage,
  public pSpellDirectDamage
{
  public:
    DarkmoonCardCrusade(EnhSim* simulator): Item(simulator, 
      false, //ppm?
      0),//cd duration 
      duration_physical_(1000),//duration
      duration_spell_(1000),
      buff_stack_physical_(0), buff_stack_spell_(0), buff_event_physical_(0), buff_event_spell_(0) {};

    virtual void proc(const int& proc_id);
    virtual void event(const int& event_id);

    int64 duration_physical_;
    int64 duration_spell_;
    int buff_stack_physical_;
    int buff_stack_spell_;
    Event* buff_event_physical_;
    Event* buff_event_spell_;
};

// class FuryOfTheFiveFlights: public Item,
//   public pMeleeDamage
// {
//   public:
//     FuryOfTheFiveFlights(EnhSim* simulator): Item(simulator, 
//       false, //ppm?
//       0),//cd duration 
//       duration_(1000),//duration
//       buff_stack_(0), buff_event_(0) {};

//     virtual void proc(const int& proc_id);
//     virtual void event(const int& event_id);

//     int64 duration_;
//     int buff_stack_;
//     Event* buff_event_;
// };

// class GrimToll: public BuffItemProc,
//   public pMeleeDamage
// {
//   public:
//     GrimToll(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1500); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class LoathebsShadow: public ItemUse {
//   public:
//     LoathebsShadow(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class MirrorOfTruth: public BuffItemProc,
//   public pMeleeCrit
// {
//   public:
//     MirrorOfTruth(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1000); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class TheSkullOfGuldan: public ItemUse {
//   public:
//     TheSkullOfGuldan(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class MeteoriteWhetstone: public BuffItemProc,
//   public pMeleeDamage
// {
//   public:
//     MeteoriteWhetstone(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1500); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class EmbraceOfTheSpider: public BuffItemProc,
//   public pSpellDamage
// {
//   public:
//     EmbraceOfTheSpider(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1000); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class DyingCurse: public BuffItemProc,
//   public pSpellDamage
// {
//   public:
//     DyingCurse(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1500); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class IllustrationOfTheDragonSoul: public Item,
//   public pSpellCast
// {
//   public:
//     IllustrationOfTheDragonSoul(EnhSim* simulator): Item(simulator, 
//       false, //ppm?
//       0),//cd duration 
//       duration_(1000),//duration
//       buff_stack_(0), buff_event_(0) {};

//     virtual void proc(const int& proc_id);
//     virtual void event(const int& event_id);

//     int64 duration_;
//     int buff_stack_;
//     Event* buff_event_;
// };

// class SundialOfTheExiled: public BuffItemProc,
//   public pSpellDirectDamage
// {
//   public:
//     SundialOfTheExiled(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1000); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class ForgeEmber: public BuffItemProc,
//   public pSpellDamage
// {
//   public:
//     ForgeEmber(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,/*using PPM*/
//                                 1000,/*duration*/
//                                 4500/*cd duration*/) { setStaticProcChance(1000); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class IncisorFragment: public ItemUse {
//   public:
//     IncisorFragment(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class MarkOfTheWarPrisoner: public ItemUse {
//   public:
//     MarkOfTheWarPrisoner(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class SphereOfTheRedDragonsBlood: public ItemUse {
//   public:
//     SphereOfTheRedDragonsBlood(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

// class TomeOfArcanePhenomena: public ItemUse {
//   public:
//     TomeOfArcanePhenomena(EnhSim* simulator):
//         ItemUse(simulator, false,
//                            2000,/*duration*/
//                            12000)/*cd duration*/ {};

//     virtual void addBuff();
//     virtual void removeBuff();
// };

#endif
