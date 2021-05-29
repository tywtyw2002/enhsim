//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#include "event_queue.h"
#include "event.h"
#include <float.h>

//SimpleEventQueue::SimpleEventQueue(): eventnode_pool_(sizeof(EventNode)),
//                                      first_(0),
//                                      now_(0) {
//}
//
//SimpleEventQueue::~SimpleEventQueue() {
//}
//
//void SimpleEventQueue::initialize() {
//  first_ = createEventNode(0, 0);
//}
//
//void SimpleEventQueue::clear() {
//  while (first_) {
//    EventNode* del = first_;
//    first_ = first_->next_;
//    deleteEventNode(del);
//  }
//}
//
//int64 SimpleEventQueue::now() {
//  return now_;
//}
//
//EventNode* SimpleEventQueue::first() {
//  return first_;
//}
//
//void SimpleEventQueue::pop() {
//  EventNode* old = first_;
//  first_ = first_->next_;
//  now_ = first_->timestamp_;
//  deleteEventNode(old);
//}
//
////all the add***Event() functions work the same way
//void SimpleEventQueue::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id) {
//  //++addcount;
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + timestamp;
//
//  EventNode* node = first_;
//  EventNode* nextnode = node->next_;
//
//  //start from timeline beginning and loop until we find an eventnode which timestamp
//  //is bigger than our events timestamp, or the timestamps are same
//  //if the timestamps are same, we dont have to create a new EventNode
//  while(node && nextnode) {
//    //++searchcount;
//    int64 tstamp = nextnode->timestamp_;
//
//    if (tstamp >= time) {
//
//      if (tstamp == time) {
//        //nextnode->highprio_[nextnode->highprio_count_++] = effect;
//        nextnode->highprio_[nextnode->highprio_count_] = effect;
//        nextnode->highprio_event_id_[nextnode->highprio_count_++] = event_id;
//        return;
//      }
//
//      EventNode* eventnode = createEventNode(time, nextnode);
//      //eventnode->highprio_[eventnode->highprio_count_++] = effect;
//      eventnode->highprio_[eventnode->highprio_count_] = effect;
//      eventnode->highprio_event_id_[eventnode->highprio_count_++] = event_id;
//      node->next_ = eventnode;
//      return;
//    }
//
//    node = nextnode;
//    nextnode = node->next_;
//  }
//
//  EventNode* eventnode = createEventNode(time, 0);
//  //eventnode->highprio_[eventnode->highprio_count_++] = effect;
//  eventnode->highprio_[eventnode->highprio_count_] = effect;
//  eventnode->highprio_event_id_[eventnode->highprio_count_++] = event_id;
//  node->next_ = eventnode;
//}
//
//void SimpleEventQueue::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id) {
//  //++addcount;
//  int64 time = now_ + timestamp;
//
//  EventNode* node = first_;
//  EventNode* nextnode = node->next_;
//
//  while(node && nextnode) {
//    //++searchcount;
//    int64 tstamp = nextnode->timestamp_;
//
//    if (tstamp >= time) {
//
//      if (tstamp == time) {
//
//        //nextnode->lowprio_[nextnode->lowprio_count_++] = effect;
//        nextnode->lowprio_[nextnode->lowprio_count_] = effect;
//        nextnode->lowprio_event_id_[nextnode->lowprio_count_++] = event_id;
//        return;
//      }
//
//      EventNode* eventnode = createEventNode(time, nextnode);
//      //eventnode->lowprio_[eventnode->lowprio_count_++] = effect;
//      eventnode->lowprio_[eventnode->lowprio_count_] = effect;
//      eventnode->lowprio_event_id_[eventnode->lowprio_count_++] = event_id;
//      node->next_ = eventnode;
//      return;
//    }
//
//    node = nextnode;
//    nextnode = node->next_;
//  }
//
//  EventNode* eventnode = createEventNode(time, 0);
//  //eventnode->lowprio_[eventnode->lowprio_count_++] = effect;
//  eventnode->lowprio_[eventnode->lowprio_count_] = effect;
//  eventnode->lowprio_event_id_[eventnode->lowprio_count_++] = event_id;
//  node->next_ = eventnode;
//}
//
//EventNode* SimpleEventQueue::addMhEvent(const int64& mh_speed) {
//  //++addcount;
//  int64 time = now_ + mh_speed;
//
//  EventNode* node = first_;
//  EventNode* nextnode = node->next_;
//
//  while(node && nextnode) {
//    //++searchcount;
//    int64 tstamp = nextnode->timestamp_;
//
//    if (tstamp >= time) {
//
//      if (tstamp == time) {
//        nextnode->mh_attack_ = true;
//        //mh.next_swing_node_ = nextnode;
//        return nextnode;
//      }
//
//      EventNode* eventnode = createEventNode(time, nextnode);
//      eventnode->mh_attack_ = true;
//      node->next_ = eventnode;
//      //mh.next_swing_node_ = eventnode;
//      return eventnode;
//    }
//
//    node = nextnode;
//    nextnode = node->next_;
//  }
//
//  EventNode* eventnode = createEventNode(time, 0);
//  eventnode->mh_attack_ = true;
//  node->next_ = eventnode;
//  //mh.next_swing_node_ = eventnode;
//  return eventnode;
//}
//
//EventNode* SimpleEventQueue::addOhEvent(const int64& oh_speed) {
//  //++addcount;
//  int64 time = now_ + oh_speed;
//
//  EventNode* node = first_;
//  EventNode* nextnode = node->next_;
//
//  while(node && nextnode) {
//    //++searchcount;
//    int64 tstamp = nextnode->timestamp_;
//
//    if (tstamp >= time) {
//
//      if (tstamp == time) {
//        nextnode->oh_attack_ = true;
//        //oh.next_swing_node_ = nextnode;
//        return nextnode;
//      }
//
//      EventNode* eventnode = createEventNode(time, nextnode);
//      eventnode->oh_attack_ = true;
//      node->next_ = eventnode;
//      //oh.next_swing_node_ = eventnode;
//      return eventnode;
//    }
//
//    node = nextnode;
//    nextnode = node->next_;
//  }
//
//  EventNode* eventnode = createEventNode(time, 0);
//  eventnode->oh_attack_ = true;
//  node->next_ = eventnode;
//  //oh.next_swing_node_ = eventnode;
//  return eventnode;
//}
//
//EventNode* SimpleEventQueue::createEventNode(const int64& timestamp, EventNode* next) {
//  return new (eventnode_pool_.malloc()) EventNode(timestamp, next);
//}
//
//void SimpleEventQueue::deleteEventNode(EventNode* p) {
//  eventnode_pool_.free(p);
//}














