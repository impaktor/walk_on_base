#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

//Texture wrapper class
class Texture{
public:
  //Initializes variables
  Texture();

  //Deallocates memory
  ~Texture();

  //Loads image at specified path
  bool loadFromFile(const std::string &path, SDL_Renderer *renderer);

  //Deallocates texture
  void free();

  //Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  //Set blending
  void setBlendMode(SDL_BlendMode blending);

  //Set alpha modulation
  void setAlpha(Uint8 alpha);

  //Renders texture at given point
  void render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip = nullptr,
              double angle = 0.0, SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  //Gets image dimensions
  int getWidth() const {
    return mWidth;
  }

  int getHeight() const{
    return mHeight;
  }

private:
  //The actual hardware texture
  SDL_Texture* mTexture;

  //Image dimensions
  int mWidth;
  int mHeight;
};

#endif
