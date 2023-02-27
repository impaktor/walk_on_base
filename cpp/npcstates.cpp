#include "npcstates.h"
#include <iostream>
#include <cstdlib>

GoToBar* GoToBar::Instance(){
  static GoToBar instance;
  return &instance;
}

void GoToBar::Enter(NPC* npc){
  std::cout << "Enter bar" << "\n";

  // if not on bar-stool, move to bar-stool, and update location when
  // done so.
}


void GoToBar::Update(NPC* npc){
  std::cout << "update bladder: " << npc->bladder << "\n";

  float r = std::rand() / (float)RAND_MAX;
  // std::cout << "r: " << r <<"\n";
  npc->bladder += r;

  if (npc->bladder > 40.0){
    npc->GetFSM()->ChangeState(Toilet::Instance());
  }
}

void GoToBar::Exit(NPC* npc){
  std::cout << "exit bar, bladder: " << npc->bladder << "\n";

  // pay bartender?
}



Toilet* Toilet::Instance(){
  static Toilet instance;
  return &instance;
}

void Toilet::Enter(NPC* npc){
  std::cout << "enter loo, bladder: " << npc->bladder << "\n";
}

void Toilet::Update(NPC* npc){
  std::cout << "urinating: " << npc->bladder << "\n";

  npc->bladder -= 0.5;

  if (npc->bladder <= 0.0)
    npc->GetFSM()->ChangeState(GoToBar::Instance());
}

void Toilet::Exit(NPC* npc){
  std::cout << "exit loo, bladder: " << npc->bladder << "\n";
}