const double TIME_TRESHOLD = 700.0;

LinkedEventQueue::LinkedEventQueue(): eventpool_(sizeof(Event)),
                                      root_(0),
                                      last_(0),
                                      newest_(0),
                                      now_(0) {
}

LinkedEventQueue::~LinkedEventQueue() {
}

void LinkedEventQueue::initialize() {
  root_ = createEvent(0, 0, 0, 0, 0, 0);
  root_->next_ = last_ = newest_ = createEvent(DBL_MAX, PRIORITY_LOWEST, 0, 0, root_, 0);
}

void LinkedEventQueue::clear() {
  Event* node = root_;

  while (node) {
    Event* del = node;
    node = node->next_;
    delEvent(del);
  }
}

void LinkedEventQueue::start() {
  now_ = root_->next_->timestamp_;
}

//int64 LinkedEventQueue::now() const {
//  return now_;
//}
//
//Event& LinkedEventQueue::first() const {
//  return *(root_->next_);
//}

void LinkedEventQueue::pop() {
  Event* old = root_->next_;
  if (old == newest_) {
    newest_ = newest_->next_;
  }
  Event* next = old->next_;
  root_->next_ = next;
  next->prev_ = root_;
  now_ = next->timestamp_;
  eventpool_.free(old);
}

//void LinkedEventQueue::addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  int64 time = timestamp + now_;
//
//  Event* node = root_->next_;
//
//  int64 nodetime = node->timestamp_;
//  while (time >= nodetime) {
//    if (time == nodetime) if (priority <= node->priority_) break;
//
//    node = node->next_;
//    nodetime = node->timestamp_;
//
//    ++passed_;
//  }
//
//  Event* nodeprev = node->prev_;
//  Event* e = createEvent(time, priority, effect, event_id, nodeprev, node);
//  nodeprev->next_ = e;
//  node->prev_ = e;
//}

void LinkedEventQueue::addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
  int64 time = timestamp + now_;
  
  int64 nodetime = newest_->timestamp_;

  if (time > nodetime) {

    Event* node = newest_->next_;

    nodetime = node->timestamp_;
    while (time >= nodetime) {
      if (time == nodetime) if (priority <= node->priority_) break;

      node = node->next_;
      nodetime = node->timestamp_;
    }

    Event* nodeprev = node->prev_;
    newest_ = nodeprev->next_ = node->prev_ = createEvent(time, priority, effect, event_id, nodeprev, node);
    //nodeprev->next_ = e;
    //node->prev_ = e;
  }
  else {

    Event* node = newest_;

    //int64 nodetime = node->timestamp_;
    while (time <= nodetime) {
      if (time == nodetime) if (priority >= node->priority_) break;

      node = node->prev_;
      nodetime = node->timestamp_;
    }

    Event* nodenext = node->next_;
    newest_ = nodenext->prev_ = node->next_ = createEvent(time, priority, effect, event_id, node, nodenext);
    //nodenext->prev_ = e;
    //node->next_ = e;
  }
}

