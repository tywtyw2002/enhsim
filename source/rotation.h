//EnhSim - Enhancement Shaman simulator
//Author: Tuomas Välimäki

#ifndef ROTATION
#define ROTATION

#include <string>

class EnhSim;
class Castable;

class Rotation {
  public:
    Rotation(EnhSim* sim): sim(*sim) {};

    virtual void action() = 0;
    bool waitSS_WF();

    EnhSim& sim;
};

class PriorityRotation: public Rotation {
  public:
    PriorityRotation(EnhSim* sim): Rotation(sim) {};

    virtual void action();
};

class GenericRotationNode {
  public:
    GenericRotationNode(): items_(0), skip_(false) {};

    bool action();
    bool skip() { return skip_; };
    void addItem(const std::string& item);

    Castable* items_;
    int item_count_;
    float** arguments_;
    bool skip_;
};

class GenericRotation: public Rotation {
  public:
    GenericRotation(EnhSim* sim): Rotation(sim), nodes_(0), node_count_(0) {};

    virtual void action();
    void addNode(const std::string& node);

    GenericRotationNode* nodes_;
    int node_count_;
};

// class FS_ES_Rotation: public Rotation {
//  public:
//    FS_ES_Rotation(EnhSim* sim): Rotation(sim) {};

//    virtual void action();
// };

// class ES_Rotation: public Rotation {
//  public:
//    ES_Rotation(EnhSim* sim): Rotation(sim) {};

//    virtual void action();
// };

// class FS_Rotation: public Rotation {
//  public:
//    FS_Rotation(EnhSim* sim): Rotation(sim) {};

//    virtual void action();
// };

// class Frost_Rotation: public Rotation {
//  public:
//    Frost_Rotation(EnhSim* sim): Rotation(sim) {};

//    virtual void action();
// };

// class SS_Rotation: public Rotation {
//  public:
//    SS_Rotation(EnhSim* sim): Rotation(sim) {};

//    virtual void action();
// };

#endif
