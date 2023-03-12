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
  Character(Sprite *sprite, TiledMap* map);

  //Checks collision against tiles & sprite facing direction
  void update();

  void render(SDL_Renderer *renderer, const SDL_Rect &camera);

  vec getPos() const {
     return mPos;
  }

  TiledMap* map;

protected:
  Sprite sprite;

  //Current and previous position of character, in map coordinates
  vec mPos, mOldPos;

  // Store time for last physics update
  Uint32 mLastUpdate;

  // (Inverse) movement speed of character (milliseconds / move)
  Uint32 mInvSpeed;

private:
  // each character have a unique ID
  static int ID;
  int thisID;
};

#endif
