//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef METAGEMS
#define METAGEMS

#include "items.h"

class ThunderingSkyfireDiamond: public BuffItemProc,
  public pMeleeDamage
{
  public:
    ThunderingSkyfireDiamond(EnhSim* simulator):
        BuffItemProc(simulator, 1.0f,/*PPM*/
                                true,/*using PPM*/
                                1000,/*duration*/
                                4000/*cd duration*/) {};

    virtual void addBuff();
    virtual void removeBuff();
};

#endif
