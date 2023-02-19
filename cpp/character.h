#ifndef CHARACTER_H
#define CHARACTER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tiledmap.h"
#include "vector2.h"
#include "sprite.h"

// A class of movable dot, with separating axis collision detection, from
// http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php

class Character{
public:
  //Initializes the variables
  Character(Sprite *sprite);

  //Moves the dot and checks collision against tiles
  //void move(Tile *tiles[]);
  void move(TiledMap &map);

  void render(SDL_Renderer *renderer, SDL_Rect &camera);

  int getPosX() const {
    return mPos.x;
  }

  int getPosY() const {
     return mPos.y;
  }

protected:
  Sprite sprite;

  //Current and previous position of character
  vec mPos, mOldPos;

  // number of pixels for a tile (assume square, W = H)
  int mTileSize;
};

#endif
