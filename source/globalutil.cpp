//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "globalutil.h"
#include "effects.h"
#include "enhsim.h"
#include "SFMT/SFMT.c"
#include <time.h>
#include <fstream>

#ifdef DEBUG
std::fstream combatlog;

void setupCombatLog(std::string filename) {
  combatlog.open(filename.c_str(), std::ios::out);
  if (combatlog.fail()) {
    std::cout << "Could not open " << filename << " for combatlog." << std::endl;
  }
}

void closeCombatLog() {
  combatlog.close();
}

std::fstream& getCombatLog() {
  return combatlog;
}
#endif

void init_random() {
  init_gen_rand(static_cast<unsigned int>(time(0)));
}

//int random(const int& max) {
//  return gen_rand32() % max;
//}
//
//int roll() {
//  return gen_rand32() % 10000;
//}

void procList(Effect* (&proc_array)[PROC_COUNT], const unsigned int& count, const int& proc_id) {
  /*for (unsigned int i=0; i<count; ++i) {
    proc_array[i]->proc(proc_id);
  }*/
  /*for (unsigned int i=0; i<PROC_COUNT; ++i) {
    if (proc_array[i]) {
      proc_array[i]->proc(proc_id);
    }
    else {
      return;
    }
  }*/
  int i=-1; 
  while (proc_array[++i]) {
    proc_array[i]->proc(proc_id);
  }
}

std::string toLower(const std::string& str) {
  int length = str.length();
  std::string result;

  for (int i=0; i<length; ++i) {
    char c = tolower(str[i]);
    std::string s;
    s.resize(1);
    s[0] = c;
    result.append(s);
  }

  return result;
}

std::string intToString(const int& i) {
  std::stringstream out;
  out << i;
  return out.str();
}

int stringToInt(const std::string& str) {
  std::istringstream buffer(str);
  int value;
  buffer >> value;
  return value;
}

f32 stringToFloat(const std::string& str) {
  std::istringstream buffer(str);
  f32 value;
  buffer >> value;
  return value;
}