//void LinkedEventQueue::addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  if (timestamp < TIME_TRESHOLD) {
//    int64 time = timestamp + now_;
//
//    Event* node = root_->next_;
//
//    int64 nodetime = node->timestamp_;
//    while (time >= nodetime) {
//      if (time == nodetime) if (priority <= node->priority_) break;
//
//      node = node->next_;
//      nodetime = node->timestamp_;
//
//      ++passed_;
//    }
//
//    Event* nodeprev = node->prev_;
//    Event* e = createEvent(time, priority, effect, event_id, nodeprev, node);
//    nodeprev->next_ = e;
//    node->prev_ = e;
//  }
//  else {
//    int64 time = timestamp + now_;
//
//    Event* node = last_->prev_;
//
//    int64 nodetime = node->timestamp_;
//    while (time <= nodetime) {
//      if (time == nodetime) if (priority >= node->priority_) break;
//
//      node = node->prev_;
//      nodetime = node->timestamp_;
//
//      ++passed_;
//    }
//
//    Event* nodenext = node->next_;
//    Event* e = createEvent(time, priority, effect, event_id, node, nodenext);
//    nodenext->prev_ = e;
//    node->next_ = e;
//  }
//}

//void LinkedEventQueue::addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  int64 time = timestamp + now_;
//
//  Event* node = last_->prev_;
//
//  int64 nodetime = node->timestamp_;
//  while (time <= nodetime) {
//    if (time == nodetime) if (priority >= node->priority_) break;
//
//    node = node->prev_;
//    nodetime = node->timestamp_;
//
//    ++passed_;
//  }
//
//  Event* nodenext = node->next_;
//  Event* e = createEvent(time, priority, effect, event_id, node, nodenext);
//  nodenext->prev_ = e;
//  node->next_ = e;
//}

//void LinkedEventQueue::addEvent(Event*& e, const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  int64 time = timestamp + now_;
//
//  Event* node = root_->next_;
//
//  int64 nodetime = node->timestamp_;
//  while (time >= nodetime) {
//    if (time == nodetime) if (priority <= node->priority_) break;
//
//    node = node->next_;
//    nodetime = node->timestamp_;
//
//    ++passed_;
//  }
//
//  Event* nodeprev = node->prev_;
//  e = createEvent(time, priority, effect, event_id, nodeprev, node);
//  nodeprev->next_ = e;
//  node->prev_ = e;
//}

//void LinkedEventQueue::addEvent(Event*& e, const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  if (timestamp < TIME_TRESHOLD) {
//    int64 time = timestamp + now_;
//
//    Event* node = root_->next_;
//
//    int64 nodetime = node->timestamp_;
//    while (time >= nodetime) {
//      if (time == nodetime) if (priority <= node->priority_) break;
//
//      node = node->next_;
//      nodetime = node->timestamp_;
//
//      ++passed_;
//    }
//
//    Event* nodeprev = node->prev_;
//    e = createEvent(time, priority, effect, event_id, nodeprev, node);
//    nodeprev->next_ = e;
//    node->prev_ = e;
//  }
//  else {
//    int64 time = timestamp + now_;
//
//    Event* node = last_->prev_;
//
//    int64 nodetime = node->timestamp_;
//    while (time <= nodetime) {
//      if (time == nodetime) if (priority >= node->priority_) break;
//
//      node = node->prev_;
//      nodetime = node->timestamp_;
//
//      ++passed_;
//    }
//
//    Event* nodenext = node->next_;
//    e = createEvent(time, priority, effect, event_id, node, nodenext);
//    nodenext->prev_ = e;
//    node->next_ = e;
//  }
//}

void LinkedEventQueue::addEvent(Event*& e, const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
  int64 time = timestamp + now_;

  int64 nodetime = newest_->timestamp_;

  if (time > nodetime) {

    Event* node = newest_->next_;

    nodetime = node->timestamp_;
    while (time >= nodetime) {
      if (time == nodetime) if (priority <= node->priority_) break;

      node = node->next_;
      nodetime = node->timestamp_;
    }

    Event* nodeprev = node->prev_;
    e = newest_ = nodeprev->next_ = node->prev_ = createEvent(time, priority, effect, event_id, nodeprev, node);
    //nodeprev->next_ = e;
    //node->prev_ = e;
  }
  else {

    Event* node = newest_;

    //int64 nodetime = node->timestamp_;
    while (time <= nodetime) {
      if (time == nodetime) if (priority >= node->priority_) break;

      node = node->prev_;
      nodetime = node->timestamp_;
    }

    Event* nodenext = node->next_;
    e = newest_ = nodenext->prev_ = node->next_ = createEvent(time, priority, effect, event_id, node, nodenext);
    //nodenext->prev_ = e;
    //node->next_ = e;
  }
}

