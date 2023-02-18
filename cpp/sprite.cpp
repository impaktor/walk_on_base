#include <cassert>
#include "sprite.h"
#include "texture.h"


Sprite::Sprite(Texture *texture, int clip_w, int clip_h):
  mTexture{texture}, clipW{clip_w}, clipH(clip_h)
{
  assert(mTexture != nullptr);

  facing = left;

  //Setup the clips for our image
  // just assume we take first four rows in first column
  int k = 0;
  for(int j = 0; j < mTexture->getHeight(); j=j+clipH){
    mClips[k].x = 0;
    mClips[k].y = j;
    mClips[k].w = clipW;
    mClips[k].h = clipH;
    k++;
    if (k==4)
      break;
  }
}

void Sprite::render(SDL_Renderer *renderer, int x, int y){
  //Show the object, relative the camera
  mTexture->render(renderer, x, y, &mClips[facing]);
}
