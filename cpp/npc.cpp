#include <iostream>
#include <ostream>
// #include <iterator>
#include "astar/AStar.h"
#include "npc.h"
#include "npcstates.h"
#include "statemachine.h"
#include "tiledmap.h"


NPC::NPC(Sprite *sprite, TiledMap *map):
  Character(sprite, map){

  // initiate state of AI
  m_pStateMachine = new StateMachine<NPC>(this);
  m_pStateMachine->SetCurrentState(Wanderlust::Instance());
  // m_pStateMachine->SetGlobalState(Panic::Instance());

  // Milliseconds between each move
  mInvSpeed = 300;

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


void NPC::SetPath(vec destination){
  int step = mTileSize;

  if(mPath.empty()){
    mPath = map->getPath(mPos/step, destination/step);
    // debug print out:
    std::cout << "Populated path vector: ";
    for(size_t i=0; i < mPath.size(); i++){
      std::cout << i << ": " << mPath[i] << " -> ";
    }
    std::cout << std::endl;
  }
}


void NPC::move(){
  int step = mTileSize;

  Uint32 t_current = SDL_GetTicks();

  // miliseconds since last update
  Uint32 dt = (t_current - mLastUpdate);

  // Do one move each mInvSpeed ms
  if (dt > mInvSpeed){
    AStar::Vec2i coordinate = mPath.back();
    mPath.pop_back();

    mPos = coordinate * step;
    std::cout << "moving to: " << mPos << "\n";

    mLastUpdate = t_current;
  }
  // update sprite facing direction
  Character::update();
}