//void LinkedEventQueue::addEvent(Event*& e, const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  int64 time = timestamp + now_;
//
//  Event* node = last_->prev_;
//
//  int64 nodetime = node->timestamp_;
//  while (time <= nodetime) {
//    if (time == nodetime) if (priority >= node->priority_) break;
//
//    node = node->prev_;
//    nodetime = node->timestamp_;
//
//    ++passed_;
//  }
//
//  Event* nodenext = node->next_;
//  e = createEvent(time, priority, effect, event_id, node, nodenext);
//  nodenext->prev_ = e;
//  node->next_ = e;
//}

void LinkedEventQueue::moveEvent(Event*& e, const int64& timestamp) {

  if (e == newest_) {
    newest_ = newest_->next_;
  }
  Event* next = e->next_;
  Event* prev = e->prev_;
  prev->next_ = next;
  next->prev_ = prev;

  int64 time = e->timestamp_ = timestamp + now_;
  int priority = e->priority_;

  int64 nodetime = newest_->timestamp_;

  if (time > nodetime) {

    Event* node = newest_->next_;

    nodetime = node->timestamp_;
    while (time >= nodetime) {
      if (time == nodetime) if (priority <= node->priority_) break;

      node = node->next_;
      nodetime = node->timestamp_;
    }

    Event* nodeprev = node->prev_;
    e->next_ = node;
    e->prev_ = nodeprev;
    nodeprev->next_ = node->prev_ = e;
  }
  else {

    Event* node = newest_;

    //int64 nodetime = node->timestamp_;
    while (time <= nodetime) {
      if (time == nodetime) if (priority >= node->priority_) break;

      node = node->prev_;
      nodetime = node->timestamp_;
    }

    Event* nodenext = node->next_;
    e->next_ = nodenext;
    e->prev_ = node;
    nodenext->prev_ = node->next_ = e;
  }
}

void LinkedEventQueue::moveEventSearchForward(Event*& e, const int64& timestamp) {

  if (e == newest_) {
    newest_ = newest_->next_;
  }
  Event* next = e->next_;
  Event* prev = e->prev_;
  prev->next_ = next;
  next->prev_ = prev;

  int64 time = e->timestamp_ = timestamp + now_;
  int priority = e->priority_;

  Event* node = e->next_;
  int64 nodetime = node->timestamp_;

  while (time >= nodetime) {
    if (time == nodetime) if (priority <= node->priority_) break;

    node = node->next_;
    nodetime = node->timestamp_;
  }

  Event* nodeprev = node->prev_;
  e->next_ = node;
  e->prev_ = nodeprev;
  nodeprev->next_ = node->prev_ = e;
}

void LinkedEventQueue::moveEventSearchBackward(Event*& e, const int64& timestamp) {

  if (e == newest_) {
    newest_ = newest_->next_;
  }
  Event* next = e->next_;
  Event* prev = e->prev_;
  prev->next_ = next;
  next->prev_ = prev;

  int64 time = e->timestamp_ = timestamp + now_;
  int priority = e->priority_;

  Event* node = e->prev_;
  int64 nodetime = node->timestamp_;

  while (time <= nodetime) {
    if (time == nodetime) if (priority >= node->priority_) break;

    node = node->prev_;
    nodetime = node->timestamp_;
  }

  Event* nodenext = node->next_;
  e->next_ = nodenext;
  e->prev_ = node;
  nodenext->prev_ = node->next_ = e;
}

void LinkedEventQueue::deleteEvent(Event* p) {
  if (p == newest_) {
    newest_ = newest_->next_;
  }
  Event* next = p->next_;
  Event* prev = p->prev_;
  prev->next_ = next;
  next->prev_ = prev;

  eventpool_.free(p);
}

Event* LinkedEventQueue::createEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id, Event* prev, Event* next) {
  return new (eventpool_.malloc()) Event(timestamp, priority, effect, event_id, prev, next);
}

void LinkedEventQueue::delEvent(Event* p) {
  eventpool_.free(p);
}
















