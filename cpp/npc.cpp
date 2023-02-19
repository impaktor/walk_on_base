#include <iostream>
// #include <iterator>
#include "astar/AStar.h"
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

/*
void NPC::AI(Uint32 tick, TiledMap &map){
  if(tick % 500 == 0){
    std::cout << "tick " << tick << std::endl;

    int step = mTileSize;

    if(mPath.empty()){
      mPath = map.getPath({mPos.x/mTileSize, mPos.y/mTileSize},
                         {mTargetPos.x/mTileSize, mTargetPos.y/mTileSize});
      std::cout << "Populated path vector" << std::endl;
    }

    AStar::Vec2i coordinate = mPath.back();
    mPath.pop_back();
    std::cout << "AI old: " << mPos.x << ", " << mPos.y
              << " coord: " << coordinate.x << ", " << coordinate.y << std::endl;
    mPos.x = step * coordinate.x;
    mPos.y = step * coordinate.y;
    std::cout << "AI new: " << mPos.x << " " << mPos.y
              << " target: " << mTargetPos.x << ", " << mTargetPos.x << std::endl;
  }
}
*/
