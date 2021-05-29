//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef TOTEMS
#define TOTEMS

#include "items.h"

class StonebreakersTotem: public BuffItemProc,
  public pShockDamage
{
  public:
    StonebreakersTotem(EnhSim* simulator):
        BuffItemProc(simulator, 0,/*PPM*/
                                false,/*using PPM*/
                                1000,/*duration*/
                                1000/*cd duration*/) { setStaticProcChance(5000); };

    virtual void addBuff();
    virtual void removeBuff();
};

// class SkycallTotem: public BuffItemProc,
//   public pLightningBoltDamage
// {
//   public:
//     SkycallTotem(EnhSim* simulator):
//         BuffItemProc(simulator, 0,/*PPM*/
//                                 false,using PPM
//                                 1000,/*duration*/
//                                 0/*cd duration*/) { setStaticProcChance(1500); };

//     virtual void addBuff();
//     virtual void removeBuff();
// };

#endif
