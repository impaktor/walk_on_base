#ifndef STATE_H
#define STATE_H

template<class entity_type>
class State{
public:

  virtual ~State(){}

  // enter sate, i.e. initialize the state
  virtual void Enter(entity_type*) = 0;

  // Execute in the state, must be able to change state
  virtual void Update(entity_type*) = 0;

  // exit states, e.g. for freeing memory
  virtual void Exit(entity_type*) = 0;

};

#endif
