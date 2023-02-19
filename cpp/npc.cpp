#include <iostream>
#include <iterator>
#include "character.h"
#include "npc.h"
#include "tiledmap.h"


NPC::NPC(Sprite *sprite):
  Character(sprite){

  srand(0);

  // temporary: move to center of map
  mTargetPos.x = int(128/2);
  mTargetPos.y = int(128/2);
}


int NPC::random_int(int max){
  return rand() % max;
}


void NPC::set_new_target(){
  // pick random point on map to move to
}


int sign(int x){
  return (x > 0) - (x < 0);
}
