EnhSim source

EnhSim is the main class of this simulator. Simulation happens in simulate() function. There is an linked list of events named timeline_. Timeline contains next tick which has events and during simulation, we loop and update timeline until desired duration is achieved. 

Timeline is of type EventNode, which represents a single tick. Tick contains high priority events, which are executed before mh and oh swings, mh and oh swings and low priority events, which are executed after mh and oh swings.

During for example, mh swing, roll is made and tested against attack table and appropriate action is taken. There are also procs called on different events like swing, hit, crit, yellow hit etc. These procs are registered to these events during initialization of the simulation with useEffect() function.

All the talents, skills, weapon enchants etc are of a base class type Effect. Effect have function proc() and event(). If you register an effect to happen on a certain event, the proc function is called. If you add an effect to event queue, at the desired time, the event() function is called.

To register an effect to an proc event, you have to overload some functions in the effect to return true instead of default false. See effects.h to see for yourself.