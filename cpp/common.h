#ifndef COMMON_H
#define COMMON_H

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

// extern const int TOTAL_TILES;

// extern const int TILE_CENTER;
// extern const int TILE_TOPLEFT;

inline bool checkCollision(const SDL_Rect &a, const SDL_Rect &b){
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  //Calculate the sides of rect B
  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  //Do spearate axis test, i.e. check if any
  //of the sides from A are outside of B
  if(bottomA <= topB)
    return false;
  if(topA >= bottomB)
    return false;
  if(rightA <= leftB)
    return false;
  if(leftA >= rightB)
    return false;

  //If none of the sides from A are outside B
  return true;
}

#endif
