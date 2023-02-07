#include <iostream>
#include "dot.h"
#include "common.h"


//Checks collision box against set of tiles
bool touchesWall(const SDL_Rect &box /*, Tile* tiles[]*/){
  // The touchesWall function checks a given collision box against
  // tiles of type TILE_CENTER, TILE_TOP, TILE_TOPRIGHT, TILE_RIGHT,
  // TILE_BOTTOMRIGHT, TILE_BOTTOM, TILE_BOTTOMLEFT, TILE_LEFT, and
  // TILE_TOPLEFT which are all wall tiles. If you check back when we
  // defined these constants, you'll see that these are numbered right
  // next to each other so all we have to do is check if the type is
  // between TILE_CENTER and TILE_TOPLEFT.

  // //Go through the tiles
  // for(int i = 0; i < TOTAL_TILES; ++i){
  //   //If the tile is a wall type tile
  //   if((tiles[i]->getType() >= TILE_CENTER) && (tiles[i]->getType() <= TILE_TOPLEFT)){
  //     //If the collision box touches the wall tile
  //     if(checkCollision(box, tiles[i]->getBox()))
  //       return true;
  //   }
  // }

  //If no wall tiles were touched
  return false;
}



Dot::Dot(Texture *texture, int level_height, int level_width){

  mTexture = texture;
  assert(mTexture != nullptr);

  mLevelHeight = level_height;
  mLevelWidth = level_width;

  //Initialize the offsets
  mPosX = 0;
  mPosY = 0;

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

  mUseClip = 0;

  mOldPosX = 0;
  mOldPosY = 0;

  //Collision box dimensions
  mCollisionBox.w = mTileSize;
  mCollisionBox.h = mTileSize;

  // Don't print debug each tick, just each event
  mEvent = true;
}

void Dot::handleEvent(SDL_Event &event){
  int step = mTileSize;

  // Suggest new position
  if(event.type == SDL_KEYDOWN){
    switch(event.key.keysym.sym){
    case SDLK_UP:    mPosY -= step; break;
    case SDLK_DOWN:  mPosY += step; break;
    case SDLK_LEFT:  mPosX -= step; break;
    case SDLK_RIGHT: mPosX += step; break;

    case SDLK_1: mUseClip = 0; break;
    case SDLK_2: mUseClip = 1; break;
    case SDLK_3: mUseClip = 2; break;
    case SDLK_4: mUseClip = 3; break;
    }
    mEvent = true;
  }
}


//void Dot::move(Tile *tiles[]){
void Dot::move(){
  mCollisionBox.x = mPosX;

  int width = mTileSize;
  int height = mTileSize;

  //If the dot went too far to the left or right
  if((mPosX < 0) || (mPosX + width > mLevelWidth) ||
     touchesWall(mCollisionBox /*, tiles*/)){
    //Move back
    mPosX = mOldPosX;
    mCollisionBox.x = mPosX;
  }
  else
    mOldPosX = mPosX;

  mCollisionBox.y = mPosY;

  //If the dot went too far up or down
  if((mPosY < 0) || (mPosY + height > mLevelHeight) ||
     touchesWall(mCollisionBox /*, tiles*/)){
    //Move back
    mPosY = mOldPosY;
    mCollisionBox.y = mPosY;
  }
  else
    mOldPosY = mPosY;

  // Only print keypress if it was updated:
  if (mEvent){
    std::cout << "\r" << "dot-x " << mPosX << ", dot-y " <<  mPosY << "; "
              << mLevelWidth << "," << mLevelHeight << std::flush;
    // don't need to print this event more (until next event)
    mEvent = false;
  }
}


void Dot::setCamera(SDL_Rect &camera){
  int width = mTileSize;
  int height = mTileSize;

  //Center the camera over the dot
  camera.x = (mCollisionBox.x + width / 2)  - WINDOW_WIDTH / 2;
  camera.y = (mCollisionBox.y + height / 2) - WINDOW_HEIGHT / 2;

  //Keep the camera in bounds
  if(camera.x < 0)
    camera.x = 0;
  if(camera.y < 0)
    camera.y = 0;
  if(camera.x > mLevelWidth - camera.w)
    camera.x = mLevelWidth - camera.w;
  if(camera.y > mLevelHeight - camera.h)
    camera.y = mLevelHeight - camera.h;
}


void Dot::render(SDL_Renderer *renderer, SDL_Rect &camera){
  //Show the dot, relative the camera
  mTexture->render(renderer, mPosX - camera.x, mPosY - camera.y, &mClips[mUseClip]);
}
