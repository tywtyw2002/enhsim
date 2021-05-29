//Event

#ifndef EVENT
#define EVENT

#include "effects.h"

class Event {
  public:
    Event(const int64& timestamp, const int& priority, Effect*& effect, const int& event_id, Event*& prev, Event*& next):
        timestamp_(timestamp), priority_(priority), effect_(effect), event_id_(event_id), prev_(prev), next_(next) {};

    //void remove();

    int64 timestamp_;
    int priority_;
    Effect* effect_;
    int event_id_;

    Event* prev_;
    Event* next_;
};

#endif
