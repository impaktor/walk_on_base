#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tiledmap.h"
#include "sprite.h"

// A class of movable dot, with separating axis collision detection, from
// http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php

class Character{
public:
  //Initializes the variables
  Character(Sprite *sprite, int level_height, int level_width);

  //Moves the dot and checks collision against tiles
  //void move(Tile *tiles[]);
  void move(TiledMap &map);

  void render(SDL_Renderer *renderer, SDL_Rect &camera);

  int getPosX() const {
    return mPosX;
  }

  int getPosY() const {
     return mPosY;
  }

protected:
  //Collision box for dot
  SDL_Rect mCollisionBox;

  Sprite sprite;

  //The X and Y offsets of the dot
  int mPosX, mPosY;

  // in pixels, total map size:
  int mLevelHeight;
  int mLevelWidth;

  int mOldPosX, mOldPosY;

  // number of pixels for a tile (assume square, W = H)
  int mTileSize;
};

#endif