//BinaryEventQueue::BinaryEventQueue(): eventnode_pool_(sizeof(EventNode)),
//                                      root_(0),
//                                      first_(0),
//                                      now_(0) {
//}
//
//BinaryEventQueue::~BinaryEventQueue() {
//}
//
//void BinaryEventQueue::initialize() {
//  root_ = first_ = createEventNode(0, 0);
//}
//
//void BinaryEventQueue::clear() {
//  /*while (first_) {
//    EventNode* del = first_;
//    first_ = first_->next_;
//    deleteEventNode(del);
//  }*/
//}
//
//int64 BinaryEventQueue::now() {
//  return now_;
//}
//
//EventNode* BinaryEventQueue::first() {
//  return first_;
//}
//
//void BinaryEventQueue::pop() {
//  EventNode* old = first_;
//
//  EventNode* p = first_->parent_;
//  if (p) {
//
//    p->left_ = 0;
//
//    EventNode* r = first_->right_;
//    if (r) {
//      p->left_ = first_->right_;
//      r->parent_ = p;
//      first_ = r;
//
//      EventNode* l = first_->left_;
//      while (l) {
//        first_ = l;
//        l = first_->left_;
//      }
//    }
//    else {
//      first_ = p;
//    }
//  }
//  else {
//    first_ = first_->right_;
//    root_ = first_;
//    root_->parent_ = 0;
//
//    EventNode* l = first_->left_;
//    while (l) {
//      first_ = l;
//      l = first_->left_;
//    }
//  }
//
//  now_ = first_->timestamp_;
//  deleteEventNode(old);
//}
//
//void BinaryEventQueue::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id) {
//
//  int64 time = timestamp + now_;
//
//  EventNode* node = root_;
//
//  int64 othertime;
//  while (true) {
//
//    othertime = node->timestamp_;
//
//    if (time > othertime) {
//      if (node->right_) {
//        node = node->right_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->right_ = n;
//        n->highprio_[n->highprio_count_] = effect;
//        n->highprio_event_id_[n->highprio_count_++] = event_id;
//        return;
//      }
//    }
//    else if (time < othertime) {
//      if (node->left_) {
//        node = node->left_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->left_ = n;
//        n->highprio_[n->highprio_count_] = effect;
//        n->highprio_event_id_[n->highprio_count_++] = event_id;
//        return;
//      }
//    }
//    else {
//      node->highprio_[node->highprio_count_] = effect;
//      node->highprio_event_id_[node->highprio_count_++] = event_id;
//      return;
//    }
//  }
//}
//
//void BinaryEventQueue::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id) {
//  int64 time = timestamp + now_;
//
//  EventNode* node = root_;
//
//  int64 othertime;
//  while (true) {
//
//    othertime = node->timestamp_;
//
//    if (time > othertime) {
//
//      EventNode* r = node->right_;
//      if (r) {
//        node = r;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->right_ = n;
//        n->lowprio_[n->lowprio_count_] = effect;
//        n->lowprio_event_id_[n->lowprio_count_++] = event_id;
//        return;
//      }
//    }
//    else if (time < othertime) {
//
//      EventNode* l = node->left_;
//      if (l) {
//        node = l;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->left_ = n;
//        n->lowprio_[n->lowprio_count_] = effect;
//        n->lowprio_event_id_[n->lowprio_count_++] = event_id;
//        return;
//      }
//    }
//    else {
//      node->lowprio_[node->lowprio_count_] = effect;
//      node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//      return;
//    }
//  }
//}
//
//EventNode* BinaryEventQueue::addMhEvent(const int64& mh_speed) {
//  int64 time = mh_speed + now_;
//
//  EventNode* node = root_;
//
//  int64 othertime;
//  while (true) {
//
//    othertime = node->timestamp_;
//
//    if (time > othertime) {
//      if (node->right_) {
//        node = node->right_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->right_ = n;
//        n->mh_attack_ = true;
//        return n;
//      }
//    }
//    else if (time < othertime) {
//      if (node->left_) {
//        node = node->left_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->left_ = n;
//        n->mh_attack_ = true;
//        return n;
//      }
//    }
//    else {
//      node->mh_attack_ = true;
//      return node;
//    }
//  }
//}
//
//EventNode* BinaryEventQueue::addOhEvent(const int64& oh_speed) {
//  int64 time = oh_speed + now_;
//
//  EventNode* node = root_;
//
//  int64 othertime;
//  while (true) {
//
//    othertime = node->timestamp_;
//
//    if (time > othertime) {
//      if (node->right_) {
//        node = node->right_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->right_ = n;
//        n->oh_attack_ = true;
//        return n;
//      }
//    }
//    else if (time < othertime) {
//      if (node->left_) {
//        node = node->left_;
//        continue;
//      }
//      else {
//        EventNode* n = createEventNode(time, 0);
//        n->parent_ = node;
//        node->left_ = n;
//        n->oh_attack_ = true;
//        return n;
//      }
//    }
//    else {
//      node->oh_attack_ = true;
//      return node;
//    }
//  }
//}
//
//EventNode* BinaryEventQueue::createEventNode(const int64& timestamp, EventNode* next) {
//  return new (eventnode_pool_.malloc()) EventNode(timestamp, next);
//}
//
//void BinaryEventQueue::deleteEventNode(EventNode* p) {
//  eventnode_pool_.free(p);
//}



