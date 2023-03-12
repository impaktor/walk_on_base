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
  Dot(Sprite *sprite, const SDL_Rect& start_pos, TiledMap *map);
  Dot(Sprite *sprite, vec start_pos, TiledMap* map);

  //Takes key presses and adjusts the dot's velocity
  void handleEvent(SDL_Event &event);

  void update();

private:

  // for debug printouts
  bool mEvent;
};

#endif
