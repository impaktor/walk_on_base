#ifndef NPC_H
#define NPC_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdlib>
#include "character.h"
#include "astar/AStar.h"
#include "vector2.h"
#include "sprite.h"
#include "statemachine.h"


class NPC: public Character{
public:
  NPC(Sprite *sprite, TiledMap *map);

  ~NPC();

  float bladder;

  void update();
  StateMachine<NPC>* GetFSM() const;

  void SetPath(vec);
  void move();
  AStar::CoordinateList mPath;

private:
  // Manage AI / states
  StateMachine<NPC>* m_pStateMachine;

  int random_int(int max);

};

#endif
