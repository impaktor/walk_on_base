#ifndef CAMERA_H
#define CAMERA_H

#include "vector2.h"
#include "tiledmap.h"
#include <SDL2/SDL_rect.h>

// For scrolling the map

class Camera{
public:
  Camera(SDL_Rect rect, const TiledMap *map);

  void set(vec pos);

  SDL_Rect get() const{
    return camera;
  }

  // upper left corner
  vec getpos() const{
    return vec{camera.x, camera.y};
  }

private:
  SDL_Rect camera;

  const TiledMap *m_map;

  int m_x_min_screen;
  int m_x_max_screen;
  int m_y_min_screen;
  int m_y_max_screen;
};

#endif
