#ifndef TILEDMAP_H
#define TILEDMAP_H

#include <SDL2/SDL.h>
#include <json/json.h>
#include <string>
#include <vector>
#include "texture.h"


class TiledMap{
public:

  TiledMap(const std::string &str, SDL_Renderer *rend);

  //~TiledMap();

  int getWidth() const {
    return mWidth;
  }

  int getHeight() const {
    return mHeight;
  };

  void render(SDL_Renderer *rend, SDL_Rect &camera);

  bool isCollision(SDL_Point pos);

private:
  // Dimensions of entire level/map in tiles
  int mWidth;
  int mHeight;

  Json::Value mRoot;

  struct clip{
    SDL_Rect rect;
    std::string tileSetName;
  };

  // Each element holds the clip to a (single) tileset
  //std::vector<SDL_Rect> mClips;
  std::vector<clip> mClips;

  // Dimensions of one tile in pixels
  int mTileWidth;
  int mTileHeight;

  std::map<std::string, Texture> mTileTextures;

  // Either orthogonal or isometric (diamond), staggered
  std::string mOrientation;

  // Auto-increments for each placed object
  int mNextObjectId;

  // Layer with this name, will not be rendered, but the tile
  // coorinates used for collision detection
  std::string mCollisionLayerName = "collisions";
};

#endif
