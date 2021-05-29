//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "trinkets.h"
#include "enhsim.h"

void DragonspineTrophy::addBuff() {
  sim.changeHaste(325 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Dragonspine Trophy procs")
}

void DragonspineTrophy::removeBuff() {
  sim.changeHaste(-325 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Dragonspine Trophy fades")
}

void MadnessOfTheBetrayer::addBuff() {
  // sim.changeArmorPenetration(42 * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
  sim.changeArmor(-300);
  COMBATLOG_EFFECT("Madness of the Betrayer procs")
}

void MadnessOfTheBetrayer::removeBuff() {
  sim.changeArmor(300);
  COMBATLOG_EFFECT("Madness of the Betrayer fades")
}

void HourglassOfTheUnraveller::addBuff() {
  sim.changeAttackPower(300);
  COMBATLOG_EFFECT("Hourglass of the Unraveller procs")
}

void HourglassOfTheUnraveller::removeBuff() {
  sim.changeAttackPower(-300);
  COMBATLOG_EFFECT("Hourglass of the Unraveller fades")
}

void TsunamiTalisman::addBuff() {
  sim.changeAttackPower(340);
  COMBATLOG_EFFECT("Tsunami Talisman procs")
}

void TsunamiTalisman::removeBuff() {
  sim.changeAttackPower(-340);
  COMBATLOG_EFFECT("Tsunami Talisman fades")
}

void ShardOfContempt::addBuff() {
  sim.changeAttackPower(230);
  COMBATLOG_EFFECT("Shard of Contempt procs")
}

void ShardOfContempt::removeBuff() {
  sim.changeAttackPower(-230);
  COMBATLOG_EFFECT("Shard of Contempt fades")
}

void BerserkersCall::addBuff() {
  sim.changeAttackPower(360);
  COMBATLOG_EFFECT("Berserker's Call used")
}

void BerserkersCall::removeBuff() {
  sim.changeAttackPower(-360);
  COMBATLOG_EFFECT("Berserker's Call fades")
}

void BloodlustBrooch::addBuff() {
  sim.changeAttackPower(278);
  COMBATLOG_EFFECT("Bloodlust Brooch used")
}

void BloodlustBrooch::removeBuff() {
  sim.changeAttackPower(-278);
  COMBATLOG_EFFECT("Bloodlust Brooch fades")
}

void AbacusOfViolentOdds::addBuff() {
  sim.changeHaste(260 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Abacus Of Violent Odds used")
}

void AbacusOfViolentOdds::removeBuff() {
  sim.changeHaste(-260 * HASTE_RATING_TO_HASTE);
  COMBATLOG_EFFECT("Abacus Of Violent Odds fades")
}

void BadgeOfTenacity::addBuff() {
  sim.changeAgility(150);
  COMBATLOG_EFFECT("Badge of Tenacity used")
}

void BadgeOfTenacity::removeBuff() {
  sim.changeAgility(-150);
  COMBATLOG_EFFECT("Badge of Tenacity fades")
}

void ShadowsongPanther::addBuff() {
  sim.changeAttackPower(320);
  COMBATLOG_EFFECT("Shadowsong Panther used")
}

void ShadowsongPanther::removeBuff() {
  sim.changeAttackPower(-320);
  COMBATLOG_EFFECT("Shadowsong Panther fades")
}

void AshtongueTalisman::addBuff() {
  sim.changeAttackPower(275);
  COMBATLOG_EFFECT("Ashtongue Talisman procs")
}

void AshtongueTalisman::removeBuff() {
  sim.changeAttackPower(-275);
  COMBATLOG_EFFECT("Ashtongue Talisman fades")
}

void BlackenedNaaruSliver::proc(const int& proc_id) {
  if (cd_) {
    if (buff_up_) {
      if (buff_stack_ < 10) {
        sim.changeAttackPower(44);
        ++buff_stack_;

        COMBATLOG_EFFECT("Blackened Naaru Sliver stacks (" << buff_stack_ << ")")
      }
    }
  }
  else {
    if (roll() < 1000) {
      buff_up_ = true;
      cd_ = true;

      //sim.changeAttackPower(44);
      //++buff_stack_;

      sim.addLowPrioEvent(duration_, this);
      sim.addHighPrioEvent(cd_duration_, this);

      proc_start_time_ = sim.now();

      COMBATLOG_EFFECT("Blackened Naaru Sliver procs")
    }
  }
}

void BlackenedNaaruSliver::event(const int& event_id) {
  if (buff_up_) {
    buff_up_ = false;

    sim.changeAttackPower(-44 * buff_stack_);
    buff_stack_ = 0;

    uptime_ += sim.now() - proc_start_time_;

    COMBATLOG_EFFECT("Blackened Naaru Sliver fades")
  }
  else {
    cd_ = false;
  }
}

void DarkmoonCardCrusade::proc(const int& proc_id) {

  if (proc_id & P_MELEE) {

    if (buff_event_physical_) {
      sim.que_.moveEvent(buff_event_physical_, duration_physical_);
    }
    else {
      sim.addLowPrioEvent(buff_event_physical_, duration_physical_, this, EVENT_ID_BUFF_FADE);
    }

    if (buff_stack_physical_ < 20) {
        
      ++buff_stack_physical_;
      sim.changeAttackPower(6);

      COMBATLOG_EFFECT("Darkmoon Card: Crusade stacks(physical) (" << buff_stack_physical_ << ")")
    }
  }
  else {

    if (buff_event_spell_) {
      sim.que_.moveEvent(buff_event_spell_, duration_spell_);
    }
    else {
      sim.addLowPrioEvent(buff_event_spell_, duration_spell_, this, EVENT_ID_BUFF2_FADE);
    }

    if (buff_stack_spell_ < 10) {

      ++buff_stack_spell_;
      sim.changeSpellpower(8);

      COMBATLOG_EFFECT("Darkmoon Card: Crusade stacks(spell) (" << buff_stack_spell_ << ")")
    }
  }
}

void DarkmoonCardCrusade::event(const int& event_id) {
  if (event_id == EVENT_ID_BUFF_FADE) {
    sim.changeAttackPower(-6 * buff_stack_physical_);
    buff_stack_physical_ = 0;

    COMBATLOG_EFFECT("Darkmoon Card: Crusade fades(physical)")

    buff_event_physical_ = 0;
  }
  else {
    sim.changeSpellpower(-8 * buff_stack_spell_);
    buff_stack_spell_ = 0;

    COMBATLOG_EFFECT("Darkmoon Card: Crusade fades(spell)")

    buff_event_spell_ = 0;
  }
}

// void FuryOfTheFiveFlights::proc(const int& proc_id) {

//   if (buff_event_) {
//     sim.que_.moveEvent(buff_event_, duration_);
//   }
//   else {
//     sim.addLowPrioEvent(buff_event_, duration_, this);
//   }

//   if (buff_stack_ < 20) {
      
//     ++buff_stack_;
//     sim.changeAttackPower(16);

//     COMBATLOG_EFFECT("Fury of the Five Flights stacks (" << buff_stack_ << ")")
//   }
// }

// void FuryOfTheFiveFlights::event(const int& event_id) {

//   sim.changeAttackPower(-16 * buff_stack_);
//   buff_stack_ = 0;

//   COMBATLOG_EFFECT("Fury of the Five Flights fades")

//   buff_event_ = 0;
// }

// void GrimToll::addBuff() {
//   sim.changeArmorPenetration(612 * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
//   COMBATLOG_EFFECT("Grim Toll procs")
// }

// void GrimToll::removeBuff() {
//   sim.changeArmorPenetration(-612 * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
//   COMBATLOG_EFFECT("Grim Toll fades")
// }

// void LoathebsShadow::addBuff() {
//   sim.changeAttackPower(670);
//   COMBATLOG_EFFECT("Loatheb's Shadow used")
// }

// void LoathebsShadow::removeBuff() {
//   sim.changeAttackPower(-670);
//   COMBATLOG_EFFECT("Loatheb's Shadow fades")
// }

// void MirrorOfTruth::addBuff() {
//   sim.changeAttackPower(1000);
//   COMBATLOG_EFFECT("Mirror of Truth procs")
// }

// void MirrorOfTruth::removeBuff() {
//   sim.changeAttackPower(-1000);
//   COMBATLOG_EFFECT("Mirror of Truth fades")
// }

// void TheSkullOfGuldan::addBuff() {
//   sim.changeHaste(175 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("The Skull of Gul'dan used")
// }

// void TheSkullOfGuldan::removeBuff() {
//   sim.changeHaste(-175 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("The Skull of Gul'dan fades")
// }

// void MeteoriteWhetstone::addBuff() {
//   sim.changeHaste(444 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Meteorite Whetstone procs")
// }

// void MeteoriteWhetstone::removeBuff() {
//   sim.changeHaste(-444 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Meteorite Whetstone fades")
// }

// void EmbraceOfTheSpider::addBuff() {
//   sim.changeHaste(505 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Embrace of the Spider procs")
// }

// void EmbraceOfTheSpider::removeBuff() {
//   sim.changeHaste(-505 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Embrace of the Spider fades")
// }

// void DyingCurse::addBuff() {
//   sim.changeSpellpower(765);
//   COMBATLOG_EFFECT("Dying Curse procs")
// }

// void DyingCurse::removeBuff() {
//   sim.changeSpellpower(-765);
//   COMBATLOG_EFFECT("Dying Curse fades")
// }

// void IllustrationOfTheDragonSoul::proc(const int& proc_id) {

//   if (buff_event_) {
//     sim.que_.moveEvent(buff_event_, duration_);
//   }
//   else {
//     sim.addLowPrioEvent(buff_event_, duration_, this);
//   }

//   if (buff_stack_ < 10) {
      
//     ++buff_stack_;
//     sim.changeSpellpower(26);

//     COMBATLOG_EFFECT("Illustration of the Dragon Soul stacks (" << buff_stack_ << ")")
//   }
// }

// void IllustrationOfTheDragonSoul::event(const int& event_id) {

//   sim.changeSpellpower(-26 * buff_stack_);
//   buff_stack_ = 0;

//   COMBATLOG_EFFECT("Illustration of the Dragon Soul fades")

//   buff_event_ = 0;
// }

// void SundialOfTheExiled::addBuff() {
//   sim.changeSpellpower(590);
//   COMBATLOG_EFFECT("Sundial of the Exiled procs")
// }

// void SundialOfTheExiled::removeBuff() {
//   sim.changeSpellpower(-590);
//   COMBATLOG_EFFECT("Sundial of the Exiled fades")
// }

// void ForgeEmber::addBuff() {
//   sim.changeSpellpower(512);
//   COMBATLOG_EFFECT("Forge Ember procs")
// }

// void ForgeEmber::removeBuff() {
//   sim.changeSpellpower(-512);
//   COMBATLOG_EFFECT("Forge Ember fades")
// }

// void IncisorFragment::addBuff() {
//   sim.changeArmorPenetration(291 * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
//   COMBATLOG_EFFECT("Incisor Fragment used")
// }

// void IncisorFragment::removeBuff() {
//   sim.changeArmorPenetration(-291 * ARMOR_PENETRATION_RATING_TO_ARMOR_PENETRATION);
//   COMBATLOG_EFFECT("Incisor Fragment fades")
// }

// void MarkOfTheWarPrisoner::addBuff() {
//   sim.changeSpellpower(346);
//   COMBATLOG_EFFECT("Mark of the War Prisoner used")
// }

// void MarkOfTheWarPrisoner::removeBuff() {
//   sim.changeSpellpower(-346);
//   COMBATLOG_EFFECT("Mark of the War Prisoner fades")
// }

// void SphereOfTheRedDragonsBlood::addBuff() {
//   sim.changeAttackPower(670);
//   COMBATLOG_EFFECT("Sphere of the Red Dragon's Blood used")
// }

// void SphereOfTheRedDragonsBlood::removeBuff() {
//   sim.changeAttackPower(-670);
//   COMBATLOG_EFFECT("Sphere of the Red Dragon's Blood fades")
// }

// void TomeOfArcanePhenomena::addBuff() {
//   sim.changeHaste(256 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Tome of Arcane Phenomena used")
// }

// void TomeOfArcanePhenomena::removeBuff() {
//   sim.changeHaste(-256 * HASTE_RATING_TO_HASTE);
//   COMBATLOG_EFFECT("Tome of Arcane Phenomena fades")
// }
