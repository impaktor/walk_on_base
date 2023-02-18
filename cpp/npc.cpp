#include <iostream>
#include <iterator>
#include "character.h"
#include "npc.h"
#include "tiledmap.h"


NPC::NPC(Sprite *sprite, int level_height, int level_width):
  Character(sprite, level_height, level_width){

  srand(0);

  // temporary: move to center of map
  mTargetPos.x = int(mLevelWidth/2);
  mTargetPos.y = int(mLevelHeight/2);
}


int NPC::random_int(int max){
  return rand() % max;
}


void NPC::set_new_target(){
  // pick random point on map to move to
  mTargetPos.x = random_int(mLevelWidth);
  mTargetPos.y = random_int(mLevelHeight);
}


int sign(int x){
  return (x > 0) - (x < 0);
}
