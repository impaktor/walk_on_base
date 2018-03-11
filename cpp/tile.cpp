#include "tile.h"
#include "common.h"

Tile::Tile(int x, int y, int tileType, Texture *tileTexture){
  //Get the offsets
  mBox.x = x;
  mBox.y = y;

  mTileTexture = tileTexture;

  //Set the collision box
  mBox.w = TILE_WIDTH;
  mBox.h = TILE_HEIGHT;

  //Get the tile type
  mType = tileType;
}

void Tile::render(SDL_Renderer *renderer, SDL_Rect &camera, SDL_Rect tileClips[]){
  //If the tile is on screen
  if(checkCollision(camera, mBox)){
    //Show the tile
    mTileTexture->render(renderer, mBox.x - camera.x, mBox.y - camera.y, &tileClips[mType]);
  }
}
