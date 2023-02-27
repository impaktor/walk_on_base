#include "npc.h"
#include "npcstates.h"
#include "statemachine.h"
#include "tiledmap.h"


NPC::NPC(Sprite *sprite):
  Character(sprite){

  // initiate state of AI
  m_pStateMachine = new StateMachine<NPC>(this);
  m_pStateMachine->SetCurrentState(GoToBar::Instance());
  // m_pStateMachine->SetGlobalState(Toilet::Panic());

  // temporary: move to center of map
  mTargetPos.x = int(128/2);
  mTargetPos.y = int(128/2);

  bladder = 0.0;
}

NPC::~NPC(){
  delete m_pStateMachine;
}

void NPC::update(){

  // So stuff that NPC needs to do, e.g.
  // fatigue++

  // Update state
  m_pStateMachine->Update();
}


StateMachine<NPC>* NPC::GetFSM() const{
  return m_pStateMachine;
}

int sign(int x){
  return (x > 0) - (x < 0);
}
