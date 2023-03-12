#include <iostream>
#include "character.h"
#include "common.h"
#include "imgui/imgui.h"
#include <SDL2/SDL_timer.h>


Character::Character(Sprite *sprite, TiledMap *tilemap):
  sprite{*sprite}
{
  thisID = ++ID;

  mPos.x = 3;
  mPos.y = 4;

  mOldPos = mPos;

  mLastUpdate = SDL_GetTicks();

  map = tilemap;
}


void Character::update(){

  bool isCollision = map->isCollision(mPos);

  // if no coordinate change, don't move:
  if (mPos == mOldPos)
    return;

  //If the dot went too far to the left or right
  if(!map->isOnMap(mPos))
    isCollision = true;

  if(mOldPos.y < mPos.y)
    sprite.facing = Sprite::down;
  else if(mOldPos.y > mPos.y)
    sprite.facing = Sprite::up;
  else if(mOldPos.x < mPos.x)
    sprite.facing = Sprite::right;
  else if(mOldPos.x > mPos.x)
    sprite.facing = Sprite::left;

  if(isCollision){
    // move back
    mPos = mOldPos;
  }
  else{
    // move, and update old pos
    mOldPos = mPos;
  }
}


void Character::render(SDL_Renderer *renderer, const SDL_Rect &camera){
  //Show the object, relative the camera

  vec screen_pos = map->get_screen_pos(mPos);

  sprite.render(renderer, screen_pos.x - camera.x, screen_pos.y - camera.y);

  std::ostringstream stream;
  stream << "ID: " << thisID << " x,y: " << mPos << " facing: " << sprite.facing;

  if(ImGui::Begin("Debug##1")){
    ImGui::Text("%s", stream.str().c_str());
  }
  ImGui::End();
}
