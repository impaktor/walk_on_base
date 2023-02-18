#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "texture.h"

// handle sprite sheets

class Sprite{
public:
  // width and height of a single sprite on the sheet
  Sprite(Texture *mTexture, int clip_w, int clip_h);

  Sprite* setTransparency(Uint8 r, Uint8 g, Uint8 b);

  //Shows the sprite on the screen, (rendering can be relative the camera)
  void render(SDL_Renderer *renderer, int x, int y);

  // Assume sprite sheet character is in first column
  // with rows matching the following directions:
  enum direction {down=0, left, right, up};

  // facing direction of sprite
  direction facing;

private:
  Texture *mTexture;

  // only store 4 clips (for now, one for each direction)
  SDL_Rect mClips[4];

  // dimensions of one sprite on the sprite sheet
  int clipW, clipH;
};


#endif
