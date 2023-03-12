#include "texture.h"
#include <stdio.h>
#include <iostream>
#include <sstream>

SDL_Color UintToColor(Uint32 color)
{
   SDL_Color tempcol;
   tempcol.r = (color >> 16) & 0xFF;
   tempcol.g = (color >> 8) & 0xFF;
   tempcol.b = (color >> 0) & 0xFF;
   tempcol.a = 255;
   return tempcol;
}

Uint32 Color2Uint(Uint8 r, Uint8 g, Uint8 b)
{
   return (Uint32)((r << 16) + (g << 8) + (b << 0));
}

SDL_Color Hex2Color(std::string hex){

  if (hex[0] == '#')
    hex.erase(0, 1);

  Uint32 dec;
  std::stringstream ss;
  ss << std::hex << hex;
  ss >> dec;

  return UintToColor(dec);
}


Texture::Texture(){
  //Initialize
  mTexture = nullptr;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture(){
  //Deallocate
  free();
}

SDL_Texture* Texture::makeTexture(SDL_Surface* loadedSurface, SDL_Renderer *renderer, Uint32 color){
  //The final texture
  SDL_Texture* newTexture = nullptr;

  //Apply transparency
  SDL_SetColorKey(loadedSurface, SDL_TRUE, color);

  //Create texture from surface pixels
  newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
  if(newTexture == nullptr)
    printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
  else{
    //Get image dimensions
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
  }

  //Get rid of old loaded surface
  SDL_FreeSurface(loadedSurface);
  return newTexture;
}


bool Texture::loadFromFile(const std::string &path, SDL_Renderer *renderer){
  //Get rid of preexisting texture
  free();

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == nullptr)
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  else{
    // Cyan (0,ff,ff) is the transparent color:
    // Magenta ff,00,ff) is the transparent color:
    Uint32 color = SDL_MapRGB(loadedSurface->format, 0xFF, 0, 0xFF);
    SDL_Texture* newTexture = makeTexture(loadedSurface, renderer, color);
    mTexture = newTexture;
  }

  //Return success
  return mTexture != nullptr;
}


bool Texture::loadFromFile(const std::string &path, SDL_Renderer *renderer, std::string hex){
  //Get rid of preexisting texture
  free();

  //Load image at specified path
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if(loadedSurface == nullptr)
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  else{
    SDL_Color color = Hex2Color(hex);

    Uint32 pixel_color = SDL_MapRGB(loadedSurface->format, color.r, color.g, color.b);

    SDL_Texture* newTexture = makeTexture(loadedSurface, renderer, pixel_color);
    mTexture = newTexture;
  }

  //Return success
  return mTexture != nullptr;
}


void Texture::free(){
  //Free texture if it exists
  if(mTexture != nullptr){
    SDL_DestroyTexture(mTexture);
    mTexture = nullptr;
    mWidth = 0;
    mHeight = 0;
  }
}

void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue){
  //Modulate texture rgb
  SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Texture::setBlendMode(SDL_BlendMode blending){
  //Set blending function
  SDL_SetTextureBlendMode(mTexture, blending);
}

void Texture::setAlpha(Uint8 alpha){
  //Modulate texture alpha
  SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Texture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect* src_rect, double angle,
                     SDL_Point* center, SDL_RendererFlip flip){
  //Set rendering space and render to screen
  SDL_Rect dst_rect = {x, y, mWidth, mHeight};

  //Set clip rendering dimensions
  if(src_rect != nullptr){
    dst_rect.w = src_rect->w;
    dst_rect.h = src_rect->h;
  }

  //Render to screen
  SDL_RenderCopyEx(renderer, mTexture, src_rect,
                   &dst_rect, angle, center, flip);
}
