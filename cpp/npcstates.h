#ifndef NPCSTATES_H
#define NPCSTATES_H

#include "npc.h"
#include "state.h"


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



#endif
