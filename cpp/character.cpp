#include <iostream>
#include "character.h"
#include "common.h"


Character::Character(Sprite *sprite, int level_height, int level_width):
  sprite{*sprite}, mLevelHeight{level_height}, mLevelWidth{level_width}
{

  //Initialize the offsets
  mPos.x = 32;
  mPos.y = 64;

  // XXX tmp:
  mTileSize=32;

  mOldPos = mPos;

  //Collision box dimensions
  mCollisionBox.w = mTileSize;
  mCollisionBox.h = mTileSize;
}


//void Character::move(Tile *tiles[]){
void Character::move(TiledMap &map){
  mCollisionBox.x = mPos.x;

  int width = mTileSize;
  int height = mTileSize;

  bool isCollision = map.isCollision(mPos);

  //If the dot went too far to the left or right
  if((mPos.x < 0) || (mPos.x + width > mLevelWidth) || isCollision){
    //Move back
    mPos.x = mOldPos.x;
    mCollisionBox.x = mPos.x;
  }
  else
    mOldPos.x = mPos.x;

  mCollisionBox.y = mPos.y;

  //If the dot went too far up or down
  if((mPos.y < 0) || (mPos.y + height > mLevelHeight) || isCollision){
    //Move back
    mPos.y = mOldPos.y;
    mCollisionBox.y = mPos.y;
  }
  else
    mOldPos.y = mPos.y;
}


void Character::render(SDL_Renderer *renderer, SDL_Rect &camera){
  //Show the object, relative the camera
  sprite.render(renderer, mPos.x - camera.x, mPos.y - camera.y);
}
