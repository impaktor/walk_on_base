#include <json/json.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <string>
#include "tiledmap.h"


TiledMap::TiledMap(const std::string &name, SDL_Renderer *renderer){
  std::cout << "tiled map name\t" << name << std::endl;
  std::ifstream ifile(name, std::ifstream::in);
  ifile >> mRoot;

  // Map dimensions in units of tiles
  mWidth = mRoot["width"].asInt();
  mHeight = mRoot["height"].asInt();

  std::cout << "tiled map dim: " << mWidth << "x" << mHeight << " tiles" << std::endl;

  // dimension of one tile in pixels
  mTileWidth = mRoot["tilewidth"].asInt();
  mTileHeight = mRoot["tileheight"].asInt();

  // (Default to orthographic, if field not found)
  mOrientation = mRoot.get("orientation", "orthographic").asString();


  for(size_t i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][(int)i];
    std::cout << "\timage " << tileset["image"].asString() << std::endl;
    std::cout << "\tcolumns " << tileset["columns"].asInt() << std::endl;
    std::cout << "\tfirstgid " << tileset["firstgid"].asInt() << std::endl;
    std::cout << "\timageheight " << tileset["imageheight"].asInt() << std::endl;
    std::cout << "\timagewidth " << tileset["imagewidth"].asInt() << std::endl;
    std::cout << "\ttileHeight " << tileset["tileheight"].asInt() << std::endl;
    std::cout << "\ttileWidth " << tileset["tilewidth"].asInt() << "\n" << std::endl;
  }


  // Populate mClips vector, where each element is a unique "gid" id
  // from tile. (gid is the index of the tile on the map, starts
  // upper left corner of map, there are mWidth x mHeight gids (as
  // many as tiles on map).
  mClips.clear();
  for(size_t i = 0; i < mRoot["tilesets"].size(); ++i){
    Json::Value tileset = mRoot["tilesets"][(int)i];
    int tileCount = tileset["tilecount"].asInt();
    int firstGid = tileset["firstgid"].asInt();

    int tileH = tileset["tileheight"].asInt();
    int tileW = tileset["tilewidth"].asInt();

    int columns = tileset["columns"].asInt();

    // this feels a bit strange, to both index the map on filename,
    // and send it as input arg...
    std::string tileFileName = tileset["image"].asString();
    mTileTextures[tileFileName] = Texture();
    mTileTextures[tileFileName].loadFromFile(tileFileName, renderer);

    clip tmp;
    tmp.rect = SDL_Rect({0,0,0,0});
    tmp.tileSetName = tileset["image"].asString();

    mClips.resize(mClips.size() + tileCount, tmp);

    int x = 0;
    int y = 0;
    int col = 0;
    for(int j = firstGid -1; j < tileCount + firstGid -1; ++j){

      //SDL_Rect tmp = {x, y, tileH, tileW};
      mClips[j].rect = {x, y, tileW, tileH};
      x += tileW;
      col++;
      if(col == columns){
        col = 0;
        x = 0;
        y += tileH;
      }
    }
  }
}


void TiledMap::render(SDL_Renderer *renderer, SDL_Rect &camera){

  // HORRIBLE! Assumes one single tile set
  // No, assumes tiles in all tilesets have same size, e.g. 32x32
  Json::Value tileset = mRoot["tilesets"][0];
  int tileH = tileset["tileheight"].asInt();
  int tileW = tileset["tilewidth"].asInt();

  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    int indexi = i;
    Json::Value layer = mRoot["layers"][indexi];
    std::string layername = layer["name"].asString();

    // Don't render collision layer (typically we use a red tile for this)
    if(layername == mCollisionLayerName){
      continue;
    }

    int x = 0;
    int y = 0;
    for(size_t j = 0; j < layer["data"].size(); ++j){
      int tileId = layer["data"][int(j)].asInt();   // "gid coordinate"

      if(tileId > 0)
        mTileTextures[mClips[tileId - 1].tileSetName].render(renderer, x - camera.x, y - camera.y, &mClips[tileId - 1].rect);

      x += tileW;
      if((j + 1) % mWidth == 0){
        y += tileH;
        x = 0;
      }
    }
  }
}


bool TiledMap::isCollision(int x, int y){

  // If we go outside the level, count as "collision"
  if (x < 0 || x > mTileWidth * mWidth)
    return true;
  if (y < 0 || y > mTileHeight * mHeight)
    return true;

  // loop through all layers to find collision layer
  for(size_t i = 0; i < mRoot["layers"].size(); ++i){
    Json::Value layer = mRoot["layers"][int(i)];
    std::string layername = layer["name"].asString();

    if(layername != mCollisionLayerName){
      continue;
    }

    // convert 2D coordinates to 1D (assuming we can only move in
    // steps of full tiles)
    int j = float(x)/mTileWidth + float(y)/mTileHeight * mWidth;
    int tileId = layer["data"][j].asInt();   // "gid coordinate"

    // if there is a tile on this coordinate, it's a collision
    return tileId > 0;
  }
  return false;
}
