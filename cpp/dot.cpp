#include <iostream>
#include "dot.h"
#include "character.h"
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


Dot::Dot(Sprite *sprite):
  Character(sprite){

  //Initialize the offsets
  mPos.x = 32;
  mPos.y = 32;

  // Don't print debug each tick, just each event
  mEvent = true;
}


void Dot::handleEvent(SDL_Event &event){
  int step = mTileSize;

  // Suggest new position
  if(event.type == SDL_KEYDOWN){
    switch(event.key.keysym.sym){
    case SDLK_UP:
      mPos.y -= step;
      break;
    case SDLK_DOWN:
      mPos.y += step;
      break;
    case SDLK_LEFT:
      mPos.x -= step;
      break;
    case SDLK_RIGHT:
      mPos.x += step;
      break;
    }
    mEvent = true;
  }
}


void Dot::move(TiledMap &map){

  Character::move(map);

  // Only print keypress if it was updated:
  if (mEvent){
    std::cout << "\r" << mPos << "; " << std::flush;
    // don't need to print this event more (until next event)
    mEvent = false;
  }
}


void Dot::setCamera(SDL_Rect &camera, const TiledMap &map){
  // size of a tile, w x h
  vec tile = map.get_tile_size();

  // map coordinate to pixel
  int w = map.getWidth() * tile.x;
  int h = map.getHeight() * tile.y;

  //Center the camera over the dot
  camera.x = (mPos.x + tile.x / 2)  - camera.w / 2;
  camera.y = (mPos.y + tile.y / 2) - camera.h / 2;

  //Keep the camera in bounds
  if(camera.x < 0)
    camera.x = 0;
  if(camera.y < 0)
    camera.y = 0;
  if(camera.x > w - camera.w)
    camera.x = w - camera.w;
  if(camera.y > h - camera.h)
    camera.y = h - camera.h;
}
