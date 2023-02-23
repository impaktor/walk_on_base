#include <iostream>
#include "character.h"
#include "common.h"


Character::Character(Sprite *sprite):
  sprite{*sprite}
{
  thisID = ++ID;

  //Initialize the offsets
  mPos.x = 32;
  mPos.y = 64;

  // XXX tmp:
  mTileSize=32;

  mOldPos = mPos;
}


void Character::move(TiledMap &map){

  bool isCollision = map.isCollision(mPos);

  // if no coordinate change, don't move:
  if (mPos == mOldPos)
    return;

  //If the dot went too far to the left or right
  if(!map.isOnMap(mPos))
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


void Character::render(SDL_Renderer *renderer, SDL_Rect &camera){
  //Show the object, relative the camera
  sprite.render(renderer, mPos.x - camera.x, mPos.y - camera.y);
}
