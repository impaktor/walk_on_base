#ifndef NPCSTATES_H
#define NPCSTATES_H

#include "npc.h"
#include "state.h"


// Starting state
class Null : public State<NPC>
{
private:

  Null(){}

  //copy ctor and assignment should be private
  Null(const Null&);
  Null& operator=(const Null&);

public:

  //this is a singleton
  static Null* Instance();

  virtual void Enter(NPC* npc);

  virtual void Update(NPC* npc);

  virtual void Exit(NPC* npc);
};



// Bar state: go to table, and drink, until bladder is full, then go
// to the toilet:
class GoToBar : public State<NPC>
{
private:

  GoToBar(){}

  //copy ctor and assignment should be private
  GoToBar(const GoToBar&);
  GoToBar& operator=(const GoToBar&);

public:

  //this is a singleton
  static GoToBar* Instance();

  virtual void Enter(NPC* npc);

  virtual void Update(NPC* npc);

  virtual void Exit(NPC* npc);
};


// Go to toilet and empty bladder.
// Then go back to bar state.
class Toilet : public State<NPC>
{
private:

  Toilet(){}

  //copy ctor and assignment should be private
  Toilet(const Toilet&);
  Toilet& operator=(const Toilet&);

public:

  //this is a singleton
  static Toilet* Instance();

  virtual void Enter(NPC* npc);

  virtual void Update(NPC* npc);

  virtual void Exit(NPC* npc);
};



// Wander randomly about, premier long distances
class Wanderlust : public State<NPC>
{
private:

  Wanderlust(){}

  //copy ctor and assignment should be private
  Wanderlust(const Wanderlust&);
  Wanderlust& operator=(const Wanderlust&);

public:

  //this is a singleton
  static Wanderlust* Instance();

  virtual void Enter(NPC* npc);

  virtual void Update(NPC* npc);

  virtual void Exit(NPC* npc);
};

#endif