//const int BUCKET_COUNT = 100;
//const int64 BUCKET_RANGE = 100;
//
//
//BucketEventQueue::BucketEventQueue(): eventnode_pool_(sizeof(EventNode)),
//                                      buckets_(0),
//                                      first_(0),
//                                      index_(0),
//                                      now_(0) {
//  buckets_ = new EventNode*[BUCKET_COUNT];
//  for (int i=0; i<BUCKET_COUNT; ++i) {
//    buckets_[i] = 0;
//  }
//}
//
//BucketEventQueue::~BucketEventQueue() {
//  delete[] buckets_;
//}
//
//void BucketEventQueue::initialize() {
//  first_ = buckets_[0] = createEventNode(0, 0);
//}
//
//void BucketEventQueue::clear() {
//  for (int i=0; i<BUCKET_COUNT; ++i) {
//    while (buckets_[i]) {
//      EventNode* del = buckets_[i];
//      buckets_[i] = buckets_[i]->next_;
//      deleteEventNode(del);
//    }
//  }
//}
//
//int64 BucketEventQueue::now() {
//  return now_;
//}
//
//EventNode* BucketEventQueue::first() {
//  return first_;
//}
//
//void BucketEventQueue::pop() {
//  EventNode* old = first_;
//
//  //is the same buckets empty?
//  EventNode* fnext = first_->next_;
//  if (!fnext) {
//    buckets_[index_] = 0;
//  }
//  else { //no, lets see is the other eventnode actually in the same bucket
//    if (fnext->bucket_ == first_->bucket_) {
//      first_ = fnext;
//      now_ = first_->timestamp_;
//      buckets_[index_] = first_;
//      deleteEventNode(old);
//      return;
//    }
//
//    //repair the bucket's first eventnode
//    buckets_[index_] = fnext;
//  }
//    
//  //search from other buckets
//  double bucket = first_->bucket_;
//
//  while (true) {
//    if (index_ == BUCKET_COUNT - 1) {
//      index_ = -1;
//      ++bucket;
//    }
//
//    EventNode* en = buckets_[++index_];
//    if (en && en->bucket_ == bucket) {
//      first_ = en;
//      now_ = first_->timestamp_;
//      deleteEventNode(old);
//      return;
//    }
//  }
//}
//
////all the add***Event() functions work the same way
//void BucketEventQueue::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + timestamp + lag;
//
//  EventNode* node = buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT];
//
//  if (!node) {
//    node = createEventNode(time, 0);
//    node->highprio_[node->highprio_count_] = effect;
//    node->highprio_event_id_[node->highprio_count_++] = event_id;
//    buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = node;
//  }
//  else {
//
//    if (time < node->timestamp_) {
//      EventNode* en = createEventNode(time, node);
//      en->highprio_[en->highprio_count_] = effect;
//      en->highprio_event_id_[en->highprio_count_++] = event_id;
//      buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = en;
//    }
//    else {
//
//      if (time == node->timestamp_) {
//        node->highprio_[node->highprio_count_] = effect;
//        node->highprio_event_id_[node->highprio_count_++] = event_id;
//        return;
//      }
//      else {
//
//        while (node->next_) {
//
//          if (time < node->next_->timestamp_) {
//            break;
//          }
//
//          if (time == node->next_->timestamp_) {
//            node = node->next_;
//            node->highprio_[node->highprio_count_] = effect;
//            node->highprio_event_id_[node->highprio_count_++] = event_id;
//            return;
//          }
//
//          node = node->next_;
//        }
//
//        EventNode* en = createEventNode(time, node->next_);
//        en->highprio_[en->highprio_count_] = effect;
//        en->highprio_event_id_[en->highprio_count_++] = event_id;
//        node->next_ = en;
//      }
//    }
//  }
//}
//
//void BucketEventQueue::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + timestamp + lag;
//
//  EventNode* node = buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT];
//
//  if (!node) {
//    node = createEventNode(time, 0);
//    node->lowprio_[node->lowprio_count_] = effect;
//    node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//    buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = node;
//  }
//  else {
//
//    if (time < node->timestamp_) {
//      EventNode* en = createEventNode(time, node);
//      en->lowprio_[en->lowprio_count_] = effect;
//      en->lowprio_event_id_[en->lowprio_count_++] = event_id;
//      buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = en;
//    }
//    else {
//
//      if (time == node->timestamp_) {
//        node->lowprio_[node->lowprio_count_] = effect;
//        node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//        return;
//      }
//      else {
//
//        while (node->next_) {
//
//          if (time < node->next_->timestamp_) {
//            break;
//          }
//
//          if (time == node->next_->timestamp_) {
//            node = node->next_;
//            node->lowprio_[node->lowprio_count_] = effect;
//            node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//            return;
//          }
//
//          node = node->next_;
//        }
//
//        EventNode* en = createEventNode(time, node->next_);
//        en->lowprio_[en->lowprio_count_] = effect;
//        en->lowprio_event_id_[en->lowprio_count_++] = event_id;
//        node->next_ = en;
//      }
//    }
//  }
//}
//
//EventNode* BucketEventQueue::addMhEvent(const int64& mh_speed) {
//
//  int64 time = now_ + mh_speed;
//
//  EventNode* node = buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT];
//
//  if (!node) {
//    node = createEventNode(time, 0);
//    node->mh_attack_ = true;
//    buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = node;
//    return node;
//  }
//  else {
//
//    if (time < node->timestamp_) {
//      EventNode* en = createEventNode(time, node);
//      en->mh_attack_ = true;
//      buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = en;
//      return en;
//    }
//    else {
//
//      if (time == node->timestamp_) {
//        node->mh_attack_ = true;
//        return node;
//      }
//      else {
//
//        while (node->next_) {
//
//          if (time < node->next_->timestamp_) {
//            break;
//          }
//
//          if (time == node->next_->timestamp_) {
//            node = node->next_;
//            node->mh_attack_ = true;
//            return node;
//          }
//
//          node = node->next_;
//        }
//
//        EventNode* en = createEventNode(time, node->next_);
//        en->mh_attack_ = true;
//        node->next_ = en;
//        return en;
//      }
//    }
//  }
//
//  return 0;
//}
//
//EventNode* BucketEventQueue::addOhEvent(const int64& oh_speed) {
//  int64 time = now_ + oh_speed;
//
//  EventNode* node = buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT];
//
//  if (!node) {
//    node = createEventNode(time, 0);
//    node->oh_attack_ = true;
//    buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = node;
//    return node;
//  }
//  else {
//
//    if (time < node->timestamp_) {
//      EventNode* en = createEventNode(time, node);
//      en->oh_attack_ = true;
//      buckets_[static_cast<unsigned int>((time / BUCKET_RANGE)) % BUCKET_COUNT] = en;
//      return en;
//    }
//    else {
//
//      if (time == node->timestamp_) {
//        node->oh_attack_ = true;
//        return node;
//      }
//      else {
//
//        while (node->next_) {
//
//          if (time < node->next_->timestamp_) {
//            break;
//          }
//
//          if (time == node->next_->timestamp_) {
//            node = node->next_;
//            node->oh_attack_ = true;
//            return node;
//          }
//
//          node = node->next_;
//        }
//
//        EventNode* en = createEventNode(time, node->next_);
//        en->oh_attack_ = true;
//        node->next_ = en;
//        return en;
//      }
//    }
//  }
//
//  return 0;
//}
//
//EventNode* BucketEventQueue::createEventNode(const int64& timestamp, EventNode* next) {
//  EventNode* node = new (eventnode_pool_.malloc()) EventNode(timestamp, next);
//  node->bucket_ = floor(timestamp / (BUCKET_COUNT * BUCKET_RANGE));
//  return node;
//}
//
//void BucketEventQueue::deleteEventNode(EventNode* p) {
//  eventnode_pool_.free(p);
//}
//
//
//
//
//
//
//
//
//
//
//bool PrioritizeEvents::operator()(const Event* e1, const Event* e2) const {
//  if (e1->timestamp_ > e2->timestamp_) return true;
//  if (e1->timestamp_ == e2->timestamp_) return e1->priority_ > e2->priority_;
//  return false;
//}
//
//
//
//HeapEventQueue::HeapEventQueue(): eventpool_(sizeof(Event)),
//                                  now_(0) {
//}
//
//HeapEventQueue::~HeapEventQueue() {
//}
//
//void HeapEventQueue::initialize() {
//  Event* event = createEvent(0, 0, 0, 0);
//  event->valid_ = false;
//  que_.push(event);
//}
//
//void HeapEventQueue::clear() {
//}
//
//int64 HeapEventQueue::now() {
//  return now_;
//}
//
//Event* HeapEventQueue::first() {
//  return que_.top();
//}
//
//void HeapEventQueue::pop() {
//  deleteEvent(que_.top());
//  que_.pop();
//  now_ = que_.top()->timestamp_;
//}
//
//
////different types of Events have own function, its for performance
//Event* HeapEventQueue::addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id) {
//  Event* event = createEvent(now_ + timestamp, priority, effect, event_id);
//  que_.push(event);
//  return event;
//}
//
////gets EventNode from memory pool
//Event* HeapEventQueue::createEvent(const int64& timestamp, const int& priority, Effect* event, const int& event_id) {
//  return new (eventpool_.malloc()) Event(timestamp, priority, event, event_id);
//}
//
//void HeapEventQueue::deleteEvent(Event* p) {
//  eventpool_.free(p);
//}










