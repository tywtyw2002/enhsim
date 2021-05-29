//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef EVENTQUEUE
#define EVENTQUEUE

#include "globalutil.h"
#include "event.h"
#include <boost/pool/pool.hpp>
//#include <boost/pool/pool_alloc.hpp>

//class EventNode;

//class SimpleEventQueue {
//  public:
//    SimpleEventQueue();
//    ~SimpleEventQueue();
//
//    void initialize();
//    void clear();
//    int64 now();
//    EventNode* first();
//    void pop();
//
//    //different types of Events have own function, its for performance
//    void addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id);
//    void addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id);
//    //void addLowestPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0);
//    EventNode* addMhEvent(const int64& mh_speed);
//    EventNode* addOhEvent(const int64& oh_speed);
//
//  private:
//    //gets EventNode from memory pool
//    EventNode* createEventNode(const int64& timestamp, EventNode* next);
//    //return EventNode to memory pool
//    void deleteEventNode(EventNode* p);
//
//    //memory pool for eventnodes
//    boost::pool<> eventnode_pool_;
//    EventNode* first_;
//    int64 now_;
//};

class LinkedEventQueue {
  public:
    LinkedEventQueue();
    ~LinkedEventQueue();

    void initialize();
    void clear();
    int64 now() const { return now_; };
    Event& first() const { return *(root_->next_); };
    void pop();
    void start();

    void addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id);
    void addEvent(Event*& e, const int64& timestamp, const int& priority, Effect* effect, const int& event_id);
    void moveEvent(Event*& e, const int64& timestamp);
    void moveEventSearchForward(Event*& e, const int64& timestamp);
    void moveEventSearchBackward(Event*& e, const int64& timestamp);

    void deleteEvent(Event* p);

  private:
    //gets EventNode from memory pool
    Event* createEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id, Event* prev, Event* next);
    //return EventNode to memory pool
    void delEvent(Event* p);

    //memory pool for eventnodes
    boost::pool<> eventpool_;
    Event* root_;
    Event* last_;
    Event* newest_;
    int64 now_;
};

//class BinaryEventQueue {
//  public:
//    BinaryEventQueue();
//    ~BinaryEventQueue();
//
//    void initialize();
//    void clear();
//    int64 now();
//    EventNode* first();
//    void pop();
//
//    //different types of Events have own function, its for performance
//    void addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id);
//    void addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id);
//    //void addLowestPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0);
//    EventNode* addMhEvent(const int64& mh_speed);
//    EventNode* addOhEvent(const int64& oh_speed);
//
//  private:
//    //gets EventNode from memory pool
//    EventNode* createEventNode(const int64& timestamp, EventNode* next);
//    //return EventNode to memory pool
//    void deleteEventNode(EventNode* p);
//
//    //memory pool for eventnodes
//    boost::pool<> eventnode_pool_;
//    EventNode* root_;
//    EventNode* first_;
//    int64 now_;
//};

//class BucketEventQueue {
//  public:
//    BucketEventQueue();
//    ~BucketEventQueue();
//
//    void initialize();
//    void clear();
//    int64 now();
//    EventNode* first();
//    void pop();
//
//    //different types of Events have own function, its for performance
//    void addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag);
//    void addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag);
//    //void addLowestPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0);
//    EventNode* addMhEvent(const int64& mh_speed);
//    EventNode* addOhEvent(const int64& oh_speed);
//
//  private:
//    //gets EventNode from memory pool
//    EventNode* createEventNode(const int64& timestamp, EventNode* next);
//    //return EventNode to memory pool
//    void deleteEventNode(EventNode* p);
//
//    //memory pool for eventnodes
//    boost::pool<> eventnode_pool_;
//    EventNode** buckets_;
//    EventNode* first_;
//    int index_;
//    int64 now_;
//};
//
//class Event {
//  public:
//    Event(const int64& timestamp, const int& priority, Effect* event, const int& event_id):
//          timestamp_(timestamp),
//          priority_(priority),
//          event_(event),
//          event_id_(event_id),
//          valid_(true) {};
//
//    int64 timestamp_;
//    int priority_;
//
//    Effect* event_;
//    int event_id_;
//
//    bool valid_;
//};
//
//
//
//class PrioritizeEvents {
//  public:
//    bool operator()(const Event* e1, const Event* e2) const;
//};
//
//
//class HeapEventQueue {
//  public:
//    HeapEventQueue();
//    ~HeapEventQueue();
//
//    void initialize();
//    void clear();
//    int64 now();
//    Event* first();
//    void pop();
//
//    //different types of Events have own function, its for performance
//    Event* addEvent(const int64& timestamp, const int& priority, Effect* effect, const int& event_id);
//
//  private:
//    //gets EventNode from memory pool
//    Event* createEvent(const int64& timestamp, const int& priority, Effect* event, const int& event_id);
//    //return EventNode to memory pool
//    void deleteEvent(Event* p);
//
//    //memory pool for eventnodes
//    boost::pool<> eventpool_;
//    std::priority_queue<Event*, std::vector<Event*, boost::fast_pool_allocator<Event*, boost::default_user_allocator_new_delete, boost::details::pool::default_mutex, 128> >, PrioritizeEvents> que_;
//    int64 now_;
//};

//class BetterEventQueue {
//  public:
//    BetterEventQueue();
//    ~BetterEventQueue();
//
//    void initialize();
//    void clear();
//    int64 now();
//    EventNode* first();
//    void pop();
//
//    //different types of Events have own function, its for performance
//    void addHighPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag);
//    void addLowPrioEvent(const int64& timestamp, Effect* effect, const int& event_id, const int64& lag);
//    //void addLowestPrioEvent(const int64& timestamp, Effect* effect, const int& event_id = 0);
//    EventNode* addMhEvent(const int64& mh_speed);
//    EventNode* addOhEvent(const int64& oh_speed);
//
//  private:
//    //gets EventNode from memory pool
//    EventNode* createEventNode(const int64& timestamp, EventNode* next);
//    //return EventNode to memory pool
//    void deleteEventNode(EventNode* p);
//
//    //memory pool for eventnodes
//    boost::pool<> eventnode_pool_;
//    std::priority_queue<EventNode que_;
//    int64 now_;
//};

#endif
