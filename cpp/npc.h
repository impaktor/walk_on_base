#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include "character.h"
#include "vector2.h"
#include "sprite.h"


class NPC: public Character{
public:
  NPC(Sprite *sprite);

private:
  vec mTargetPos;
  int speed;

  int random_int(int max);
  void set_new_target();

};

#endif
