#include <iostream>
#include <iterator>
#include "character.h"
#include "npc.h"
#include "tiledmap.h"


NPC::NPC(Texture *texture, int level_height, int level_width):
  Character(texture, level_height, level_width){

  srand(0);

  // temporary: move to center of map
  mTargetPosX = int(mLevelWidth/2);
  mTargetPosY = int(mLevelHeight/2);
}


int NPC::random_int(int max){
  return rand() % max;
}


void NPC::set_new_target(){
  // pick random point on map to move to
  mTargetPosX = random_int(mLevelWidth);
  mTargetPosY = random_int(mLevelHeight);
}


int sign(int x){
  return (x > 0) - (x < 0);
}
