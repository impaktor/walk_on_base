#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "texture.h"
#include "tiledmap.h"

// A class of movable dot, with separating axis collision detection, from
// http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php

class Dot{
public:
  //Initializes the variables
  Dot(Texture* texture, int level_height, int level_width);

  //Takes key presses and adjusts the dot's velocity
  void handleEvent(SDL_Event &event);

  //Moves the dot and checks collision against tiles
  //void move(Tile *tiles[]);
  void move(TiledMap &map);

  //Shows the dot on the screen, (rendering can be relative the camera)
  void render(SDL_Renderer *renderer, SDL_Rect &camera);

  //Centers the camera over the dot
  void setCamera(SDL_Rect &camera);

  int getPosX() const {
    return mPosX;
  }

  int getPosY() const {
     return mPosY;
  }

private:
  //Collision box for dot
  SDL_Rect mCollisionBox;

  //The X and Y offsets of the dot
  int mPosX, mPosY;

  // in pixels, total map size:
  int mLevelHeight;
  int mLevelWidth;

  int mOldPosX, mOldPosY;

  // for debug printouts
  bool mEvent;

  // number of pixels for a tile (assume square, W = H)
  int mTileSize;

  //Specify a default clip to start with
  //I.e. default part/color of the sprite to show
  int mUseClip;

  SDL_Rect mClips[4];

  Texture *mTexture;
};

#endif
