#ifndef DOT_H
#define DOT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cassert>
#include "character.h"
#include "tiledmap.h"
#include "sprite.h"

// A class of movable dot, with separating axis collision detection, from
// http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php

class Dot: public Character{
public:
  Dot(Sprite *sprite, const SDL_Rect& start_pos);

  //Takes key presses and adjusts the dot's velocity
  void handleEvent(SDL_Event &event);

  //Centers the camera over the dot
  void setCamera(SDL_Rect &camera, const TiledMap &level);

  // Why do I need to include this?
  void move(TiledMap &map);

private:

  // for debug printouts
  bool mEvent;
};

#endif
