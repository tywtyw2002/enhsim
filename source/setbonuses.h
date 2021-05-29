//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef SET_BONUSES
#define SET_BONUSES

#include "items.h"

class DesolationBattlegear: public BuffItemProc,
  public pMeleeDamage
{
  public:
    DesolationBattlegear(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1500,/*duration*/
                                0/*cd duration*/) { setStaticProcChance(100); };

    virtual void addBuff();
    virtual void removeBuff();
};

class SkyshatterHarness: public BuffItemProc,
  public pMhStormstrikeMiss,
  public pMhStormstrikeDodge,
  public pMhStormstrikeDamage
{
  public:
    SkyshatterHarness(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1200,/*duration*/
                                0/*cd duration*/) { setStaticProcChance(10000); };

    virtual void addBuff();
    virtual void removeBuff();
};

#endif
