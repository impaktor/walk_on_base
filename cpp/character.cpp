#include <iostream>
#include "character.h"
#include "common.h"


Character::Character(Texture *texture, int level_height, int level_width):
  mTexture{texture}, mLevelHeight{level_height}, mLevelWidth{level_width}
{
  assert(mTexture != nullptr);

  //Initialize the offsets
  mPosX = 32;
  mPosY = 64;

  // XXX tmp:
  mTileSize=32;

  // The dimensions of _one_ dot. (The sprite sheet has 2x2 dots)
  int clipW = 32;
  int clipH = 32;

  //Setup the clips for our image
  for(int i = 0; i < 4; ++i){
    mClips[i].x = i / 2 * clipW;
    mClips[i].y = i % 2 * clipH;
    mClips[i].w = clipW;
    mClips[i].h = clipH;
  }

  mUseClip = 2;

  mOldPosX = mPosX;
  mOldPosY = mPosY;

  //Collision box dimensions
  mCollisionBox.w = mTileSize;
  mCollisionBox.h = mTileSize;
}


//void Character::move(Tile *tiles[]){
void Character::move(TiledMap &map){
  mCollisionBox.x = mPosX;

  int width = mTileSize;
  int height = mTileSize;

  bool isCollision = map.isCollision(mPosX, mPosY);

  //If the dot went too far to the left or right
  if((mPosX < 0) || (mPosX + width > mLevelWidth) || isCollision){
    //Move back
    mPosX = mOldPosX;
    mCollisionBox.x = mPosX;
  }
  else
    mOldPosX = mPosX;

  mCollisionBox.y = mPosY;

  //If the dot went too far up or down
  if((mPosY < 0) || (mPosY + height > mLevelHeight) || isCollision){
    //Move back
    mPosY = mOldPosY;
    mCollisionBox.y = mPosY;
  }
  else
    mOldPosY = mPosY;
}


void Character::render(SDL_Renderer *renderer, SDL_Rect &camera){
  //Show the object, relative the camera
  mTexture->render(renderer, mPosX - camera.x, mPosY - camera.y, &mClips[mUseClip]);
}
