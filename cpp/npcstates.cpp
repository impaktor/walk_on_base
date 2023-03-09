#include "npcstates.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include "vector2.h"
#include "tiledmap.h"
#include <SDL2/SDL_timer.h>


Null* Null::Instance(){
  static Null instance;
  return &instance;
}

void Null::Enter(NPC* npc [[maybe_unused]]){
}

void Null::Update(NPC* npc){
  npc->GetFSM()->ChangeState(GoToBar::Instance());
}

void Null::Exit(NPC* npc [[maybe_unused]]){
}



GoToBar* GoToBar::Instance(){
  static GoToBar instance;
  return &instance;
}

void GoToBar::Enter(NPC* npc){
  std::cout << "Enter bar" << "\n";

  vec bar_destination = {160, 256};
  if (not (npc->getPos() == bar_destination)){
    std::cout << "Not on bar stool -> moving there" << "\n";
    npc->SetPath(bar_destination);
  }
}


void GoToBar::Update(NPC* npc){
  // if not at destination, move:
  if (npc->mPath.size() > 0){
    npc->move();
  }
  else{
    Uint32 t = SDL_GetTicks();
    if (t % 30){
      // if at destination, drink!
      std::cout << "drinking, bladder: " << npc->bladder << "\n";
      float r = std::rand() / (float)RAND_MAX;
      npc->bladder += r;
    }
  }

  // if bladder is full, go to the loo!
  if (npc->bladder > 50.0){
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

  vec destination = {36, 1};
  if (not (npc->getPos() == destination)){
    std::cout << "Not on bar stool -> moving there" << "\n";
    npc->SetPath(destination);
  }
}

void Toilet::Update(NPC* npc){
  if (npc->mPath.size() > 0){
    npc->move();
  }
  else{
    Uint32 t = SDL_GetTicks();
    if (t % 30){
      std::cout << "urinating, bladder: " << npc->bladder << "\n";
      npc->bladder -= 0.5;
    }
  }
  if (npc->bladder <= 0.0)
    npc->GetFSM()->ChangeState(GoToBar::Instance());
}

void Toilet::Exit(NPC* npc){
  std::cout << "exit loo, bladder: " << npc->bladder << "\n";
}



Wanderlust* Wanderlust::Instance(){
  static Wanderlust instance;
  return &instance;
}

void Wanderlust::Enter(NPC* npc){
  std::cout << "Finding a place to walk to: ";

  int w = npc->map->getWidth();
  int h = npc->map->getHeight();
  bool try_again = true;
  vec destination;

  int i = 0;
  while (try_again) {
    int x = float(w) * std::rand() / (float)RAND_MAX;
    int y = float(h) * std::rand() / (float)RAND_MAX;
    destination = {x, y};
    std::cout << i << " " << destination << std::endl;
    ++i;

    if (not npc->map->isCollision(destination))
      try_again = false;
  }
  std::cout << destination << " tries: " << i << "\n";

  npc->SetPath(destination);
}

void Wanderlust::Update(NPC* npc){
  if (npc->mPath.size() > 0){
    npc->move();
  }
  else
    npc->GetFSM()->ChangeState(Wanderlust::Instance());
}

void Wanderlust::Exit(NPC* npc [[maybe_unused]]){
  std::cout << "Reached goal: " << "\n";
}