//BetterEventQueue::BetterEventQueue(): eventnode_pool_(sizeof(EventNode)),
//                                      que_(),
//                                      now_(0) {
//}
//
//BetterEventQueue::~BetterEventQueue() {
//}
//
//void BetterEventQueue::initialize() {
//  //first_ = createEventNode(0, 0);
//  que_[0] = createEventNode(0 ,0);
//}
//
//void BetterEventQueue::clear() {
//  std::map<int64, EventNode*>::iterator& it = que_.begin();
//
//  for (; it != que_.end(); ++it) {
//    deleteEventNode(it->second);
//  }
//}
//
//int64 BetterEventQueue::now() {
//  return now_;
//}
//
//EventNode* BetterEventQueue::first() {
//  return que_.begin()->second;
//}
//
//void BetterEventQueue::pop() {
//  std::map<int64, EventNode*>::iterator& old = que_.begin();
//  deleteEventNode(old->second);
//  que_.erase(old);
//  now_ = que_.begin()->second->timestamp_;
//}
//
////all the add***Event() functions work the same way
//void BetterEventQueue::addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + timestamp + lag;
//
//  std::map<int64, EventNode*>::iterator& it = que_.find(time);
//  if (it != que_.end()) {
//    EventNode* node = it->second;
//    node->highprio_[node->highprio_count_] = effect;
//    node->highprio_event_id_[node->highprio_count_++] = event_id;
//  }
//  else {
//    EventNode* node = createEventNode(time, 0);
//    node->highprio_[node->highprio_count_] = effect;
//    node->highprio_event_id_[node->highprio_count_++] = event_id;
//    que_[time] = node;
//  }
//}
//
//void BetterEventQueue::addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag) {
//
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + timestamp + lag;
//
//  std::map<int64, EventNode*>::iterator& it = que_.find(time);
//  if (it != que_.end()) {
//    EventNode* node = it->second;
//    node->lowprio_[node->lowprio_count_] = effect;
//    node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//  }
//  else {
//    EventNode* node = createEventNode(time, 0);
//    node->lowprio_[node->lowprio_count_] = effect;
//    node->lowprio_event_id_[node->lowprio_count_++] = event_id;
//    que_[time] = node;
//  }
//}
//
//EventNode* BetterEventQueue::addMhEvent(const int64& mh_speed) {
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + mh_speed;
//
//  EventNode* node;
//
//  std::map<int64, EventNode*>::iterator& it = que_.find(time);
//  if (it != que_.end()) {
//    node = it->second;
//    node->mh_attack_ = true;
//  }
//  else {
//    node = createEventNode(time, 0);
//    node->mh_attack_ = true;
//    que_[time] = node;
//  }
//
//  return node;
//}
//
//EventNode* BetterEventQueue::addOhEvent(const int64& oh_speed) {
//  //calculate the events time
//  //timestamp is in relative time so we need add now to get absolute time
//  int64 time = now_ + oh_speed;
//
//  EventNode* node;
//
//  std::map<int64, EventNode*>::iterator& it = que_.find(time);
//  if (it != que_.end()) {
//    node = it->second;
//    node->oh_attack_ = true;
//  }
//  else {
//    node = createEventNode(time, 0);
//    node->oh_attack_ = true;
//    que_[time] = node;
//  }
//
//  return node;
//}
//
//EventNode* BetterEventQueue::createEventNode(const int64& timestamp, EventNode* next) {
//  return new (eventnode_pool_.malloc()) EventNode(timestamp, next);
//}
//
//void BetterEventQueue::deleteEventNode(EventNode* p) {
//  eventnode_pool_.free(p);
//}
