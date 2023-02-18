#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "cstdlib"

// Load an image to a SDL_Texture, e.g. a set of sprites or tileset or single image

//Texture wrapper class
class Texture{
public:
  //Initializes variables
  Texture();

  //Deallocates memory
  ~Texture();

  //Loads image at specified path
  bool loadFromFile(const std::string &path, SDL_Renderer *renderer);
  bool loadFromFile(const std::string &path, SDL_Renderer *renderer, Uint8 *rgb);

  //Deallocates texture
  void free();

  //Set color modulation
  void setColor(Uint8 red, Uint8 green, Uint8 blue);

  //Set blending
  void setBlendMode(SDL_BlendMode blending);

  //Set alpha modulation
  void setAlpha(Uint8 alpha);

  //Renders texture at given point, and possibly a subset of the texture
  //(e.g. for rendering a single tile from a tile set)
  void render(SDL_Renderer *renderer, int x, int y, SDL_Rect* clip = nullptr,
              double angle = 0.0, SDL_Point* center = nullptr,
              SDL_RendererFlip flip = SDL_FLIP_NONE);

  //Gets image full dimensions
  int getWidth() const {
    return mWidth;
  }

  int getHeight() const{
    return mHeight;
  }

private:
  SDL_Texture* makeTexture(SDL_Surface* loadedSurface, SDL_Renderer *renderer, Uint32 color);

  //The actual hardware texture
  SDL_Texture* mTexture;

  //Full image dimensions
  int mWidth;
  int mHeight;
};

#endif
