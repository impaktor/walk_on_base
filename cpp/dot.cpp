#include <iostream>
#include <sstream>
#include "dot.h"
#include "character.h"
#include "common.h"
#include "imgui/imgui.h"


Dot::Dot(Sprite *sprite, vec start_pos, TiledMap* map):
  Character(sprite, map){

  //Initialize the offsets
  mPos.x = start_pos.x;
  mPos.y = start_pos.y;

  // Don't print debug each tick, just each event
  mEvent = true;
}

Dot::Dot(Sprite *sprite, const SDL_Rect& start_pos, TiledMap* map):
  Character(sprite, map){
  Dot(sprite, vec{start_pos.x, start_pos.y}, map);
}

void Dot::handleEvent(SDL_Event &event){

  // Suggest new position
  if(event.type == SDL_KEYDOWN){
    switch(event.key.keysym.sym){
    case SDLK_UP:
      mPos.y--;
      break;
    case SDLK_DOWN:
      mPos.y++;
      break;
    case SDLK_LEFT:
      mPos.x--;
      break;
    case SDLK_RIGHT:
      mPos.x++;
      break;
    }
    mEvent = true;
  }
}


void Dot::update(){

  Character::update();

  // Only print keypress if it was updated:
  if (mEvent){
    std::cout << "\r" << mPos << "; " << std::flush;
    // don't need to print this event more (until next event)
    mEvent = false;
  }
}
