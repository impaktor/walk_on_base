#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include "texture.h"

// Would be good to keep collision detection and position separate,
// but for now, same.
// TODO. Fix this, since floor should not be "collidable"
// http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php


//The tile
class Tile{
public: //Initializes position and type
  Tile(int x, int y, int tileType, Texture *tileTexture);

  static const int TILE_WIDTH = 80;
  static const int TILE_HEIGHT = 80;

  //Shows the tile
  void render(SDL_Renderer *renderer, SDL_Rect& camera, SDL_Rect tiles[]);

  int getType() const {
    return mType;
  }

  // Get collision box
  SDL_Rect getBox() const {
    return mBox;
  }

private:
  //The attributes of the tile
  SDL_Rect mBox;

  Texture *mTileTexture;

  //The tile type
  int mType;
};


#endif
