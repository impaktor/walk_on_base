#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include "texture.h"
#include "character.h"


class NPC: public Character{
public:
  NPC(Texture *texture, int level_height, int level_width);

private:
  int mTargetPosX, mTargetPosY;
  int speed;

  int random_int(int max);
  void set_new_target();

};

#endif
